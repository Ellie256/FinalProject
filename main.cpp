#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

void Swap(int a, int b, vector<int>& v); // send in indices that need to be swapped
void ShellSort(vector<int> &v);
void MergeSort(vector<int> &v);

// implement two non-quadratic sorts and compare performance of both
// Shell sort
// Merge sort
// 100,000 pieces of data

// note
int main() {
    vector<int> vec = {7, 4, 9, 3, 2, 8, 6, 5};

    // get current time
    std::chrono::high_resolution_clock::time_point start1 = std::chrono::high_resolution_clock::now();

    // get current time
    std::chrono::high_resolution_clock::time_point end1 = std::chrono::high_resolution_clock::now();

    // measure difference
    std::chrono::duration<double> elapsed1 = end1 - start1;
    cout << "Elapsed time to push in seconds: " << elapsed1.count() << endl;



    return 0;
}

void Swap(int a, int b, vector<int> &v) {
    int temp = v.at(a);
    v.at(a) = v.at(b);
    v.at(b) = temp;
}

void ShellSort(vector<int> &v) {

}

void MergeSort(vector<int> &v) {

}