#include "level.hpp"

namespace rva {

Level::Level(int init_level, int init_max)
	: background_elem(nullptr), background_elems_count(0),
	  current_level(init_level), max_level(init_max) {}

Level::~Level() {
	clear();
}

void Level::clear() {
	delete[] background_elem;
	background_elem = nullptr;
	background_elems_count = 0;
}

void Level::add_background_elem(const GameObject& elem) {
	GameObject* temp = new GameObject[background_elems_count + 1];
	for (int i = 0; i < background_elems_count; i++) {
		temp[i] = background_elem[i];
	}
	temp[background_elems_count] = elem;
	delete[] background_elem;
	background_elem = temp;
	background_elems_count++;
}

void Level::next_level() {
	current_level++;
	if (current_level > max_level) {
		current_level = 1;
	}
}

int Level::get_current_level() const {
	return current_level;
}

int Level::get_max_level() const {
	return max_level;
}

void Level::load(int level_num) {
	current_level = level_num;
	clear();

	if (current_level == 1) {
		add_background_elem(GameObject(20, 20, 40, 5, PLATFORM));
		add_background_elem(GameObject(30, 10, 5, 3, FULL_BOX));
		add_background_elem(GameObject(50, 10, 5, 3, FULL_BOX));
		add_background_elem(GameObject(60, 15, 40, 10, PLATFORM));
		add_background_elem(GameObject(60, 5, 10, 3, BOX));
		add_background_elem(GameObject(70, 5, 5, 3, FULL_BOX));
		add_background_elem(GameObject(75, 5, 5, 3, BOX));
		add_background_elem(GameObject(80, 5, 5, 3, FULL_BOX));
		add_background_elem(GameObject(85, 5, 10, 3, BOX));
		add_background_elem(GameObject(100, 20, 20, 5, PLATFORM));
		add_background_elem(GameObject(120, 15, 10, 10, PLATFORM));
		add_background_elem(GameObject(150, 20, 40, 5, PLATFORM));
		add_background_elem(GameObject(210, 15, 10, 10, FINISH));
	} else if (current_level == 2) {
		add_background_elem(GameObject(20, 20, 40, 5, PLATFORM));
		add_background_elem(GameObject(60, 15, 10, 10, PLATFORM));
		add_background_elem(GameObject(80, 20, 20, 5, PLATFORM));
		add_background_elem(GameObject(120, 15, 10, 10, PLATFORM));
		add_background_elem(GameObject(150, 20, 40, 5, PLATFORM));
		add_background_elem(GameObject(210, 15, 10, 10, FINISH));
	} else if (current_level == 3) {
		add_background_elem(GameObject(20, 20, 40, 5, PLATFORM));
		add_background_elem(GameObject(80, 20, 15, 5, PLATFORM));
		add_background_elem(GameObject(120, 15, 15, 10, PLATFORM));
		add_background_elem(GameObject(160, 10, 15, 15, FINISH));
	}
}

GameObject* Level::get_elements() {
	return background_elem;
}

int Level::get_count() const {
	return background_elems_count;
}

void Level::hit_block(int index) {
	if (index >= 0 && index < background_elems_count) {
		if (background_elem[index].get_kind() == FULL_BOX) {
			background_elem[index].set_kind(BOX);
		}
	}
}

}