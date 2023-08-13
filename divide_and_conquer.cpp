#include <iostream>
#include <vector>
#include <ctime>

template<typename T>
void merge(std::vector<T>& a, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;

	std::vector<T> left(n1 + 1);
	std::vector<T> right(n2 + 1);

	for (int i = 0; i < n1; ++i)
		left[i] = std::move(a[p + i]);
	for (int j = 0; j < n2; ++j)
		right[j] = std::move(a[q + j + 1]);

	left[n1] = 999999999;
	right[n2] = 999999999;
	int i = 0;
	int j = 0;

	for (int k = p; k <= r; ++k)
	{
		if (left[i] <= right[j])
			a[k] = std::move(left[i++]);
		else
			a[k] = std::move(right[j++]);

	}

}



template<typename T>
void mergeSort(std::vector<T>& a, int p, int r)
{
	//std::cout << "p=" << p << " r = " << r << std::endl;

	if (p < r)
	{
		int q = (p + r) / 2; // divide step
		mergeSort(a, p, q); 
		mergeSort(a, q + 1, r);
		//std::cout << "merging, p=" << p << " q = " << q << " r = " << r << std::endl;
		merge(a, p, q, r);

	}
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

	

	
	int sz = 10000000;
	std::vector<int> a(sz);
	for (int i = 0; i < sz; ++i)
		a[i] = sz - i;

	std::vector<int> hibbardGaps{};
	for (int i = sz / 2; i /= 2; i > 1)
		hibbardGaps.push_back(i - 1);
	
	std::clock_t start;
	double duration;

	start = std::clock();
	//mergeSort2(a);
	//mergeSort(a, 0, a.size()-1);
	shellSort(a, hibbardGaps);
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	
	std::cout << "printf: " << duration << '\n';
	
}

/*


*/


/*

*/



/*




*/
