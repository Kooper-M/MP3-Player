#pragma once
#include <filesystem>
#include <string>
#include <fstream> 
#include <chrono>
#include <iostream>

struct Song {
    std::filesystem::path path;
    std::string file_path_as_string;
    std::string name;
    //move used to not have to call copy constructor. Move marks p as movable and then fs::path move constructor transfers the ownership
    explicit Song(std::filesystem::path p) : path(std::move(p)), file_path_as_string(path.string()), name(path.stem().string()) {}

    void print() const {
        std::cout << "Song Title: " << name << " Song Link: " << file_path_as_string << "\n";
    }
};