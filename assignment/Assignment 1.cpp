
/* 
* This program  C++ program will put the emphasisis on class,
* big 5 understanding, and it will also show the performance effect of vector
* comapared to built-in array, and it has four parts
*/ 

/* Delta time for LargeType is displayed for 1000 because 50000 takes so much time : 0.0356345s */
/* Delta time for LargeTypeRaw is displayed for 1000 because 50000 takes so much time : 0.0226291s */
/* Hints given in class has helped me to complete the assignment since I wrote down 
every single code line and for the standard library, I copy this code on this
follwing website and modify it: https://en.cppreference.com/w/cpp/chrono
*/



#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>


/*
1- The class is defined as a template class, with a single template parameter T. This means 
that the class can be instantiated with any type, and the vector 'data' will hold 
elements of that type.

2- The constructor takes an optional argument 'size', which is used to initialize the vector
'data' with that many elements. If no argument is provided, the vector is initialized 
with 10 elements by default.

The class has a public method 'getSize()' which returns the size of the vector 'data'.

The class also overloads the 'operator<' function. This allows two LargeType objects 
to be compared using the '<' operator, and the comparison is based on the size of 
their 'data' vectors.

The class has a private member variable 'data', which is a vector of type T.



*/
template <typename T>
class LargeType {
public:
    explicit LargeType(int size = 10) : data(size) {}
    int getSize() const { return data.size(); }
    bool operator<(const LargeType& rhs) const { return getSize() < rhs.getSize(); }

private:
    std::vector<T> data;
};



template <typename T>
class LargeTypeRaw {
public:
    LargeTypeRaw(int size = 10) : data(new T[size]), size(size) {}

    // copy constructor 
    LargeTypeRaw(const LargeTypeRaw& other) : data(new T[other.size]), size(other.size) {
        std::copy(other.data, other.data + size, data);
    }

    // move constructor 
    LargeTypeRaw(LargeTypeRaw&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    // copy assignment operator 
    LargeTypeRaw& operator=(const LargeTypeRaw& other) {
        if (this != &other) {
            T* newData = new T[other.size];
            std::copy(other.data, other.data + other.size, newData);
            delete[] data;
            data = newData;
            size = other.size;
        }
        return *this;
    }

    // move assignement operator
    LargeTypeRaw& operator=(LargeTypeRaw&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // destructor 
    ~LargeTypeRaw() { delete[] data; }
    int getSize() const { return size; }
    bool operator<(const LargeTypeRaw& rhs) const { return getSize() < rhs.getSize(); }

private:
    T* data;
    int size;
};

/*

The function is defined as a template function, with a single template parameter T. 
This means that the function can be called with a vector of any type, and it will sort 
the elements of that vector using the insertion sort algorithm.

The function takes a single argument 'vec', which is a reference to a vector of type T.

The function uses the insertion sort algorithm to sort the elements of the vector 'vec' 
in ascending order, based on the size of each LargeType instance's data field.

The function assumes that the vector 'vec' contains LargeType objects with data of different sizes.

The function is implemented using the pseudocode provided in the problem statement,
but with the necessary adjustments for the fact that array indices start at 0 in C++.


*/

template <typename T>
void insertionSort(std::vector<T>& vec) {
    for (int i = 1; i < vec.size(); i++) {
        T key = vec[i];
        int j = i - 1;
        while (j >= 0 && key < vec[j]) {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = key;
    }
}

int main() {
    std::vector<LargeType<int>> vec;
    for (int i = 0; i < 1000; i++) {
        int size = rand() % 10;
        vec.push_back(LargeType<int>{size});
    }
    std::cout << "The sorting numbers" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    insertionSort(vec);
    auto end = std::chrono::high_resolution_clock::now();
    
    for (int i = 1; i < vec.size(); i++) {
        std::cout << vec[i].getSize() << std::endl;
    }
    std::chrono::duration<double> diff = end - start;
    std::cout << diff.count() << "s" << std::endl;
}

