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


// 2 - Affichage

// Afficher tout le CDATAFRAME
void afficher_tout_CDATAFRAME (CDataframe* Datafram) {
    printf("title DATAFRAME : %s, taille logique : %d, taille physique : %d\n", 
           Datafram->titre,
           Datafram->taille_logique,
           Datafram->taille_physique);
    for (int i = 0; i < Datafram->taille_logique; i++) {
        printf("title column[%d] : %s, taille logique : %d, taille physique : %d\n", 
               i,
               Datafram->columns[i]->titre,
               Datafram->columns[i]->taille_logique,
               Datafram->columns[i]->taille_physique);
        
        print_col(Datafram->columns[i]);
        printf("\n");
    }
}

// Afficher une partie des lignes du CDataframe selon une limite fournie par l’utilisateur
void afficher_CDATAFRAME_ligne (CDataframe* Datafram, int nb_ligne) {
    printf("title DATAFRAME : %s, taille logique : %d, taille physique : %d\n", Datafram->titre, Datafram->taille_logique, Datafram->taille_physique);
    for (int i = 0; i < Datafram->taille_logique; i++) {
        printf("title column[%d] : %s, taille logique : %d, taille physique : %d\n",
               i, 
               Datafram->columns[i]->titre,
               Datafram->columns[i]->taille_logique,
               Datafram->columns[i]->taille_physique);
        for (int j = 0; (j < Datafram->columns[i]->taille_logique && j < nb_ligne); j ++) {
            COL_TYPE *p = Datafram->columns[i]->data[j];
            printf("Index %d = %s\n", i, convert_value(Datafram->columns[i]->column_type, *p));
        }
        printf("\n");
    }
}

// Afficher une partie des colonnes du CDataframe selon une limite fournie par l’utilisateur
void afficher_CDATAFRAME_colonne (CDataframe* Datafram, int nb_colonne) {
    printf("title DATAFRAME : %s, taille logique : %d, taille physique : %d\n", Datafram->titre, Datafram->taille_logique, Datafram->taille_physique);
    for (int i = 0; (i < Datafram->taille_logique && i < nb_colonne); i++) {
        printf("title column[%d] : %s, taille logique : %d, taille physique : %d\n", 
               i,
               Datafram->columns[i]->titre,
               Datafram->columns[i]->taille_logique,
               Datafram->columns[i]->taille_physique );
        for (int j = 0; j < Datafram->columns[i]->taille_logique; j ++) {
            COL_TYPE *p = Datafram->columns[i]->data[j];
            printf("Index %d = %s\n", i, convert_value(Datafram->columns[i]->column_type, *p));
            // On a utilisé la fonction convert_value pour pouvoir afficher chaque valeur, ce qui nous permet d'éviter de
            // faire un switch et de tester le bon %.. pour chaque ENUM TYPE.
        }
        printf("\n");
    }
}

// 3 - Opérations usuelles
// — Ajouter une ligne de valeurs au CDataframe
void ajouter_ligne_valeurs_CDataFrame (CDataframe *DataFrame)
{
    // A faire s'il reste du temps
}

// — Supprimer une ligne de valeurs du CDataframe
void supprimer_ligne_valeurs_CDataFrame (CDataframe *DataFrame)
{
    // A faire s'il reste du temps
}

// — Ajouter une colonne au CDataframe

void ajouter_colonne_valeurs_CDataFrame (CDataframe *DataFrame, COLUMN *column) {
    if (DataFrame->columns == NULL) {
        DataFrame->columns = (COLUMN**)malloc(DataFrame->taille_physique * sizeof(COLUMN));
    } else {
        // si le tableau est "plein" => on réalloue dynamiquement la taille physique
        if(DataFrame->taille_physique == DataFrame->taille_logique) {
            DataFrame->taille_physique += REALOC_SIZE;
            DataFrame->columns = (COLUMN**)realloc(DataFrame->columns, DataFrame->taille_physique * sizeof(COLUMN));
        }
    }
    if (DataFrame->columns == NULL) return;
    
    DataFrame->columns[DataFrame->taille_logique] = column;
    DataFrame->taille_logique++;
}

// — Supprimer une colonne du CDataframe
void supprimer_colonne_valeurs_CDataFrame (CDataframe *DataFrame, int pos) 
{
    if (pos > DataFrame->taille_logique) return;
    
    // A faire s'il reste du temps
}

// — Renommer le titre d’une colonne du CDataframe
void renommer_colonne_CDataFrame (CDataframe *DataFrame, char *titre, char *nouveau_titre)
{
    if (nouveau_titre == NULL) return;
    
    for (int i = 0; i < DataFrame->taille_logique; i++) {
        COLUMN *col = DataFrame->columns[i];
        if (strcmp(col->titre, titre) == 0) {
            free(col->titre);
            col->titre = malloc(strlen(nouveau_titre) + 1);
            strcpy(col->titre, nouveau_titre);
        }
    }
}

// — Vérifier l’existence d’une valeur dans le CDataframe
int occurence_valeur_Cdataframe(CDataframe* DataFrame, ENUM_TYPE type, COL_TYPE value) {
    int nb = 0;
    for (int i = 0; i < DataFrame->taille_logique; i++) {
        COLUMN *col = DataFrame->columns[i];
        if (col->column_type == type)
            nb += occu_val(col, value);
    }
    if (nb == 0) {
        return 0;
    }
    return 1;
}

// — Accéder/remplacer la valeur se trouvant dans une cellule du CDataframe en utilisant son numéro de ligne et de colonne
int remplacer_valeur_CDataFrame (CDataframe* DataFrame, int num_ligne, int num_colonne, COL_TYPE nouvelle_valeur)
{
    if (num_colonne > DataFrame->taille_logique ) return FALSE;
    
    COLUMN *col = DataFrame->columns[num_colonne];    
    return replace_value(col, num_ligne, nouvelle_valeur);
}

// - Afficher les noms des colonnes
void afficher_nom_colonne_cdataframe (CDataframe* DataFrame) 
{
    for (int i = 0; i < DataFrame->taille_logique; i++) {
        printf("nom colonne [%d] : %s\n", i, DataFrame->columns[i]->titre);
    }
}

// 4 - Analyse et statistiques
// — Afficher le nombre de lignes
void Afficher_nb_lignes_Cdataframe (CDataframe* Dataframe)
{    
    for (int i = 0; i < Dataframe->taille_logique; i++) {
        printf("'%s' - Nombre lignes %d\n", 
               Dataframe->columns[i]->titre,
               Dataframe->columns[i]->taille_logique);
    }
}

// — Afficher le nombre de colonnes
void Afficher_nb_colonnes_Cdataframe (CDataframe* Dataframe) 
{
    printf("Nombre de colonnes présente est de %d\n", Dataframe->taille_logique);
}

// Nombre de cellules contenant une valeur égale à x donné en paramètre
void valeurs_egale_x_CdataFrame (CDataframe* DataFrame, int x) 
{
    int nb = 0;
    for (int i = 0; i < DataFrame->taille_logique; i++) {
        for (int j = 0; j < DataFrame->columns[i]->taille_logique; j ++) {
            COL_TYPE *p = DataFrame->columns[i]->data[j];
            switch (DataFrame->columns[i]->column_type) {
                case INT:
                    if (p->int_value == x) nb++;
                    break;
                case UINT:
                    if (p->uint_value == x) nb++;
                    break;
                case FLOAT:
                    if (p->float_value == x) nb++;
                case DOUBLE:
                    if (p->double_value == x) nb++;
                    break;
                default:
                    break;
            }
        }
    }
    printf("le nombre de cellules contenant une valeur égale à %d est : %d", x, nb);
}

// Nombre de cellules contenant une valeur supérieure à x
void valeurs_sup_x_CdataFrame (CDataframe* DataFrame, int x) 
{
    int nb = 0;
    for (int i = 0; i < DataFrame->taille_logique; i++) {
        for (int j = 0; j < DataFrame->columns[i]->taille_logique; j ++) {
            COL_TYPE *p = DataFrame->columns[i]->data[j];
            switch (DataFrame->columns[i]->column_type) {
                case INT:
                    if (p->int_value > x) nb++;
                    break;
                case UINT:
                    if (p->uint_value > x) nb++;
                    break;
                case FLOAT:
                    if (p->float_value > x) nb++;
                case DOUBLE:
                    if (p->double_value > x) nb++;
                    break;
                default:
                    break;
            }
        }
    }
    printf("le nombre de cellules contenant une valeur supérieur à %d est : %d", x, nb);
}

// Nombre de cellules contenant une valeur inférieure à x donné
void valeurs_inf_x_CdataFrame (CDataframe* DataFrame, int x) 
{
    int nb = 0;
    for (int i = 0; i < DataFrame->taille_logique; i++) {
        for (int j = 0; j < DataFrame->columns[i]->taille_logique; j ++) {
            COL_TYPE *p = DataFrame->columns[i]->data[j];
            switch (DataFrame->columns[i]->column_type) {
                case INT:
                    if (p->int_value < x) nb++;
                    break;
                case UINT:
                    if (p->uint_value < x) nb++;
                    break;
                case FLOAT:
                    if (p->float_value < x) nb++;
                case DOUBLE:
                    if (p->double_value < x) nb++;
                    break;
                default:
                    break;
            }
        }
    }
    printf("le nombre de cellules contenant une valeur inférieur à %d est : %d", x, nb);
}

// Vérifier l’existence d’une valeur (recherche) dans le CDataframe
int verifier_existence_valeur(CDataframe* DataFrame, ENUM_TYPE type, COL_TYPE value)
{
    for (int i = 0; i < DataFrame->taille_logique; i++) {
        COLUMN *col = DataFrame->columns[i];

        if (type == col->column_type) {
            int occurences = occu_val(col, value);
            if (occurences > 0) {
                char *res = convert_value(col->column_type, value);
                printf("Valeur (%s) - Trouvé en colonne %d\n", res, i);
                
                return TRUE;
            }
        }
    }
    
    
    printf("Non trouvé\n");
    
    return FALSE;
}
