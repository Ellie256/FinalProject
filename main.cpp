#include <iostream>
#include <vector>
#include <chrono>
#include <math.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include "Song.h"
using namespace std;

void Swap (vector<Song> &v, int a, int b);
void ShellSort(vector<Song> &v, int option);
void MergeSort(vector<Song> &v, int left, int right, int option);
void Merge(vector<Song> &v, int left, int mid, int right, int option);
template <typename T>
int JumpSearch(vector<Song> &v, int search, int option); // returns the index, returns -1 if not found
template <typename T>
int FibonacciSearch(vector<Song> &v, int search, int option); // returns the index, returns -1 if not found
void LoadData(string &path, vector<Song> &one, vector<Song> &two);
void PrintMainMenu();
void PrintSortMenu();

int main() {
    /*
    // get current time
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    // get current time
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    // measure difference
    std::chrono::duration<double> elapsed = end - start;
    cout << "Elapsed time to push in seconds: " << elapsed.count() << endl;
     */

    vector<Song> shell;
    vector<Song> merge;
    string path = "example.csv";
    LoadData(path, shell, merge);

    /*
    ShellSort(shell, 5);

    for(int i = 0; i < shell.size(); i++) {
        cout << "name: " << shell.at(i).GetName() << endl;
        cout << "artist: " << shell.at(i).GetArtist() << endl;
        cout << "popularity: " << shell.at(i).GetPopularity() << endl;
        cout << "danceability: " << shell.at(i).GetDanceability() << endl;
        cout << "duration: " << shell.at(i).GetTime() << endl;
        cout << "tempo: " << shell.at(i).GetTempo() << endl;
        cout << "loudness: " << shell.at(i).GetLoudness() << endl;
        cout << "year: " << shell.at(i).GetYear() << endl;
        cout << endl;
    }
     */

    int option = 0;

    // This while loop is for the whole program
    while (option != -1) {
        // This while loop is to get a valid main menu option
        while (option != -1) {
            // Menu
            PrintMainMenu();
            cin >> option;

            // Enter another number if it's not 1 or 2
            if (option != 1 && option != 2) {
                cout << "Error: Please enter a valid option." << endl;
            }
            else {
                break;
            }
        }
        if (option != -1) {
            switch (option) {
                // Sort
                case 1:
                    PrintSortMenu();
                    cin >> option;
                    // Exit if user inputs -1
                    if (option == -1) {
                        break;
                    }
                        // Enter another number if option is not valid
                    else if (option < 1 || option > 8) {
                        throw runtime_error("Error: Please enter a valid option.");
                    }

                    break;
                // Search
                case 2:
                    break;
                default:
                    break;
            }
        }
    }

    return 0;
}

void Swap(vector<Song> &v, int a, int b) {
    Song temp = v.at(a);
    v.at(a) = v.at(b);
    v.at(b) = temp;
}

// function inspired by powerpoint, "Graphs-2", slide 34, by Amanpreet Kapoor
void ShellSort(vector<Song> &v, int option) {
    // Initialize k to be the largest so that gap is not larger than the size of the vector
    int k = (int) (log(v.size()) / log(2));
    // The gap function is based on Hibbard's sequence
    int gap = pow(2, k) - 1;

    // The gap will decrease until it is 1
    while (gap > 0) {
        // Compare Strings
        if (option < 3) {
            // Compare elements that are a gap away from each other
            for (int i = 0; i < v.size() - gap; i++) {
                if (v.at(i).GetString(option) > v.at(i + gap).GetString(option)) {
                    Swap(v, i, i + gap);

                    // If two elements are swapped, then check previous elements that are gaps away
                    for (int j = i; j >= gap; j -= gap) {
                        if (v.at(j).GetString(option) < v.at(j - gap).GetString(option)) {
                            Swap(v, j, j - gap);
                        }
                        else {
                            break;
                        }
                    }
                }
            }
        }
        // Compare Floats
        else {
            // Compare elements that are a gap away from each other
            for (int i = 0; i < v.size() - gap; i++) {
                if (v.at(i).GetFloat(option) > v.at(i + gap).GetFloat(option)) {
                    Swap(v, i, i + gap);

                    // If two elements are swapped, then check previous elements that are gaps away
                    for (int j = i; j >= gap; j -= gap) {
                        if (v.at(j).GetFloat(option) < v.at(j - gap).GetFloat(option)) {
                            Swap(v, j, j - gap);
                        }
                        else {
                            break;
                        }
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
void MergeSort(vector<Song> &v, int left, int right, int option) {
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
void Merge(vector<Song> &v, int left, int mid, int right, int option) {
    // Create X ← arr[left..mid] & Y ← arr[mid+1..right]
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Song X[n1], Y[n2];

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

    // Compare Strings
    if (option < 3) {
        // Combine the arrays in sorted order
        while (i < n1 && j < n2) {
            if (X[i].GetString(option) <= Y[j].GetString(option)) {
                v.at(k) = X[i];
                i++;
            }
            else {
                v.at(k) = Y[j];
                j++;
            }
            k++;
        }
    }
    // Compare Floats
    else {
        // Combine the arrays in sorted order
        while (i < n1 && j < n2) {
            if (X[i].GetFloat(option) <= Y[j].GetFloat(option)) {
                v.at(k) = X[i];
                i++;
            }
            else {
                v.at(k) = Y[j];
                j++;
            }
            k++;
        }
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
    while (getline(inFile, lineFromFile)) {

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
        float popularity = stof(s);

        // Get danceability
        getline(lineStream, s, ',');
        float danceability = stof(s);

        // Get duration
        getline(lineStream, s, ',');
        float duration = stof(s);

        // Get tempo
        getline(lineStream, s, ',');
        float tempo = stof(s);

        // Get loudness
        getline(lineStream, s, ',');
        float loudness = stof(s);

        // Get year
        getline(lineStream, s);
        float year = stof(s);

        // Make new Song
        Song newSong(name, artist, popularity, danceability, duration, tempo, loudness, year);

        // Put new Song into vector
        one.push_back(newSong);
        two.push_back(newSong);
    }
}

// function inspired by GeeksforGeeks article, "Jump Search"
template <typename T>
int JumpSearch(vector<Song> &v, T search, int option) {
    int jump = sqrt(v.size());
    int minIndex = 0;
    int maxIndex;

    // Jump
    // Compare Strings
    if (option > 3) {
        for (int i = 0; i < v.size(); i += jump) {
            if (search == v.at(i).GetString(option)) {
                return i;
            }
            else if (search < v.at(i).GetString(option)) {
                maxIndex = i;
                break;
            } else {
                minIndex = i;
            }
        }

        // Check for case that search is near the end of v
        if (search > v.at(maxIndex).GetString(option)) {
            minIndex = maxIndex;
            maxIndex = v.size();
        }

        // Linear
        for (int i = minIndex + 1; i < maxIndex; i++) {
            if (search == v.at(i).GetString(option)) {
                return i;
            }
        }
    }
    // Compare Floats
    else {
        for (int i = 0; i < v.size(); i += jump) {
            if (search == v.at(i).GetFloat(option)) {
                return i;
            }
            else if (search < v.at(i).GetFloat(option)) {
                maxIndex = i;
                break;
            }
            else {
                minIndex = i;
            }
        }

        // Check for case that search is near the end of v
        if (search > v.at(maxIndex).GetFloat(option)) {
            minIndex = maxIndex;
            maxIndex = v.size();
        }

        // Linear
        for (int i = minIndex + 1; i < maxIndex; i++) {
            if (search == v.at(i).GetFloat(option)) {
                return i;
            }
        }
    }

    // If nothing has been returned, it doesn't exist
    return -1;
}

// function inspired by GeeksforGeeks article, "Fibonacci Search"
template <typename T>
int FibonacciSearch(vector<Song> &v, T search, int option) {
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

    // Compare Strings
    if (option < 3) {
        while (fib3 > 1) {
            int i;
            if (offset + fib1 <= v.size() - 1) {
                i = offset + fib1;
            }
            else {
                i = v.size() - 1;
            }

            if (search > v.at(i).GetString(option)) {
                fib3 = fib2;
                fib2 = fib1;
                fib1 = fib3 - fib2;
                offset = i;
            }
            else if (search < v.at(i).GetString(option)) {
                fib3 = fib1;
                fib2 = fib2 - fib1;
                fib1 = fib3 - fib2;
            }
            else {
                return i;
            }
        }

        if (fib2 != 0 && v.at(offset + 1).GetString(option) == search) {
            return offset + 1;
        }
    }
    // Compare Floats
    else {
        while (fib3 > 1) {
            int i;
            if (offset + fib1 <= v.size() - 1) {
                i = offset + fib1;
            }
            else {
                i = v.size() - 1;
            }

            if (search > v.at(i).GetFloat(option)) {
                fib3 = fib2;
                fib2 = fib1;
                fib1 = fib3 - fib2;
                offset = i;
            }
            else if (search < v.at(i).GetFloat(option)) {
                fib3 = fib1;
                fib2 = fib2 - fib1;
                fib1 = fib3 - fib2;
            }
            else {
                return i;
            }
        }

        if (fib2 != 0 && v.at(offset + 1).GetFloat(option) == search) {
            return offset + 1;
        }
    }

    // If nothing has been returned, it doesn't exist
    return -1;
}

void PrintMainMenu() {
    cout << "---------------------------------------------------" << endl;
    cout << "Main Menu" << endl;
    cout << "1. Sort" << endl;
    cout << "2. Search" << endl;
    cout << "(Enter an option, type -1 to exit)" << endl;
    cout << "---------------------------------------------------" << endl;
}

void PrintSortMenu() {
    cout << "---------------------------------------------------" << endl;
    cout << "Would you like to sort by: " << endl;
    cout << "1. Song Name" << endl;
    cout << "2. Artist" << endl;
    cout << "3. Popularity" << endl;
    cout << "4. Danceability" << endl;
    cout << "5. Song Duration" << endl;
    cout << "6. Tempo" << endl;
    cout << "7. Loudness" << endl;
    cout << "8. Year" << endl;
    cout << "(Enter an option, type -1 to go back to Main Menu)" << endl;
    cout << "---------------------------------------------------" << endl;
}



