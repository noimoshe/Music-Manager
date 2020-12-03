//
// Created by noimo on 08/05/2020.
//

#ifndef WET1_SONG_H
#define WET1_SONG_H
#include<iostream>
#include "ArtistNode.h"


//Song for songs avl-tree of Artist in Music Manager
class Song {
public:
    int num_of_streams;
    SongNode* song_in_list;
    int song_id;
    int artist_id;
    Song(int song_id, int artist_id);
    ~Song() = default;
    Song(const Song& other);
    void AddSongInList(SongNode* song_in_list);
    void increaseStreams();
    SongNode* getSongInList();
    bool operator<(const Song& other) ;
    bool operator>(const Song& other) ;
    bool operator==(const Song& other) const;
};

#endif //WET1_SONG_H
