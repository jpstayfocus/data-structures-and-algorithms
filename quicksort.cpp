#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

int partition(std::vector<int>& arr, int p, int r)
{
	int pivot = arr[r];
	int i = p - 1;
	for (int j = p; j < r; ++j)
		if (arr[j] <= pivot)
		{
			++i;
			std::swap(arr[i], arr[j]);
		}
	std::swap(arr[i + 1], arr[r]);

	return i + 1;
}

int randomizedPartition(std::vector<int>& arr, int p, int r)
{
	int i = rand() % (r - p) + p;
	std::swap(arr[r], arr[i]);
	return partition(arr, p, r);

}

void quicksort(std::vector<int>& arr, int p, int r)
{
	if (p < r)
	{
		int q = randomizedPartition(arr, p, r);
		quicksort(arr, p, q - 1);
		quicksort(arr, q + 1, r);
	}
}



int partition2(std::vector<int>& arr, int start, int end)
{

	int pivot = arr[start];

	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (arr[i] <= pivot)
			count++;
	}

	// Giving pivot element its correct position
	int pivotIndex = start + count;
	std::swap(arr[pivotIndex], arr[start]);

	// Sorting left and right parts of the pivot element
	int i = start, j = end;

	while (i < pivotIndex && j > pivotIndex) {

		while (arr[i] <= pivot) {
			i++;
		}

		while (arr[j] > pivot) {
			j--;
		}

		if (i < pivotIndex && j > pivotIndex) {
			std::swap(arr[i++], arr[j--]);
		}
	}

	return pivotIndex;
}

void quicksort2(std::vector<int>& arr, int start, int end)
{
	if (start >= end)
		return;

	int p = partition2(arr, start, end);

	quicksort2(arr, start, p - 1);
	quicksort2(arr, p + 1, end);
}

template<typename Comparable>
void merge2(std::vector<Comparable>& a,
	std::vector<Comparable>& tmpArray, int leftPos, int rightPos, int rightEnd)
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;


	while (leftPos <= leftEnd && rightPos <= rightEnd)
		if (a[leftPos] <= a[rightPos])
			tmpArray[tmpPos++] = std::move(a[leftPos++]);
		else
			tmpArray[tmpPos++] = std::move(a[rightPos++]);

	while (leftPos <= leftEnd) // Copy rest of first half
		tmpArray[tmpPos++] = std::move(a[leftPos++]);

	while (rightPos <= rightEnd) // Copy rest of right half
		tmpArray[tmpPos++] = std::move(a[rightPos++]);

	// Copy tmpArray back
	for (int i = 0; i < numElements; ++i, --rightEnd)
		a[rightEnd] = std::move(tmpArray[rightEnd]);

}


template<typename Comparable>
void mergeSort2(std::vector<Comparable>& a,
	std::vector<Comparable>& tmpArray, int left, int right)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		mergeSort2(a, tmpArray, left, center);
		mergeSort2(a, tmpArray, center + 1, right);
		merge2(a, tmpArray, left, center + 1, right);
	}
}

template<typename Comparable>
void mergeSort2(std::vector<Comparable>& a)
{
	std::vector<Comparable> tmpArray(a.size());
	mergeSort2(a, tmpArray, 0, a.size() - 1);
}

template<typename T>
void shellSort(std::vector<T>& a, std::vector<int> gaps)
{
	for (int gap : gaps)
	{
		for (int i = gap; i < a.size(); ++i)
		{
			T tmp = std::move(a[i]);
			int j = i;
			for (; j >= gap && tmp < a[j - gap]; j -= gap)
				a[j] = std::move(a[j - gap]);
			a[j] = std::move(tmp);
		}
	}
}



int main()
{
	int n = 10000000;
	std::vector<int> arr(n);
	for (int i = 0; i < n; ++i)
	{
		arr[i] = rand() % n;
	}

	std::vector<int> hibbardGaps{};
	for (int i = n / 2; i /= 2; i > 1)
		hibbardGaps.push_back(i - 1);

	std::clock_t start;
	double duration;


	start = std::clock();
	std::sort(arr.begin(), arr.end());
	//shellSort(arr, hibbardGaps); 
	//quicksort(arr,0,arr.size()-1);
	//mergeSort2(arr);
	//quicksort2(arr, 0, arr.size() - 1);
	//for (auto elem : arr)
	//		std::cout << elem << std::endl;
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "printf: " << duration << '\n';
	
}

/*
int partition(std::vector<int>& arr, int p, int r)
{
	int pivot = arr[r];
	int i = p - 1;
	for (int j = p; j < r; ++j)
		if (arr[j] <= pivot)
		{
			++i;
			std::swap(arr[i], arr[j]);
		}
	std::swap(arr[i + 1], arr[r]);

	return i+1;
}

int randomizedPartition(std::vector<int>& arr, int p, int r)
{
	int i = rand() % (r-p) + p;
	std::swap(arr[r], arr[i]);
	return partition(arr, p, r);

}

void quicksort(std::vector<int>& arr, int p, int r)
{
	if (p < r)
	{
		int q = partition(arr, p, r);
		quicksort(arr, p, q - 1);
		quicksort(arr, q + 1, r);
	}
}


int partition2(std::vector<int>& arr, int start, int end)
{

	int pivot = arr[start];

	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (arr[i] <= pivot)
			count++;
	}

	// Giving pivot element its correct position
	int pivotIndex = start + count;
	std::swap(arr[pivotIndex], arr[start]);

	// Sorting left and right parts of the pivot element
	int i = start, j = end;

	while (i < pivotIndex && j > pivotIndex) {

		while (arr[i] <= pivot) {
			i++;
		}

		while (arr[j] > pivot) {
			j--;
		}

		if (i < pivotIndex && j > pivotIndex) {
			std::swap(arr[i++], arr[j--]);
		}
	}

	return pivotIndex;
}

void quicksort2(std::vector<int>& arr, int start, int end)
{
	if (start >= end)
		return;

	int p = partition2(arr, start, end);

	quicksort2(arr, start, p - 1);
	quicksort2(arr, p + 1, end);
}

template<typename Comparable>
void merge2(std::vector<Comparable>& a,
	std::vector<Comparable>& tmpArray, int leftPos, int rightPos, int rightEnd)
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;


	while (leftPos <= leftEnd && rightPos <= rightEnd)
		if (a[leftPos] <= a[rightPos])
			tmpArray[tmpPos++] = std::move(a[leftPos++]);
		else
			tmpArray[tmpPos++] = std::move(a[rightPos++]);

	while (leftPos <= leftEnd) // Copy rest of first half
		tmpArray[tmpPos++] = std::move(a[leftPos++]);

	while (rightPos <= rightEnd) // Copy rest of right half
		tmpArray[tmpPos++] = std::move(a[rightPos++]);

	// Copy tmpArray back
	for (int i = 0; i < numElements; ++i, --rightEnd)
		a[rightEnd] = std::move(tmpArray[rightEnd]);

}


template<typename Comparable>
void mergeSort2(std::vector<Comparable>& a,
	std::vector<Comparable>& tmpArray, int left, int right)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		mergeSort2(a, tmpArray, left, center);
		mergeSort2(a, tmpArray, center + 1, right);
		merge2(a, tmpArray, left, center + 1, right);
	}
}

template<typename Comparable>
void mergeSort2(std::vector<Comparable>& a)
{
	std::vector<Comparable> tmpArray(a.size());
	mergeSort2(a, tmpArray, 0, a.size() - 1);
}

template<typename T>
void shellSort(std::vector<T>& a, std::vector<int> gaps)
{
	for (int gap : gaps)
	{
		for (int i = gap; i < a.size(); ++i)
		{
			T tmp = std::move(a[i]);
			int j = i;
			for (; j >= gap && tmp < a[j - gap]; j -= gap)
				a[j] = std::move(a[j - gap]);
			a[j] = std::move(tmp);
		}
	}
}
*/

/*

int partition(std::vector<int>& arr, int p, int r)
{
	std::cout << "partitioning, p=" << p << " r= " << r << " pivot = " << arr[r] << std::endl;
	std::cout << "vector at start of partition:" << std::endl;
	for (auto& elem : arr)
		std::cout << elem << ", ";
	std::cout << std::endl;

	int pivot = arr[r];
	int i = p - 1;
	for (int j = p; j < r; ++j)
		if (arr[j] <= pivot)
		{
			++i;
			std::cout << "in loop, swapping " << arr[i] << " with " << arr[j] << std::endl;
			std::swap(arr[i], arr[j]);
		}
	std::cout << "done loop, swapping " << arr[i + 1] << " with " << arr[r] << std::endl;
	std::swap(arr[i + 1], arr[r]);

	std::cout << "DONE partitioning, vector at end of partition:" << std::endl;
	for (auto& elem : arr)
		std::cout << elem << ", ";
	std::cout << std::endl;

	return i+1;
}

void quicksort(std::vector<int>& arr, int p, int r)
{
	if (p < r)
	{
		int q = partition(arr, p, r);
		std::cout << "calling mergesort recursively on left half, p=" << p << " q-1=" << q - 1 << std::endl;
		quicksort(arr, p, q - 1);
		std::cout << "calling mergesort recursively on right half, p+1=" << q+1 << " r=" << r<< std::endl;
		quicksort(arr, q + 1, r);
	}
	else {
		std::cout << "p >= r, returning" << std::endl;
	}
}


*/
