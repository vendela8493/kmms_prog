#include "enemy.hpp"
#include "level.hpp"
#include "map.hpp"
#include "player.hpp"
#include "section.hpp"

#include <cstdlib>
#include <new>
#include <windows.h>

using namespace rva;

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
	
		player_collision_model(
			player, enemy, enemies_count, level, score, current_level
		);
		
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

Enemy* add_new_enemy(Enemy*& enemy, int& enemies_count) {
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