#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <windows.h>

const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 25;

struct GameObject {
	float x, y;
	float width, height;
	float vertical_speed, horizontal_speed;
	char kind;
	bool is_flying;
};


char map[MAP_HEIGHT][MAP_WIDTH+1];
GameObject player;

GameObject* background_elem = nullptr;
int background_elems_count = 0;

GameObject* enemy = nullptr;
int enemies_count = 0;

int current_level = 1;
int score = 0;
int max_level = 3;

void add_object_on_map(const GameObject& obj);
GameObject* add_new_background_elem();
GameObject* add_new_enemy();
bool check_collision(const GameObject& obj_1, const GameObject& obj_2);
void clear_map();
void create_level(int level);
void horizontal_move_object(GameObject* obj);
void init_object(GameObject* obj, float init_x, float init_y, float init_width, float init_height, char init_kind);
void kill_player();
bool object_within_map(int x, int y);
void player_collision_model();
void remove_enemy(int i);
void scroll_map(float dx);
void set_cursor(int x, int y);
void set_object_pos(GameObject* obj, float obj_pos_x, float obj_pos_y);
void show_map();
void show_score();
void vertical_move_object(GameObject* obj);


int main()
{
	create_level(current_level);
	
	do 
	{
		clear_map();
		
		if (!player.is_flying && GetKeyState(VK_SPACE) < 0)
		{
			player.vertical_speed = -1;
		}
		if (GetKeyState('A') < 0)
		{
			scroll_map(1);
		}
		if (GetKeyState('D') < 0)
		{
			scroll_map(-1);
		}
		
		if (player.y > MAP_HEIGHT)
		{
			kill_player();
		}
		
		vertical_move_object(&player);
		player_collision_model();
		
		for (int i = 0; i < background_elems_count; i++)
		{
			add_object_on_map(background_elem[i]);
		}
		
		for (int i = 0; i < enemies_count; i++)
		{
			vertical_move_object(&enemy[i]);
			horizontal_move_object(&enemy[i]);
			
			if (enemy[i].y > MAP_HEIGHT)
			{
				remove_enemy(i);
				i--;
				continue;
			}
			
			add_object_on_map(enemy[i]);
		}
		add_object_on_map(player);
		show_score();
		
		set_cursor(0, 0);
		show_map();
		
		Sleep(10);
	}
	while (GetKeyState(VK_ESCAPE) >= 0);
	
	free(background_elem);
	free(enemy);
	
	return 0;
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
			if (object_within_map(i,j))
			{
	 			map[j][i] = obj.kind;
			}
		}
	}
}

GameObject *add_new_background_elem()
{
	background_elems_count++;
	GameObject* temp = (GameObject*)realloc(background_elem, sizeof(*background_elem) * background_elems_count);
	if (temp != nullptr)
	{
		background_elem = temp;
	}
	return &background_elem[background_elems_count - 1];
}

GameObject *add_new_enemy()
{
	enemies_count++;
	GameObject* temp = (GameObject*)realloc( enemy, sizeof(*enemy) * enemies_count );
	if (temp != nullptr)
	{
		enemy = temp;
	}
	return &enemy[enemies_count - 1];
}

bool check_collision(const GameObject& obj_1, const GameObject& obj_2)
{
	return ((obj_1.x + obj_1.width) > obj_2.x) && (obj_1.x < (obj_2.x + obj_2.width)) &&
		   ((obj_1.y + obj_1.height) > obj_2.y) && (obj_1.y < (obj_2.y + obj_2.height));
}

void clear_map()
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		map[0][i] = ' ';
	}
	map[0][MAP_WIDTH] = '\0';
	for (int j = 1; j < MAP_HEIGHT; j++)
	{
		for (int k = 0; k < MAP_WIDTH + 1; k++)
		{
			map[j][k] = map[0][k];
		}
	}
}

void create_level(int lvl)
{
	system("color 9F");
	
	free(background_elem);
	background_elems_count = 0;
	background_elem = nullptr;
	
	free(enemy);
	enemies_count = 0;
	enemy = nullptr;
	
	init_object(&player, 39, 10, 3, 3, '@');
	score = 0;
	
	if (lvl == 1)
	{
		init_object(add_new_background_elem(), 20, 20, 40, 5, '#');
		init_object(add_new_background_elem(), 30, 10, 5, 3, '?');
		init_object(add_new_background_elem(), 50, 10, 5, 3, '?');
		init_object(add_new_background_elem(), 60, 15, 40, 10, '#');
		init_object(add_new_background_elem(), 60, 5, 10, 3, '-');
		init_object(add_new_background_elem(), 70, 5, 5, 3, '?');
		init_object(add_new_background_elem(), 75, 5, 5, 3, '-');
		init_object(add_new_background_elem(), 80, 5, 5, 3, '?');
		init_object(add_new_background_elem(), 85, 5, 10, 3, '-');
		init_object(add_new_background_elem(), 100, 20, 20, 5, '#');
		init_object(add_new_background_elem(), 120, 15, 10, 10, '#');
		init_object(add_new_background_elem(), 150, 20, 40, 5, '#');
		init_object(add_new_background_elem(), 210, 15, 10, 10, '+');
		
		init_object(add_new_enemy(), 25, 10, 3, 2, 'o');
		init_object(add_new_enemy(), 80, 10, 3, 2, 'o');
	}
	
	if (lvl == 2)
	{
		init_object(add_new_background_elem(), 20, 20, 40, 5, '#');
		init_object(add_new_background_elem(), 60, 15, 10, 10, '#');
		init_object(add_new_background_elem(), 80, 20, 20, 5, '#');
		init_object(add_new_background_elem(), 120, 15, 10, 10, '#');
		init_object(add_new_background_elem(), 150, 20, 40, 5, '#');
		init_object(add_new_background_elem(), 210, 15, 10, 10, '+');

		init_object(add_new_enemy(), 25, 10, 3, 2, 'o');
		init_object(add_new_enemy(), 80, 10, 3, 2, 'o');
		init_object(add_new_enemy(), 65, 10, 3, 2, 'o');
		init_object(add_new_enemy(), 120, 10, 3, 2, 'o');
		init_object(add_new_enemy(), 160, 10, 3, 2, 'o');
		init_object(add_new_enemy(), 175, 10, 3, 2, 'o');
	}
	
	if (lvl == 3)
	{
		init_object(add_new_background_elem(), 20, 20, 40, 5, '#');
		init_object(add_new_background_elem(), 80, 20, 15, 5, '#');
		init_object(add_new_background_elem(), 120, 15, 15, 10, '#');
		init_object(add_new_background_elem(), 160, 10, 15, 15, '+');
		
		init_object(add_new_enemy(), 25, 10, 3, 2, 'o');
		init_object(add_new_enemy(), 50, 10, 3, 2, 'o');
		init_object(add_new_enemy(), 80, 10, 3, 2, 'o');
		init_object(add_new_enemy(), 90, 10, 3, 2, 'o');
		init_object(add_new_enemy(), 120, 10, 3, 2, 'o');
		init_object(add_new_enemy(), 130, 10, 3, 2, 'o');
	}
	
	max_level = 3;
}

void horizontal_move_object(GameObject *obj)
{
	obj->x += obj->horizontal_speed;
	
	for (int i = 0; i < background_elems_count; i++)
		if (check_collision(*obj, background_elem[i]))
		{
			obj->x -= obj->horizontal_speed;
			obj->horizontal_speed = -obj->horizontal_speed;
			return;
		}
	
	if (obj->kind == 'o')
	{
		GameObject tmp = *obj;
		vertical_move_object(&tmp);
		if (tmp.is_flying)
		{
			obj->x -= obj->horizontal_speed;
			obj->horizontal_speed = -obj->horizontal_speed;
		}
	}
}

void init_object(GameObject *obj, float init_x, float init_y, float init_width, float init_height, char init_kind)
{
	set_object_pos(obj, init_x, init_y);
	obj->width = init_width;
	obj->height = init_height;
	obj->vertical_speed = 0;
	obj->kind = init_kind;
	obj->horizontal_speed = 0.2;
	obj->is_flying = false;
}

void kill_player()
{
	system("color 4F");
	Sleep(500);
	create_level(current_level);
}

bool object_within_map(int x, int y)
{
	return ((x >= 0) && (x < MAP_WIDTH) && (y >= 0) && (y < MAP_HEIGHT));
}

void player_collision_model()
{
	for (int i = 0; i < enemies_count; i++)
	{
		if (check_collision( player, enemy[i]))
		{
			if (enemy[i].kind == 'o')
			{
				if ((player.is_flying == true) &&
					(player.vertical_speed > 0) &&
					(player.y + player.height < enemy[i].y + enemy[i].height * 0.5 ))
				{
					score += 50;
					remove_enemy(i);
					i--;
					continue;
				}
				else
				{
					kill_player();
				}
			}
			
			if (enemy[i].kind == '$')
			{
				score += 100;
				remove_enemy(i);
				i--;
				continue;
			}
		}
	}
}

void remove_enemy(int i) 
{
	enemies_count--;
	enemy[i] = enemy[enemies_count];
	if (enemies_count == 0) 
	{
		free(enemy);
		enemy = nullptr;
	}
	else
	{
		GameObject* temp = (GameObject*)realloc(enemy, sizeof(*enemy) * enemies_count);
		if (temp != nullptr)
		{
			enemy = temp;
		}
	}	
}

void scroll_map(float dx)
{
	player.x -= dx;
	for (int i = 0; i < background_elems_count; i++)
	{
		if (check_collision(player, background_elem[i]))
		{
			player.x += dx;
			return;
		}
	}
	player.x += dx;
	
	for (int i = 0; i < background_elems_count; i++)
	{
		background_elem[i].x += dx;
	}
	for (int i = 0; i < enemies_count; i++)
	{
		enemy[i].x += dx;
	}
}

void set_cursor(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_object_pos(GameObject *obj, float obj_pos_x, float obj_pos_y)
{
	obj->x = obj_pos_x;
	obj->y = obj_pos_y;
}

void show_map()
{
	map[MAP_HEIGHT - 1][MAP_WIDTH - 1] = '\0';
	for (int j = 0; j < MAP_HEIGHT; j++)
	{
		std::cout << map[j] << '\n';
	}
}

void show_score()
{
	std::ostringstream ss;
	ss << "Score: " << score;
	std::string text = ss.str();
	for (int i = 0; i < text.length(); i++)
	{
		map[1][i + 5] = text[i];
	}
}

void vertical_move_object(GameObject *obj)
{
	obj->is_flying = true;
	obj->vertical_speed += 0.05;
	set_object_pos(obj, obj->x, obj->y + obj->vertical_speed);
	
	for (int i = 0; i < background_elems_count; i++)
	{
		if (check_collision(*obj, background_elem[i]))
		{
			if (obj->vertical_speed > 0)
			{
				obj->is_flying = false;
			}
			
			if ((background_elem[i].kind == '?') && (obj->vertical_speed < 0) && (obj == &player))
			{
				background_elem[i].kind = '-';
				init_object(add_new_enemy(), background_elem[i].x, background_elem[i].y-3, 3, 2, '$');
				enemy[enemies_count - 1].vertical_speed = -0.7;
			}
			
			obj->y -= obj->vertical_speed;
			obj->vertical_speed = 0;

			if (background_elem[i].kind == '+')
			{
				current_level++;
				if (current_level > max_level)
				{
					current_level = 1;
				}
				
				system("color 2F");
				Sleep(500); 
				create_level(current_level);
			}
			break;
		}
	}
}
