#include "enemy.hpp"
#include "player.hpp"

namespace rva {

Enemy::Enemy(
	float init_x, float init_y, 
	float init_width, float init_height, char init_kind
)
	: MovingObject(init_x, init_y, init_width, init_height, init_kind) {}

void Enemy::move(GameObject* background_elem, int background_elems_count) {
	MovingObject::move(background_elem, background_elems_count);

	move_by(horizontal_speed, 0);

	for (int i = 0; i < background_elems_count; i++) {
		if (check_collision(background_elem[i])) {
			move_by(-horizontal_speed, 0);
			horizontal_speed = -horizontal_speed;
			return;
		}
	}

	if (kind == ENEMY) {
		MovingObject tmp = *this;
		tmp.MovingObject::move(background_elem, background_elems_count);
		if (tmp.get_is_flying()) {
			move_by(-horizontal_speed, 0);
			horizontal_speed = -horizontal_speed;
		}
	}
}

int Enemy::handle_collision(const Player& player, int& score) {
	if (kind == ENEMY) {
		if (player.is_stomping(*this)) {
			score += 50;
			return 1;
		} else {
			return -1;
		}
	} else if (kind == COIN) {
		score += 100;
		return 1;
	}
	return 0;
}

}