#include <iostream>
#include <vector>
#include <chrono>
#include <math.h>
#include <fstream>
#include <sstream>
#include "Song.h"
using namespace std;

void Swap(int a, int b, vector<int>& v); // send in indices that need to be swapped
void ShellSort(vector<int> &v);
void Merge(vector<int> &v, int left, int mid, int right);
void MergeSort(vector<int> &v, int left, int right);
vector<Song> LoadData(string &path);

int main() {
    // vector<int> v = {7, 4, 9, 3, 2, 8, 6, 5, 4, 7, 11, 2, 3, 9};
    // vector<int> v = {12, 34, 54, 2, 3};
    vector<int> v = {6, 5, 22, 10, 9, 1};
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

    // ShellSort(v);
    MergeSort(v, 0, v.size() - 1);
    cout << "[ ";
    for(int i = 0; i < v.size(); i++) {
        cout << v.at(i) << ", ";
    }
    cout << "]" << endl;

    return 0;
}

void Swap(int a, int b, vector<int> &v) {
    int temp = v.at(a);
    v.at(a) = v.at(b);
    v.at(b) = temp;
}

// function inspired by powerpoint, "Graphs-2", slide 34, by Amanpreet Kapoor
// The gap function is based on Hibbard's sequence
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

// function inspired by powerpoint, "Graphs-2", slide 49, by Amanpreet Kapoor
void MergeSort(vector<int> &v, int left, int right) {
    if (left < right) {
        // m is the point where the array is divided into two subarrays
        int mid = left + (right - left) / 2;

        MergeSort(v, left, mid);
        MergeSort(v, mid + 1, right);

        // Merge the sorted subarrays
        Merge(v, left, mid, right);
    }
}

// function inspired by powerpoint, "Graphs-2", slide 50, by Amanpreet Kapoor
// Merge two subarrays from arr
void Merge(vector<int> &v, int left, int mid, int right) {
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

vector<Song> LoadData(string &path) {
    // Put data from file into ifstream
    ifstream inFile;
    // Open the file
    inFile.open(path);

    // Make a vector of Songs
    vector<Song> songs;

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
        songs.push_back(newSong);
    }

    return songs;
}