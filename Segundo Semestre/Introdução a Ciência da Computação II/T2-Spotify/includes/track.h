// Bernardo Marques Costa - 11795551

#ifndef _TRACK_H_
#define _TRACK_H_

#include "boolean.h"

// Armazena dados correspondentes ao álbum da faixa analisada
typedef struct _album {
    char *album_name; 
    char *album_id;
} ALBUM;

// Armazena dados correspondentes ao artista da faixa analisada
typedef struct _artist {
    char *artist_name; 
    char *artist_id; 
} ARTIST;

// Armazena dados correspondentes aos atributos da faixa analisada
typedef struct _attributes {
    double acousticness;
    double danceability; 
    double energy; 
    double instrumentalness; 
    double liveness; 
    double loudness; 
    double speechiness; 
    double tempo; 
    int time_signature; 
} ATTRIBUTES;

// Armazena dados correspondentes à música da faixa
typedef struct _music {
    char *track_name;
    char *track_id;
    char *release_date; 
    long int length; 
    double popularity; 
} MUSIC;

// Une as structs anteriores obtendo a faixa analisada
typedef struct _track {
    ARTIST *artist;
    ALBUM *album;
    MUSIC *music;
    ATTRIBUTES *attributes;
} TRACK;

boolean track_destruct(TRACK **);
TRACK *return_track_from_csv_string(char *);
void print_track(TRACK *);
void track_print(TRACK *);
int track_binary_search(TRACK **, char * , int , int);

#endif