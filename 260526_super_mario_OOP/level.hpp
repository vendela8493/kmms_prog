#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "game_object.hpp"
#include "section.hpp"

namespace rva {

class Level {
	private:
		GameObject* background_elem;
		int background_elems_count;
		int current_level;
		int max_level;

	public:
		Level(int init_level = 1, int init_max = 3);
		~Level();

		void clear();
		void add_background_elem(const GameObject& elem);
		void next_level();

		int get_current_level() const;
		int get_max_level() const;

		void load(int level_num);
		
		GameObject* get_elements();
		int get_count() const;
		void hit_block(int index);
};

}

#endif // LEVEL_HPP