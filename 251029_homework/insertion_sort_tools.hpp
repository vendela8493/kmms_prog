#ifndef INSERTION_SORT_TOOLS_HPP
#define INSERTION_SORT_TOOLS_HPP

namespace rva{
	void insertion_sort(int* arr, const int size);
    bool is_sorted(const int* arr, const int size);
    void create_data(int* arr, const int size, const int max_value);
}

#endif