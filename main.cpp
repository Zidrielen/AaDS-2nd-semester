#include <vector>
#include <iostream>

#include <math.h>
#include <conio.h>

#include "sorting_algorithms.h"

int lcg() {
	static int x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

void menu()
{
	system("cls");
	std::cout << "Count number of comparisons, time and number of copies\n";
	std::cout << "\n\t1. Average";
	std::cout << "\n\t2. For a fully sorted array";
	std::cout << "\n\t3. For a reverse sorted array";

	std::cout << "\n\n4. Exit";

	std::cout << "\n\nEnter the number: ";
}

int choose_algorithm()
{
	system("cls");
	std::cout << "Choose sorting algorithm:\n";
	std::cout << "\n\t1. Bubble sort";
	std::cout << "\n\t2. Quick sort";
	std::cout << "\n\t3. Heap sort";
	std::cout << "\n\nEnter the number: ";

	int n = 0;
	std::cin >> n;
	std::cout << "\n\n";
	if (n > 3 || n < 1) return -1;
	return n;
}

int main()
{
	std::vector<int> sizes;
	stats data;
	int n = 0;

	//Заполнение массива, отражающего количество элементов в массиве sort_arr
	for (int i = 1; i <= 10; i++) sizes.push_back(1000 * i);
	for (int i = 0; i <= 2; i++) sizes.push_back(25000 * (int)pow(2, i));

	while (1)
	{
		menu();
		std::cin >> n;

		if (n == 1)
		{
			if ((n = choose_algorithm()) == -1) continue;

			for (auto i : sizes)
			{
				size_t sum_comparison = 0, sum_copy = 0, sum_time = 0;

				for (int j = 0; j < 100; j++)
				{
					std::vector<int> sort_arr;
					for (int k = 0; k < i; k++) sort_arr.push_back(lcg());

					if (n == 1) data = bubble_sort(sort_arr);
					else if (n == 2) data = quick_sort(sort_arr);
					else data = heap_sort(sort_arr);

					sum_comparison += data.comparison_count;
					sum_copy += data.copy_count;
					sum_time += data.time_count;
				}

				std::cout << i << "   ";
				std::cout << sum_comparison / 100 << "   ";
				std::cout << sum_copy / 100 << "   ";
				std::cout << (double)sum_time / 100 << " mcs" << "\n";
			}
			std::cout << "\nProcess completed. Press any key to return to the menu";
			_getch();
		}

		else if (n == 2)
		{
			if ((n = choose_algorithm()) == -1) continue;

			for (auto i : sizes)
			{
				std::vector<int> sort_arr;
				for (int k = 1; k <= i; k++) sort_arr.push_back(k);

				if (n == 1) data = bubble_sort(sort_arr);
				else if (n == 2) data = quick_sort(sort_arr);
				else data = heap_sort(sort_arr);

				std::cout << i << "   ";
				std::cout << data.comparison_count << "   ";
				std::cout << data.copy_count << "   ";
				std::cout << data.time_count << " mcs" << "\n";
			}
			std::cout << "\nProcess completed. Press any key to return to the menu";
			_getch();
		}

		else if (n == 3)
		{
			if ((n = choose_algorithm()) == -1) continue;

			for (auto i : sizes)
			{
				std::vector<int> sort_arr;
				for (int k = i; k >= 1; k--) sort_arr.push_back(k);

				if (n == 1) data = bubble_sort(sort_arr);
				else if (n == 2) data = quick_sort(sort_arr);
				else data = heap_sort(sort_arr);

				std::cout << i << "   ";
				std::cout << data.comparison_count << "   ";
				std::cout << data.copy_count << "   ";
				std::cout << data.time_count << " mcs" << "\n";
			}
			std::cout << "\nProcess completed. Press any key to return to the menu";
			_getch();
		}

		else if (n == 4) break;
	}
}
