#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "game_object.hpp"
#include "moving_object.hpp"
#include "section.hpp"

namespace rva {

class Player;

class Enemy : public MovingObject {
	public:
		Enemy(
			float init_x = 0, float init_y = 0, 
			float init_width = 3, float init_height = 2, 
			char init_kind = ENEMY
		);

		void move(GameObject* background_elem, int background_elems_count);
		int handle_collision(const Player& player, int& score);
};

}

#endif // ENEMY_HPP