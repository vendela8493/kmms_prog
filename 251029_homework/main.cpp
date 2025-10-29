#include "io.hpp"
#include "interesting_sort.hpp"

int main() {
	const int sortable_arr_size = 10;
	const int max_value = 5;
	
	int *sortable_arr = new int[sortable_arr_size]{};
	int *amount_arr = new int[max_value]{};
	
	rva::create_data(sortable_arr, sortable_arr_size, max_value);
	rva::print("Массив до сортировки: ", sortable_arr, sortable_arr_size);
	
	rva::amount(sortable_arr, amount_arr, sortable_arr_size);
	rva::print("Количество элементов: ", amount_arr, max_value);
	
	rva::sort_arr(sortable_arr, amount_arr, max_value);
	rva::print("Отсортированный массив: ", sortable_arr, sortable_arr_size);
	
	delete[] sortable_arr;
	delete[] amount_arr;
}