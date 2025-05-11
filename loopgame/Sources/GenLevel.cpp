#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include "../Headers/Tileset.hpp"

std::string line;
std::regex block_regex(R"(block_(\d+)=(.*))");
std::regex x_regex(R"(block_(\d+)_x=(\d+))");
std::regex y_regex(R"(block_(\d+)_y=(\d+))");
std::smatch match;

std::string block_names;
std::vector<float> tile_x;
std::vector<float> tile_y;
std::vector<float> block_x;
std::vector<float> block_y;

void GenLevel(){
    std::ifstream inputFile("Levels/level_3.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Không thể mở file data.txt" << std::endl;
        return ;
    }

    while (std::getline(inputFile, line)) {
        if (std::regex_match(line, match, block_regex)) {
            block_names = match[2].str();
            if (block_names == "Terrain 001")
            {
                tile_x.push_back(0.0f);
                tile_y.push_back(0.0f);
            }
            else if (block_names == "Terrain 002")
            {
                tile_x.push_back(32.0f);
                tile_y.push_back(0.0f);
            }
            else if (block_names == "Terrain 003")
            {
                tile_x.push_back(64.0f);
                tile_y.push_back(0.0f);
            }
            else if (block_names == "Terrain 004")
            {
                tile_x.push_back(0.0f);
                tile_y.push_back(32.0f);
            }
            else if (block_names == "Terrain 005")
            {
                tile_x.push_back(32.0f);
                tile_y.push_back(32.0f);
            }
            else if (block_names == "Terrain 006")
            {
                tile_x.push_back(64.0f);
                tile_y.push_back(32.0f);
            }
            else if (block_names == "Block 002")
            {
                tile_x.push_back(0.0f);
                tile_y.push_back(64.0f);
            }
        }
        else if (std::regex_match(line, match, x_regex)) {
            block_x.push_back(std::stof(match[2].str()));
        }
        else if (std::regex_match(line, match, y_regex))
        {
            block_y.push_back(std::stof(match[2].str()));
        }
    }
    for (int i = 0; i < block_x.size(); ++i)
    {
        addObstacleBlock(block_x[i], block_y[i], tile_x[i], tile_y[i]);
    }
    inputFile.close();
}