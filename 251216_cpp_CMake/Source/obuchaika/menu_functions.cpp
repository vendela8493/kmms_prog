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


const rva::MenuItem* rva::sum(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const rva::MenuItem* rva::substract(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const rva::MenuItem* rva::multiply(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const rva::MenuItem* rva::divide(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const rva::MenuItem* rva::diff_eq(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const rva::MenuItem* rva::integral(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}

const rva::MenuItem* rva::go_back(const MenuItem* current)
{
	std::cout << current->title << std::endl << std::endl;
	return current->parent->parent;
}