#include <cmath>
#include "Artist.h"

Song* Artist::addSongNodeToList(ArtistNode*& artist_node, StreamingNode head, int song_id, int artist_id){
    Song* song_to_insert=new Song(song_id,artist_id);
    SongNode* new_song_node = new SongNode(artist_id,song_id,0,head);
    AVLTree<SongNode>* song_node_tree = artist_node->getSongsTree();
    song_node_tree->insert(new_song_node);
    song_to_insert->AddSongInList(new_song_node);
    return song_to_insert;
}

//Constructor
Artist::Artist(int artist_id, int songs_number, StreamingNode head) {
    if(head == nullptr) this->songs = nullptr;
    if(head != nullptr) {
        AVLTree<Song>* songstree = new AVLTree<Song>;
        this->songs = songstree;
        //Add the new artist to the list
        ArtistNode* node_to_list = new ArtistNode(head, artist_id);
        this->in_list = node_to_list;

        int middle=floor((double)songs_number/2);
        Song* song_to_insert=addSongNodeToList(node_to_list,head,middle,artist_id);
        this->songs->insert(song_to_insert);
        for(int i=1;i<middle; i++){
            if(this->songs->nodes_count < songs_number){
            Song* insert1= addSongNodeToList(node_to_list,head,middle-i,artist_id);
            this->songs->insert(insert1);
            }
            if(this->songs->nodes_count < songs_number) {
                Song *insert2 = addSongNodeToList(node_to_list, head,
                                                  middle + i, artist_id);
                this->songs->insert(insert2);
            }
        }
        if(songs_number%2==0){
            if(this->songs->nodes_count < songs_number) {
                Song *insert1 = addSongNodeToList(node_to_list, head, 0,
                                                  artist_id);
                this->songs->insert(insert1);
            }
        }
        else{
            if(this->songs->nodes_count < songs_number) {
                Song *insert1 = addSongNodeToList(node_to_list, head, 0,
                                                  artist_id);
                this->songs->insert(insert1);
            }
            if(this->songs->nodes_count < songs_number){
                Song* insert2= addSongNodeToList(node_to_list,head,songs_number-1,artist_id);
                this->songs->insert(insert2);
            }
        }
        head->artists->insert(node_to_list);
    }
    this->songs_number = songs_number;
    this->artist_id = artist_id;
    //create artist's streams array
    this->streams_array = new int[songs_number];
    for(int i=0; i<songs_number; i++){
        this->streams_array[i] = 0;
    }
}

//Destructor
Artist::~Artist() {
    if(this->songs)
        delete this->songs;
    delete[] this->streams_array;
}

Artist::Artist(const Artist &other) {
    this->artist_id = other.artist_id;
    this->songs_number = other.songs_number;
    this->songs = other.songs;
    this->songs = nullptr;
    this->streams_array = other.streams_array;
}

int Artist::getSongNumberOfStreams(int song_id) {
    return this->streams_array[song_id];
}

bool Artist::operator<(const Artist& other) {
    return other.artist_id > this->artist_id;
}

bool Artist::operator>(const Artist& other) {
    return other.artist_id < this->artist_id;
}

bool Artist::operator==(const Artist& other) const {
    return other.artist_id == this->artist_id;
}

AVLTree<Song>* Artist::getSongsTree() {
    return this->songs;
}

//Add one stream to a song
void Artist::changeStreamsArray(int id) {
    this->streams_array[id]++;
}

int Artist::getSongsNumber() {
    return this->songs_number;
}