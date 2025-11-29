#pragma once

#include "menu.hpp"

namespace rva
{
	const MenuItem* show_menu(const MenuItem* current);
	const MenuItem* exit(const MenuItem* current);
	
	const MenuItem* data(const MenuItem* current);
	const MenuItem* programming(const MenuItem* current);
	const MenuItem* technology(const MenuItem* current);
		
	const MenuItem* languages(const MenuItem* current);
	const MenuItem* algorythms(const MenuItem* current);
	const MenuItem* others(const MenuItem* current);
	const MenuItem* go_back(const MenuItem* current);
}