#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <windows.h>

class GameObject {
protected:
	float x, y;
	float width, height;
	char kind;
	
public:	
	GameObject(float init_x = 0, float init_y = 0, float init_width = 1, float init_height = 1, char init_kind = ' ') {
		x = init_x;
		y = init_y;
		width = init_width;
		height = init_height;
		kind = init_kind;
	}

	float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    char getKind() const { return kind; }
	
	void setPos(float new_x, float new_y) { x = new_x; y = new_y; }
	void moveBy(float dx, float dy) { x += dx; y += dy; }
    void setKind(char new_kind) { kind = new_kind; }

	bool checkCollision(const GameObject& other) const {
		return ((x + width) > other.x) && (x < (other.x + other.width)) &&
		       ((y + height) > other.y) && (y < (other.y + other.height));
	}
};

class MovingObject : public GameObject {
protected:
	float vertical_speed, horizontal_speed;
	bool is_flying;
	
public:
	MovingObject(float init_x = 0, float init_y = 0, float init_width = 1, float init_height = 1, char init_kind = ' '): GameObject(init_x, init_y, init_width, init_height, init_kind) {
		vertical_speed = 0;
		horizontal_speed = 0.2f;
		is_flying = false;
	}
	
	float getVerticalSpeed() const { return vertical_speed; }
    void setVerticalSpeed(float speed) { vertical_speed = speed; }
    float getHorizontalSpeed() const { return horizontal_speed; }
    void setHorizontalSpeed(float speed) { horizontal_speed = speed; }
    bool getIsFlying() const { return is_flying; }
    void setIsFlying(bool flying) { is_flying = flying; }
};

class Player : public MovingObject {
public:
	Player(float init_x = 0, float init_y = 0, float init_width = 3, float init_height = 3)
		: MovingObject(init_x, init_y, init_width, init_height, '@') {}

	void jump() {
		if (!is_flying) {
			vertical_speed = -1.0f;
		}
	}
};

class Enemy : public MovingObject {
public:
	Enemy(float init_x = 0, float init_y = 0, float init_width = 3, float init_height = 2, char init_kind = 'o')
		: MovingObject(init_x, init_y, init_width, init_height, init_kind) {}
};

class Map {
private:
	int width;
	int height;
	char** grid;
	
	bool isWithin(int x, int y) const {
		return (x >= 0 && x < width && y >= 0 && y < height);
	}
		
public:
	Map(int w = 80, int h = 25): width(w), height(h)
	{
		grid = new char*[height];
		
		for (int i = 0; i < height; i++)
			grid[i] = new char[width + 1];
	}
	
	~Map()
	{
		for (int i = 0; i < height; i++)
			delete[] grid[i];
		
		delete[] grid;
	}
	
	void clear()
	{
		for (int i = 0; i < width; i++)
			grid[0][i] = ' ';
		
		grid[0][width] = '\0';
		
		for (int j = 1; j < height; j++)
			for (int k = 0; k < width + 1; k++)
				grid[j][k] = grid[0][k];
	}
	
	void addObject(const GameObject& obj) 
    {
        int int_x = (int)round(obj.getX());
        int int_y = (int)round(obj.getY());
        int int_width = (int)round(obj.getWidth());
        int int_height = (int)round(obj.getHeight());

        for (int i = int_x; i < (int_x + int_width); i++) 
            for (int j = int_y; j < (int_y + int_height); j++) 
                if (isWithin(i, j)) 
                    grid[j][i] = obj.getKind();
    }
	
	void showScore(int score) 
    {
        std::ostringstream ss;
        ss << "Score: " << score;
        std::string text = ss.str();
        for (size_t i = 0; i < text.length() && (i + 5) < (size_t)width; i++) 
            grid[1][i + 5] = text[i];
    }

    void render() const 
    {
        grid[height - 1][width - 1] = '\0';
		
        for (int j = 0; j < height; j++) 
            std::cout << grid[j] << '\n';
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
};
	
	

GameObject* add_new_background_elem(GameObject*& background_elem, int& background_elems_count);
Enemy* add_new_enemy(Enemy*& enemy, int& enemies_count);
void create_level(int current_level, Player& player, GameObject*& background_elem, int& background_elems_count, Enemy*& enemy, int& enemies_count, int& score);
void horizontal_move_object(MovingObject* obj, Player& player, GameObject*& background_elem, int& background_elems_count, Enemy*& enemy, int& enemies_count, int& score, int& current_level, int max_level);
void kill_player(Player& player, GameObject*& background_elem, int& background_elems_count, Enemy*& enemy, int& enemies_count, int& score, int& current_level);
void player_collision_model(Player& player, Enemy*& enemy, int& enemies_count, GameObject*& background_elem, int& background_elems_count, int& score, int& current_level);
void remove_enemy(int i, Enemy*& enemy, int& enemies_count);
void scroll_map(float dx, Player& player, GameObject*& background_elem, int& background_elems_count, Enemy*& enemy, int enemies_count);
void set_cursor(int x, int y);
void vertical_move_object(MovingObject* obj, Player& player, GameObject*& background_elem, int& background_elems_count, Enemy*& enemy, int& enemies_count, int& score, int& current_level, int max_level);

int main()
{
	const int MAP_WIDTH = 80;
	const int MAP_HEIGHT = 25;

	Map map(MAP_WIDTH, MAP_HEIGHT);
	
	Player player;
	
	GameObject* background_elem = nullptr;
	int background_elems_count = 0;
	
	Enemy* enemy = nullptr;
	int enemies_count = 0;
	
	int score = 0;
	int current_level = 1;
	int max_level = 3;

	
	create_level(current_level, player, background_elem, background_elems_count, enemy, enemies_count, score);
	
	do 
	{
		map.clear();
		
		if (GetKeyState(VK_SPACE) < 0)
		{
			player.jump();
		}
		if (GetKeyState('A') < 0)
		{
			scroll_map(1, player, background_elem, background_elems_count, enemy, enemies_count);
		}
		if (GetKeyState('D') < 0)
		{
			scroll_map(-1, player, background_elem, background_elems_count, enemy, enemies_count);
		}
		
		if (player.getY() > MAP_HEIGHT)
		{
			kill_player(player, background_elem, background_elems_count, enemy, enemies_count, score, current_level);
		}
		
		vertical_move_object(&player, player, background_elem, background_elems_count, enemy, enemies_count, score, current_level, max_level);
		player_collision_model(player, enemy, enemies_count, background_elem, background_elems_count, score, current_level);
		
		for (int i = 0; i < background_elems_count; i++)
		{
			map.addObject(background_elem[i]);
		}
		
		for (int i = 0; i < enemies_count; i++)
		{
			vertical_move_object(&enemy[i], player, background_elem, background_elems_count, enemy, enemies_count, score, current_level, max_level);
			horizontal_move_object(&enemy[i], player, background_elem, background_elems_count, enemy, enemies_count, score, current_level, max_level);
			
			if (enemy[i].getY() > MAP_HEIGHT)
			{
				remove_enemy(i, enemy, enemies_count);
				i--;
				continue;
			}
			
			map.addObject(enemy[i]);
		}
		
		map.addObject(player);
		map.showScore(score);
		
		set_cursor(0, 0);
		map.render();
		
		Sleep(10);
	}
	while (GetKeyState(VK_ESCAPE) >= 0);
	
	free(background_elem);
	free(enemy);
	
	return 0;
}

GameObject *add_new_background_elem(GameObject*& background_elem, int& background_elems_count)
{
	background_elems_count++;
	GameObject* temp = (GameObject*)realloc(background_elem, sizeof(*background_elem) * background_elems_count);
	if (temp != nullptr)
	{
		background_elem = temp;
	}
	return &background_elem[background_elems_count - 1];
}

Enemy *add_new_enemy(Enemy*& enemy, int& enemies_count)
{
	enemies_count++;
	Enemy* temp = (Enemy*)realloc( enemy, sizeof(*enemy) * enemies_count );
	if (temp != nullptr)
	{
		enemy = temp;
	}
	return &enemy[enemies_count - 1];
}

void create_level(int current_level, Player& player, GameObject*& background_elem, int& background_elems_count, Enemy*& enemy, int& enemies_count, int& score)
{
	system("color 9F");
	
	free(background_elem);
	background_elems_count = 0;
	background_elem = nullptr;
	
	free(enemy);
	enemies_count = 0;
	enemy = nullptr;
	
	player = Player(39, 10);
	score = 0;
	
	if (current_level == 1)
	{
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(20, 20, 40, 5, '#');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(30, 10, 5, 3, '?');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(50, 10, 5, 3, '?');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(60, 15, 40, 10, '#');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(60, 5, 10, 3, '-');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(70, 5, 5, 3, '?');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(75, 5, 5, 3, '-');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(80, 5, 5, 3, '?');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(85, 5, 10, 3, '-');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(100, 20, 20, 5, '#');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(120, 15, 10, 10, '#');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(150, 20, 40, 5, '#');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(210, 15, 10, 10, '+');
		
		*add_new_enemy(enemy, enemies_count) = Enemy(25, 10, 3, 2, 'o');
		*add_new_enemy(enemy, enemies_count) = Enemy(80, 10, 3, 2, 'o');
	}
	
	if (current_level == 2)
	{
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(20, 20, 40, 5, '#');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(60, 15, 10, 10, '#');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(80, 20, 20, 5, '#');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(120, 15, 10, 10, '#');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(150, 20, 40, 5, '#');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(210, 15, 10, 10, '+');

		*add_new_enemy(enemy, enemies_count) = Enemy(25, 10, 3, 2, 'o');
		*add_new_enemy(enemy, enemies_count) = Enemy(80, 10, 3, 2, 'o');
		*add_new_enemy(enemy, enemies_count) = Enemy(65, 10, 3, 2, 'o');
		*add_new_enemy(enemy, enemies_count) = Enemy(120, 10, 3, 2, 'o');
		*add_new_enemy(enemy, enemies_count) = Enemy(160, 10, 3, 2, 'o');
		*add_new_enemy(enemy, enemies_count) = Enemy(175, 10, 3, 2, 'o');
	}
	
	if (current_level == 3)
	{
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(20, 20, 40, 5, '#');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(80, 20, 15, 5, '#');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(120, 15, 15, 10, '#');
		*add_new_background_elem(background_elem, background_elems_count) = GameObject(160, 10, 15, 15, '+');
		
		*add_new_enemy(enemy, enemies_count) = Enemy(25, 10, 3, 2, 'o');
		*add_new_enemy(enemy, enemies_count) = Enemy(50, 10, 3, 2, 'o');
		*add_new_enemy(enemy, enemies_count) = Enemy(80, 10, 3, 2, 'o');
		*add_new_enemy(enemy, enemies_count) = Enemy(90, 10, 3, 2, 'o');
		*add_new_enemy(enemy, enemies_count) = Enemy(120, 10, 3, 2, 'o');
		*add_new_enemy(enemy, enemies_count) = Enemy(130, 10, 3, 2, 'o');
	}
}

void horizontal_move_object(MovingObject *obj, Player& player, GameObject*& background_elem, int& background_elems_count, Enemy*& enemy, int& enemies_count, int& score, int& current_level, int max_level)
{
	obj->moveBy(obj->getHorizontalSpeed(), 0);
	
	for (int i = 0; i < background_elems_count; i++)
		if (obj->checkCollision(background_elem[i]))
		{
			obj->moveBy(-obj->getHorizontalSpeed(), 0);
			obj->setHorizontalSpeed(-obj->getHorizontalSpeed());
			return;
		}
	
	if (obj->getKind() == 'o')
	{
		MovingObject tmp = *obj;
		vertical_move_object(&tmp, player, background_elem, background_elems_count, enemy, enemies_count, score, current_level, max_level);
		if (tmp.getIsFlying())
		{
			obj->moveBy(-obj->getHorizontalSpeed(), 0);
			obj->setHorizontalSpeed(-obj->getHorizontalSpeed());
		}
	}
}

void kill_player(Player& player, GameObject*& background_elem, int& background_elems_count, Enemy*& enemy, int& enemies_count, int& score, int& current_level)
{
	system("color 4F");
	Sleep(500);
	create_level(current_level, player, background_elem, background_elems_count, enemy, enemies_count, score);
}

void player_collision_model(Player& player, Enemy*& enemy, int& enemies_count, GameObject*& background_elem, int& background_elems_count, int& score, int& current_level)
{
	for (int i = 0; i < enemies_count; i++)
	{
		if (player.checkCollision(enemy[i]))
		{
			if (enemy[i].getKind() == 'o')
			{
				if ((player.getIsFlying() == true) &&
					(player.getVerticalSpeed() > 0) &&
					(player.getY() + player.getHeight() < enemy[i].getY() + enemy[i].getHeight() * 0.5 ))
				{
					score += 50;
					remove_enemy(i, enemy, enemies_count);
					i--;
					continue;
				}
				else
				{
					kill_player(player, background_elem, background_elems_count, enemy, enemies_count, score, current_level);
				}
			}
			
			if (enemy[i].getKind() == '$')
			{
				score += 100;
				remove_enemy(i, enemy, enemies_count);
				i--;
				continue;
			}
		}
	}
}

void remove_enemy(int i, Enemy*& enemy, int& enemies_count) 
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
		Enemy* temp = (Enemy*)realloc(enemy, sizeof(*enemy) * enemies_count);
		if (temp != nullptr)
		{
			enemy = temp;
		}
	}	
}

void scroll_map(float dx, Player& player, GameObject*& background_elem, int& background_elems_count, Enemy*& enemy, int enemies_count)
{
	player.moveBy(-dx, 0);
	for (int i = 0; i < background_elems_count; i++)
	{
		if (player.checkCollision(background_elem[i]))
		{
			player.moveBy(dx, 0);
			return;
		}
	}
	player.moveBy(dx, 0);
	
	for (int i = 0; i < background_elems_count; i++)
	{
		background_elem[i].moveBy(dx, 0);
	}
	for (int i = 0; i < enemies_count; i++)
	{
		enemy[i].moveBy(dx, 0);
	}
}

void set_cursor(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void vertical_move_object(MovingObject *obj, Player& player, GameObject*& background_elem, int& background_elems_count, Enemy*& enemy, int& enemies_count, int& score, int& current_level, int max_level)
{
	obj->setIsFlying(true);
	obj->setVerticalSpeed(obj->getVerticalSpeed() + 0.05f);
	obj->moveBy(0, obj->getVerticalSpeed());
	
	for (int i = 0; i < background_elems_count; i++)
	{
		if (obj->checkCollision(background_elem[i]))
		{
			if (obj->getVerticalSpeed() > 0)
			{
				obj->setIsFlying(false);
			}
			
			if ((background_elem[i].getKind() == '?') && (obj->getVerticalSpeed() < 0) && (obj == &player))
			{
				background_elem[i].setKind('-');
				*add_new_enemy(enemy, enemies_count) = Enemy(background_elem[i].getX(), background_elem[i].getY() - 3, 3, 2, '$');
				enemy[enemies_count - 1].setVerticalSpeed(-0.7f);
			}
			
			obj->moveBy(0, -obj->getVerticalSpeed());
			obj->setVerticalSpeed(0);

			if (background_elem[i].getKind() == '+')
			{
				current_level++;
				if (current_level > max_level)
				{
					current_level = 1;
				}
				
				system("color 2F");
				Sleep(500); 
				create_level(current_level, player, background_elem, background_elems_count, enemy, enemies_count, score);
			}
			break;
		}
	}
}