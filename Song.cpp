#include "Song.h"

Song::Song(string _name, string _artist, int _popularity, float _danceability, int _duration, float _tempo,
           float _loudness, int _year) {
    name = _name;
    artist = _artist;
    popularity = _popularity;
    danceability = _danceability;
    duration = _duration;
    tempo = _tempo;
    loudness = _loudness;
    year = _year;
}
