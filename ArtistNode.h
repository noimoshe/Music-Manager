#ifndef WET1_ARTISTNODE_H
#define WET1_ARTISTNODE_H
#include "AvlTree.h"

typedef struct StreamingNode_t *StreamingNode;

//SongNode for avl-tree consists of ArtistNodes in the streaming list
class SongNode {
public:
    int artist_id;
    int song_id;
    int num_of_streams;
    StreamingNode head;
    SongNode(int artist_id, int song_id, int streams, StreamingNode head):
            artist_id(artist_id),song_id(song_id),num_of_streams(streams),
            head(head){};
    ~SongNode() = default;
    SongNode(const SongNode& other){
        this->artist_id = other.artist_id;
        this->song_id = other.song_id;
        this->num_of_streams = other.num_of_streams;
        this->head = other.head;
    }
    StreamingNode getHead(){
        return this->head;
    }
    int getArtistId(){
        return this->artist_id;
    }
    int getSongId(){
        return this->song_id;
    }
    int getNumOfStreams(){
        return this->num_of_streams;
    }
    void changeHead(StreamingNode head){
        this->head = head;
    }
    void increaseStreams(){
        this->num_of_streams++;
    }
    bool operator<(const SongNode other){
        return other.song_id > this->song_id;
    }

    bool operator>(const SongNode other){
        return other.song_id < this->song_id;
    }

    bool operator==(const SongNode& other) const{
        return other.song_id == this->song_id &&
        other.artist_id == this->artist_id;
    }
};

//ArtistNode for artists avl tree in the streaming list
class ArtistNode {
public:
    AVLTree<SongNode>* songs;
    //StreamingNode head;
    int artist_id;
    ArtistNode(StreamingNode head, int artist_id) : songs(nullptr), artist_id(artist_id) {
        this->songs = new AVLTree<SongNode>;
    }
    ~ArtistNode(){
        delete this->songs;
    }
    ArtistNode(const ArtistNode& other){
        this->artist_id = other.artist_id;
        this->songs = nullptr;
        //this->songs = other.songs;
    }
    AVLTree<SongNode>* getSongsTree(){
        return songs;
    }

    bool operator<(const ArtistNode other){
        return other.artist_id > this->artist_id;
    }

    bool operator>(const ArtistNode other){
        return other.artist_id < this->artist_id;
    }

    bool operator==(const ArtistNode& other) const {
        return other.artist_id == this->artist_id;
    }
};


#endif //WET1_ARTISTNODE_H
