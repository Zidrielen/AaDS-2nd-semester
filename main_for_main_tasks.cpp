#include <iostream>
#include <conio.h>
#include <windows.h>

#include <vector>

#include "class_binary_tree.h"
#include "functions.h"

int main()
{
	//Вектор, хранящий объекты типа Set<T>
	std::vector<set> arr;
	int size = 0, n = 0, m = 0;
	int num = 0;

	while (1)
	{
		options_menu();
		std::cin >> n;

		if (n == 1)
		{
			std::cout << "\n- Enter the number of nodes: ";
			std::cin >> n;
			if (n < 0)
			{
				std::cout << "\n\tIncorrect number of nodes!";
				Sleep(1500);
				continue;
			}

			set obj; size++;
			arr.push_back(obj);
			for (int i = 0; i < n; i++) arr[size - 1].insert(lcg());
		}

		else if (n == 2)
		{
			if ((n = check_number_of_tree(size)) < 0) continue;
			std::cout << "\n- Values in tree: ";
			arr[n].print(); _getch();
		}

		else if (n == 3)
		{
			if ((n = check_number_of_tree(size)) < 0) continue;
			std::cout << "\n- Enter the number: ";
			std::cin >> num;
			if (!arr[n].insert(num))
			{
				std::cout << "\n\tThe entered value is already present!";
				Sleep(3000);
			}
		}

		else if (n == 4)
		{
			if ((n = check_number_of_tree(size)) < 0) continue;
			std::cout << "- Enter the number: ";
			std::cin >> num;
			if (!arr[n].erase(num))
			{
				std::cout << "\n\tThe entered value is already missing!";
				Sleep(3000);
			}
		}

		else if (n == 5)
		{
			//Откуда копируем
			if ((n = check_number_of_tree(size)) < 0) continue;
			arr.push_back(arr[n]); size++;
		}

		else if (n == 6)
		{
			// Откуда копируем
			if ((n = check_number_of_tree(size)) < 0) continue;

			//Куда копируем
			if ((m = check_number_of_tree(size)) < 0) continue;
			arr[m] = arr[n];
		}

		else if (n == 7)
		{
			if ((n = check_number_of_tree(size)) < 0) continue;
			arr.erase(arr.begin() + n); size--;
		}

		else if (n == 8) { arr.clear(); size = 0; }

		else if (n == 11) break;
	}

	arr.clear();
}
