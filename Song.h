#pragma once
#include <string>
using namespace std;

class Song {
public:
    // Constructor
    Song(string _name = "", string _artist = "", float _popularity = -1, float _danceability = -1,
         float _duration = -1, float _tempo = -1, float _loudness = 1, float _year = -1);

    // Accessors
    string GetName() {return name;}
    string GetArtist() {return artist;}
    float GetPopularity() {return popularity;}
    float GetDanceability() {return danceability;}
    float GetDuration() {return duration;}
    float GetTempo() {return tempo;}
    float GetLoudness() {return loudness;}
    float GetYear() {return year;}
    string GetTime() {return time;}
    string GetString(int option);
    float GetFloat(int option);

    // Mutators
    void SetName(string _name) {name = _name;}
    void SetArtist(string _artist) {artist = _artist;}
    void SetPopularity(float _popularity) {popularity = _popularity;}
    void SetDanceability(float _danceability) {danceability = _danceability;}
    void SetDuration(float _duration) {duration = _duration;}
    void SetTempo(float _tempo) {tempo = _tempo;}
    void SetLoudness(float _loudness) {loudness = _loudness;}
    void SetYear(float _year) {year = _year;}

private:
    string name;
    string artist;
    float popularity;
    float danceability;
    float duration;
    float tempo;
    float loudness;
    float year;
    string time;
};
