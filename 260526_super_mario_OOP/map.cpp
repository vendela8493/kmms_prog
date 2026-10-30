#include "map.hpp"

#include <cmath>
#include <iostream>
#include <sstream>

namespace rva {

Map::Map(int w, int h) : width(w), height(h) {
	grid = new char*[height];
	for (int i = 0; i < height; i++) {
		grid[i] = new char[width + 1];
	}
}

Map::~Map() {
	for (int i = 0; i < height; i++) {
		delete[] grid[i];
	}
	delete[] grid;
}

bool Map::is_within(int x, int y) const {
	return (x >= 0 && x < width && y >= 0 && y < height);
}

void Map::clear() {
	for (int i = 0; i < width; i++) {
		grid[0][i] = ' ';
	}
	grid[0][width] = '\0';

	for (int j = 1; j < height; j++) {
		for (int k = 0; k < width + 1; k++) {
			grid[j][k] = grid[0][k];
		}
	}
}

void Map::add_object(const GameObject& obj) {
	int int_x = (int)round(obj.get_x());
	int int_y = (int)round(obj.get_y());
	int int_width = (int)round(obj.get_width());
	int int_height = (int)round(obj.get_height());

	for (int i = int_x; i < (int_x + int_width); i++) {
		for (int j = int_y; j < (int_y + int_height); j++) {
			if (is_within(i, j)) {
				grid[j][i] = obj.get_kind();
			}
		}
	}
}

void Map::show_score(int score) {
	std::ostringstream ss;
	ss << "Score: " << score;
	std::string text = ss.str();
	for (size_t i = 0; i < text.length() && (i + 5) < (size_t)width; i++) {
		grid[1][i + 5] = text[i];
	}
}

void Map::render() const {
	grid[height - 1][width - 1] = '\0';
	for (int j = 0; j < height; j++) {
		std::cout << grid[j] << '\n';
	}
}

int Map::get_width() const {
	return width;
}

int Map::get_height() const {
	return height;
}

}