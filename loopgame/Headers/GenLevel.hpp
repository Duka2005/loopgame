#pragma once
#ifndef GENLEVEL_HPP
#define GENLEVEL_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include "GameClass.hpp"

extern std::string line;
extern std::regex block_regex;
extern std::regex x_regex;
extern std::regex y_regex;
extern std::smatch match;

extern std::string block_names;
extern std::vector<float> tile_x;
extern std::vector<float> tile_y;
extern std::vector<float> block_x;
extern std::vector<float> block_y;

extern void GenLevel(Level& lvl, std::string level, int position);

#endif