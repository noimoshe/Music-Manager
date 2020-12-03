#ifndef WET1_MUSICMANAGER_H
#define WET1_MUSICMANAGER_H

#include <stdbool.h>
#include "Artist.h"
#include "AvlTree.h"
//#include "ArtistNode.h"
#include "Song.h"

//Music Manager
class MusicManager {
public:
    AVLTree<Artist>* artists_tree;
    StreamingNode streaming_list_head;
    StreamingNode streaming_list_end;
    MusicManager();
    MusicManager(const MusicManager& other);
    ~MusicManager();
    Artist* AddArtist(int artist_id, int numOfSongs);
    void AddStreamToSong(int artist_id, int song_id);
    void RemoveArtistFromMusicManager(int artist_id, int* is_exists);
    void DeleteStreamingList();
    AVLTree<Artist>* getArtistsTree();
    void RecommendedSongsFromList(int numOfSongs, int* artists, int* songs,int* enough_songs);
    void RecommendedArtistsFromLowest(int numOfSongs, int* artists, int* songs, int* counter, avl_node<ArtistNode>* node);
    void RecommendedArtists(int numOfSongs, int* artists, int* songs,int* counter, avl_node<ArtistNode>* node);
    void RecommendedSongsFromLowest(int numOfSongs, int* artists, int* songs,int* counter, avl_node<SongNode>* node);
    void RecommendedSongs(int numOfSongs, int* artists, int* songs,int* counter, avl_node<SongNode>* node);
    void DeleteArtistFromList(ArtistNode* todelete);
    void DeleteArtistFromListTree(avl_node<Song>* root);
    avl_node<Artist>* findArtist(int artist_id);
    avl_node<Song>* findSong(int artist_id, int song_id, Artist* artist_data);
    void deleteArtistFromStreamingNode(int artist_id,StreamingNode next,
            int song_id);
    void deleteStreamingNodeFromList(StreamingNode next);
    void updateStreamingNode( StreamingNode next, StreamingNode new_node);
};

#endif //WET1_MUSICMANAGER_H