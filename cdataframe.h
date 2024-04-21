

#ifndef cdataframe_h
#define cdataframe_h

#include "colonne.h"

// On souhait d'abord créer un objet et une structure colonne :
// Création de l'objet et des attributs d'un CDATAFRAM
typedef struct {
    char titre[20];
    COLUMN **columns; // Cela nous permet ainsi de créer un tableau de colonne, nous déclarons un pointeur vers un tableau de pointeurs vers des colonnes. Cela signifie que nous pouvons stocker plusieurs pointeurs de colonnes dans columns, ce qui nous permet de représenter un tableau dynamique de colonnes.
    int taille_physique;
    int taille_logique;
} CDataframe;

// fonctionnalités 1 :
CDataframe* create_CDATAFRAME(char *title);
CDataframe* create_CDATAFRAME_Saisi(char *title, int taille_logique, int taille_physique, COLUMN** tableau_colonne);

// fonctionnalités 2 :
void afficher_tout_CDATAFRAME (CDataframe* Datafram);
void afficher_CDATAFRAME_ligne (CDataframe* Datafram, int nb_ligne);
void afficher_CDATAFRAME_colonne (CDataframe* Datafram, int nb_colonne);

// fonctionnalités 3 :

void ajouter_ligne_valeurs_CDataFrame (CDataframe *DataFrame);
void supprimer_ligne_valeurs_CDataFrame (CDataframe *DataFrame);
void ajouter_colonne_valeurs_CDataFrame (CDataframe *DataFrame);
void supprimer_colonne_valeurs_CDataFrame (CDataframe *DataFrame);
void renommer_collone_CDataFrame (CDataframe *DataFrame, char* ancien_titre, char* noveau_titre);
int occurence_valeur_Cdataframe (CDataframe* DataFrame, int x);
void remplacer_valeur_CDataFrame (CDataframe* DataFrame, int nouvelle_valeur, int num_ligne, int num_colonne);

void afficher_nom_colonne_cdataframe (CDataframe* DataFrame);

// fonctionnalités 4 :
void Afficher_nb_lignes_Cdataframe (CDataframe* Dataframe);
void Afficher_nb_colonnes_Cdataframe (CDataframe* Dataframe);
void valeurs_egale_x_CdataFrame (CDataframe* DataFrame, int x);
void valeurs_sup_x_CdataFrame (CDataframe* DataFrame, int x);
void valeurs_inf_x_CdataFrame (CDataframe* DataFrame, int x);

#endif /* cdataframe_h */
