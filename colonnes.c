#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colonnes.h"



COLUMN *create_column(ENUM_TYPE type, char *title)
{
    COLUMN* c = (COLUMN*)malloc(sizeof(COLUMN));
    if (c == NULL) return NULL;
    
    c->titre = malloc(strlen(title) + 1); // On ajoute 1 pour inclure le caractère '\0' pour les chaines de caractere, si on ne l'ajoute pas cela pourrait potenitelemment créer des erreurs.
    strcpy(c->titre, title);
    
    c->taille_physique = REALOC_SIZE;
    c->taille_logique = 0;
    c->data = NULL;
    c->column_type = type;
    c->index = NULL;        // champ nécessaire pour l'étape 3
    c->valid_index = 0;     // champ nécessaire pour l'étape 3
    c->sort_dir = ASC;      // champ nécessaire pour l'étape 3
    
    return c;
}

//Fonction permettant d'inserer une valeur dans une colonne, on a preferer mettre en paramètre un type COL_TYPE qu'un pointeur de void, car on se disait

int insert_value(COLUMN *col, COL_TYPE value)
{
    // On va d'abord vérifier si la taille logique < taille physique et possiblement réalloc, et sinon on va allouer un espace dynamique au champ data (qui est un tableau de pointeurs de COL_TYPE)
    
    // si la colonne ne contient aucune valeurs => on alloue dynamiquement la taille physique
    if (col->data == NULL) {
        // col->data = (void**)malloc(col->taille_physique * sizeof(void*));
        col->data = (COL_TYPE**)malloc(col->taille_physique * sizeof(COL_TYPE));
    } else {
        // si le tableau est "plein" => on réalloue dynamiquement la taille physique
        if(col->taille_physique == col->taille_logique) {
            col->taille_physique += REALOC_SIZE;
            col->data = (COL_TYPE**)realloc(col->data, col->taille_physique * sizeof(COL_TYPE));
        }
    }
    if (col->data == NULL) return FALSE; // Si l'allocatio dynamique n'a pas marché on return
    int index = col->taille_logique;
    
    col->data[index] = (COL_TYPE*) malloc (sizeof(COL_TYPE));
        
    switch(col->column_type) {
        case STRING:
            if (value.string_value == NULL) col->data[index]->string_value = NULL;
            else col->data[index]->string_value = strdup(value.string_value);
            break;
        default: {
            *(col->data[index]) = value;
            break;
        }
    }
        
    col->taille_logique++;

    return TRUE;
}


int replace_value(COLUMN* col, int index, COL_TYPE value)
{
    if (index > col->taille_logique) return FALSE;
    
    switch(col->column_type) {
        case STRING:
            if (col->data[index]->string_value != NULL)
                free(col->data[index]->string_value);
            if (value.string_value == NULL) col->data[index]->string_value = NULL;
            else col->data[index]->string_value = strdup(value.string_value);
            break;
        default: {
            *(col->data[index]) = value;
            break;
        }
    }

    return TRUE;
}



COL_TYPE val_at_pos(COLUMN* col,int pos)
{
    if (pos > col->taille_logique) return (COL_TYPE)0;
    
    COL_TYPE *p = col->data[pos];

    return *p;
}

int occu_val(COLUMN* col, COL_TYPE value)
{
    int i,cpt=0;
    for(i = 0; i < col->taille_logique ; i++) {
        COL_TYPE *p = col->data[i];

        // On fait un switch pour chaque type, puisqu'il est question de comparaison entre notre parametre value, et la
        // valeur contenue par les pointeurs du tableau data. pour comparer ces valeurs on aura besoin de choisir le
        // membre que l'on veut pour les int par exemple il faudra écrire value.int_value
        
        switch (col->column_type) {
            case INT:
                if (p->int_value == value.int_value) cpt++;
                break;
            case UINT:
                if (p->uint_value == value.uint_value) cpt++;
                break;
            case STRING:
                if (p->string_value != NULL && strcmp(p->string_value, value.string_value) == 0) cpt++;
            case CHAR:
                if (p->char_value == value.char_value) cpt++;
                break;
            case FLOAT:
                if (p->float_value == value.float_value) cpt++;
                break;
            case DOUBLE:
                if (p->double_value == value.double_value) cpt++;
                break;
            case STRUCTURE:
                break;
            default:
                break;
        }
    }
    
    return cpt;
}



int nb_val_supp(COLUMN* col, COL_TYPE value)
{
    int i,cpt=0;
    for(i = 0; i < col->taille_logique; i++) {
        COL_TYPE *p = col->data[i];
        
        // Pour répondre à la problématique de cette question il faudra faire de même que pour la fonction précdente, il
        // nécessaire d'utiliser le switch pour comparer les valeurs.
        
        switch (col->column_type) {
            case INT:
                if (p->int_value > value.int_value) cpt++;
                break;
            case UINT:
                if (p->uint_value > value.uint_value) cpt++;
                break;
            case STRING: {
                int val = strcmp(p->string_value, value.string_value);
                if (val > 0) cpt++;
                break;
                // Valeurs de retour pour un strcmp
                // 0 : Les deux chaînes sont égales.
                // < 0 : La première chaîne (p->string_value) est inférieure à la seconde (value.string_value) en termes de valeur ASCII.
                // > 0 : La première chaîne (p->string_value) est supérieure à la seconde (value.string_value) en termes de valeur ASCII
            }
            case FLOAT:
                if (p->float_value > value.float_value) cpt++;
                break;
            case DOUBLE:
                if (p->double_value > value.double_value) cpt++;
                break;
            case STRUCTURE:
                break;
            default:
                break;
        }
    }
    
    return cpt;
}

// Même fonction que la précedente sauf que là on met des <
int nb_val_inf(COLUMN* col, COL_TYPE value)
{
    int i,cpt=0;
    for(i = 0; i < col->taille_logique ; i++) {
        COL_TYPE *p = col->data[i];
        switch (col->column_type) {
            case INT:
                if (p->int_value < value.int_value) cpt++;
                break;
            case UINT:
                if (p->uint_value < value.uint_value) cpt++;
                break;
            case STRING: {
                int val = strcmp(p->string_value, value.string_value);
                if (val < 0) cpt++;
                break;
            } // il est necessaire de mettre de {} car sinon il considere que la variable val n'a pas été déclaré.
            case FLOAT:
                if (p->float_value < value.float_value) cpt++;
                break;
            case DOUBLE:
                if (p->double_value < value.double_value) cpt++;
                break;
            case STRUCTURE:
                break;
            default:
                break;
        }
    }
    
    return cpt;
}

// la fonction delete_column, permet de supprimer une colonne. Pour supprimer une colonen, il sera nécessaire de liberer
// l'espace alloué dynamiquement au different champs de la struct. On va liberer tous les espaces dynamiques soit data,
// index et titre. et ensuite on libere la structure en elle même.
void delete_column(COLUMN *col)
{
    
    // Cette ligne nous permettait de mieux debug, ici on a fait appel à la macro pour printf le type de la colonne.
    printf("`%s` Release (type: %s)\n", col->titre, ENUM_TYPE_STR(col->column_type));
    
    for (int i=0;i<col->taille_logique;i++) {
        COL_TYPE *p = col->data[i];
        if (col->column_type == STRING) {
            if (col->data[i]->string_value != NULL)
                free(col->data[i]->string_value);
        }
        if (p != NULL) free(p);
    }

    free(col->data);
    free(col->index);
    free(col->titre);
    free(col);
}


//Fonction permettant de permutter des valeurs a et b qui servira au trie quicksort et à la focntion partition

void permutation(ENUM_TYPE column_type, COL_TYPE *a, COL_TYPE *b)
{
    if (column_type == INT) {
        int temp = a->int_value;
        a->int_value = b->int_value;
        b->int_value = temp;
    }
    else if (column_type == UINT) {
        int temp = a->uint_value;
        a->uint_value = b->uint_value;
        b->uint_value = temp;
    }
    else if (column_type == FLOAT) {
        int temp = a->float_value;
        a->float_value = b->float_value;
        b->float_value = temp;
    }
    else if (column_type == CHAR) {
        int temp = a->char_value;
        a->char_value = b->char_value;
        b->char_value = temp;
    }
    else if (column_type == DOUBLE) {
        int temp = a->double_value;
        a->double_value = b->double_value;
        b->double_value = temp;
    }
    else if (column_type == STRING) {
        char *temp = a->string_value;
        a->string_value = b->string_value;
        b->string_value = temp;
    }
}

// La fonction partition fait partie d'un algorithme de tri rapide (Quicksort).
// Cette fonction est utilisée pour réorganiser les éléments d'un tableau de sorte que tous les éléments inférieurs ou
// égaux à un pivot soient placés avant ceux qui sont supérieurs.

int partition(ENUM_TYPE column_type, COL_TYPE tab[], int left, int right)
{
    int i = left; // indice de debut de la zone à triée
    int j = right; // indice de fin de la zone à triée
    
    if (column_type == INT) {
        int pivot  = tab[left].int_value; // Le pivot est choisi comme le premier élément du tableau
        while (i < j) {
            while (tab[i].int_value <= pivot && i <= right - 1) {
                i++;
            }
            // boucle qui s'arrete lorsque tab[i] est superieur à notre pivot
            while (tab[j].int_value > pivot && j >= left + 1) {
                j--;
            }
            // boucle qui s'arrete lorsque tab[i] est inferieur à notre pivot
            if (i < j) {
                permutation(column_type, &tab[i], &tab[j]);
            // on permute les élements les plus grands et plus petit.
            }
        }
        permutation(column_type, &tab[left], &tab[j]);
    }
    else if (column_type == UINT) {
        unsigned int pivot  = tab[left].uint_value;
        while (i < j) {
            while (tab[i].uint_value <= pivot && i <= right - 1) {
                i++;
            }
            
            while (tab[j].uint_value > pivot && j >= left + 1) {
                j--;
            }
            if (i < j) {
                permutation(column_type, &tab[i], &tab[j]);
            }
        }
        permutation(column_type, &tab[left], &tab[j]);
    }
    else if (column_type == FLOAT) {
        float pivot  = tab[left].float_value;
        while (i < j) {
            while (tab[i].float_value <= pivot && i <= right - 1) {
                i++;
            }
            
            while (tab[j].float_value > pivot && j >= left + 1) {
                j--;
            }
            if (i < j) {
                permutation(column_type, &tab[i], &tab[j]);
            }
        }
        permutation(column_type, &tab[left], &tab[j]);
    }
    else if (column_type == DOUBLE) {
        float pivot  = tab[left].double_value;
        while (i < j) {
            while (tab[i].double_value <= pivot && i <= right - 1) {
                i++;
            }
            
            while (tab[j].double_value > pivot && j >= left + 1) {
                j--;
            }
            if (i < j) {
                permutation(column_type, &tab[i], &tab[j]);
            }
        }
        permutation(column_type, &tab[left], &tab[j]);
        permutation(column_type, &tab[left], &tab[j]);
    }
    else if (column_type == CHAR) {
        float pivot  = tab[left].char_value;
        while (i < j) {
            while (tab[i].char_value <= pivot && i <= right - 1) {
                i++;
            }
            
            while (tab[j].char_value > pivot && j >= left + 1) {
                j--;
            }
            if (i < j) {
                permutation(column_type, &tab[i], &tab[j]);
            }
        }
        permutation(column_type, &tab[left], &tab[j]);
    }
    else if (column_type == STRING) {
        char *pivot  = tab[left].string_value;
        while (i < j) {
            while (strcmp(tab[i].string_value, pivot) <= 0 && i <= right - 1) {
                i++;
            }
            
            while (strcmp(tab[j].string_value, pivot) >= 1 && j >= left + 1) {
                j--;
            }

            if (i < j) {
                permutation(column_type, &tab[i], &tab[j]);
            }
        }
        permutation(column_type, &tab[left], &tab[j]);
    }
        
    return j;
} 

//  Fonction de trie quicksort fait dans un cas Ascendant
void quickSort(ENUM_TYPE column_type, COL_TYPE tab[], int left, int right)
{
    if (left < right) {
        int partitionIndex = partition(column_type, tab, left, right);
        quickSort(column_type, tab, left, partitionIndex - 1);
        quickSort(column_type, tab, partitionIndex + 1, right);
    }
}

// Fonction de trie dependant du champ sort_dir soit ASC ou DESC
void sort(COLUMN *col, int sort_dir)
{
    switch(col->column_type) {
        case INT:
        case UINT:
        case FLOAT:
        case DOUBLE:
        case CHAR:
        case STRING:
            quickSort(col->column_type, (COL_TYPE *)col->data, 0, col->taille_logique - 1);
            if (sort_dir == DESC) {
                // Inverse order of col->data
            }
            break;
        default:
            break;
    }
}

// Fonction permettant d'afficher le contenue d'une colonne triée en fonction du tableau d'index.

void print_col_by_index(COLUMN *col) {
    
}


// Fonction permettant de liberer le tableau d'index

void erase_index(COLUMN *col) {
    if (col->index) free(col->index);
    col->index = NULL;
    col->valid_index = 0;
    col->sort_dir = ASC;
}

// Vérifier si une colonne dispose d’un index

int check_index(COLUMN *col) {
    return col->valid_index;
}



void update_index(COLUMN *col) {
    
}


int search_value_in_column(COLUMN *col, COL_TYPE value) {
    return 0;
}


char *convert_value(ENUM_TYPE column_type, COL_TYPE value) {
    static char string[256];
    // on crée un tableau en static pour que lors du retour de la fonction le tableau soit conservée sinon
    // cela nous renverrait un tableau de caracteres mais il serait desalloue car défini en local.
    
    switch(column_type) {
        case INT: {
            sprintf(string, "%d", value.int_value); // Sprintf convertit la valeur entière value.int_value en une chaîne de
            // caractères et la stocke dans la variable string.
            break;
        }
        case FLOAT: {
            sprintf(string, "%f", value.float_value);
            break;
        }
        case DOUBLE: {
            sprintf(string, "%lf", value.double_value);
            break;
        }
        case CHAR: {
            sprintf(string, "%c", value.char_value);
            break;
        }
        case STRING: {
            if (value.string_value == NULL) strcpy(string, "NULL");
            else sprintf(string, "%s", value.string_value);
            break;
        }
        case UINT: {
            sprintf(string, "%d", value.uint_value);
            break;
        }
        case STRUCTURE: {
            break;
        }
        default:
            break;
    }
    return string;
}

// Afficher le contenu d’une colonne

void print_col(COLUMN* col) {
    printf("Colonne %s type: %s\n", col->titre, ENUM_TYPE_STR(col->column_type));
    for(int i=0;i<col->taille_logique;i++)
    {
        COL_TYPE *p = col->data[i];
        printf("Index %d = %s\n", i, convert_value(col->column_type, *p));
        
    }
    printf("\n");
}
