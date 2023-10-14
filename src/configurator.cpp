#include "../include/configurator.h"

configurator::configurator(std::string configFilePath){
    configPath = configFilePath;
    if(fs::is_regular_file(configFilePath)){
        std::ifstream fileStream(configFilePath);
        fileStream >> config;
        fileStream.close();
        return;
    }

    config["images"] = json::array();
    saveConfig();
}

void configurator::addImageToConfig(image *img){
    if(isImageExistInConfig(img)){
        std::cout << "Image '" << img->fullPath << "' already exist in JSON." << std::endl;
        return;
    }

    json imageJson;
    imageJson["name"] = img->name;
    imageJson["fullPath"] = img->fullPath;
    imageJson["size"] = img->size;

    config["images"].push_back(imageJson);
    saveConfig();
}

void configurator::removeImageFromConfig(image *img){
    if(isImageExistInConfig(img)){
        std::cout << "Image '" << img->fullPath << "' is not exist in the JSON." << std::endl;
        return;
    }

    for (auto it = config["images"].begin(); it != config["images"].end(); ++it) {
        if (it->at("fullPath") == img->fullPath) {
            config["images"].erase(it);
            saveConfig();
            return;
        }
    }
    std::cout << "Key '" << img->fullPath << "' not found in the JSON." << std::endl;
}

json configurator::getConfig(){
    return config;
}

bool configurator::isImageExistInConfig(image *img){
    std::ifstream file("config.json");
    json jsonData;

    if (file.is_open()) {
        try {
            file >> jsonData;
        } catch (const std::exception& e) {
            std::cerr << "Error reading JSON: " << e.what() << std::endl;
            return 1;
        }

        return jsonData.contains(img->fullPath) ? true : false;
    }
}

void configurator::saveConfig() {
    std::ofstream file(configPath);
    file << config.dump(4);  
    file.close();
}