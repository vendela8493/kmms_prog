#include <iostream>
#include "menu_functions.hpp"
#include "menu_items.hpp"

int main() {
    const rva::MenuItem* current = &rva::MAIN;
    
    while (true) {
        current = current->func(current);
    }
    
    return 0;
}