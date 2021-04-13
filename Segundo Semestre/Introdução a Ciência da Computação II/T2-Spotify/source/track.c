// Bernardo Marques Costa - 11795551

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "track.h"
#include "utils.h"

/* Destruct da struct track, libera a memória */
boolean track_destruct(TRACK **track){
    
    if(track == NULL || (*track) == NULL)
        return FALSE; 

    free((*track)->album->album_name);
    free((*track)->album->album_id);
    free((*track)->album);
    
    free((*track)->artist->artist_name);
    free((*track)->artist->artist_id);
    free((*track)->artist);
    
    free((*track)->music->track_name);
    free((*track)->music->track_id);

    free((*track)->music->release_date);
    free((*track)->music);

    free((*track)->attributes);
    free((*track));
    (*track) = NULL;

    return TRUE;
}

/* Retorna os dados correspondentes ao álbum da track (linha) analisada */
ALBUM *return_album(char *string_csv, int *start, boolean *is_end){
    ALBUM *new_album = calloc(1, sizeof(ALBUM));

    new_album->album_name = part_string(string_csv, *start, is_end); 
    *start += strlen(new_album->album_name) + 2;
    
    new_album->album_id = part_string(string_csv, *start, is_end); 
    *start += strlen(new_album->album_id) + 2;

    return new_album;
}

/* Retorna os dados correspondentes ao artista da track (linha) analisada */
ARTIST *return_artist(char *string_csv, int *start, boolean *is_end){
    ARTIST *new_artist = calloc(1, sizeof(ARTIST));

    new_artist->artist_name = part_string(string_csv, *start, is_end);
    *start += strlen(new_artist->artist_name) + 2;

    new_artist->artist_id = part_string(string_csv, *start, is_end);
    *start += strlen(new_artist->artist_id) + 2;

    return new_artist;
}

/* Retorna os dados correspondentes aos atributos da track (linha) analisada */
ATTRIBUTES *return_attributes(char *string_csv, int *start, boolean *is_end){
    ATTRIBUTES *new_attributes = calloc(1, sizeof(ATTRIBUTES));

    char *acousticness = part_string(string_csv, *start, is_end);
    *start += strlen(acousticness) + 2;
    new_attributes->acousticness = atof(acousticness);
    free(acousticness);

    char *danceability =  part_string(string_csv, *start, is_end);
    *start += strlen(danceability) + 2;
    new_attributes->danceability = atof(danceability);
    free(danceability);

    char *energy = part_string(string_csv, *start, is_end);
    *start += strlen(energy) + 2;
    new_attributes->energy = atof(energy);
    free(energy);

    char *instrumentalness = part_string(string_csv, *start, is_end);
    *start += strlen(instrumentalness) + 2;
    new_attributes->instrumentalness = atof(instrumentalness);
    free(instrumentalness);

    char *liveness = part_string(string_csv, *start, is_end);
    *start += strlen(liveness) + 2;  
    new_attributes->liveness = atof(liveness);
    free(liveness);  

    char *loudness = part_string(string_csv, *start, is_end);
    *start += strlen(loudness) + 2;
    new_attributes->loudness = atof(loudness);
    free(loudness);

    char *speechiness = part_string(string_csv, *start, is_end);
    *start += strlen(speechiness) + 2;
    new_attributes->speechiness = atof(speechiness);
    free(speechiness);

    char *tempo = part_string(string_csv, *start, is_end);
    *start += strlen(tempo) + 2;
    new_attributes->tempo = atof(tempo);
    free(tempo);

    char *time_signature = part_string(string_csv, *start, is_end);
    *start += strlen(time_signature) + 2;
    new_attributes->time_signature = atoi(time_signature);
    free(time_signature);

    return new_attributes;
}
 
/* Contrói a faixa (track), analisada na linha do CSV considerada no momento */
TRACK *return_track_from_csv_string(char *string_csv){
    if(string_csv == NULL) return FALSE;

    TRACK *new_track = calloc(1, sizeof(TRACK));
    new_track->music = calloc(1, sizeof(MUSIC));
    
    int start = 0;
    boolean is_end = FALSE;
    
    new_track->music->track_name = part_string(string_csv, start, &is_end);
    start += strlen(new_track->music->track_name) + 2;

    new_track->music->track_id = part_string(string_csv, start, &is_end);
    start += strlen(new_track->music->track_id) + 2;

    new_track->album = return_album(string_csv, &start, &is_end);
    new_track->artist = return_artist(string_csv, &start, &is_end);

    new_track->music->release_date = part_string(string_csv, start, &is_end);
    start += strlen(new_track->music->release_date) + 2;

    char *length = part_string(string_csv, start, &is_end);
    start += strlen(length) + 2;
    new_track->music->length = atoi(length);
    free(length);

    char *popularity = part_string(string_csv, start, &is_end);
    start += strlen(popularity) + 2;
    new_track->music->popularity = atof(popularity);
    free(popularity);

    new_track->attributes = return_attributes(string_csv, &start, &is_end);

    return new_track;
}

/* 
    Realiza uma busca binária em uma lista de tracks (que deve ser previamente ordeanada) 
    informando a existência ou não existência de um track_id nesta lista de múscias       
*/
int track_binary_search(TRACK **db, char * id, int low, int high) {
    if(db == NULL) return -404;

    while(low <= high) {
        int mid = (int) low + (high - low)/2;

        if(strcmp(db[mid]->music->track_id, id) == 0)
            return mid;
        
        else if(strcmp(db[mid]->music->track_id, id) < 0)
            low = mid + 1;

        else 
            high = mid - 1; 
    }

    return -1;
}