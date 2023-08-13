// heapSort

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }

    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapsort(int arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n-1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    int arr[100000];

    srand(time(0));

    // Initialize array with random values
    for (int i = 0; i < 100000; i++) {
        arr[i] = rand() % 1000000;
    }

    // Sort array using heapsort
    heapsort(arr, 100000);

    // Print sorted array
    for (int i = 0; i < 100000; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}


// Tree Sort AVL

#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;

// Definition of AVL tree node
class Node {
public:
    int data;
    int height;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

// Helper functions...

// Helper function to insert a node into AVL tree
Node* insert(Node* root, int val) {
    // Implementation...
}

// Tree sort function
void treeSort(int arr[], int n) {
    // Implementation...
}

int main() {
    // Generate random array of size 100000
    const int n = 100000;
    int arr[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }

    // Sort the array using Tree Sort algorithm with AVL tree
    auto start = chrono::high_resolution_clock::now();
    treeSort(arr, n);
    auto end = chrono::high_resolution_clock::now();

    // Print the sorted array and execution time
    cout << "Sorted array:" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Execution time: " << duration.count() << " ms" << endl;

    return 0;
}

// Treesort BST

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

void insert(Node* &root, int val) {
    if (root == NULL) {
        root = new Node(val);
        return;
    }

    if (val < root->data) {
        insert(root->left, val);
    } else {
        insert(root->right, val);
    }
}

void inorderTraversal(Node* root, int arr[], int &i) {
    if (root == NULL) {
        return;
    }

    inorderTraversal(root->left, arr, i);
    arr[i++] = root->data;
    inorderTraversal(root->right, arr, i);
}

void treesort(int arr[], int n) {
    Node* root = NULL;

    // Build BST from array
    for (int i = 0; i < n; i++) {
        insert(root, arr[i]);
    }

    // Inorder traversal to get sorted array
    int i = 0;
    inorderTraversal(root, arr, i);
}

int main() {
    int arr[100000];

    srand(time(0));

    // Initialize array with random values
    for (int i = 0; i < 100000; i++) {
        arr[i] = rand() % 1000000;
    }
    // Sort array using treesort
    treesort(arr, 100000);

    // Print sorted array
    for (int i = 0; i < 100000; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}


/*

 Part 2c
Heap sort, Tree sort, Quick sort, and Merge sort are all comparison-based sorting algorithms.
They have different time and space complexity characteristics that can make them more or less suitable for different types of input data.

Heap sort has a time complexity of O(n log n) in the worst case and is an in-place sorting algorithm, which means it has a space complexity of O(1). 
Heap sort is particularly useful for large data sets or when the input data is presented in the form of a stream.

Tree sort has a time complexity of O(n log n) in the worst case and a space complexity of O(n) because it requires
additional memory to store the binary search tree. Tree sort can be particularly useful when the input data is 
dynamic and can be inserted into the binary search tree incrementally.

Quick sort has a time complexity of O(n log n) in the average case and O(n^2) in the worst case, 
but it can be optimized to have a worst-case time complexity of O(n log n) with careful selection of the pivot element. 
Quick sort is an in-place sorting algorithm, which means it has a space complexity of O(1). Quick sort is particularly 
useful for large data sets and when the input data is not distributed uniformly.

Merge sort has a time complexity of O(n log n) in the worst case and requires additional memory to merge the subarrays, 
which gives it a space complexity of O(n). Merge sort is particularly useful for large data sets and when the input data is distributed uniformly.


*/
