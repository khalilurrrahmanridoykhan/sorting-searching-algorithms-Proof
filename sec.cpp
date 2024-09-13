#include <iostream>
#include <chrono>
using namespace std;

void sortingArray()
{
    int arr[5];
    auto start = std::chrono::high_resolution_clock::now();
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    // operation to be timed ...

    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";
}