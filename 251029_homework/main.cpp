#include "io.hpp"
#include <iostream>
#include "insertion_sort_tools.hpp"

int main() {
	const int sortable_arr_size = 10;
	const int max_value = 100;
	
	int *sortable_arr = new int[sortable_arr_size]{};
		
	rva::create_data(sortable_arr, sortable_arr_size, max_value);
	rva::print("Массив до сортировки: ", sortable_arr, sortable_arr_size);
	
	rva::insertion_sort(sortable_arr, sortable_arr_size);
	
	if (rva::is_sorted(sortable_arr, sortable_arr_size)) {
        std::cout << "Массив успешно отсортирован!" << std::endl;
		rva::print("Отсортированный массив: ", sortable_arr, sortable_arr_size);
    } else {
        std::cout << "Ошибка сортировки!" << std::endl;
    }
    
    delete[] sortable_arr;
}