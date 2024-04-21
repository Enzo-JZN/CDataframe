
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colonne.h"

// On va maintenant faire une fonction qui permettra de créer une colonne vide (d'abord son prototype) (tache 4.1.1)
COLUMN *create_column( char* title) {
    // On crée une tableau dynamique qui retoune un pointeur column.
    COLUMN *column = (COLUMN*)malloc(sizeof(COLUMN)); // Ici column est notre objet, c'est le nom de l'objet, on donne à column un espace d'octer pour qu'il soit alloué dynamiquement.
    strcpy(column->titre, title); // Puisqu'on a defini un tableau dynamique / pointeur sur column on utilise -> pour acceder au attribut.
    column->taille_logique = 0;
    column->taille_physique = 0;
    column->donnees = NULL;
    
    return column;
}

// tache 4.1.2, Inserer une valeur dans une colonne.
int insert_value(COLUMN* col, int value) {
    if (col->taille_logique == col->taille_physique) {
        // COLUMN *col = (COLUMN*)realloc(col, REALOC_SIZE); Pourquoi on ne touche pas au nomnbre d'octet alloué à l'objet mais plutot à son attribut ne doit on pas modifier les 2 ?
        if (col->taille_physique == REALOC_SIZE) {
            return 0;
        }
        
        if (col->donnees == NULL) col->donnees = (int*)malloc(sizeof(COLUMN) * REALOC_SIZE);
        else col->donnees = (int*)realloc(col->donnees, REALOC_SIZE);
        
        col->taille_physique = REALOC_SIZE;
    }
    col->donnees[col->taille_logique] = value; // on insere value au tableau donnees à l'indice taille logique.
    col->taille_logique += 1;
    
    return 1;
}

// tache 4.1.3, Libérer l’espace allouée par une colonne.
void delete_column(COLUMN **col) {
    if ((*col) != NULL) {
        //On libere d'abord l'espace memoire alloué à l'attribut donnée de l'objet column
        free((*col)->donnees);
        //Puis on libere l'espace alloué à l'objet
        free((*col));
        //On met le pointeur à NULL pour éviter des bad access.
        *col = NULL;
    }
}

// tache 4.1.4, Afficher le contenu d’une colonne
void print_col(COLUMN* col) {
    // on crée une boucle allant de 0 à la taille logique et on affiche les valeurs.
    for (int i = 0; i < col->taille_logique; i++) {
        printf("[%d] %d\n", i, col->donnees[i]);
    }
}

// tache 4.1.5, Autres fonctions
// 1 - Retourner le nombre d'occurences d'une valeur x donnée en paramètre
int occurence(COLUMN *col, int x){
    int occurence = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        if (col->donnees[i] == x) {
            occurence += 1;
        }
    }
    return occurence;
}

// 2 - Retourner la valeur présente à la position x donné en paramètre
int valeur_presente_x (COLUMN *col, int x) {
    if (col->taille_logique > x) {
        return col->donnees[x];
    }
    return 0; // 0 correspond ici à (impossible de retourner une valeur)
}

// 3 - Retourner le nombre de valeurs qui sont supérieures à x donné en paramètre
int valeur_superieur_x (COLUMN *col, int x) {
    int nb = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        if (col->donnees[i] > x) {
            nb += 1;
        }
    }
    return nb;
}

// 4 - Retourner le nombre de valeurs qui sont inférieures à x donné en paramètre
int valeur_inferieur_x (COLUMN *col, int x) {
    int nb = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        if (col->donnees[i] < x) {
            nb += 1;
        }
    }
    return nb;
}

// 5 - Retourner le nombre de valeurs qui sont égales à x donné en paramètre
int valeur_egale_x (COLUMN *col, int x) {
    int nb = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        if (col->donnees[i] == x) {
            nb += 1;
        }
    }
    return nb;
}
