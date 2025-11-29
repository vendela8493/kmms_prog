#include <cstdlib>
#include <iostream>

#include "menu_functions.hpp"

const rva::MenuItem* rva::show_menu(const MenuItem* current)
{
	std::cout << "Обучайка привествует тебя!" << std::endl;
	for (int i = 1; i < current->children_count; i++)
	{	
		std::cout << current->children[i]->title << std::endl;
	}
	std::cout << current->children[0]->title << std::endl;
	std::cout << "Обучайка >> ";
	
	int user_input;
	std::cin >> user_input;
	std::cout << std::endl;
	
	return current->children[user_input];
}

const rva::MenuItem* rva::exit(const MenuItem* current)
{
	std::exit(0);
}

const rva::MenuItem* rva::data(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}

const rva::MenuItem* rva::programming(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}

const rva::MenuItem* rva::technology(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}

const rva::MenuItem* rva::go_back(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent->parent;
}

const rva::MenuItem* rva::languages(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}

const rva::MenuItem* rva::algorythms(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}

const rva::MenuItem* rva::others(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}