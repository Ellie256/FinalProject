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
int JumpSearchString(vector<Song> &v, string search, int option); // returns the index, returns -1 if not found
int JumpSearchFloat(vector<Song> &v, float search, int option); // returns the index, returns -1 if not found
int FibonacciSearchString(vector<Song> &v, string search, int option); // returns the index, returns -1 if not found
int FibonacciSearchFloat(vector<Song> &v, float search, int option); // returns the index, returns -1 if not found
void LoadData(string &path, vector<Song> &one, vector<Song> &two);
void PrintMainMenu();
void PrintSortMenu();
void PrintSortOptionMenu();
void PrintSearchOptionMenu();
int SortOption(vector<Song> &shell, vector<Song> &merge, int option);
int SearchOption(vector<Song> &v, int option);
void PrintSong(Song &s);

int main() {

    vector<Song> shell;
    vector<Song> merge;
    string path = "data.csv";
    LoadData(path, shell, merge);

    int option = 0;
    int sortedBy = 0;

    // In order to search, the vectors must be sorted
    cout << "---------------------------------------------------" << endl;
    cout << "Welcome to the Song Searcher" << endl;
    cout << "Songs Have 8 Characteristics: " << endl;
    cout << "   Name of the Song" << endl;
    cout << "   Artist" << endl;
    cout << "   Popularity (Ranges from 0 to 100)" << endl;
    cout << "   Danceability (Ranges from 0 to 1)" << endl;
    cout << "   Duration of the Song" << endl;
    cout << "   Tempo in Beats per Minute" << endl;
    cout << "   Year the Song was Released" << endl;
    cout << "First, Choose a Characteristic to Sort the Songs By" << endl;
    cout << "---------------------------------------------------" << endl;
    option = SortOption(shell, merge, option);
    sortedBy = option;

    // This while loop is for the whole program
    while (option != -1) {
        // This while loop is to get a valid main menu option
        while (option != -1) {
            // Menu
            PrintMainMenu();
            cin >> option;

            // Enter another number if it's not 1 or 2
            if (option != -1 && option != 1 && option != 2) {
                cout << "Error: Please enter a valid option." << endl;
            }
            else {
                break;
            }
        }
        // Next go into either Sort or Search
        if (option != -1) {
            switch (option) {
                // Sort
                case 1:
                    option = SortOption(shell, merge, option);
                    sortedBy = option;
                    break;
                // Search
                case 2:
                    option = SearchOption(shell, sortedBy);
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

// function inspired by powerpoint, "Sorting-2", slide 34, by Amanpreet Kapoor
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

// function inspired by powerpoint, "Sorting-2", slide 49, by Amanpreet Kapoor
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

// function inspired by powerpoint, "Sorting-2", slide 50, by Amanpreet Kapoor
// Merge two subarrays from arr
void Merge(vector<Song> &v, int left, int mid, int right, int option) {
    // Create X ← arr[left..mid] & Y ← arr[mid+1..right]
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Song> X;
    vector<Song> Y;

    for (int i = 0; i < n1; i++) {
        X.push_back(v.at(left + i));
    }
    for (int j = 0; j < n2; j++) {
        Y.push_back(v.at(mid + 1 + j));
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
            //cout << "n1: " << n1 << endl;
            //cout << "i: " << i << endl;
            //cout << "n2: " << n2 << endl;
            //cout << "j: " << j << endl;
            //cout << "X: " << X[i].GetString(option) << endl;
            //cout << "Y: " << Y[j].GetString(option) << endl;
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

        // Get year
        getline(lineStream, s, ',');
        float year = stof(s);

        // Make new Song
        Song newSong(name, artist, popularity, danceability, duration, tempo, year);

        // Put new Song into vector
        one.push_back(newSong);
        two.push_back(newSong);
    }
}

// function inspired by GeeksforGeeks article, "Jump Search"
int JumpSearchString(vector<Song> &v, string search, int option) {
    int jump = sqrt(v.size());
    int minIndex = 0;
    int maxIndex;

    // Jump
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


    // If nothing has been returned, it doesn't exist
    return -1;
}

// function inspired by GeeksforGeeks article, "Jump Search"
int JumpSearchFloat(vector<Song> &v, float search, int option) {
    int jump = sqrt(v.size());
    int minIndex = 0;
    int maxIndex;

    // Jump
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


    // If nothing has been returned, it doesn't exist
    return -1;
}

// function inspired by GeeksforGeeks article, "Fibonacci Search"
int FibonacciSearchString(vector<Song> &v, string search, int option) {
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

    // If nothing has been returned, it doesn't exist
    return -1;
}

// function inspired by GeeksforGeeks article, "Fibonacci Search"
int FibonacciSearchFloat(vector<Song> &v, float search, int option) {
    int fib1 = 0;
    int fib2 = 1;
    int fib3 = 1;

    while (fib3 < v.size()) {
        fib1 = fib2;
        fib2 = fib3;
        fib3 = fib1 + fib2;
    }

    int offset = -1;

    while (fib3 > 1 && offset < (int)v.size() - 1) {
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

    if (fib2 != 0 && v.at(offset).GetFloat(option) == search) {
        return offset;
    }

    if (offset + 1 < v.size()) {
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
    cout << "7. Year" << endl;
    cout << "(Enter an option, type -1 to exit)" << endl;
    cout << "---------------------------------------------------" << endl;
}

void PrintSortOptionMenu() {
    cout << "---------------------------------------------------" << endl;
    cout << "Would you like to use: " << endl;
    cout << "1. Shell Sort" << endl;
    cout << "2. Merge Sort" << endl;
    cout << "(Enter an option, type -1 to exit)" << endl;
    cout << "---------------------------------------------------" << endl;
}

void PrintSearchOptionMenu() {
    cout << "---------------------------------------------------" << endl;
    cout << "Would you like to use: " << endl;
    cout << "1. Jump Search" << endl;
    cout << "2. Fibonacci Search" << endl;
    cout << "(Enter an option, type -1 to exit)" << endl;
    cout << "---------------------------------------------------" << endl;
}

int SortOption(vector<Song> &shell, vector<Song> &merge, int option) {
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    std::chrono::duration<double> elapsed;

    int option2 = 0;
    int compare = 0;

    // This while loop is to get a valid sort menu option
    while (option != -1) {
        PrintSortMenu();
        cin >> option;

        // Enter another number if option is not valid
        if (option != -1 && (option < 1 || option > 7)) {
            cout << "Error: Please enter a valid option." << endl;
        }
        else {
            break;
        }
    }

    // This while loop is to get a valid sort option
    while (option2 != -1 && option != -1) {
        PrintSortOptionMenu();
        cin >> option2;

        // Enter another number if option is not valid
        if (option2 != -1 && option2 != 1 && option2 != 2) {
            cout << "Error: Please enter a valid option." << endl;
        }
        else {
            break;
        }
    }

    if(option2 == 1) {
        start = std::chrono::high_resolution_clock::now();
        ShellSort(shell, option);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        cout << "Time for Shell Sort in seconds: " << elapsed.count() << endl;

        start = std::chrono::high_resolution_clock::now();
        MergeSort(merge, 0, merge.size() - 1, option);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;

        // This while loop is to get a valid option
        while (option2 != -1) {
            cout << "---------------------------------------------------" << endl;
            cout << "Do you want to compare this time with Merge Sort?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            cout << "---------------------------------------------------" << endl;

            cin >> compare;
            // Enter another number if option is not valid
            if (compare != 1 && compare != 2) {
                cout << "Error: Please enter a valid option." << endl;
            }
            else {
                break;
            }
        }

        if(compare == 1) {
            cout << "Time for Merge Sort in seconds: " << elapsed.count() << endl;
        }
    }
    else if(option2 == 2) {
        start = std::chrono::high_resolution_clock::now();
        MergeSort(merge, 0, merge.size() - 1, option);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        cout << "Time for Merge Sort in seconds: " << elapsed.count() << endl;

        start = std::chrono::high_resolution_clock::now();
        ShellSort(shell, option);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;

        // This while loop is to get a valid option
        while (option2 != -1) {
            cout << "---------------------------------------------------" << endl;
            cout << "Do you want to compare this time with Shell Sort?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            cout << "---------------------------------------------------" << endl;

            cin >> compare;
            // Enter another number if option is not valid
            if (compare != 1 && compare != 2) {
                cout << "Error: Please enter a valid option." << endl;
            }
            else {
                break;
            }
        }

        if(compare == 1) {
            cout << "Time for Shell Sort in seconds: " << elapsed.count() << endl;
        }
    }

    if (option == -1 || option2 == -1) {
        return -1;
    }
    else {
        return option;
    }
}

int SearchOption(vector<Song> &v, int option) {
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    std::chrono::duration<double> elapsed;

    string s;
    float f;
    int option2 = 1;
    int index = 0;

    switch (option) {
        case 1:
            cout << "---------------------------------------------------" << endl;
            cout << "Enter a song name you want to search for" << endl;
            cout << "---------------------------------------------------" << endl;
            getline(cin, s);
            getline(cin, s);
            break;
        case 2:
            cout << "---------------------------------------------------" << endl;
            cout << "Enter a artist you want to search for" << endl;
            cout << "---------------------------------------------------" << endl;
            getline(cin, s);
            getline(cin, s);
            break;
        case 3:
            cout << "---------------------------------------------------" << endl;
            cout << "Enter a popularity you want to search for" << endl;
            cout << "---------------------------------------------------" << endl;
            cin >> f;
            break;
        case 4:
            cout << "---------------------------------------------------" << endl;
            cout << "Enter a danceability you want to search for" << endl;
            cout << "---------------------------------------------------" << endl;
            cin >> f;
            break;
        case 5:
            cout << "---------------------------------------------------" << endl;
            cout << "Enter a duration you want to search for" << endl;
            cout << "---------------------------------------------------" << endl;
            cin >> f;
            break;
        case 6:
            cout << "---------------------------------------------------" << endl;
            cout << "Enter a tempo you want to search for" << endl;
            cout << "---------------------------------------------------" << endl;
            cin >> f;
            break;
        case 7:
            cout << "---------------------------------------------------" << endl;
            cout << "Enter a year you want to search for" << endl;
            cout << "---------------------------------------------------" << endl;
            cin >> f;
            break;
        default:
            break;
    }

    // This while loop is to get a valid search option
    while (option2 != -1) {
        PrintSearchOptionMenu();
        cin >> option2;
        // Enter another number if option is not valid
        if (option2 != -1 && option2 != 1 && option2 != 2) {
            cout << "Error: Please enter a valid option." << endl;
        }
        else {
            break;
        }
    }

    if (option2 == 1) {
        if (option < 3) {
            start = std::chrono::high_resolution_clock::now();
            index = JumpSearchString(v, s, option);
            if (index != -1) {
                int i = index;
                while (v.at(i).GetString(option) == s && i > -1) {
                    PrintSong(v.at(i));
                    i--;
                }
                i = index + 1;
                while (v.at(i).GetString(option) == s && i < v.size()) {
                    PrintSong(v.at(i));
                    i++;
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
            }
            else {
                cout << "Song not found" << endl;
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
            }
        }
        else {
            start = std::chrono::high_resolution_clock::now();
            index = JumpSearchFloat(v, f, option);
            if (index != -1) {
                int i = index;
                while (v.at(i).GetFloat(option) == f && i > -1) {
                    PrintSong(v.at(i));
                    i--;
                }
                i = index + 1;
                while (v.at(i).GetFloat(option) == f && i < v.size()) {
                    PrintSong(v.at(i));
                    i++;
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
            }
            else {
                cout << "Song not found" << endl;
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
            }
        }
        cout << "Time for Jump Search in seconds: " << elapsed.count() << endl;
        return option2;
    }
    else if (option2 == 2) {
        if (option < 3) {
            start = std::chrono::high_resolution_clock::now();
            index = FibonacciSearchString(v, s, option);
            if (index != -1) {
                int i = index;
                while (v.at(i).GetString(option) == s && i > -1) {
                    PrintSong(v.at(i));
                    i--;
                }
                i = index + 1;
                while (v.at(i).GetString(option) == s && i < v.size()) {
                    PrintSong(v.at(i));
                    i++;
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
            }
            else {
                cout << "Song not found" << endl;
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
            }
        }
        else {
            start = std::chrono::high_resolution_clock::now();
            index = FibonacciSearchFloat(v, f, option);
            if (index != -1) {
                int i = index;
                while (v.at(i).GetFloat(option) == f && i > -1) {
                    PrintSong(v.at(i));
                    i--;
                }
                i = index + 1;
                while (v.at(i).GetFloat(option) == f && i < v.size()) {
                    PrintSong(v.at(i));
                    i++;
                }
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
            }
            else {
                cout << "Song not found" << endl;
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
            }
        }
        cout << "Time for Fibonacci Search in seconds: " << elapsed.count() << endl;
        return option2;
    }
    else {
        return -1;
    }

}

void PrintSong(Song &s) {
    cout << "name: " << s.GetName() << endl;
    cout << "artist: " << s.GetArtist() << endl;
    cout << "popularity: " << s.GetPopularity() << endl;
    cout << "danceability: " << s.GetDanceability() << endl;
    cout << "duration: " << s.GetTime() << endl;
    cout << "tempo: " << s.GetTempo() << endl;
    cout << "year: " << s.GetYear() << endl;
    cout << endl;
}



