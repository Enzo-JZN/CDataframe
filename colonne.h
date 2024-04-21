
#ifndef colonne_h
#define colonne_h

#define REALOC_SIZE 256

typedef struct {
    char titre[100];
    int taille_physique;
    int taille_logique;
    int* donnees; // correspond au tableau (au differentes valeurs qui seront presentes dans la colonne)
} COLUMN ;

COLUMN *create_column( char* title);
int insert_value(COLUMN* col, int value);
void delete_column(COLUMN **col);
void print_col(COLUMN* col);

int occurence(COLUMN *col, int x);
int valeur_presente_x (COLUMN *col, int x);
int valeur_superieur_x (COLUMN *col, int x);
int valeur_inferieur_x (COLUMN *col, int x) ;
int valeur_egale_x (COLUMN *col, int x);

#endif /* colonne_h */
