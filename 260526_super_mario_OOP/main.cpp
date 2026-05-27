#include <iostream>
#include <windows.h>

class GameMap
{
private:
    static const int MAP_HEIGHT = 25;
    static const int MAP_WIDTH = 80;
    char map[MAP_HEIGHT][MAP_WIDTH + 1];

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
};

class GameObject
{
public:
    float x, y;
    float width, height;
    
    float vertical_speed, horizontal_speed;
    
    char kind;
    bool is_flying;

    GameObject()
    {
        x = 0;
        y = 0;
        width = 0;
        height = 0;
        vertical_speed = 0;
        horizontal_speed = 0.2;
        kind = ' ';
        is_flying = false;
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
        vertical_speed = 0;
        horizontal_speed = 0.2;
        kind = init_kind;
        is_flying = false;
    }
};

int main()
{
    GameObject player;

    player.init_object(39, 10, 3, 3, '@');

	GameMap game_map;
    game_map.clear_map();
    game_map.show_map();
	
    return 0;
}