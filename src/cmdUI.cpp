#include <iostream>
#include <vector>
#include "../include/imageManager.h"
#include "../include/wallpaperChanger.h"

//TODO: дописати ось цю менюшку

void showImages(std::vector<image> images)
{
    for (int i = 0; i < images.size(); i++){
        std::cout << '[' << i << ']' << " " << images[i].name << std::endl;
    }
}

void changeImage(imageManager* im){
    std::cout << "Enter image index: ";
    int choice;
    std::cin >> choice;
    if(choice < im->getImagesCount()){
        auto images = im->getImages();
        auto result = wallpaperChanger::setWallpaper(&images[choice]);

        if(result){
            std::cout << "Wallpaper successfully changed." << std::endl;
            return;
        }
        std::cerr << "An error occurred while setting new wallpaper." << std::endl;
        return;
    }
    std::cerr << "Index that you enter was outside of range." << std::endl;
}

void menu(imageManager* im){
    int choice;
    do {
        std::cout << "Test menu:" << std::endl;
        std::cout << "1. show images" << std::endl;
        std::cout << "2. set wallpaper" << std::endl;
        std::cout << "3. settings" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Choose option (1/2/3/4): ";
        
        std::cin >> choice;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                showImages(im->getImages());
                break;
            case 2:
                changeImage(im);
                break;
            case 3:
                std::cout << "Settings" << std::endl;
                break;
            case 4:
                std::cout << "Exit." << std::endl;
                break;
            default:
                std::cout << "Incorrect choose." << std::endl;
                break;
        }
    } while (choice != 4);
}