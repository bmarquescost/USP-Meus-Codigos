// Bernardo Marques Costa - 11795551
#ifndef _SPOTIFY_H_
#define _SPOTIFY_H_

#include "track.h"

typedef struct _spotify_list {
    ARTIST *artist_data;
    TRACK **all_tracks;
    int num_tracks;
    double average_popularity;
} SPOTIFY_LIST;


SPOTIFY_LIST *make_spotify_list(TRACK **track_list, int num_tracks, int *num_artists);
int check_artist_index_in_list(SPOTIFY_LIST *list, char *artist_name, int num_artists);
void print_spotify_list(SPOTIFY_LIST *list, int n_artists, int n_tracks);
void sort_list_popularity(SPOTIFY_LIST *list, int n_artists);
void compute_average_popularity(SPOTIFY_LIST *list, int size);


#endif