#include <iostream>

#include "quicksort.h"

int main(int argc, char** argv) {
    int array[] = {8, 3, 5, 9, 19, 4, 1, 11, 28, 15};
    std::cout << "befor sort: " << std::endl;
    for (auto elem : array) {
        std::cout << elem << '\t';
    }
    std::cout << std::endl;

    quicksort(array, 0, 9);

    std::cout << "after sort: " << std::endl;
    for (auto elem : array) {
        std::cout << elem << '\t';
    }
    std::cout << std::endl;
}
