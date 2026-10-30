#include "game_object.hpp"
#include "map.hpp"
#include "moving_object.hpp"
#include "section.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <new>
#include <sstream>
#include <windows.h>

using namespace rva;

class Player : public MovingObject {
	public:
		Player(
			float init_x = 0, float init_y = 0,
			float init_width = 3, float init_height = 3
		);

		void jump();
		
		char move_and_check(
			GameObject* background_elem, int background_elems_count,
			float& hit_x, float& hit_y, int& hit_index
		);
		
		bool is_stomping(const GameObject& enemy) const;
};

class Enemy : public MovingObject {
	public:
		Enemy(
			float init_x = 0, float init_y = 0, 
			float init_width = 3, float init_height = 2, char init_kind = ENEMY
		);
			
		void move(GameObject* background_elem, int background_elems_count);
		int handle_collision(const Player& player, int& score);
};
	
class Level {
	private:
		GameObject* background_elem;
		int background_elems_count;
		int current_level;
		int max_level;

	public:
		Level(int init_level = 1, int init_max = 3);
		~Level();

		void clear();
		void add_background_elem(const GameObject& elem);
		void next_level();

		int get_current_level() const;
		int get_max_level() const;

		void load(int level_num);
		
		GameObject* get_elements();
		int get_count() const;
		void hit_block(int index);
};

Enemy* add_new_enemy(Enemy*& enemy, int& enemies_count);

void spawn_coin(float x, float y, Enemy*& enemy, int& enemies_count);

void create_level(
	int current_level, Player& player, Level& level, 
	Enemy*& enemy, int& enemies_count, int& score
);

void kill_player(
	Player& player, Level& level, Enemy*& enemy,
	int& enemies_count, int& score, int& current_level
);

void switch_level(
	Player& player, Level& level, Enemy*& enemy,
	int& enemies_count, int& score
);

void player_collision_model(
	Player& player, Enemy*& enemy, int& enemies_count,
	Level& level, int& score, int& current_level
);

void remove_enemy(int i, Enemy*& enemy, int& enemies_count);

void scroll_map(
	float dx, Player& player, Level& level,
	Enemy*& enemy, int enemies_count
);

void set_cursor(int x, int y);

int main()
{
	const int MAP_WIDTH = 80;
	const int MAP_HEIGHT = 25;

	Map map(MAP_WIDTH, MAP_HEIGHT);
	
	Player player;
	
	Level level;
	
	Enemy* enemy = nullptr;
	int enemies_count = 0;
	
	int score = 0;
	int current_level = 1;
	int max_level = 3;

	
	create_level(current_level, player, level, enemy, enemies_count, score);
	
	do {
		map.clear();
		
		if (GetKeyState(VK_SPACE) < 0) {
			player.jump();
		}
		
		if (GetKeyState('A') < 0) {
			scroll_map(1, player, level, enemy, enemies_count);
		}

		if (GetKeyState('D') < 0) {
			scroll_map(-1, player, level, enemy, enemies_count);
		}
		
		if (player.get_y() > MAP_HEIGHT) {
			kill_player(player, level, enemy, enemies_count, score, current_level);
			continue;
		}
		
		float hit_x = 0, hit_y = 0;
		int hit_idx = -1;
		
		char hit = player.move_and_check(
			level.get_elements(), level.get_count(),
			hit_x, hit_y, hit_idx
		);
		
		if (hit == FULL_BOX) {
			level.hit_block(hit_idx);
			spawn_coin(hit_x, hit_y, enemy, enemies_count);
		} else if (hit == FINISH) {
			switch_level(player, level, enemy, enemies_count, score);
			continue;
		}
	
		player_collision_model(player, enemy, enemies_count, level, score, current_level);
		
		for (int i = 0; i < level.get_count(); i++) {
			map.add_object(level.get_elements()[i]);
		}
		
		for (int i = 0; i < enemies_count; i++) {
			enemy[i].move(level.get_elements(), level.get_count());
			
			if (enemy[i].get_y() > MAP_HEIGHT) {
				remove_enemy(i, enemy, enemies_count);
				i--;
				continue;
			}
			map.add_object(enemy[i]);
		}
		
		map.add_object(player);
		map.show_score(score);
		
		set_cursor(0, 0);
		map.render();
		
		Sleep(10);
	} while (GetKeyState(VK_ESCAPE) >= 0);
	
	free(enemy);
	
	return 0;
}

Enemy *add_new_enemy(Enemy*& enemy, int& enemies_count) {
	enemies_count++;
	Enemy* temp = (Enemy*)realloc( enemy, sizeof(*enemy) * enemies_count );
	if (temp != nullptr) {
		enemy = temp;
	}
	new (&enemy[enemies_count - 1]) Enemy();
	return &enemy[enemies_count - 1];
}

void spawn_coin(float x, float y, Enemy*& enemy, int& enemies_count) {
	*add_new_enemy(enemy, enemies_count) = Enemy(x, y - 3, 3, 2, COIN);
	enemy[enemies_count - 1].set_vertical_speed(-0.7f);
}

void create_level(
	int current_level, Player& player, Level& level, 
	Enemy*& enemy, int& enemies_count, int& score
) {
	system("color 9F");
	
	level.load(current_level);
	
	free(enemy);
	enemies_count = 0;
	enemy = nullptr;
	
	player = Player(39, 10);
	
	if (current_level == 1) {
		*add_new_enemy(enemy, enemies_count) = Enemy(25, 10, 3, 2, ENEMY);
		*add_new_enemy(enemy, enemies_count) = Enemy(80, 10, 3, 2, ENEMY);
	}
	else if (current_level == 2) {
		*add_new_enemy(enemy, enemies_count) = Enemy(25, 10, 3, 2, ENEMY);
		*add_new_enemy(enemy, enemies_count) = Enemy(80, 10, 3, 2, ENEMY);
		*add_new_enemy(enemy, enemies_count) = Enemy(65, 10, 3, 2, ENEMY);
		*add_new_enemy(enemy, enemies_count) = Enemy(120, 10, 3, 2, ENEMY);
		*add_new_enemy(enemy, enemies_count) = Enemy(160, 10, 3, 2, ENEMY);
		*add_new_enemy(enemy, enemies_count) = Enemy(175, 10, 3, 2, ENEMY);
	}
	else if (current_level == 3) {
		*add_new_enemy(enemy, enemies_count) = Enemy(25, 10, 3, 2, ENEMY);
		*add_new_enemy(enemy, enemies_count) = Enemy(50, 10, 3, 2, ENEMY);
		*add_new_enemy(enemy, enemies_count) = Enemy(80, 10, 3, 2, ENEMY);
		*add_new_enemy(enemy, enemies_count) = Enemy(90, 10, 3, 2, ENEMY);
		*add_new_enemy(enemy, enemies_count) = Enemy(120, 10, 3, 2, ENEMY);
		*add_new_enemy(enemy, enemies_count) = Enemy(130, 10, 3, 2, ENEMY);
	}
}

void kill_player(
	Player& player, Level& level, Enemy*& enemy,
	int& enemies_count, int& score, int& current_level
) {
	system("color 4F");
	Sleep(500);
	score = 0;
	create_level(current_level, player, level, enemy, enemies_count, score);
}

void switch_level(
	Player& player, Level& level,
	Enemy*& enemy, int& enemies_count, int& score
) {
	level.next_level();
	system("color 2F");
	Sleep(500);
	create_level(level.get_current_level(), player, level, enemy, enemies_count, score);
}

void player_collision_model(
	Player& player, Enemy*& enemy, int& enemies_count, 
	Level& level, int& score, int& current_level
) {
	for (int i = 0; i < enemies_count; i++) {
		if (player.check_collision(enemy[i])) {
			int result = enemy[i].handle_collision(player, score);
			
			if (result == 1) {
					remove_enemy(i, enemy, enemies_count);
					i--;
					continue;
			} else if (result == -1) {
					kill_player(player, level, enemy, enemies_count, score, current_level);
					return;
			}
		}
	}
}

void remove_enemy(int i, Enemy*& enemy, int& enemies_count) {
	enemies_count--;
	enemy[i] = enemy[enemies_count];
	if (enemies_count == 0) {
		free(enemy);
		enemy = nullptr;
	} else {
		Enemy* temp = (Enemy*)realloc(enemy, sizeof(*enemy) * enemies_count);
		
		if (temp != nullptr)
			enemy = temp;
	}	
}

void scroll_map(
	float dx, Player& player, Level& level,
	Enemy*& enemy, int enemies_count
) {
	GameObject* background_elem = level.get_elements();
    int background_elems_count = level.get_count();
	
	player.move_by(-dx, 0);
	for (int i = 0; i < background_elems_count; i++) {
		if (player.check_collision(background_elem[i])) {
			player.move_by(dx, 0);
			return;
		}
	}
	player.move_by(dx, 0);
	
	for (int i = 0; i < background_elems_count; i++) {
		background_elem[i].move_by(dx, 0);
	}
		
	for (int i = 0; i < enemies_count; i++) {
		enemy[i].move_by(dx, 0);
	}
}

void set_cursor(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

Player::Player(float init_x, float init_y, float init_width, float init_height)
	: MovingObject(init_x, init_y, init_width, init_height, MARIO) {}

void Player::jump() {
	if (!is_flying) {
		vertical_speed = -1.0f;
	}
}

char Player::move_and_check(
	GameObject* background_elem, int background_elems_count,
	float& hit_x, float& hit_y, int& hit_index
) {
	is_flying = true;
	vertical_speed += 0.05f;
	move_by(0, vertical_speed);

	for (int i = 0; i < background_elems_count; i++) {
		if (check_collision(background_elem[i])) {
			char hit_kind = ' ';

			if (background_elem[i].get_kind() == FULL_BOX && vertical_speed < 0) {
				hit_kind = FULL_BOX;
				hit_x = background_elem[i].get_x();
				hit_y = background_elem[i].get_y();
				hit_index = i;
			} else if (background_elem[i].get_kind() == FINISH) {
				hit_kind = FINISH;
			}
			
			if (vertical_speed > 0) {
				y = background_elem[i].get_y() - height;
				is_flying = false;
			} else if (vertical_speed < 0) {
				y = background_elem[i].get_y() + background_elem[i].get_height();
			}

			vertical_speed = 0;
			return hit_kind;
		}
	}
	return ' ';
}

bool Player::is_stomping(const GameObject& enemy) const {
	return is_flying && (vertical_speed > 0) &&
		   ((y + height) <= (enemy.get_y() + enemy.get_height() * 0.5f + 1.0f));
}

Enemy::Enemy(float init_x, float init_y, float init_width, float init_height, char init_kind)
	: MovingObject(init_x, init_y, init_width, init_height, init_kind) {}

void Enemy::move(GameObject* background_elem, int background_elems_count) {
	MovingObject::move(background_elem, background_elems_count);

	move_by(horizontal_speed, 0);

	for (int i = 0; i < background_elems_count; i++) {
		if (check_collision(background_elem[i])) {
			move_by(-horizontal_speed, 0);
			horizontal_speed = -horizontal_speed;
			return;
		}
	}

	if (kind == ENEMY) {
		MovingObject tmp = *this;
		tmp.MovingObject::move(background_elem, background_elems_count);
		if (tmp.get_is_flying()) {
			move_by(-horizontal_speed, 0);
			horizontal_speed = -horizontal_speed;
		}
	}
}

int Enemy::handle_collision(const Player& player, int& score) {
	if (kind == ENEMY) {
		if (player.is_stomping(*this)) {
			score += 50;
			return 1;
		} else {
			return -1;
		}
	} else if (kind == COIN) {
		score += 100;
		return 1;
	}
	return 0;
}

Level::Level(int init_level, int init_max)
	: background_elem(nullptr), background_elems_count(0),
	  current_level(init_level), max_level(init_max) {}

Level::~Level() {
	clear();
}

void Level::clear() {
	delete[] background_elem;
	background_elem = nullptr;
	background_elems_count = 0;
}

void Level::add_background_elem(const GameObject& elem) {
	GameObject* temp = new GameObject[background_elems_count + 1];
	for (int i = 0; i < background_elems_count; i++) {
		temp[i] = background_elem[i];
	}
	temp[background_elems_count] = elem;
	delete[] background_elem;
	background_elem = temp;
	background_elems_count++;
}

void Level::next_level() {
	current_level++;
	if (current_level > max_level) {
		current_level = 1;
	}
}

int Level::get_current_level() const { return current_level; }
int Level::get_max_level() const { return max_level; }

void Level::load(int level_num) {
	current_level = level_num;
	clear();

	if (current_level == 1) {
		add_background_elem(GameObject(20, 20, 40, 5, PLATFORM));
		add_background_elem(GameObject(30, 10, 5, 3, FULL_BOX));
		add_background_elem(GameObject(50, 10, 5, 3, FULL_BOX));
		add_background_elem(GameObject(60, 15, 40, 10, PLATFORM));
		add_background_elem(GameObject(60, 5, 10, 3, BOX));
		add_background_elem(GameObject(70, 5, 5, 3, FULL_BOX));
		add_background_elem(GameObject(75, 5, 5, 3, BOX));
		add_background_elem(GameObject(80, 5, 5, 3, FULL_BOX));
		add_background_elem(GameObject(85, 5, 10, 3, BOX));
		add_background_elem(GameObject(100, 20, 20, 5, PLATFORM));
		add_background_elem(GameObject(120, 15, 10, 10, PLATFORM));
		add_background_elem(GameObject(150, 20, 40, 5, PLATFORM));
		add_background_elem(GameObject(210, 15, 10, 10, FINISH));
	}
	else if (current_level == 2) {
		add_background_elem(GameObject(20, 20, 40, 5, PLATFORM));
		add_background_elem(GameObject(60, 15, 10, 10, PLATFORM));
		add_background_elem(GameObject(80, 20, 20, 5, PLATFORM));
		add_background_elem(GameObject(120, 15, 10, 10, PLATFORM));
		add_background_elem(GameObject(150, 20, 40, 5, PLATFORM));
		add_background_elem(GameObject(210, 15, 10, 10, FINISH));
	}
	else if (current_level == 3) {
		add_background_elem(GameObject(20, 20, 40, 5, PLATFORM));
		add_background_elem(GameObject(80, 20, 15, 5, PLATFORM));
		add_background_elem(GameObject(120, 15, 15, 10, PLATFORM));
		add_background_elem(GameObject(160, 10, 15, 15, FINISH));
	}
}

GameObject* Level::get_elements() { return background_elem; }
int Level::get_count() const { return background_elems_count; }

void Level::hit_block(int index) {
	if (index >= 0 && index < background_elems_count) {
		if (background_elem[index].get_kind() == FULL_BOX) {
			background_elem[index].set_kind(BOX);
		}
	}
}