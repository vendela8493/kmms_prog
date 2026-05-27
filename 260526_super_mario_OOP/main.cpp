#include <iostream>
#include <windows.h>
#include <cmath>

class GameObject
{
	public:
		float x, y;
		float width, height;
		char kind;

		GameObject()
		{
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			kind = ' ';
		}

		void set_object_pos(float obj_pos_x, float obj_pos_y)
		{
			x = obj_pos_x;
			y = obj_pos_y;
		}

		void init_object(float init_x, float init_y, float init_width, float init_height, char init_kind)
		{
			set_object_pos(init_x, init_y);
			width = init_width;
			height = init_height;
			kind = init_kind;
		}
		
		bool check_collision(const GameObject& obj) const
		{
			return (x + width) > obj.x && x < (obj.x + obj.width) &&
			(y + height) > obj.y && y < (obj.y + obj.height);
		}
};

class MovingObject : public GameObject
{
	public:
		float vertical_speed = 0;
		float horizontal_speed = 0.2;
		bool is_flying = false;

		void init_object(float init_x, float init_y, float init_width, float init_height, char init_kind)
		{
			GameObject::init_object(init_x, init_y, init_width, init_height, init_kind);
			vertical_speed = 0;
		}

		void vertical_move_object(const GameObject& obj)
		{
			vertical_speed += 0.05;
			GameObject::set_object_pos(x, y + vertical_speed);

			if (check_collision(obj))
			{
				y -= vertical_speed;
				vertical_speed = 0;
			}
		}
};

class Player : public MovingObject
{
public:
    void jump()
    {
        if (!is_flying && GetKeyState(VK_SPACE) < 0)
            vertical_speed = -1;
    }
};

class GameMap
	{
	private:
		static const int MAP_HEIGHT = 25;
		static const int MAP_WIDTH = 80;
		char map[MAP_HEIGHT][MAP_WIDTH + 1];
		
		bool object_within_map(int x, int y) const
		{
			return x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT;
		}
		
	public:
		void clear_map()
		{
			for (int i = 0; i < MAP_WIDTH; i++)
				map[0][i] = ' ';
			map[0][MAP_WIDTH] = '\0';
			
			for (int j = 1; j < MAP_HEIGHT; j++)
				for (int k = 0; k < MAP_WIDTH + 1; k++)
					map[j][k] = map[0][k];
		}

		void show_map()
		{
			COORD coord = { 0, 0 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		
			map[MAP_HEIGHT - 1][MAP_WIDTH - 1] = '\0';
			
			for (int j = 0; j < MAP_HEIGHT; j++)
				std::cout << map[j] << '\n';
		}
		
		void add_object_on_map(const GameObject& obj)
		{
			int int_x = (int)round(obj.x);
			int int_y = (int)round(obj.y);
			int int_width = (int)round(obj.width);
			int int_height = (int)round(obj.height);

			for (int i = int_x; i < (int_x + int_width); i++)
			{
				for (int j = int_y; j < (int_y + int_height); j++)
				{
					if (object_within_map(i, j))
					{
						map[j][i] = obj.kind;
					}
				}
			}
		}
		
		void scroll_map(GameObject& obj, float dx)
		{
			obj.x += dx;
		}

		void forward(GameObject& obj)
		{
			if (GetKeyState('A') < 0) scroll_map(obj, 1);
		}

		void back(GameObject& obj)
		{
			if (GetKeyState('D') < 0) scroll_map(obj, -1);
		}
};

int main()
{
	GameMap game_map;
	Player player;
    player.init_object(39, 10, 3, 3, '@');
    GameObject back_ground_elem;
    back_ground_elem.init_object(20, 13, 40, 5, '#');
	
	do
	{
		game_map.clear_map();
		
		player.jump();
		game_map.forward(back_ground_elem);
		game_map.back(back_ground_elem);
		
		player.vertical_move_object(back_ground_elem);
		
		game_map.add_object_on_map(back_ground_elem);
		game_map.add_object_on_map(player);
		game_map.show_map();
		
		Sleep(10);
	}
	while (GetKeyState(VK_ESCAPE) >= 0);
	
    return 0;
}