
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cdataframe.h"

// 4.2.1 Creation du CDATAFRAME + Fonctionnalités
// le CDataframe ne sera autre qu’un tableau de colonnes


// 1 - Alimentation
// Création d'un CDataFrame vide
// On crée un pointeur car cela nous permet d'allouer un espace dynamiquement.

CDataframe* create_CDATAFRAME(char *title) {
    CDataframe* DataFrame = (CDataframe*)malloc(sizeof(CDataframe));
    
    strcpy(DataFrame->titre, title);
    DataFrame->taille_logique = 0;
    DataFrame->taille_physique = 0;
    DataFrame->columns = NULL;
    
    return DataFrame;
}

// Remplissage du CDataframe à partir de saisies utilisateurs
CDataframe* create_CDATAFRAME_Saisi(char *title, int taille_logique, int taille_physique, COLUMN** tableau_colonne) {
    CDataframe* DataFrame = (CDataframe*)malloc(sizeof(CDataframe));
    strcpy(DataFrame->titre, title);
    DataFrame->taille_logique = taille_logique;
    DataFrame->taille_physique = taille_physique;
    DataFrame->columns = (COLUMN**)malloc(taille_physique*sizeof(COLUMN*));
    if (DataFrame->taille_logique != 0) {
        // Copier les pointeurs de colonnes un par un
        for (int i = 0; i < taille_logique; i++) {
            DataFrame->columns[i] = tableau_colonne[i];
        }
    }
    return DataFrame;
}

// Remplissage en dur du CDataframe ...

// 2 - Affichage

// Afficher tout le CDATAFRAME
void afficher_tout_CDATAFRAME (CDataframe* Datafram) {
    printf("title DATAFRAME : %s, taille logique : %d, taille physique : %d\n", Datafram->titre, Datafram->taille_logique, Datafram->taille_physique);
    for (int i = 0; i < Datafram->taille_logique; i++) {
        printf("title column[%d] : %s, taille logique : %d, taille physique : %d\n", i, Datafram->columns[i]->titre, Datafram->columns[i]->taille_logique, Datafram->columns[i]->taille_physique );
        for (int j = 0; j < Datafram->columns[i]->taille_logique; j ++) {
            printf("[%d] %d\n", j, Datafram->columns[i]->donnees[j]);
        }
        printf("\n");
    }
}

// Afficher une partie des lignes du CDataframe selon une limite fournie par l’utilisateur
void afficher_CDATAFRAME_ligne (CDataframe* Datafram, int nb_ligne) {
    printf("title DATAFRAME : %s, taille logique : %d, taille physique : %d\n", Datafram->titre, Datafram->taille_logique, Datafram->taille_physique);
    for (int i = 0; i < Datafram->taille_logique; i++) {
        printf("title column[%d] : %s, taille logique : %d, taille physique : %d\n", i, Datafram->columns[i]->titre, Datafram->columns[i]->taille_logique, Datafram->columns[i]->taille_physique );
        for (int j = 0; (j < Datafram->columns[i]->taille_logique && j < nb_ligne); j ++) {
            printf("[%d] %d\n", j, Datafram->columns[i]->donnees[j]);
        }
        printf("\n");
    }
}

// Afficher une partie des colonnes du CDataframe selon une limite fournie par l’utilisateur
void afficher_CDATAFRAME_colonne (CDataframe* Datafram, int nb_colonne) {
    printf("title DATAFRAME : %s, taille logique : %d, taille physique : %d\n", Datafram->titre, Datafram->taille_logique, Datafram->taille_physique);
    for (int i = 0; (i < Datafram->taille_logique && i < nb_colonne); i++) {
        printf("title column[%d] : %s, taille logique : %d, taille physique : %d\n", i, Datafram->columns[i]->titre, Datafram->columns[i]->taille_logique, Datafram->columns[i]->taille_physique );
        for (int j = 0; j < Datafram->columns[i]->taille_logique; j ++) {
            printf("[%d] %d\n", j, Datafram->columns[i]->donnees[j]);
        }
        printf("\n");
    }
}

// 3 - Opérations usuelles
// — Ajouter une ligne de valeurs au CDataframe
void ajouter_ligne_valeurs_CDataFrame (CDataframe *DataFrame);

// — Supprimer une ligne de valeurs du CDataframe
void supprimer_ligne_valeurs_CDataFrame (CDataframe *DataFrame);

// — Ajouter une colonne au CDataframe
void ajouter_colonne_valeurs_CDataFrame (CDataframe *DataFrame);

// — Supprimer une colonne du CDataframe
void supprimer_colonne_valeurs_CDataFrame (CDataframe *DataFrame);

// — Renommer le titre d’une colonne du CDataframe
void renommer_collone_CDataFrame (CDataframe *DataFrame, char* ancien_titre, char* noveau_titre);

// — Vérifier l’existence d’une valeur (recherche) dans le CDataframe
int occurence_valeur_Cdataframe (CDataframe* DataFrame, int x) {
    int nb = 0;
    for (int i = 0; i < DataFrame->taille_logique; i++) {
        nb += occurence(DataFrame->columns[i], x);
    }
    if (nb == 0) {
        return 0;
    }
    return 1;
}

// — Accéder/remplacer la valeur se trouvant dans une cellule du CDataframe en utilisant son numéro de ligne et de colonne
void remplacer_valeur_CDataFrame (CDataframe* DataFrame, int nouvelle_valeur, int num_ligne, int num_colonne);

// - Afficher les noms des colonnes
void afficher_nom_colonne_cdataframe (CDataframe* DataFrame) {
    for (int i = 0; i < DataFrame->taille_logique; i++) {
        printf("nom colonne [%d] : %s", i, DataFrame->columns[i]->titre);
    }
}

// 4 - Analyse et statistiques
// — Afficher le nombre de lignes
void Afficher_nb_lignes_Cdataframe (CDataframe* Dataframe){
    int nb_lignes = 0;
        for (int j = 0; j < Dataframe->columns[0]->taille_logique; j++) {
            nb_lignes += 1;
        printf("Le nombre de lignes est de %d\n", nb_lignes);
    }
}

// — Afficher le nombre de colonnes
void Afficher_nb_colonnes_Cdataframe (CDataframe* Dataframe){
    printf("Le nombre de lignes est de %d\n", Dataframe->taille_logique);
    }

// Nombre de cellules contenant une valeur égale à x donné en paramètre
void valeurs_egale_x_CdataFrame (CDataframe* DataFrame, int x) {
    int nb = 0;
    for (int i = 0; i < DataFrame->taille_logique; i++) {
        nb += occurence(DataFrame->columns[i], x);
    }
    printf("le nombre de cellules contenant une valeur égale à x est : %d", nb);
}

// Nombre de cellules contenant une valeur supérieure à x donné en paramètre
void valeurs_sup_x_CdataFrame (CDataframe* DataFrame, int x) {
    int nb = 0;
    for (int i = 0; i < DataFrame->taille_logique; i++) {
        nb += valeur_superieur_x (DataFrame->columns[i], x);
    }
    printf("le nombre de cellules contenant une valeur égale à x est : %d", nb);
}

// Nombre de cellules contenant une valeur inférieure à x donné en paramètre
void valeurs_inf_x_CdataFrame (CDataframe* DataFrame, int x) {
    int nb = 0;
    for (int i = 0; i < DataFrame->taille_logique; i++) {
        nb += valeur_inferieur_x(DataFrame->columns[i], x);
    }
    printf("le nombre de cellules contenant une valeur inférieur à x est : %d", nb);
}
