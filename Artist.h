//
// Created by noimo on 08/05/2020.
//

#ifndef WET1_ARTIST_H
#define WET1_ARTIST_H
#include "Song.h"
//#include "ArtistNode.h"
#include "AvlTree.h"

//StreamingNode for streaming-list
struct StreamingNode_t {
    AVLTree<ArtistNode>* artists;
    int num_of_streams;
    StreamingNode_t* next_num;
    StreamingNode_t* previous_num;
};

//Artist for avl-tree of artists in the Music Manager
class Artist {
    int artist_id;
    int songs_number;
    AVLTree<Song>* songs;
    int* streams_array;
public:
    ArtistNode* in_list;
    Artist(int artist_id, int songs_number, StreamingNode head);
    Artist(const Artist& other);
    ~Artist();
    AVLTree<Song>* getSongsTree();
    int getSongNumberOfStreams(int song_id);
    void changeStreamsArray(int id);
    bool operator<(const Artist& other);
    bool operator>(const Artist& other);
    bool operator==(const Artist& other) const;
    int getSongsNumber();
    Song* addSongNodeToList(ArtistNode*& artist_node, StreamingNode head,int song_id, int artist_id);
};

#endif //WET1_ARTIST_H
