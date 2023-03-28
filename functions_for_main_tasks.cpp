void options_menu()
{
	system("cls");
	std::cout << "1. Create binary search tree filled with N nodes\n\n";
	std::cout << "2. Print the values stored in the tree\n\n";
	std::cout << "3. Add number to tree\n\n";
	std::cout << "4. Remove number from tree\n\n";
	std::cout << "5. Create a new tree that is a copy of an existing tree\n\n";
	std::cout << "6. Assign to an already existing tree the values of another tree\n\n";
	std::cout << "7. Remove one tree from array\n\n";
	std::cout << "8. Remove all trees from array\n\n";
	std::cout << "9. Measure the average time of operations with a tree\n\n";
	std::cout << "10. Perform a task\n\n";
	std::cout << "11. Exit\n\n";

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

int lcg() {
	static int x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}
