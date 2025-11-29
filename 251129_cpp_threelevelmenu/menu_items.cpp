#include "menu_items.hpp"

#include <cstddef>

#include "menu_functions.hpp"



const rva::MenuItem rva::GO_BACK =
{
	"0 - Вернуться к выбору предметов...", rva::go_back, &rva::OTHERS
};
const rva::MenuItem rva::GO_BACK_TO_MENU =
{
	"0 - Вернуться в главное меню...", rva::go_back, &rva::STUDY
};

const rva::MenuItem rva::DATA =
{
	"1 - Хочу изучать базы данных!", rva::data, &rva::OTHERS
};
const rva::MenuItem rva::PROGRAMMING =
{
	"2 - Хочу изучать многопоточное программирование!", rva::programming, &rva::OTHERS
};
const rva::MenuItem rva::TECHNOLOGY =
{
	"3 - Хочу изучать сетевые технологии!", rva::technology, &rva::OTHERS
};



namespace
{
	const rva::MenuItem* const others_children[] = 
	{
		&rva::GO_BACK,
		&rva::DATA,
		&rva::PROGRAMMING,
		&rva::TECHNOLOGY,
	};
	const int others_size = sizeof(others_children) / sizeof(others_children[0]);
}

namespace
{
	const rva::MenuItem* const language_children[] = 
	{
		&rva::GO_BACK_TO_MENU
	};
	const int language_size = sizeof(language_children) / sizeof(language_children[0]);

	const rva::MenuItem* const algorythms_children[] = 
	{
		&rva::GO_BACK_TO_MENU
	};
	const int algorythms_size = sizeof(algorythms_children) / sizeof(algorythms_children[0]);
}

const rva::MenuItem rva::LANGUAGE =
{
	"1 - Хочу изучать языки программирования!", rva::show_menu, &rva::STUDY, language_children, language_size
};
const rva::MenuItem rva::ALGORYTHMS =
{
	"2 - Хочу изучать алгоритмы и структуры!", rva::show_menu, &rva::STUDY, algorythms_children, algorythms_size
};
const rva::MenuItem rva::OTHERS =
{
	"3 - Хочу изучать другие технологии!", rva::show_menu, &rva::STUDY, others_children, others_size
};

namespace
{
	const rva::MenuItem* const study_children[] =
	{
		&rva::GO_BACK_TO_MENU,
		&rva::LANGUAGE,
		&rva::ALGORYTHMS,
		&rva::OTHERS,
	};
	const int study_size = sizeof(study_children) / sizeof(study_children[0]);
}

const rva::MenuItem rva::STUDY =
{
	"1 - Хочу изучать программирование!", rva::show_menu, &rva::MAIN, study_children, study_size
};
const rva::MenuItem rva::EXIT =
{
	"0 - Я пойду играть в футбол", rva::exit, &rva::MAIN
};

namespace
{
	const rva::MenuItem* const main_children[] =
	{
		&rva::EXIT,
		&rva::STUDY
	};
	const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

const rva::MenuItem rva::MAIN =
{
	nullptr, rva::show_menu, nullptr, main_children, main_size
};