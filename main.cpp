#include <iostream>
#include <vector>
#include <chrono>
#include <math.h>
using namespace std;

void Swap(int a, int b, vector<int>& v); // send in indices that need to be swapped
void ShellSort(vector<int> &v);
void MergeSort(vector<int> &v);

// implement two non-quadratic sorts and compare performance of both
// Shell sort
// Merge sort
// 100,000 pieces of data

// changed
int main() {
    vector<int> v = {7, 4, 9, 3, 2, 8, 6, 5, 4, 7, 11, 2, 3, 9};
    // vector<int> v = {12, 34, 54, 2, 3};
    cout << "[ ";
    for(int i = 0; i < v.size(); i++) {
        cout << v.at(i) << ", ";
    }
    cout << "]" << endl;

    /*
    // get current time
    std::chrono::high_resolution_clock::time_point start1 = std::chrono::high_resolution_clock::now();

    // get current time
    std::chrono::high_resolution_clock::time_point end1 = std::chrono::high_resolution_clock::now();

    // measure difference
    std::chrono::duration<double> elapsed1 = end1 - start1;
    cout << "Elapsed time to push in seconds: " << elapsed1.count() << endl;
    */

    ShellSort(v);


    return 0;
}

void Swap(int a, int b, vector<int> &v) {
    int temp = v.at(a);
    v.at(a) = v.at(b);
    v.at(b) = temp;
}

void ShellSort(vector<int> &v) {
    int pass = 1;
    int k = (int) (log(v.size()) / log(2));
    int gap = pow(2, k) - 1;
    while(gap > 0) {
        for(int i = 0; i < v.size() - gap; i++) {
            if(v.at(i) > v.at(i + gap)) {
                Swap(i, i+gap, v);

                for(int j = i; j >= gap; j -= gap) {
                    if(v.at(j) < v.at(j - gap)) {
                        Swap(j, j-gap, v);
                    }
                    else {
                        break;
                    }
                }
            }
        }
        cout << "Gap " << gap << ": [ ";
        for(int i = 0; i < v.size(); i++) {
            cout << v.at(i) << ", ";
        }
        cout << "]" << endl;
        pass++;
        k--;
        gap = pow(2, k) - 1;
    }
}

void MergeSort(vector<int> &v) {

}