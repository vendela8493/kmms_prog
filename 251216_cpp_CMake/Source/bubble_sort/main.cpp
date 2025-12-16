#include <iostream>

#include "bubble_sort.hpp"

using namespace std;

int main() {
	int arr[] = {6, 2, 5, 3, 9};
	const int m = sizeof(arr) / sizeof(arr[0]);
	
	rva::bubble_sort(arr, m);
	
	for (auto i : arr)
		cout << i << " ";
	return 0;
}