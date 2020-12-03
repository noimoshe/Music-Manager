#include "library1.h"
#include "MusicManager.h"
#include "AvlTree.h"

void * Init() {
    MusicManager *DS = new MusicManager ();
    return ( void *)DS;
}

StatusType AddArtist( void * DS, int artistID, int numOfSongs) {
     if(numOfSongs<=0 || DS == nullptr || artistID<=0) return INVALID_INPUT;

     AVLTree<Artist>* artists_tree =((MusicManager*)DS)->getArtistsTree();
     Artist to_find(artistID,0, nullptr);
     avl_node<Artist>* is_exist= artists_tree->find(&to_find);
     if(is_exist != nullptr){
         return FAILURE;
     }

    Artist* result=((MusicManager *)DS)->AddArtist(artistID, numOfSongs);
    if (result== nullptr) return ALLOCATION_ERROR;

    return SUCCESS;
}

StatusType RemoveArtist(void *DS, int artistID){
    if(DS == nullptr || artistID<=0) return INVALID_INPUT;

    int is_exists=1;
    ((MusicManager*)DS)->RemoveArtistFromMusicManager(artistID, &is_exists);
    if(is_exists==0) return FAILURE;

    return SUCCESS;
}

StatusType AddToSongCount(void *DS, int artistID, int songID){
   if(DS== nullptr || artistID<=0 || songID<0) return INVALID_INPUT;

    AVLTree<Artist>* artists_tree =((MusicManager*)DS)->getArtistsTree();
    Artist to_find(artistID,0, nullptr);
    avl_node<Artist>* is_exist= artists_tree->find(&to_find);
    if(!is_exist){
        return FAILURE;
    }
    if (songID >= is_exist->data->getSongsNumber()) {
        return INVALID_INPUT;
    }
    ((MusicManager*)DS)->AddStreamToSong(artistID, songID);
    return SUCCESS;
};

StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams){

    if(DS == nullptr || streams == nullptr || artistID<=0 || songID<0) return INVALID_INPUT;

    AVLTree<Artist>* artists_tree =((MusicManager*)DS)->getArtistsTree();
    Artist to_find(artistID,0,NULL);
    avl_node<Artist>* is_exist= artists_tree->find(&to_find);

    if(!is_exist) {
        return FAILURE;
    }
    if (songID >= is_exist->data->getSongsNumber()) {
        return INVALID_INPUT;
    }

    *streams = is_exist->data->getSongNumberOfStreams(songID);
    return SUCCESS;
};

StatusType GetRecommendedSongs(void *DS, int numOfSongs, int *artists,
        int *songs){
    if(DS == nullptr) return INVALID_INPUT;
    if(numOfSongs<=0) return ALLOCATION_ERROR;

    int enough_songs=1;
    ((MusicManager*)(DS))->RecommendedSongsFromList(numOfSongs, artists, songs, &enough_songs);
    if (enough_songs==0) return FAILURE;

    return SUCCESS;
}

void Quit(void** DS){
    delete *(MusicManager**)(DS);
    *(MusicManager**)(DS) = NULL;
}