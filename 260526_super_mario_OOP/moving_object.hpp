#ifndef MOVING_OBJECT_HPP
#define MOVING_OBJECT_HPP

#include "game_object.hpp"

namespace rva {

class MovingObject : public GameObject {
	protected:
		float vertical_speed, horizontal_speed;
		bool is_flying;

	public:
		MovingObject(
			float init_x = 0, float init_y = 0, 
			float init_width = 1, float init_height = 1, 
			char init_kind = ' '
		);

		virtual ~MovingObject();

		virtual void move(
			GameObject* background_elem, 
			int background_elems_count
		);

		float get_vertical_speed() const;
		void set_vertical_speed(float speed);
		float get_horizontal_speed() const;
		void set_horizontal_speed(float speed);
		bool get_is_flying() const;
		void set_is_flying(bool flying);
};

}

#endif // MOVING_OBJECT_HPP