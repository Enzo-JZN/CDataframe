#ifndef _COLONNES_H
#define _COLONNES_H

#define TRUE            1
#define FALSE           0

#define ASC             0
#define DESC            1

#define REALOC_SIZE     256 // Taille de réallocation demandé.

// On fait un enum, ce qui nous permet ainsi de répresenter les differents tpyes possibles des colonnes par des valeurs constantes, rendant le code plus compréhensible.
enum enum_type
{
    NULLVAL = 1 , UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
};
typedef enum enum_type ENUM_TYPE; // On fait un typedef pour faciliter l'écriture du programme, on sera ainsi plus obliger d'écrire enum enum_type variable = ... On gagne du temps et de la lisibilité.

#define ENUM_TYPE_STR(type) \
    (NULLVAL    == type ? "NULLVAL" : \
    (UINT       == type ? "UINT"    : \
    (INT        == type ? "INT"     : \
    (CHAR       == type ? "CHAR"    : \
    (FLOAT      == type ? "FLOAT"   : \
    (DOUBLE     == type ? "DOUBLE"  : \
    (STRING     == type ? "STRING"  : \
    (STRUCTURE  == type ? "STRUCTURE" : "Indéfini" \
))))))))

// on a fait appel à une macro pour nous permettre d'obtenir une chaîne de caractères représentant le nom du type énuméré correspondant. Pour débug ou afficher le type, c'est plus facile de créer une macro pour mieux comprendre

/* Afin de permettre au CDataframe de stocker des données de types différents, il est nécessaire de
modifier la structure de la colonne. En effet, il s’agira toujours d’un ensemble de colonnes. Seulement,
nous souhaitons que les données d’une même colonne soient de même type mais que celles de deux
colonnes différentes soient de deux types différents.
*/

union column_type {
    unsigned int uint_value; // entier positif ou nul --> 4 octets
    signed int int_value; // entier positif, négatif ou nul --> 4 octets
    char char_value; // caractere --> 1 octet
    float float_value; // réel --> 4 octets
    double double_value; // réel long --> 8 octets
    char* string_value; // pointeur vers une chaine --> 8 octets
    void* struct_value; // pointeur vers une structure --> 8 octets
};
typedef union column_type COL_TYPE ; // COL_TYPE devient en quelque sorte lui même une structure grâce au typedef et union

// Une union permet de stocker différentes variables dans le même emplacement mémoire. Cela signifie que l'union peut contenir une seule de ces valeurs à la fois. La taille de l'union est déterminer par la taille de son plus grand membre. Cela nous permettrait que quelque soit le type de la column, on aura assez de place pour la stocker dans l'emplacement mémoire.

struct column {
    char *titre;
    unsigned int taille_logique; //taille logique
    unsigned int taille_physique; //taille physique
    ENUM_TYPE column_type; // type de la colonne
    COL_TYPE **data; // tableau de pointeurs vers les données stockées
    
    unsigned long long  *index; // tableaux d'index
    int valid_index; // 0: no index, -1 : invalid index, 1 : valid index
    int sort_dir; // 0: ASC, 1: DESC // Pour les fonctions de tri.
};
typedef struct column COLUMN;

// Prototypes des différentes fonctions :

COLUMN *create_column(ENUM_TYPE type, char *title); // Créer une colonne
int insert_value(COLUMN *col, COL_TYPE value); // Insérer une valeur dans une colonne
int replace_value(COLUMN* col, int ligne, COL_TYPE value); // Remplace une valeur à une ligne spécifique dans une colonne.
void delete_column(COLUMN *col); // Supprime et libère la mémoire d'une colonne.

void sort(COLUMN *col, int sort_dir); // Trie les valeurs d"une colonne dans un ordre spécifique.
void erase_index(COLUMN *col);
int check_index(COLUMN *col);
void update_index(COLUMN *col);
int search_value_in_column(COLUMN *col, COL_TYPE value); // Recherche une valeur dans une colonne.

void print_col_by_index(COLUMN *col); // affiche les valeurs d'une colonne par leur index
char *convert_value(ENUM_TYPE column_type, COL_TYPE value);
void print_col(COLUMN* col); // affiche une colonne

COL_TYPE val_at_pos(COLUMN* col,int pos); // Retourne une valeur à une position spécifique dans une colonne.
int occu_val(COLUMN* col, COL_TYPE value); // Retourne le nombre d'occurrences d'une valeur dans une colonne.
int nb_val_supp(COLUMN* col, COL_TYPE value); // Retourne le nombre de valeurs supérieures à une valeur spécifiée.
int nb_val_inf(COLUMN* col, COL_TYPE value); // Retourne le nombre de valeurs inferieures à une valeur spécifiée.


#endif
