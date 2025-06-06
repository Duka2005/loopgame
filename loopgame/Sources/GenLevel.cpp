﻿#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Headers/GameClass.hpp"
#include "../Headers/Tileset.hpp"
#include "../Headers/Level.hpp"
#include "../Headers/Enemy.hpp"

#include <ctre.hpp>

std::string line;
//std::regex block_regex(R"(block_(\d+)=(.*))");
//std::regex x_regex(R"(block_(\d+)_x=(\d+))");
//std::regex y_regex(R"(block_(\d+)_y=(\d+))");
//std::smatch match;

std::string block_names;
std::vector<float> tile_x;
std::vector<float> tile_y;
std::vector<float> block_x;
std::vector<float> block_y;

std::vector<std::string> enemy_name;
std::vector<float> enemypos_x;
std::vector<float> enemypos_y;

//generate level map function
void GenLevel(Level& lvl, std::string level, int position) {
    std::ifstream inputFile(level);
    if (!inputFile.is_open()) {
        std::cerr << "can't open file" << std::endl;
        return;
    }
    lvl.pos = position;
    while (std::getline(inputFile, line)) {
        for (auto& match : ctre::search_all<"block_(\\d+)=(.*)">(line)) {
            block_names = match.get<2>().to_string();
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
            else if (block_names == "Pipe 001")
            {
                tile_x.push_back(96.0f);
                tile_y.push_back(0.0f);
            }
            else if (block_names == "Pipe 002")
            {
                tile_x.push_back(128.0f);
                tile_y.push_back(0.0f);
            }
            else if (block_names == "Pipe 003")
            {
                tile_x.push_back(96.0f);
                tile_y.push_back(32.0f);
            }
            else if (block_names == "Pipe 004")
            {
                tile_x.push_back(128.0f);
                tile_y.push_back(32.0f);
            }
        }
        for (auto& match : ctre::search_all<"block_(\\d+)_x=(\\d+)">(line)) {
            block_x.push_back(match.get<2>().to_number());
        }
        for (auto& match : ctre::search_all<"block_(\\d+)_y=(\\d+)">(line)) {
            block_y.push_back(match.get<2>().to_number());
        }

        for (auto& match : ctre::search_all<"npc_(\\d+)=(.*)">(line)) {
            enemy_name.push_back(match.get<2>().to_string());
        }
        for (auto& match : ctre::search_all<"npc_(\\d+)_x=(.*)">(line)) {
            enemypos_x.push_back(match.get<2>().to_number());
        }
        for (auto& match : ctre::search_all<"npc_(\\d+)_y=(.*)">(line)) {
            enemypos_y.push_back(match.get<2>().to_number());
        }
    }
    for (int i = 0; i < block_x.size(); ++i)
    {
        addObstacleBlock(lvl, block_x[i], block_y[i], tile_x[i], tile_y[i]);
    }

    for (int i = 0; i < enemypos_x.size(); ++i)
    {
        if (enemy_name[i] == "Common 022") {
            AddPiranhaGround(lvl, enemypos_x[i], enemypos_y[i]);
        }
        else if (enemy_name[i] == "Common 001") {
            AddGoomba(lvl, enemypos_x[i], enemypos_y[i]);
        }
        else if (enemy_name[i] == "Common 016") {
            AddSpiny(lvl, enemypos_x[i], enemypos_y[i]);
        }
        if (enemy_name[i] == "Common 020") {
            AddPiranha(lvl, enemypos_x[i], enemypos_y[i]);
        }
    }

    block_x.clear();
    block_y.clear();
    tile_x.clear();
    tile_y.clear();
    enemy_name.clear();
    enemypos_x.clear();
    enemypos_y.clear();
    inputFile.close();
}