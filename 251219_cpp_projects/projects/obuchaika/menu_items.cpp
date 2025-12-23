#include "menu_items.hpp"

#include <cstddef>

#include "menu_functions.hpp"

const rva::MenuItem rva::GO_BACK =
{
	"0 - Вернуться к выбору предметов...", rva::go_back, &rva::ALGEBRA
};
const rva::MenuItem rva::GO_BACK_TO_MENU =
{
	"0 - Вернуться в главное меню...", rva::go_back, &rva::STUDY
};

const rva::MenuItem rva::SUM =
{
	"1 - Хочу научиться складывать!", rva::sum, &rva::ALGEBRA
};
const rva::MenuItem rva::SUBSTRACT =
{
	"2 - Хочу научиться вычитать!", rva::substract, &rva::ALGEBRA
};
const rva::MenuItem rva::MULTIPLY =
{
	"3 - Хочу научиться умножать!", rva::multiply, &rva::ALGEBRA
};
const rva::MenuItem rva::DIVIDE =
{
	"4 - Хочу научиться делить!", rva::divide, &rva::ALGEBRA
};

namespace
{
	const rva::MenuItem* const algebra_children[] = 
	{
		&rva::GO_BACK,
		&rva::SUM,
		&rva::SUBSTRACT,
		&rva::MULTIPLY,
		&rva::DIVIDE
	};
	const int algebra_size = sizeof(algebra_children) / sizeof(algebra_children[0]);
}

const rva::MenuItem rva::DIFF_EQ =
{
	"1 - Хочу изучить дифференциальное исчисление!", rva::diff_eq, &rva::MATH_ANALYSIS
};
const rva::MenuItem rva::INTEGRAL =
{
	"2 - Хочу изучить интегральное исчисление!", rva::integral, &rva::MATH_ANALYSIS
};

namespace
{
	const rva::MenuItem* const math_analysis_children[] = 
	{
		&rva::GO_BACK,
		&rva::DIFF_EQ,
		&rva::INTEGRAL
	};
	const int math_analysis_size = sizeof(math_analysis_children) / sizeof(math_analysis_children[0]);
}

const rva::MenuItem rva::ALGEBRA =
{
	"1 - Хочу изучать алгебру!", rva::show_menu, &rva::STUDY, algebra_children, algebra_size
};
const rva::MenuItem rva::MATH_ANALYSIS =
{
	"2 - Хочу изучать математический анализ!", rva::show_menu, &rva::STUDY, math_analysis_children, math_analysis_size
};

namespace
{
	const rva::MenuItem* const study_children[] =
	{
		&rva::GO_BACK_TO_MENU,
		&rva::ALGEBRA,
		&rva::MATH_ANALYSIS
	};
	const int study_size = sizeof(study_children) / sizeof(study_children[0]);
}

const rva::MenuItem rva::STUDY =
{
	"1 - Хочу учиться математике!", rva::show_menu, &rva::MAIN, study_children, study_size
};
const rva::MenuItem rva::EXIT =
{
	"0 - Я лучше пойду полежу...", rva::exit, &rva::MAIN
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