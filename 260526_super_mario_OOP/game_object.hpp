#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

namespace rva {

class GameObject {
	protected:
		float x, y;
		float width, height;
		char kind;

	public:
		GameObject(
			float init_x = 0, float init_y = 0, float init_width = 1,
			float init_height = 1, char init_kind = ' '
		);

		float get_x() const;
		float get_y() const;
		float get_width() const;
		float get_height() const;
		char get_kind() const;

		void set_pos(float new_x, float new_y);
		void move_by(float dx, float dy);
		void set_kind(char new_kind);

		bool check_collision(const GameObject& other) const;
};

}

#endif