#include "insertion_sort_tools.hpp"

#include <algorithm>
#include <ctime>
#include <random>

namespace rva {
    void insertion_sort(int* arr, const int size) {
        if (size <= 1) return;
        for (int i = 1; i < size; ++i) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
    
    bool is_sorted(const int* arr, const int size) {
        for (int i = 1; i < size; ++i) {
            if (arr[i] < arr[i - 1]) {
                return false;
            }
        }
        return true;
    }
    void create_data(int* arr, const int size, const int max_value) {
        std::mt19937 mt(time(nullptr));
		for (int i = 0; i < size; ++i) {
			arr[i] = (mt() % max_value);
		}
    }
}