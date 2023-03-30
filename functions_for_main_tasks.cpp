#include <chrono>
using namespace std::chrono;

void options_menu()
{
	system("cls");
	std::cout << "1. Create binary search tree filled with N nodes\n\n";
	std::cout << "2. Print the values stored in the tree\n\n";
	std::cout << "3. Find an element in a tree\n\n";
	std::cout << "4. Add number to tree\n\n";
	std::cout << "5. Remove number from tree\n\n";
	std::cout << "6. Create a new tree that is a copy of an existing tree\n\n";
	std::cout << "7. Assign to an already existing tree the values of another tree\n\n";
	std::cout << "8. Remove one tree from array\n\n";
	std::cout << "9. Remove all trees from array\n\n";
	std::cout << "10. Measure the average time of operations with a tree\n\n";
	std::cout << "11. Find intersection of sets\n\n";
	std::cout << "12. Find the set difference\n\n";
	std::cout << "13. Exit\n\n";

	std::cout << "Enter the number: ";
}

int check_number_of_tree(int size)
{
	int n = 0;
	std::cout << "\n- Enter the number of tree: ";
	std::cin >> n;
	if (n >= size || n < 0)
	{
		std::cout << "\n\tIncorrect number of tree!";
		Sleep(1500);
		return -1;
	}
	return n;
}

int lcg() 
{
	static int x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

void intersection_sets(const Node* node, const set& obj_1, set& obj_2)
{
	if (!node) return;
	if (obj_1.contains(node->data)) obj_2.insert(node->data);
	intersection_sets(node->left, obj_1, obj_2);
	intersection_sets(node->right, obj_1, obj_2);
}

void difference_sets(const Node* node, const set& obj_1, set& obj_2)
{
	if (!node) return;
	if (!obj_1.contains(node->data)) obj_2.insert(node->data);
	difference_sets(node->left, obj_1, obj_2);
	difference_sets(node->right, obj_1, obj_2);
}


void test_fill_set(const int numb, const int rep)
{
	int res = 0;
	for (int j = 0; j < rep; j++)
	{
		set test;
		auto start = high_resolution_clock::now();

		for (int i = 0; i < numb; i++) test.insert(lcg());

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		res += duration.count();
	}
	std::cout << "Time of FILL for " << numb << " for " << rep;
	std::cout << " times: " << (double)res / rep << " microseconds\n";
}

void test_contains_set(const int numb, const int rep)
{
	set test;
	for (int i = 0; i < numb; i++) test.insert(lcg());

	long double res = 0;
	for (int j = 0; j < rep; j++)
	{
		auto start = high_resolution_clock::now();

		test.contains(lcg());
		/*При такой проверке маловероятен шанс нахождения элемента, поэтому
		считаем, что мы рассматриваем худшее время поиска элемента во множестве*/

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		res += duration.count();
	}
	std::cout << "Time of IS_CONTAINS for " << numb << " for " << rep;
	std::cout << " times: " << (double)res / rep << " nanoseconds\n";
}

void test_insert_set(const int numb, const int rep)
{
	set test;
	for (int i = 0; i < numb; i++) test.insert(lcg());

	int res = 0;
	for (int j = 0; j < rep; j++)
	{
		set tmp = test;
		/*При 100000 элементах программа "застынет", т.к
		нужно 1000 раз копировать это дерево в новое дерево*/

		auto start = high_resolution_clock::now();

		tmp.insert(lcg());

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		res += duration.count();
	}
	std::cout << "Time of INSERT for " << numb << " for " << rep;
	std::cout << " times: " << (double)res / rep << " nanoseconds\n";
}

void test_erase_set(const int numb, const int rep)
{
	set test;
	for (int i = 0; i < numb; i++) test.insert(lcg());

	int res = 0;
	for (int j = 0; j < rep; j++)
	{
		set tmp = test;
		/*При 100000 элементах программа "застынет", т.к
		нужно 1000 раз копировать это дерево в новое дерево*/

		auto start = high_resolution_clock::now();

		tmp.erase(lcg());

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		res += duration.count();
	}
	std::cout << "Time of ERASE for " << numb << " for " << rep;
	std::cout << " times: " << (double)res / rep << " nanoseconds\n";
}


void test_fill_vector(const int numb, const int rep)
{
	int res = 0;
	for (int j = 0; j < rep; j++)
	{
		std::vector<int> test(numb);
		auto start = high_resolution_clock::now();

		for (int i = 0; i < numb; i++) test.push_back(lcg());

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		res += duration.count();
	}
	std::cout << "Time of FILL vector for " << numb << " for " << rep;
	std::cout << " times: " << (double)res / rep << " microseconds\n";
}

void test_contains_vector(const int numb, const int rep)
{
	std::vector<int> test(numb);
	for (int i = 0; i < numb; i++) test.push_back(lcg());

	long double res = 0;
	for (int j = 0; j < rep; j++)
	{
		auto start = high_resolution_clock::now();

		std::find(test.begin(), test.end(), lcg());
		/*При такой проверке маловероятен шанс нахождения элемента, поэтому
		считаем, что мы рассматриваем худшее время поиска элемента в векторе*/

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		res += duration.count();
	}
	std::cout << "Time of IS_CONTAINS vector for " << numb << " for " << rep;
	std::cout << " times: " << (double)res / rep << " nanoseconds\n";
}

void test_insert_vector(const int numb, const int rep)
{
	std::vector<int> test(numb);
	for (int i = 0; i < numb; i++) test.push_back(lcg());

	int res = 0;
	for (int j = 0; j < rep; j++)
	{
		std::vector<int> tmp = test;
		auto start = high_resolution_clock::now();

		tmp.push_back(lcg());

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		res += duration.count();
	}
	std::cout << "Time of INSERT vector for " << numb << " for " << rep;
	std::cout << " times: " << (double)res / rep << " nanoseconds\n";
}

void test_erase_vector(const int numb, const int rep)
{
	std::vector<int> test(numb);
	for (int i = 0; i < numb; i++) test.push_back(lcg());

	int res = 0;
	for (int j = 0; j < rep; j++)
	{
		std::vector<int> tmp = test;
		auto start = high_resolution_clock::now();

		tmp.erase(std::remove(tmp.begin(), tmp.end(), lcg()), tmp.end());

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		res += duration.count();
	}
	std::cout << "Time of ERASE vector for " << numb << " for " << rep;
	std::cout << " times: " << (double)res / rep << " nanoseconds\n";
}
