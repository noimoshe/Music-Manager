//
// Created by noimo on 08/05/2020.
//
#include "Song.h"
//Constructor of new Song
Song::Song(int song_number, int artist_number) : num_of_streams(0), song_in_list(nullptr),
song_id(song_number), artist_id(artist_number)
{};

bool Song::operator<(const Song& other){
    return other.song_id > this->song_id;
}

bool Song::operator>(const Song& other){
    return other.song_id < this->song_id;
}

bool Song::operator==(const Song& other)const {
    return other.song_id == this->song_id;
}

Song::Song(const Song &other) {
    this->num_of_streams = other.num_of_streams;
    this->song_in_list = other.song_in_list;
    this->artist_id = other.artist_id;
    this->song_id = other.song_id;
}

void Song::AddSongInList(SongNode* song_in_list) {
    this->song_in_list = song_in_list;
}

SongNode* Song::getSongInList() {
    return this->song_in_list;
}

void Song::increaseStreams() {
    this->num_of_streams++;
}