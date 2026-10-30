#include "moving_object.hpp"

namespace rva {

MovingObject::MovingObject(
	float init_x, float init_y, 
	float init_width, float init_height, char init_kind
)
	: GameObject(init_x, init_y, init_width, init_height, init_kind) {
	vertical_speed = 0;
	horizontal_speed = 0.2f;
	is_flying = false;
}

MovingObject::~MovingObject() {}

void MovingObject::move(
	GameObject* background_elem, 
	int background_elems_count
) {
	is_flying = true;
	vertical_speed += 0.05f;
	move_by(0, vertical_speed);

	for (int i = 0; i < background_elems_count; i++) {
		if (check_collision(background_elem[i])) {
			if (vertical_speed > 0) {
				y = background_elem[i].get_y() - height;
				is_flying = false;
			} else if (vertical_speed < 0) {
				y = background_elem[i].get_y() + 
				    background_elem[i].get_height();
			}
			vertical_speed = 0;
			break;
		}
	}
}

float MovingObject::get_vertical_speed() const {
	return vertical_speed;
}

void MovingObject::set_vertical_speed(float speed) {
	vertical_speed = speed;
}

float MovingObject::get_horizontal_speed() const {
	return horizontal_speed;
}

void MovingObject::set_horizontal_speed(float speed) {
	horizontal_speed = speed;
}

bool MovingObject::get_is_flying() const {
	return is_flying;
}

void MovingObject::set_is_flying(bool flying) {
	is_flying = flying;
}

}