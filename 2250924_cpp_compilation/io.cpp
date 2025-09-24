#include "io.hpp"
#include <iostream>
using namespace std;

void biv::print_array(const char* const comment, int* arr, const int size) {
	cout << comment << endl;
    cout << "[";
    for (int i = 0; i < size; ++i) {
        cout << arr[i];
        if (i < size - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}