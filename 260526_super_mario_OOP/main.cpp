#include <iostream>
#include <windows.h>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <string>

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

class Enemy : public MovingObject
{
	public:
		void horizontal_move_object(GameObject* background_elems, int background_elems_count)
		{
			x += horizontal_speed;

			for (int i = 0; i < background_elems_count; i++)
			{
				if (check_collision(background_elems[i]))
				{
					x -= horizontal_speed;
					horizontal_speed = -horizontal_speed;
					return;
				}
			}

			if (kind == 'o')
			{
				Enemy tmp = *this;
				tmp.vertical_move_object(background_elems, background_elems_count); 
				if (tmp.is_flying)
				{
					x -= horizontal_speed;
					horizontal_speed = -horizontal_speed;
				}
			}
		}
};

class Player;

class Level
{
	public:
		void add_new_background_elem(GameObject*& background_elems, int& background_elems_count, float x, float y, float width, float height, char kind)
		{
			GameObject* temp = new GameObject[background_elems_count + 1];
			for (int i = 0; i < background_elems_count; i++)
				temp[i] = background_elems[i];
			
			delete[] background_elems;
			background_elems = temp;
			
			background_elems[background_elems_count].init_object(x, y, width, height, kind);
			background_elems_count++;
		}

		void add_new_enemy(Enemy*& enemies, int& enemies_count, float x, float y, float width, float height, char kind)
        {
            Enemy* temp = new Enemy[enemies_count + 1];
            for (int i = 0; i < enemies_count; i++)
                temp[i] = enemies[i];
            
            delete[] enemies;
            enemies = temp;
            
            enemies[enemies_count].init_object(x, y, width, height, kind);
            enemies_count++;
        }
		
		void delete_background_elem(GameObject*& background_elems, int& background_elems_count)
		{
			delete[] background_elems;
			background_elems = nullptr;
			background_elems_count = 0;
		}
		
		void delete_enemies(Enemy*& enemies, int& enemies_count)
        {
            delete[] enemies;
            enemies = nullptr;
            enemies_count = 0;
        }

        void remove_enemy(int index, Enemy*& enemies, int& enemies_count)
        {
            enemies_count--;
            enemies[index] = enemies[enemies_count];
            
            if (enemies_count == 0)
            {
                delete[] enemies;
                enemies = nullptr;
            }
            else
            {
                Enemy* temp = new Enemy[enemies_count];
                for(int i=0; i < enemies_count; i++)
					temp[i] = enemies[i];
                delete[] enemies;
                enemies = temp;
            }
		}
		
		void create_level(Player& player, GameObject*& background_elems, int& background_elems_count, Enemy*& enemies, int& enemies_count, int& score);
};

class Player : public MovingObject
{
public:
    void jump()
    {
        if (!is_flying && GetKeyState(VK_SPACE) < 0)
            vertical_speed = -1;
    }
	
	bool check_collisions(Enemy* enemies, int& enemies_count, Level& level, int& score)
	{
        for (int i = 0; i < enemies_count; i++)
        {
            if (check_collision(enemies[i]))
            {
                if (enemies[i].kind == 'o')
                {
                    if (is_flying && vertical_speed > 0 && (y + height < enemies[i].y + enemies[i].height * 0.5))
                    {
                        score += 50;
                        level.remove_enemy(i, enemies, enemies_count);
                        i--;
                        continue;
                    }
                    else
                    {
                        return true;
                    }
                }
                else if (enemies[i].kind == '$')
                {
                    score += 100;
                    level.remove_enemy(i, enemies, enemies_count);
                    i--;
                    continue;
                }
			}
        }
        return false;
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
		static int get_map_height() { return MAP_HEIGHT; }
	
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
		
		void scroll_map(float dx, Player& player, GameObject* background_elems, int background_elems_count, Enemy* enemies, int enemy_count)
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
			
			for (int i = 0; i < enemy_count; i++)
                enemies[i].x += dx;
		}

		void forward(Player& player, GameObject* background_elems, int background_elems_count, Enemy* enemies, int enemies_count)
		{
			if (GetKeyState('A') < 0) 
				scroll_map(1, player, background_elems, background_elems_count, enemies, enemies_count);
		}

		void back(Player& player, GameObject* background_elems, int background_elems_count, Enemy* enemies, int enemies_count)
		{
			if (GetKeyState('D') < 0) 
				scroll_map(-1, player, background_elems, background_elems_count, enemies, enemies_count);
		}
		
		void show_score(int score)
		{
			std::ostringstream ss;
			ss << "Score: " << score;
			std::string text = ss.str();
			for (int i = 0; i < text.length(); i++)
			{
				if (i + 5 < MAP_WIDTH)
					map[1][i + 5] = text[i];
			}
		}
};

void Level::create_level(Player& player, GameObject*& background_elems, int& background_elems_count, Enemy*& enemies, int& enemies_count, int& score)
		{
			system("color 9F");
			delete_background_elem(background_elems, background_elems_count);
			delete_enemies(enemies, enemies_count);

			player.init_object(39, 10, 3, 3, '@');
			score = 0;

			add_new_background_elem(background_elems, background_elems_count, 20, 20, 40, 5, '#');
			add_new_background_elem(background_elems, background_elems_count, 30, 10, 5, 3, '?');
			add_new_background_elem(background_elems, background_elems_count, 50, 10, 5, 3, '?');
			add_new_background_elem(background_elems, background_elems_count, 60, 15, 40, 10, '#');
			add_new_background_elem(background_elems, background_elems_count, 60, 5, 10, 3, '-');
			add_new_background_elem(background_elems, background_elems_count, 70, 5, 5, 3, '?');
			add_new_background_elem(background_elems, background_elems_count, 75, 5, 5, 3, '-');
			add_new_background_elem(background_elems, background_elems_count, 80, 5, 5, 3, '?');
			add_new_background_elem(background_elems, background_elems_count, 85, 5, 10, 3, '-');
			add_new_background_elem(background_elems, background_elems_count, 100, 20, 20, 5, '#');
			add_new_background_elem(background_elems, background_elems_count, 120, 15, 10, 10, '#');
			add_new_background_elem(background_elems, background_elems_count, 150, 20, 40, 5, '#');
			add_new_background_elem(background_elems, background_elems_count, 210, 15, 10, 10, '+');
			
			add_new_enemy(enemies, enemies_count, 25, 10, 3, 2, 'o');
            add_new_enemy(enemies, enemies_count, 80, 10, 3, 2, 'o');
		}
		
int main()
{
	GameMap game_map;
	Player player;
	
	GameObject* background_elems = nullptr;
	int background_elems_count = 0;
	
	Enemy* enemies = nullptr;
    int enemies_count = 0;
	
	Level level;
	int score = 0;
	
    level.create_level(player, background_elems, background_elems_count, enemies, enemies_count, score);
	
	do
	{
		game_map.clear_map();
		
		player.jump();
		game_map.forward(player, background_elems, background_elems_count, enemies, enemies_count);
		game_map.back(player, background_elems, background_elems_count, enemies, enemies_count);
		
		player.vertical_move_object(background_elems, background_elems_count);
		
		if (player.check_collisions(enemies, enemies_count, level, score))
        {
            level.create_level(player, background_elems, background_elems_count, enemies, enemies_count, score);
            continue;
        }
		
		for (int i = 0; i < background_elems_count; i++)
        {
            game_map.add_object_on_map(background_elems[i]);
        }
		
		for (int i = 0; i < enemies_count; i++)
        {
            enemies[i].vertical_move_object(background_elems, background_elems_count);
            enemies[i].horizontal_move_object(background_elems, background_elems_count);
            
            if (enemies[i].y > GameMap::get_map_height())
            {
                level.remove_enemy(i, enemies, enemies_count);
                i--;
                continue;
            }
            game_map.add_object_on_map(enemies[i]);
        }
		
		game_map.add_object_on_map(player);
		game_map.show_score(score);
		game_map.show_map();
		
		Sleep(10);
	}
	while (GetKeyState(VK_ESCAPE) >= 0);
	
	level.delete_background_elem(background_elems, background_elems_count);
	level.delete_enemies(enemies, enemies_count);

    return 0;
}