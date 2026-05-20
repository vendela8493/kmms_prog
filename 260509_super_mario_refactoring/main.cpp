#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 25;


struct GameObject {
	float x, y;
	float width, height;
	float vertical_speed;
	float horizontal_speed;
	char kind;
	bool is_flying;
};


char map[MAP_HEIGHT][MAP_WIDTH+1];
GameObject player;

GameObject* background_elem = NULL;
int background_elems_count = 0;

GameObject* sprite = NULL;
int sprites_count = 0;

int current_level = 1;
int score = 0;
int max_level = 3;

void add_object_on_map(GameObject obj);
GameObject* add_new_background_elem();
GameObject* add_new_sprite();
bool check_collision(GameObject o1, GameObject o2);
void clear_map();
void create_level(int level);
void horizontal_move_object(GameObject* obj);
void init_object(GameObject* obj, float init_x, float init_y, float init_width, float init_height, char init_kind);
void kill_player();
bool object_within_map(int x, int y);
void player_collision_model();
void remove_sprite(int i);
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
		
		if ((player.is_flying == false) && (GetKeyState(VK_SPACE) < 0))
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
		
		for (int i = 0; i < sprites_count; i++)
		{
			vertical_move_object(sprite + i);
			horizontal_move_object(sprite + i);
			add_object_on_map(sprite[i]);
			
			if (sprite[i].y > MAP_HEIGHT)
			{
				remove_sprite(i);
				i--;
				continue;
			}
			add_object_on_map(sprite[i]);
		}
		add_object_on_map(player);
		show_score();
		
		set_cursor(0, 0);
		show_map();
		
		Sleep(10);
	}
	while (GetKeyState(VK_ESCAPE) >= 0);
	
	return 0;
}


void add_object_on_map(GameObject obj)
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
	background_elem = (GameObject*)realloc(background_elem, sizeof(*background_elem) * background_elems_count);
	return background_elem + background_elems_count - 1;
}

GameObject *add_new_sprite()
{
	sprites_count++;
	sprite = (GameObject*)realloc( sprite, sizeof(*sprite) * sprites_count );
	return sprite + sprites_count - 1;
}

bool check_collision(GameObject o1, GameObject o2)
{
	return ((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) &&
		   ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
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
		sprintf(map[j], map[0]);
	}
}

void create_level(int lvl)
{
	system("color 9F");
	
	background_elems_count = 0;
	background_elem = (GameObject*)realloc(background_elem, 0);
	sprites_count = 0;
	sprite = (GameObject*)realloc(sprite, 0);
	
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
		
		init_object(add_new_sprite(), 25, 10, 3, 2, 'o');
		init_object(add_new_sprite(), 80, 10, 3, 2, 'o');
	}
	
	if (lvl == 2)
	{
		init_object(add_new_background_elem(), 20, 20, 40, 5, '#');
		init_object(add_new_background_elem(), 60, 15, 10, 10, '#');
		init_object(add_new_background_elem(), 80, 20, 20, 5, '#');
		init_object(add_new_background_elem(), 120, 15, 10, 10, '#');
		init_object(add_new_background_elem(), 150, 20, 40, 5, '#');
		init_object(add_new_background_elem(), 210, 15, 10, 10, '+');

		init_object(add_new_sprite(), 25, 10, 3, 2, 'o');
		init_object(add_new_sprite(), 80, 10, 3, 2, 'o');
		init_object(add_new_sprite(), 65, 10, 3, 2, 'o');
		init_object(add_new_sprite(), 120, 10, 3, 2, 'o');
		init_object(add_new_sprite(), 160, 10, 3, 2, 'o');
		init_object(add_new_sprite(), 175, 10, 3, 2, 'o');
	}
	
	if (lvl == 3)
	{
		init_object(add_new_background_elem(), 20, 20, 40, 5, '#');
		init_object(add_new_background_elem(), 80, 20, 15, 5, '#');
		init_object(add_new_background_elem(), 120, 15, 15, 10, '#');
		init_object(add_new_background_elem(), 160, 10, 15, 15, '+');
		
		init_object(add_new_sprite(), 25, 10, 3, 2, 'o');
		init_object(add_new_sprite(), 50, 10, 3, 2, 'o');
		init_object(add_new_sprite(), 80, 10, 3, 2, 'o');
		init_object(add_new_sprite(), 90, 10, 3, 2, 'o');
		init_object(add_new_sprite(), 120, 10, 3, 2, 'o');
		init_object(add_new_sprite(), 130, 10, 3, 2, 'o');
	}
	
	max_level = 3;
}

void horizontal_move_object(GameObject *obj)
{
	obj[0].x += obj[0].horizontal_speed;
	
	for (int i = 0; i < background_elems_count; i++)
		if (check_collision(obj[0], background_elem[i]))
		{
			obj[0].x -= obj[0].horizontal_speed;
			obj[0].horizontal_speed = -obj[0].horizontal_speed;
			return;
		}
	
	if (obj[0].kind == 'o')
	{
		GameObject tmp = *obj;
		vertical_move_object(&tmp);
		if (tmp.is_flying == true)
		{
			obj[0].x -= obj[0].horizontal_speed;
			obj[0].horizontal_speed = -obj[0].horizontal_speed;
		}
	}
}

void init_object(GameObject *obj, float init_x, float init_y, float init_width, float init_height, char init_kind)
{
	set_object_pos(obj, init_x, init_y);
	(*obj).width = init_width;
	(*obj).height = init_height;
	(*obj).vertical_speed = 0;
	(*obj).kind = init_kind;
	(*obj).horizontal_speed = 0.2;
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
	for (int i = 0; i < sprites_count; i++)
	{
		if (check_collision( player, sprite[i]))
		{
			if (sprite[i].kind == 'o')
			{
				if ((player.is_flying == true) &&
					(player.vertical_speed > 0) &&
					(player.y + player.height < sprite[i].y + sprite[i].height * 0.5 ))
				{
					score += 50;
					remove_sprite(i);
					i--;
					continue;
				}
				else
				{
					kill_player();
				}
			}
			
			if (sprite[i].kind == '$')
			{
				score += 100;
				remove_sprite(i);
				i--;
				continue;
			}
		}
	}
}

void remove_sprite(int i) 
{
	sprites_count--;
	sprite[i] = sprite[sprites_count];
	sprite = (GameObject*)realloc(sprite, sizeof(*sprite) * sprites_count);
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
	for (int i = 0; i < sprites_count; i++)
	{
		sprite[i].x += dx;
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
	(*obj).x = obj_pos_x;
	(*obj).y = obj_pos_y;
}

void show_map()
{
	map[MAP_HEIGHT - 1][MAP_WIDTH - 1] = '\0';
	for (int j = 0; j < MAP_HEIGHT; j++)
	{
		printf("%s\n", map[j]);
	}
}

void show_score()
{
	char score_text[30];
	sprintf(score_text, "Score: %d", score);
	int length = strlen(score_text);
	for (int i = 0; i < length; i++)
	{
		map[1][i + 5] = score_text[i];
	}
}

void vertical_move_object(GameObject *obj)
{
	(*obj).is_flying = true;
	(*obj).vertical_speed += 0.05;
	set_object_pos(obj, (*obj).x, (*obj).y + (*obj).vertical_speed);
	
	for (int i = 0; i < background_elems_count; i++)
	{
		if (check_collision( *obj, background_elem[i]))
		{
			if (obj[0].vertical_speed > 0)
			{
				obj[0].is_flying = false;
			}
			
			if ((background_elem[i].kind == '?') && (obj[0].vertical_speed < 0) && (obj == &player))
			{
				background_elem[i].kind = '-';
				init_object(add_new_sprite(), background_elem[i].x, background_elem[i].y-3, 3, 2, '$');
				sprite[sprites_count - 1].vertical_speed = -0.7;
			}
			
			(*obj).y -= (*obj).vertical_speed;
			(*obj).vertical_speed = 0;

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
