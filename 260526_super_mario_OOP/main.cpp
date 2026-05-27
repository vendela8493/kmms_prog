#include <iostream>
#include <windows.h>
#include <cmath>
#include <cstdlib>

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

		void vertical_move_object(GameObject* background_elems, int background_elems_count)
		{
			is_flying = true;
			vertical_speed += 0.05;
			GameObject::set_object_pos(x, y + vertical_speed);
			
			for (int i = 0; i < background_elems_count; i++)
			{
				if (check_collision(background_elems[i]))
				{
					if (vertical_speed > 0) 
					{
						is_flying = false;
					}
					y -= vertical_speed;
					vertical_speed = 0;
					break;
				}
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
		
		void scroll_map(float dx, Player& player, GameObject* background_elems, int background_elems_count)
		{
			player.x -= dx;
			for (int i = 0; i < background_elems_count; i++)
			{
				if (player.check_collision(background_elems[i]))
				{
					player.x += dx;
					return;
				}
			}
			player.x += dx;
			for (int i = 0; i < background_elems_count; i++)
				background_elems[i].x += dx;
		}

		void forward(Player& player, GameObject* background_elems, int background_elems_count)
		{
			if (GetKeyState('A') < 0) 
				scroll_map(1, player, background_elems, background_elems_count);
		}

		void back(Player& player, GameObject* background_elems, int background_elems_count)
		{
			if (GetKeyState('D') < 0) 
				scroll_map(-1, player, background_elems, background_elems_count);
		}
};

class Level
{
	public:
		void add_new_background_elem(GameObject*& background_elems, int& count, float x, float y, float w, float h, char k)
		{
			GameObject* temp = new GameObject[count + 1];
			for (int i = 0; i < count; i++)
				temp[i] = background_elems[i];
			
			delete[] background_elems;
			background_elems = temp;
			
			background_elems[count].init_object(x, y, w, h, k);
			count++;
		}

		void delete_background_elem(GameObject*& background_elems, int& count)
		{
			delete[] background_elems;
			background_elems = nullptr;
			count = 0;
		}
		
		void create_level(Player& player, GameObject*& background_elems, int& count)
		{
			system("color 9F");
			delete_background_elem(background_elems, count);

			player.init_object(39, 10, 3, 3, '@');

			add_new_background_elem(background_elems, count, 20, 20, 40, 5, '#');
			add_new_background_elem(background_elems, count, 30, 10, 5, 3, '?');
			add_new_background_elem(background_elems, count, 50, 10, 5, 3, '?');
			add_new_background_elem(background_elems, count, 60, 15, 40, 10, '#');
			add_new_background_elem(background_elems, count, 60, 5, 10, 3, '-');
			add_new_background_elem(background_elems, count, 70, 5, 5, 3, '?');
			add_new_background_elem(background_elems, count, 75, 5, 5, 3, '-');
			add_new_background_elem(background_elems, count, 80, 5, 5, 3, '?');
			add_new_background_elem(background_elems, count, 85, 5, 10, 3, '-');
			add_new_background_elem(background_elems, count, 100, 20, 20, 5, '#');
			add_new_background_elem(background_elems, count, 120, 15, 10, 10, '#');
			add_new_background_elem(background_elems, count, 150, 20, 40, 5, '#');
			add_new_background_elem(background_elems, count, 210, 15, 10, 10, '+');
		}
};
int main()
{
	GameMap game_map;
	Player player;
	
	GameObject* background_elems = nullptr;
	int background_elems_count = 0;
	Level level;
	
    level.create_level(player, background_elems, background_elems_count);
	
	do
	{
		game_map.clear_map();
		
		player.jump();
		game_map.forward(player, background_elems, background_elems_count);
		game_map.back(player, background_elems, background_elems_count);
		
		player.vertical_move_object(background_elems, background_elems_count);
		
		for (int i = 0; i < background_elems_count; i++)
        {
            game_map.add_object_on_map(background_elems[i]);
        }
		game_map.add_object_on_map(player);
		game_map.show_map();
		
		Sleep(10);
	}
	while (GetKeyState(VK_ESCAPE) >= 0);
	
	level.delete_background_elem(background_elems, background_elems_count);

    return 0;
}