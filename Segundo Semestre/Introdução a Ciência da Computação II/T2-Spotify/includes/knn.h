// Bernardo Marques Costa - 11795551

#ifndef _KNN_C_
#define _KNN_C_

typedef struct _cell CELL;
typedef struct _dm DM;

struct _cell {
    double distance;
    char *id;
};

struct _dm {
    CELL **values;
    int size;
};

DM *create_matrix(TRACK **, int);
void dm_delete(DM **);
void print_most_similar_tracks(DM *, char *, int, TRACK **);

#endif