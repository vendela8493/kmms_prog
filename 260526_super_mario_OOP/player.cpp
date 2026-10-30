#include "player.hpp"

namespace rva {

Player::Player(float init_x, float init_y, float init_width, float init_height)
	: MovingObject(init_x, init_y, init_width, init_height, MARIO) {}

void Player::jump() {
	if (!is_flying) {
		vertical_speed = -1.0f;
	}
}

char Player::move_and_check(
	GameObject* background_elem, int background_elems_count,
	float& hit_x, float& hit_y, int& hit_index
) {
	is_flying = true;
	vertical_speed += 0.05f;
	move_by(0, vertical_speed);

	for (int i = 0; i < background_elems_count; i++) {
		if (check_collision(background_elem[i])) {
			char hit_kind = ' ';

			if (background_elem[i].get_kind() == FULL_BOX && vertical_speed < 0) {
				hit_kind = FULL_BOX;
				hit_x = background_elem[i].get_x();
				hit_y = background_elem[i].get_y();
				hit_index = i;
			} else if (background_elem[i].get_kind() == FINISH) {
				hit_kind = FINISH;
			}

			if (vertical_speed > 0) {
				y = background_elem[i].get_y() - height;
				is_flying = false;
			} else if (vertical_speed < 0) {
				y = background_elem[i].get_y() + background_elem[i].get_height();
			}

			vertical_speed = 0;
			return hit_kind;
		}
	}
	return ' ';
}

bool Player::is_stomping(const GameObject& enemy) const {
	return is_flying && (vertical_speed > 0) &&
		   ((y + height) <= (enemy.get_y() + enemy.get_height() * 0.5f + 1.0f));
}

}