#pragma once
#include <filesystem>
#include <string>
#include <fstream> 
#include <chrono>

struct Song {
    std::filesystem::path path;
    std::string file_path_as_string;
    std::string name;
    double music_length_seconds;

    explicit Song(std::filesystem::path p) : path(p), file_path_as_string(p.string()), name(p.stem().string()){
        auto file_size = std::filesystem::file_size(p); 

        std::ifstream file(file_path_as_string, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error opening file" << std::endl;
        } 
        file.seekg(16, std::ios::beg);

        int bitRate;

        file.read(reinterpret_cast<char*>(&bitRate), sizeof(bitRate));

        file.close();

        music_length_seconds = (static_cast<double>(file_size) * 8.0) / (bitRate * 1000.0);
        std::cout << music_length_seconds << std::endl;
    };

    void print() {
        std::cout << "Song Title: " << name << " Song Link: " << file_path_as_string << std::endl;
    }
};