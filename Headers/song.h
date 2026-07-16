#pragma once
#include <filesystem>
#include <string>


struct Song {
    std::filesystem::path path;
    std::string file_path_as_string;
    std::string name;

    Song(std::filesystem::path p) {
        path = p;
        file_path_as_string = p.string();
        auto temp = p.filename().string();
        name = temp.erase(temp.rfind('.'));
    };

    void print() {
        std::cout << "Song Title: " << name << " Song Link: " << file_path_as_string << std::endl;
    }
};