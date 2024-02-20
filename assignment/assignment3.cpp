// Insertion Sort

/*
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

vector<int> insertionSort(vector<int>&& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = std::move(arr[i]);
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = std::move(arr[j]);
            j = j - 1;
        }
        arr[j + 1] = std::move(key);
    }
    return arr;
}

int main() {
    int N = 1000000;

    // Pre-sorted
    vector<int> arr1(N);
    for (int i = 0; i < N; i++) {
        arr1[i] = i + 1;
    }

    // Reverse-sorted
    vector<int> arr2(N);
    for (int i = N - 1; i >= 0; i--) {
        arr2[N - 1 - i] = i + 1;
    }

    // Rand%N
    vector<int> arr3(N);
    for (int i = 0; i < N; i++) {
        arr3[i] = rand() % N;
    }

    // Rand%10
    vector<int> arr4(N);
    for (int i = 0; i < N; i++) {
        arr4[i] = rand() % 10;
    }

    // Zeros
    vector<int> arr5(N);

    auto start = chrono::steady_clock::now();
    vector<int> sortedArr1 = insertionSort(std::move(arr1));
    auto end = chrono::steady_clock::now();
    auto diff1 = end - start;

    start = chrono::steady_clock::now();
    vector<int> sortedArr2 = insertionSort(std::move(arr2));
    end = chrono::steady_clock::now();
    auto diff2 = end - start;

    start = chrono::steady_clock::now();
    vector<int> sortedArr3 = insertionSort(std::move(arr3));
    end = chrono::steady_clock::now();
    auto diff3 = end - start;

    start = chrono::steady_clock::now();
    vector<int> sortedArr4 = insertionSort(std::move(arr4));
    end = chrono::steady_clock::now();
    auto diff4 = end - start;

    start = chrono::steady_clock::now();
    vector<int> sortedArr5 = insertionSort(std::move(arr5));
    end = chrono::steady_clock::now();
    auto diff5 = end - start;

    cout << "Pre-sorted: Time taken: " << chrono::duration <double> (diff1).count() << " s" << endl;
    cout << "Reverse-sorted: Time taken: " << chrono::duration <double> (diff2).count() << " s" << endl;
    cout << "Rand%N: Time taken: " << chrono::duration <double> (diff3).count() << " s" << endl;
    cout << "Rand%10: Time taken: " << chrono::duration <double> (diff4).count() << " s" << endl;
    cout << "Zeros: Time taken: " << chrono::duration <double> (diff5).count() << " s" << endl;


    return 0;
}

*/

// Shell Sort

/*

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

vector<int> shellSort(vector<int>&& arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = std::move(arr[i]);
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = std::move(arr[j - gap]);
            }
            arr[j] = std::move(temp);
        }
    }
    return arr;
}

int main() {
    int N = 1000000;

    // Pre-sorted
    vector<int> arr1(N);
    for (int i = 0; i < N; i++) {
        arr1[i] = i + 1;
    }

    // Reverse-sorted
    vector<int> arr2(N);
    for (int i = N - 1; i >= 0; i--) {
        arr2[N - 1 - i] = i + 1;
    }

    // Rand%N
    vector<int> arr3(N);
    for (int i = 0; i < N; i++) {
        arr3[i] = rand() % N;
    }

    // Rand%10
    vector<int> arr4(N);
    for (int i = 0; i < N; i++) {
        arr4[i] = rand() % 10;
    }

    // Zeros
    vector<int> arr5(N);

    auto start = chrono::steady_clock::now();
    vector<int> sortedArr1 = shellSort(std::move(arr1));
    auto end = chrono::steady_clock::now();
    auto diff1 = end - start;

    start = chrono::steady_clock::now();
    vector<int> sortedArr2 = shellSort(std::move(arr2));
    end = chrono::steady_clock::now();
    auto diff2 = end - start;

    start = chrono::steady_clock::now();
    vector<int> sortedArr3 = shellSort(std::move(arr3));
    end = chrono::steady_clock::now();
    auto diff3 = end - start;

    start = chrono::steady_clock::now();
    vector<int> sortedArr4 = shellSort(std::move(arr4));
    end = chrono::steady_clock::now();
    auto diff4 = end - start;

    start = chrono::steady_clock::now();
    vector<int> sortedArr5 = shellSort(std::move(arr5));
    end = chrono::steady_clock::now();
    auto diff5 = end - start;

    cout << "Pre-sorted: Time taken: " << chrono::duration <double> (diff1).count() << " s" << endl;
    cout << "Reverse-sorted: Time taken: " << chrono::duration <double> (diff2).count() << " s" << endl;
    cout << "Rand%N: Time taken: " << chrono::duration <double> (diff3).count() << " s" << endl;
    cout << "Rand%10: Time taken: " << chrono::duration <double> (diff4).count() << " s" << endl;
    cout << "Zeros: Time taken: " << chrono::duration <double> (diff5).count() << " s" << endl;

    return 0;
}

*/

// Merge Sort

/*

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

void merge(vector<int>& arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);
    for (i = 0; i < n1; i++)
        L[i] = std::move(arr[l + i]);
    for (j = 0; j < n2; j++)
        R[j] = std::move(arr[m + 1 + j]);
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = std::move(L[i]);
            i++;
        }
        else {
            arr[k] = std::move(R[j]);
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = std::move(L[i]);
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = std::move(R[j]);
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main() {
    int N = 100;

    // Pre-sorted
    vector<int> arr1(N);
    for (int i = 0; i < N; i++) {
        arr1[i] = i + 1;
    }

    // Reverse-sorted
    vector<int> arr2(N);
    for (int i = N - 1; i >= 0; i--) {
        arr2[N - 1 - i] = i + 1;
    }

    // Rand%N
    vector<int> arr3(N);
    for (int i = 0; i < N; i++) {
        arr3[i] = rand() % N;
    }

    // Rand%10
    vector<int> arr4(N);
    for (int i = 0; i < N; i++) {
        arr4[i] = rand() % 10;
    }

    // Zeros
    vector<int> arr5(N);

    auto start = chrono::steady_clock::now();
    mergeSort(arr1, 0, N - 1);
    auto end = chrono::steady_clock::now();
    auto diff1 = end - start;

    start = chrono::steady_clock::now();
    mergeSort(arr2, 0, N - 1);
    end = chrono::steady_clock::now();
    auto diff2 = end - start;

    start = chrono::steady_clock::now();
    mergeSort(arr3, 0, N - 1);
    end = chrono::steady_clock::now();
    auto diff3 = end - start;

    start = chrono::steady_clock::now();
    mergeSort(arr4, 0, N - 1);
    end = chrono::steady_clock::now();
    auto diff4 = end - start;

    start = chrono::steady_clock::now();
    mergeSort(arr5, 0, N - 1);
    end = chrono::steady_clock::now();
    auto diff5 = end - start;
    
    cout << "Pre-sorted: Time taken: " << chrono::duration <double> (diff1).count() << " s" << endl;
    cout << "Reverse-sorted: Time taken: " << chrono::duration <double> (diff2).count() << " s" << endl;
    cout << "Rand%N: Time taken: " << chrono::duration <double> (diff3).count() << " s" << endl;
    cout << "Rand%10: Time taken: " << chrono::duration <double> (diff4).count() << " s" << endl;
    cout << "Zeros: Time taken: " << chrono::duration <double> (diff5).count() << " s" << endl;

    return 0;

}

*/

// Radix Sort

/*

#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void countingSort(vector<int>& arr, int exp)
{
  int n = arr.size();
  vector<int> output(n);
  vector<int> count(10, 0);
  for (int i = 0; i < n; i++)
      count[(arr[i] / exp) % 10]++;
  for (int i = 1; i < 10; i++)
      count[i] += count[i - 1];
  for (int i = n - 1; i >= 0; i--) {
      output[count[(arr[i] / exp) % 10] - 1] = arr[i];
      count[(arr[i] / exp) % 10]--;
  }
  for (int i = 0; i < n; i++)
      arr[i] = output[i];
}

void radixSort(vector<int>& arr)
{
  int n = arr.size();
  int max_val = *max_element(arr.begin(), arr.end());
  for (int exp = 1; max_val / exp > 0; exp *= 10)
      countingSort(arr, exp);
}

int main() {
    int N = 1000000;

    // Pre-sorted
    vector<int> arr1(N);
    for (int i = 0; i < N; i++) {
        arr1[i] = i + 1;
    }

    // Reverse-sorted
    vector<int> arr2(N);
    for (int i = N - 1; i >= 0; i--) {
        arr2[N - 1 - i] = i + 1;
    }

    // Rand%N
    vector<int> arr3(N);
    for (int i = 0; i < N; i++) {
        arr3[i] = rand() % N;
    }

    // Rand%10
    vector<int> arr4(N);
    for (int i = 0; i < N; i++) {
        arr4[i] = rand() % 10;
    }

    // Zeros
    vector<int> arr5(N);

    auto start = chrono::steady_clock::now();
    radixSort(arr1);
    auto end = chrono::steady_clock::now();
    auto diff1 = end - start;

    start = chrono::steady_clock::now();
    radixSort(arr2);
    end = chrono::steady_clock::now();
    auto diff2 = end - start;

    start = chrono::steady_clock::now();
    radixSort(arr3);
    end = chrono::steady_clock::now();
    auto diff3 = end - start;

    start = chrono::steady_clock::now();
    radixSort(arr4);
    end = chrono::steady_clock::now();
    auto diff4 = end - start;

    start = chrono::steady_clock::now();
    radixSort(arr5);
    end = chrono::steady_clock::now();
    auto diff5 = end - start;
    
    
    cout << "Pre-sorted: Time taken: " << chrono::duration <double> (diff1).count() << " s" << endl;
    cout << "Reverse-sorted: Time taken: " << chrono::duration <double> (diff2).count() << " s" << endl;
    cout << "Rand%N: Time taken: " << chrono::duration <double> (diff3).count() << " s" << endl;
    cout << "Rand%10: Time taken: " << chrono::duration <double> (diff4).count() << " s" << endl;
    cout << "Zeros: Time taken: " << chrono::duration <double> (diff5).count() << " s" << endl;

    return 0;

}

*/

// Quick Sort

/*

#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int>& arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high)
{
  if (low < high) {
      int pi = partition(arr, low, high);
      quickSort(arr, low, pi - 1);
      quickSort(arr, pi + 1, high);
  }
}

int main() {
    int N = 1000000;

    // Pre-sorted
    vector<int> arr1(N);
    for (int i = 0; i < N; i++) {
        arr1[i] = i + 1;
    }

    // Reverse-sorted
    vector<int> arr2(N);
    for (int i = N - 1; i >= 0; i--) {
        arr2[N - 1 - i] = i + 1;
    }

    // Rand%N
    vector<int> arr3(N);
    for (int i = 0; i < N; i++) {
        arr3[i] = rand() % N;
    }

    // Rand%10
    vector<int> arr4(N);
    for (int i = 0; i < N; i++) {
        arr4[i] = rand() % 10;
    }

    // Zeros
    vector<int> arr5(N);

    auto start = chrono::steady_clock::now();
    quickSort(arr1, 0, N - 1);
    auto end = chrono::steady_clock::now();
    auto diff1 = end - start;

    start = chrono::steady_clock::now();
    quickSort(arr2, 0, N - 1);
    end = chrono::steady_clock::now();
    auto diff2 = end - start;

    start = chrono::steady_clock::now();
    quickSort(arr3, 0, N - 1);
    end = chrono::steady_clock::now();
    auto diff3 = end - start;

    start = chrono::steady_clock::now();
    quickSort(arr4, 0, N - 1);
    end = chrono::steady_clock::now();
    auto diff4 = end - start;

    start = chrono::steady_clock::now();
    quickSort(arr5, 0, N - 1);
    end = chrono::steady_clock::now();
    auto diff5 = end - start;

    
    cout << "Pre-sorted: Time taken: " << chrono::duration <double> (diff1).count() << " s" << endl;
    cout << "Reverse-sorted: Time taken: " << chrono::duration <double> (diff2).count() << " s" << endl;
    cout << "Rand%N: Time taken: " << chrono::duration <double> (diff3).count() << " s" << endl;
    cout << "Rand%10: Time taken: " << chrono::duration <double> (diff4).count() << " s" << endl;
    cout << "Zeros: Time taken: " << chrono::duration <double> (diff5).count() << " s" << endl;

    return 0;

}

/*

// Std::Sort

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

void stdSort(std::vector<int>& vec) {
    std::sort(vec.begin(), vec.end());
}

int main() {
    int N = 1000000;

    // Pre-sorted
    std::vector<int> arr1(N);
    for (int i = 0; i < N; i++) {
        arr1[i] = i + 1;
    }

    // Reverse-sorted
    std::vector<int> arr2(N);
    for (int i = N - 1; i >= 0; i--) {
        arr2[N - 1 - i] = i + 1;
    }

    // Rand%N
    std::vector<int> arr3(N);
    for (int i = 0; i < N; i++) {
        arr3[i] = rand() % N;
    }

    // Rand%10
    std::vector<int> arr4(N);
    for (int i = 0; i < N; i++) {
        arr4[i] = rand() % 10;
    }

    // Zeros
    std::vector<int> arr5(N);

    auto start = std::chrono::steady_clock::now();
    std::sort(arr1.begin(), arr1.end());
    auto end = std::chrono::steady_clock::now();
    auto diff1 = end - start;

    start = std::chrono::steady_clock::now();
    std::sort(arr2.begin(), arr2.end());
    end = std::chrono::steady_clock::now();
    auto diff2 = end - start;

    start = std::chrono::steady_clock::now();
    std::sort(arr3.begin(), arr3.end());
    end = std::chrono::steady_clock::now();
    auto diff3 = end - start;

    start = std::chrono::steady_clock::now();
    std::sort(arr4.begin(), arr4.end());
    end = std::chrono::steady_clock::now();
    auto diff4 = end - start;

    start = std::chrono::steady_clock::now();
    std::sort(arr5.begin(), arr5.end());
    end = std::chrono::steady_clock::now();
    auto diff5 = end - start;
    
    
    std::cout << "Pre-sorted: Time taken: " << std::chrono::duration <double> (diff1).count() << " s" << std::endl;
    std::cout << "Reverse-sorted: Time taken: " << std::chrono::duration <double> (diff2).count() << " s" << std::endl;
    std::cout << "Rand%N: Time taken: " << std::chrono::duration <double> (diff3).count() << " s" << std::endl;
    std::cout << "Rand%10: Time taken: " << std::chrono::duration <double> (diff4).count() << " s" << std::endl;
    std::cout << "Zeros: Time taken: " << std::chrono::duration <double> (diff5).count() << " s" << std::endl;

    return 0;
}

*/

