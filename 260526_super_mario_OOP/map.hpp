#ifndef MAP_HPP
#define MAP_HPP

#include "game_object.hpp"

namespace rva {

class Map {
	private:
		int width;
		int height;
		char** grid;

		bool is_within(int x, int y) const;

	public:
		Map(int w = 80, int h = 25);
		~Map();

		void clear();
		void add_object(const GameObject& obj);
		void show_score(int score);
		void render() const;

		int get_width() const;
		int get_height() const;
};

}

#endif