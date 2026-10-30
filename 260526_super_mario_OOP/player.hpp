#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "game_object.hpp"
#include "moving_object.hpp"
#include "section.hpp"

namespace rva {

class Player : public MovingObject {
	public:
		Player(
			float init_x = 0, float init_y = 0,
			float init_width = 3, float init_height = 3
		);

		void jump();

		char move_and_check(
			GameObject* background_elem, int background_elems_count,
			float& hit_x, float& hit_y, int& hit_index
		);

		bool is_stomping(const GameObject& enemy) const;
};

}

#endif