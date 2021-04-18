#include <iostream>
#include <vector>
#include <chrono>
#include <math.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include "Song.h"
using namespace std;

// jump search and fibonacci search
// Relearn Template Functions

void Swap(int a, int b, vector<int>& v); // send in indices that need to be swapped
void ShellSort(vector<int> &v, int option);
void MergeSort(vector<int> &v, int left, int right, int option);
void Merge(vector<int> &v, int left, int mid, int right, int option);
int JumpSearch(vector<int> &v, int search, int option); // returns the index, returns -1 if not found
int FibonacciSearch(vector<int> &v, int search, int option); // returns the index, returns -1 if not found
void LoadData(string &path, vector<Song> &one, vector<Song> &two);

int main() {
    /*
    // vector<int> v = {7, 4, 9, 3, 2, 8, 6, 5, 4, 7, 11, 2, 3, 9};
    // vector<int> v = {12, 34, 54, 2, 3};
    vector<int> v = {6, 5, 22, 10, 9, 1};
    cout << "[ ";
    for(int i = 0; i < v.size(); i++) {
        cout << v.at(i) << ", ";
    }
    cout << "]" << endl;


    // get current time
    std::chrono::high_resolution_clock::time_point start1 = std::chrono::high_resolution_clock::now();

    // get current time
    std::chrono::high_resolution_clock::time_point end1 = std::chrono::high_resolution_clock::now();

    // measure difference
    std::chrono::duration<double> elapsed1 = end1 - start1;
    cout << "Elapsed time to push in seconds: " << elapsed1.count() << endl;


    // ShellSort(v);
    // MergeSort(v, 0, v.size() - 1);
    cout << "[ ";
    for(int i = 0; i < v.size(); i++) {
        cout << v.at(i) << ", ";
    }
    cout << "]" << endl;


    vector<Song> shell;
    vector<Song> merge;
    string path = "example.csv";
    LoadData(path, shell, merge);

    for(int i = 0; i < shell.size(); i++) {
        cout << "name: " << shell.at(i).GetName() << endl;
        cout << "artist: " << shell.at(i).GetArtist() << endl;
        cout << "popularity: " << shell.at(i).GetPopularity() << endl;
        cout << "danceability: " << shell.at(i).GetDanceability() << endl;
        cout << "duration: " << shell.at(i).GetDuration() << endl;
        cout << "tempo: " << shell.at(i).GetTempo() << endl;
        cout << "loudness: " << shell.at(i).GetLoudness() << endl;
        cout << "year: " << shell.at(i).GetYear() << endl;
        cout << endl;
    }
    */

    //                  0, 1, 2, 3, 4, 5, 6, 7,  8,  9,  10, 11, 12,  13,  14,  15,  16
    vector<int> arr = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 700 };
    int search = 4;
    cout << "Index: " << FibonacciSearch(arr, search, 0);

    return 0;
}

void Swap(int a, int b, vector<int> &v) {
    int temp = v.at(a);
    v.at(a) = v.at(b);
    v.at(b) = temp;
}

// function inspired by powerpoint, "Graphs-2", slide 34, by Amanpreet Kapoor
void ShellSort(vector<int> &v, int option) {
    // Initialize k to be the largest so that gap is not larger than the size of the vector
    int k = (int) (log(v.size()) / log(2));
    // The gap function is based on Hibbard's sequence
    int gap = pow(2, k) - 1;

    // The gap will decrease until it is 1
    while(gap > 0) {

        // Compare elements that are a gap away from each otehr
        for(int i = 0; i < v.size() - gap; i++) {
            if(v.at(i) > v.at(i + gap)) {
                Swap(i, i+gap, v);

                // If two elements are swapped, then check previous elements that are gaps away
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

        // Update the gap
        k--;
        gap = pow(2, k) - 1;
    }
}

// function inspired by powerpoint, "Graphs-2", slide 49, by Amanpreet Kapoor
void MergeSort(vector<int> &v, int left, int right, int option) {
    if (left < right) {
        // m is the point where the array is divided into two subarrays
        int mid = left + (right - left) / 2;

        MergeSort(v, left, mid, option);
        MergeSort(v, mid + 1, right, option);

        // Merge the sorted subarrays
        Merge(v, left, mid, right, option);
    }
}

// function inspired by powerpoint, "Graphs-2", slide 50, by Amanpreet Kapoor
// Merge two subarrays from arr
void Merge(vector<int> &v, int left, int mid, int right, int option) {
    // Create X ← arr[left..mid] & Y ← arr[mid+1..right]
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int X[n1], Y[n2];

    for (int i = 0; i < n1; i++) {
        X[i] = v.at(left + i);
    }
    for (int j = 0; j < n2; j++) {
        Y[j] = v.at(mid + 1 + j);
    }

    // Merge the arrays X and Y into arr
    int i, j, k;
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (X[i] <= Y[j]) {
            v.at(k) = X[i];
            i++;
        }
        else {
            v.at(k) = Y[j];
            j++;
        }
        k++;
    }
    // When we run out of elements in either X or Y append the remaining elements
    while (i < n1) {
        v.at(k) = X[i];
        i++;
        k++;
    }

    while (j < n2) {
        v.at(k) = Y[j];
        j++;
        k++;
    }
}

void LoadData(string &path, vector<Song> &one, vector<Song> &two) {
    // Put data from file into ifstream
    ifstream inFile;
    // Open the file
    inFile.open(path);

    string lineFromFile;
    // Ignore headers
    getline(inFile, lineFromFile);

    // Get line from file
    while(getline(inFile, lineFromFile)) {

        // Make a separate string stream
        istringstream lineStream(lineFromFile);

        // Get name
        string name;
        getline(lineStream, name, ',');

        // Get artist
        string artist;
        getline(lineStream, artist, ',');
        artist.erase(0, 2);
        artist.erase(artist.end() - 2, artist.end());

        // Get popularity
        string s;
        getline(lineStream, s, ',');
        int popularity = stoi(s);

        // Get danceability
        getline(lineStream, s, ',');
        float danceability = stof(s);

        // Get duration
        getline(lineStream, s, ',');
        int duration = stoi(s);

        // Get tempo
        getline(lineStream, s, ',');
        float tempo = stof(s);

        // Get loudness
        getline(lineStream, s, ',');
        float loudness = stof(s);

        // Get year
        getline(lineStream, s);
        int year = stoi(s);

        // Make new Song
        Song newSong(name, artist, popularity, danceability, duration, tempo, loudness, year);

        // Put new Song into vector
        one.push_back(newSong);
        two.push_back(newSong);
    }
}

// function inspired by GeeksforGeeks article, "Jump Search"
int JumpSearch(vector<int> &v, int search, int option) {
    int jump = sqrt(v.size());
    int minIndex = 0;
    int maxIndex;

    // Jump
    for(int i = 0; i < v.size(); i += jump) {
        if(search == v.at(i)) {
            return i;
        }
        else if(search < v.at(i)) {
            maxIndex = i;
            break;
        }
        else {
            minIndex = i;
        }
    }

    // Check for case that search is near the end of v
    if(search > v.at(maxIndex)) {
        minIndex = maxIndex;
        maxIndex = v.size();
    }

    // Linear
    for(int i = minIndex + 1; i < maxIndex; i++) {
        if(search == v.at(i)) {
            return i;
        }
    }

    // If nothing has been returned, it doesn't exist
    return -1;
}

// function inspired by GeeksforGeeks article, "Fibonacci Search"
int FibonacciSearch(vector<int> &v, int search, int option) {
    // 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55

    int fib1 = 0;
    int fib2 = 1;
    int fib3 = 1;

    while (fib3 < v.size()) {
        fib1 = fib2;
        fib2 = fib3;
        fib3 = fib1 + fib2;
    }

    int offset = -1;

    while (fib3 > 1) {
        int i;
        if(offset + fib1 <= v.size() - 1) {
            i = offset + fib1;
        }
        else {
            i = v.size() - 1;
        }

        // 0, 1, 1, 2, 3,    5, 8, 13,       21, 34, 55
        if (search > v.at(i)) {
            fib3 = fib2;
            fib2 = fib1;
            fib1 = fib3 - fib2;
            offset = i;
        }
        else if (search < v.at(i)) {
            fib3 = fib1;
            fib2 = fib2 - fib1;
            fib1 = fib3 - fib2;
        }
        else {
            return i;
        }
    }

    if(fib2 != 0 && v.at(offset + 1) == search) {
        return offset + 1;
    }
    else {
        return -1;
    }

}





