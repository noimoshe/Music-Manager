

#ifndef _234218_WET1
#define _234218_WET1

#ifdef __cplusplus
extern "C" {
#endif

/* Return Values
 * ----------------------------------- */
typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;

//O(1)
void *Init();

//O(log(n)+m) where n=number of artists, m=numOfSongs
StatusType AddArtist(void *DS, int artistID, int numOfSongs);

//O(mlog(n)) where n=number of artists, m=number of songs of artistID
StatusType RemoveArtist(void *DS, int artistID);

//O(log(n)+log(m)) where n=number of artists, m=number of songs of artistID
StatusType AddToSongCount(void *DS, int artistID, int songID);

//O(log(n)) where n=number of artists
StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams);

//O(numOfSongs)
StatusType GetRecommendedSongs(void *DS, int numOfSongs, int *artists, int *songs);

//O(n+m) where n=number of artists, m=total number of songs in system
void Quit(void** DS);


//space complexity: O(n+m) where n=number of artists, m=total number of songs in system

#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET1 */
