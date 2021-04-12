#pragma once
#include <string>
using namespace std;

class Song {
public:
    // Constructor
    Song(string _name = "", string _artist = "", int _popularity = -1, float _danceability = -1,
         int _duration = -1, float _tempo = -1, float _loudness = 1, int _year = -1);

    // Accessors
    string GetName() {return name;}
    string GetArtist() {return artist;}
    int GetPopularity() {return popularity;}
    float GetDanceability() {return danceability;}
    int GetDuration() {return duration;}
    float GetTempo() {return tempo;}
    float GetLoudness() {return loudness;}
    int GetYear() {return year;}

    // Mutators
    void SetName(string _name) {name = _name;}
    void SetArtist(string _artist) {artist = _artist;}
    void SetPopularity(int _popularity) {popularity = _popularity;}
    void SetDanceability(float _danceability) {danceability = _danceability;}
    void SetDuration(int _duration) {duration = _duration;}
    void SetTempo(float _tempo) {tempo = _tempo;}
    void SetLoudness(float _loudness) {loudness = _loudness;}
    void SetYear(int _year) {year = _year;}

private:
    string name;
    string artist;
    int popularity;
    float danceability;
    int duration;
    float tempo;
    float loudness;
    int year;
};
