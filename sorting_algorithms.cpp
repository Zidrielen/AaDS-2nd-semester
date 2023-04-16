#include <chrono>
using namespace std::chrono;

struct stats
{
	size_t comparison_count = 0;
	size_t copy_count = 0;
	int time_count = 0;
};

//Перестановка элементов (1 вызов этой функции - это плюс 3 к общему числу копирований элементов)
void swap(int& a, int& b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

//Пузырьковая сортировка в немного оптимизированном виде
stats bubble_sort(std::vector<int>& arr)
{
	stats data;

	auto start = high_resolution_clock::now();
	for (int i = 0; i < arr.size() - 1; i++)
	{
		bool flag = true;
		for (int j = 0; j < arr.size() - i - 1; j++)
		{
			if (arr[j] > arr[j+1])
			{
				flag = false;
				swap(arr[j], arr[j+1]);
				data.copy_count += 3;
			}
			data.comparison_count++;
		}
		if (flag) break;
	}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	data.time_count = (int)duration.count();
	return data;
}

//Функция для быстрой сортировки (главная часть сортировки)
int hoar_sort(std::vector<int>& arr, int left, int right, stats& data)
{
	int pivot = arr[(left + right)/2];

	while (left <= right)
	{
		while (arr[left] < pivot)
		{
			left++;
			data.comparison_count++;
		}
		data.comparison_count++;

		while (arr[right] > pivot)
		{
			right--;
			data.comparison_count++;
		}
		data.comparison_count++;

		if (left <= right)
		{
			swap(arr[left], arr[right]);
			data.copy_count += 3;
			left++;
			right--;
		}
	}
	return left;
}

//Функция для быстрой сортировки (посредник между главной частью и вызываемой из вне функции)
void q_sort(std::vector<int>& arr, int start, int end, stats& data)
{
	if (start >= end) return;
	int start_right = hoar_sort(arr, start, end, data);

	q_sort(arr, start, start_right-1, data);
	q_sort(arr, start_right, end, data);
}

//Быстрая сортировка
stats quick_sort(std::vector<int>& arr)
{
	stats data;

	auto start = high_resolution_clock::now();
	q_sort(arr, 0, arr.size()-1, data);

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	data.time_count = (int)duration.count();
	return data;
}

//Функция для сортировки кучей (главная часть сортировки)
void siftDown(std::vector<int>& arr, int root, int bottom, stats& data)
{
	int maxChild;
	int done = 0;

	while ((root * 2 <= bottom) && (!done))
	{
		if (root * 2 == bottom)
			maxChild = root * 2;

		else if (arr[root * 2] > arr[root * 2 + 1])
			maxChild = root * 2;
		else
			maxChild = root * 2 + 1;

		if (arr[root] < arr[maxChild])
		{
			swap(arr[root], arr[maxChild]);
			data.copy_count += 3;
			root = maxChild;
		}
		else
			done = 1;
		data.comparison_count++;
	}
}

//Пирамидная сортировка (сортировка кучей)
stats heap_sort(std::vector<int>& arr)
{
	stats data;
	int size = arr.size();

	auto start = high_resolution_clock::now();
	for (int i = (size / 2); i >= 0; i--)
		siftDown(arr, i, size - 1, data);
	
	for (int i = size - 1; i >= 1; i--)
	{
		swap(arr[0], arr[i]);
		data.copy_count += 3;
		siftDown(arr, 0, i - 1, data);
	}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	data.time_count = (int)duration.count();
	return data;
}
