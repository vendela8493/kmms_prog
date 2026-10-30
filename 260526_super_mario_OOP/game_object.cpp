#include "game_object.hpp"

namespace rva {

GameObject::GameObject(
	float init_x, float init_y,
	float init_width, float init_height, char init_kind
) {
	x = init_x;
	y = init_y;
	width = init_width;
	height = init_height;
	kind = init_kind;
}

float GameObject::get_x() const {
	return x;
}

float GameObject::get_y() const {
	return y;
}

float GameObject::get_width() const {
	return width;
}

float GameObject::get_height() const {
	return height;
}

char GameObject::get_kind() const {
	return kind;
}

void GameObject::set_pos(float new_x, float new_y) {
	x = new_x;
	y = new_y;
}

void GameObject::move_by(float dx, float dy) {
	x += dx;
	y += dy;
}

void GameObject::set_kind(char new_kind) {
	kind = new_kind;
}

bool GameObject::check_collision(const GameObject& other) const {
	return ((x + width) > other.x) && (x < (other.x + other.width)) &&
		   ((y + height) > other.y) && (y < (other.y + other.height));
}

}