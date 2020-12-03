#include "MusicManager.h"

//Constructor of new music manager, empty artists tree and empty streaming list
MusicManager::MusicManager() {
    this->artists_tree = new AVLTree<Artist>;
    //create streaming list
    AVLTree<ArtistNode>* artists_to_list = new AVLTree<ArtistNode>;
    StreamingNode new_streaming_list_head = new StreamingNode_t;
    if(new_streaming_list_head != nullptr) {
        new_streaming_list_head->num_of_streams = 0;
        new_streaming_list_head->next_num = nullptr;
        new_streaming_list_head->previous_num = nullptr;
        new_streaming_list_head->artists = artists_to_list;
    }
    this->streaming_list_head = new_streaming_list_head;
    this->streaming_list_end = this->streaming_list_head;
}

MusicManager::~MusicManager() {
    DeleteStreamingList();
    delete this->artists_tree;
}

MusicManager::MusicManager(const MusicManager &other) {
    this->artists_tree = other.artists_tree;
    this->streaming_list_head = other.streaming_list_head;
    this->streaming_list_end = other.streaming_list_end;
}

//Delete streaming list of the Music Manager
void MusicManager::DeleteStreamingList() {
    StreamingNode curr = this->streaming_list_head;
    while(curr != nullptr){
        StreamingNode next = curr->next_num;
        StreamingNode to_delete = curr;
        delete to_delete->artists;
        delete to_delete;
        curr = next;
    }
}


Artist* MusicManager::AddArtist(int artist_id, int numOfSongs) {
    Artist* new_artist = new Artist(artist_id, numOfSongs,
            this->streaming_list_head);
        //Add the new artist to the avl tree of artists
        this->artists_tree->insert(new_artist);
        return new_artist;
}

//Delete Artist from streaming list when we remove it from Music Manager
void MusicManager::DeleteArtistFromList(ArtistNode* todelete){
    StreamingNode curr = this->streaming_list_head;
    while(curr){
        curr->artists->remove(todelete);
        StreamingNode temp = curr;
        StreamingNode tempnext = curr->next_num;
        if(curr->artists->nodes_count == 0 && curr->num_of_streams != 0) {
            curr->previous_num->next_num = curr->next_num;
            if(curr->next_num)
                curr->next_num->previous_num = curr->previous_num;
            if(curr == streaming_list_end)
               streaming_list_end = curr->previous_num;
            delete temp->artists;
            delete temp;
        }
        curr = tempnext;
      //  curr = curr->next_num;
    }
    /*SongNode* songsInList = root->data->getSongInList();
    StreamingNode streaming = songsInList->getHead();
    ArtistNode* artistnode = new ArtistNode(streaming, songsInList->getArtistId());
    avl_node<ArtistNode>* found = streaming->artists->find(artistnode);
    if(!found) return;
    ArtistNode* artist = found->data;
    delete artistnode;
    if(artist){
        AVLTree<SongNode>* artist_tree = artist->getSongsTree();
        artist_tree->deleteTree();
    }*/
};

//Remove Artist
void MusicManager::RemoveArtistFromMusicManager(int artist_id, int* is_exists){
    if(is_exists == nullptr) return;
    //find the artist in the artists avl tree of the music manager
    Artist* to_find = new Artist(artist_id, 0,nullptr);
    avl_node<Artist>* to_remove_node = this->artists_tree->find(to_find);
    delete to_find;
    //in case there is no Artist with this id:
    if(to_remove_node== nullptr){
        *is_exists=0;
        return;
    }
    Artist* to_remove = to_remove_node->data;
    //delete all the artistsnodes from streaming list
    ArtistNode* artistNode = new ArtistNode(this->streaming_list_end, artist_id);
    DeleteArtistFromList(artistNode);
    delete artistNode;
    //remove artist from music manager artists tree
    this->artists_tree->remove(to_remove);
}

AVLTree<Artist>* MusicManager::getArtistsTree() {
    return this->artists_tree;
}


avl_node<Artist>* MusicManager::findArtist(int artist_id){
    Artist* to_find = new Artist(artist_id, 0, nullptr);
    AVLTree<Artist>* artists_tree=this->artists_tree;
    avl_node<Artist>* artist_found = artists_tree->find(to_find);
    delete to_find;
    return artist_found;
}

avl_node<Song>* MusicManager::findSong(int artist_id, int song_id, Artist* artist_data){
    AVLTree<Song>* songs = artist_data->getSongsTree();
    Song* song_to_find = new Song(song_id, artist_id);
    avl_node<Song>* found = songs->find(song_to_find);
    delete song_to_find;
    return found;
}

void MusicManager::deleteArtistFromStreamingNode(int artist_id,
        StreamingNode current, int song_id){
    if(current == nullptr) return;
    ArtistNode* to_remove = new ArtistNode(streaming_list_head,
                                           artist_id);
    ArtistNode* from_tree = current->artists->find(to_remove)->data;
    if(from_tree){
        SongNode* song_to_remove = new SongNode(artist_id, song_id, 0,
                                                nullptr);
        from_tree->songs->remove(song_to_remove);
        delete song_to_remove;
        if(from_tree->songs->nodes_count == 0){
            current->artists->remove(to_remove);
        }
    }
    delete to_remove;
}

void MusicManager::deleteStreamingNodeFromList(StreamingNode current){
    if(current == nullptr) return;
    StreamingNode to_delete = current;
    current->previous_num->next_num = current->next_num;
    current->next_num->previous_num = current->previous_num;
    delete to_delete->artists;
    delete to_delete;
}

void MusicManager::updateStreamingNode(StreamingNode current,
        StreamingNode new_node){
    if(current->next_num != nullptr)
        current->next_num->previous_num = new_node;
    current->next_num = new_node;
}


//AddCount to song in the Music Manager
void MusicManager::AddStreamToSong(int artist_id, int song_id) {
    //find artist in the artists tree of the music manager
    avl_node<Artist> *found_artist_node = this->findArtist(artist_id);
    if (!found_artist_node) return;

    //increase song's streams number in array
    Artist *found_artist = found_artist_node->data;
    if (!found_artist) return;
    found_artist->changeStreamsArray(song_id);

    //increase streams field of the song
    avl_node<Song> *found_song_node = this->findSong(artist_id, song_id,
                                                     found_artist);
    if (!found_song_node) return;
    Song *song = found_song_node->data;
    song->increaseStreams();


    //change SongNode location in streaming list
    SongNode *song_node = song->getSongInList();
    SongNode *new_song_node = new SongNode(song_node->artist_id, song_node->song_id,
                                           song_node->num_of_streams,
                                           song_node->head);
    new_song_node->increaseStreams();
    StreamingNode current = song_node->getHead();
    StreamingNode next = song_node->getHead()->next_num;
    song->AddSongInList(new_song_node);
    //if streaming node with current num of streaming already exists
    if (next && next->num_of_streams == new_song_node->getNumOfStreams()) {
        ArtistNode *artist_to_find = new ArtistNode(nullptr, artist_id);
        avl_node<ArtistNode> *foundinlist = next->artists->find(artist_to_find);
        delete artist_to_find;
        //if artist doesnt have another song with same num of streaming
        if (!foundinlist) {
            ArtistNode *new_node = new ArtistNode(next, artist_id);
            new_node->songs->insert(new_song_node);
            new_song_node->changeHead(next);
            next->artists->insert(new_node);
            //if artist has another song with same num of streaming
        } else {
            ArtistNode *in_list = foundinlist->data;
            in_list->songs->insert(new_song_node);
            new_song_node->changeHead(next);
        }
        //delete artist from previous streaming Node
        this->deleteArtistFromStreamingNode(artist_id, current, song_id);
    }
        //if streaming node with current num of streaming doesnt exist
    else {
        //create new streaming node
        StreamingNode new_streaming_node = new StreamingNode_t;
        new_streaming_node->next_num = next;
        new_streaming_node->previous_num = current;
        new_streaming_node->num_of_streams = new_song_node->getNumOfStreams();
        if(current == streaming_list_end)
            streaming_list_end = new_streaming_node;
        //create artist node to insert
        ArtistNode *new_node = new ArtistNode(new_streaming_node,
                                              artist_id);
        AVLTree<SongNode> *tree = new_node->getSongsTree();
        new_song_node->changeHead(new_streaming_node);
        tree->insert(new_song_node);
        //create avltree of ArtistNode and insert the artist
        AVLTree<ArtistNode> *new_artists_tree = new AVLTree<ArtistNode>;
        new_streaming_node->artists = new_artists_tree;
        new_artists_tree->insert(new_node);
        this->deleteArtistFromStreamingNode(artist_id, current, song_id);
        //update previous streaming node
        this->updateStreamingNode(current, new_streaming_node);
    }
    //if old artist song of old streaming node is now empty
    if (current != streaming_list_head && current->artists->nodes_count == 0) {
        this->deleteStreamingNodeFromList(current);
    }
}

//get recommended songs from streaming list
void MusicManager::RecommendedSongsFromList(int numOfSongs, int *artists,
                                            int *songs, int* enough_songs){
    StreamingNode curr = this->streaming_list_end;
    StreamingNode next;
    int counter = 0;
    while(curr != nullptr) {
        next = curr->previous_num;
        avl_node<ArtistNode>* tostart = curr->artists->getMin();
        RecommendedArtistsFromLowest(numOfSongs, artists, songs, &counter, tostart);
        curr = next;
    }
    if (counter<numOfSongs) *enough_songs = 0;
}

void MusicManager::RecommendedArtistsFromLowest(int numOfSongs, int *artists,
                                                int *songs, int *counter,
                                                avl_node<ArtistNode> *node){
    if(node != nullptr && *counter < numOfSongs){
        RecommendedSongsFromLowest(numOfSongs, artists, songs, counter, node->data->songs->min_node);
        RecommendedArtists(numOfSongs, artists, songs, counter, node->right);
        RecommendedArtistsFromLowest(numOfSongs, artists, songs, counter, node->father);
    }
}

void MusicManager::RecommendedArtists(int numOfSongs, int *artists, int *songs,
                                      int *counter,
                                      avl_node<ArtistNode> *node) {
    if(node != nullptr && *counter < numOfSongs){
        RecommendedArtists(numOfSongs, artists, songs, counter, node->left);
        if(*counter < numOfSongs){
            RecommendedSongsFromLowest(numOfSongs, artists, songs, counter, node->data->songs->min_node);
        }
        RecommendedArtists(numOfSongs, artists, songs, counter, node->right);
    }
}

void MusicManager::RecommendedSongsFromLowest(int numOfSongs, int *artists,
                                                int *songs, int *counter,
                                                avl_node<SongNode> *node) {
    if(node != nullptr && *counter < numOfSongs){
        artists[*counter] = node->data->artist_id;
        songs[*counter] = node->data->song_id;
        *counter = *counter + 1;
        RecommendedSongs(numOfSongs, artists, songs, counter, node->right);
        RecommendedSongsFromLowest(numOfSongs, artists, songs, counter, node->father);
    }
}

void MusicManager::RecommendedSongs(int numOfSongs, int *artists, int *songs,
                                      int *counter,
                                      avl_node<SongNode> *node) {
    if(node != nullptr && *counter < numOfSongs){
        RecommendedSongs(numOfSongs, artists, songs, counter, node->left);
        if(*counter < numOfSongs) {
            artists[*counter] = node->data->artist_id;
            songs[*counter] = node->data->song_id;
            *counter = *counter + 1;
        }
            RecommendedSongs(numOfSongs, artists, songs, counter, node->right);
        }
    }