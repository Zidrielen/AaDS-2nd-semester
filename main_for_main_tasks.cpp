#include <iostream>
#include <conio.h>
#include <windows.h>

#include <vector>

#include "class_binary_tree.h"
#include "functions.h"

int main()
{
	//Вектор, хранящий объекты типа set
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

			std::cout << "\n- Enter the number in tree: ";
			std::cin >> m;

			if (arr[n].contains(m)) std::cout << "\nThe entered element is in the tree";
			else std::cout << "\nThe entered element is not in the tree";
			_getch();
		}

		else if (n == 4)
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

		else if (n == 5)
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

		else if (n == 6)
		{
			//Откуда копируем
			if ((n = check_number_of_tree(size)) < 0) continue;
			arr.push_back(arr[n]); size++;
		}

		else if (n == 7)
		{
			// Откуда копируем
			if ((n = check_number_of_tree(size)) < 0) continue;
			//Куда копируем
			if ((m = check_number_of_tree(size)) < 0) continue;
			arr[m] = arr[n];
		}

		else if (n == 8)
		{
			if ((n = check_number_of_tree(size)) < 0) continue;
			arr.erase(arr.begin() + n); size--;
		}

		else if (n == 9) { arr.clear(); size = 0; }

		else if (n == 10)
		{
			system("cls");
			std::cout << "MY SET CLASS:\n\n";

			test_fill_set(1000, 100);
			test_fill_set(10000, 100);
			test_fill_set(100000, 100);

			std::cout << std::endl;

			test_contains_set(1000, 1000);
			test_contains_set(10000, 1000);
			test_contains_set(100000, 1000);

			std::cout << std::endl;

			test_insert_set(1000, 1000);
			test_insert_set(10000, 1000);
			test_insert_set(100000, 1000);

			std::cout << std::endl;

			test_erase_set(1000, 1000);
			test_erase_set(10000, 1000);
			test_erase_set(100000, 1000);

			std::cout << "\nVECTOR CLASS:\n\n";

			test_fill_vector(1000, 100);
			test_fill_vector(10000, 100);
			test_fill_vector(100000, 100);

			std::cout << std::endl;

			test_contains_vector(1000, 1000);
			test_contains_vector(10000, 1000);
			test_contains_vector(100000, 1000);

			std::cout << std::endl;

			test_insert_vector(1000, 1000);
			test_insert_vector(10000, 1000);
			test_insert_vector(100000, 1000);

			std::cout << std::endl;

			test_erase_vector(1000, 1000);
			test_erase_vector(10000, 1000);
			test_erase_vector(100000, 1000);

			std::cout << "\nTime counting is finished, press any key";
			_getch();
		}

		else if (n == 11)
		{
			//Множество А
			if ((n = check_number_of_tree(size)) < 0) continue;
			//Множество В
			if ((m = check_number_of_tree(size)) < 0) continue;

			set obj; size++;
			arr.push_back(obj);
			intersection_sets(arr[n].get_root(), arr[m], arr[size-1]);

			std::cout << "\nThe set at number " << size-1;
			std::cout << ", which is the intersection of other sets, is created";
			_getch();
		}

		else if (n == 12)
		{
			//Множество А
			if ((n = check_number_of_tree(size)) < 0) continue;
			//Множество В
			if ((m = check_number_of_tree(size)) < 0) continue;

			set obj; size++;
			arr.push_back(obj);
			difference_sets(arr[n].get_root(), arr[m], arr[size - 1]);

			std::cout << "\nThe set at number " << size - 1;
			std::cout << ", which is the difference of other sets, has been created";
			_getch();
		}

		else if (n == 13) break;
	}

	arr.clear();
}
