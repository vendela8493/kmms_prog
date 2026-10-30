#ifndef SECTION_HPP
#define SECTION_HPP

namespace rva {

enum Section : char {
	BOX = '-',
	COIN = '$',
	FINISH = '+',
	FULL_BOX = '?',
	ENEMY = 'o',
	MARIO = '@',
	PLATFORM = '#'
};

}

#endif