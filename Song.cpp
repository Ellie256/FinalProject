#include "Song.h"

Song::Song(string _name, string _artist, float _popularity, float _danceability, float _duration, float _tempo,
           float _year) {
    name = _name;
    artist = _artist;
    popularity = _popularity;
    danceability = _danceability;
    duration = _duration;
    tempo = _tempo;
    year = _year;

    int seconds = (int)duration / 1000;
    int minutes = seconds / 60;
    seconds = seconds - (minutes * 60);
    time = to_string(minutes);
    if(seconds < 10) {
        time += ":0" + to_string(seconds);
    }
    else {
        time += ":" + to_string(seconds);
    }
}

string Song::GetString(int option) {
    switch (option) {
        case 1:
            return name;
            break;
        case 2:
            return artist;
            break;
        default:
            return "";
            break;
    }
}

float Song::GetFloat(int option) {
    switch (option) {
        case 3:
            return popularity;
            break;
        case 4:
            return danceability;
            break;
        case 5:
            return duration;
            break;
        case 6:
            return tempo;
            break;
        case 7:
            return year;
            break;
        default:
            return 0;
            break;
    }
}
