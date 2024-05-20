#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"


int main(int argc, char **argv)
{
    // Allocation d'un CDataFrame
    CDataframe *dataframe = create_CDATAFRAME("First CDataframe");
    
    // Création d'une colonne de type INT et insertion des valeurs de type INT
    COLUMN *col_int = create_column(INT,"Column INT");
    insert_value(col_int, (COL_TYPE)-52);
    insert_value(col_int, (COL_TYPE)44);
    insert_value(col_int, (COL_TYPE)-15);
    insert_value(col_int, (COL_TYPE)-15);
        
    // Création d'une colonne de UINT INT et insertion des valeurs de type UINT
    COLUMN *col_uint = create_column(UINT,"Column UINT");
    insert_value(col_uint, (COL_TYPE)100);
    insert_value(col_uint, (COL_TYPE)300);
    insert_value(col_uint, (COL_TYPE)200);
    sort(col_uint, ASC);
    
    // Création d'une colonne de type STRING et insertion des valeurs de type STRING
    COLUMN *col_string = create_column(STRING,"Column STRING");
    insert_value(col_string, (COL_TYPE)"C - Value 1");
    insert_value(col_string, (COL_TYPE)"A - Value 2");
    insert_value(col_string, (COL_TYPE)"B - Value 3");
    insert_value(col_string, (COL_TYPE)NULL);
    insert_value(col_string, (COL_TYPE)"C - Value 4");
    
    // Création d'une colonne de type CHAR et insertion des valeurs de type CHAR
    COLUMN *col_char = create_column(CHAR,"Column CHAR");
    insert_value(col_char, (COL_TYPE)'C');
    insert_value(col_char, (COL_TYPE)'D');
    insert_value(col_char, (COL_TYPE)'E');

    // Création d'une colonne de type FLOAT et insertion des valeurs de type FLOAT
    COLUMN *col_float = create_column(FLOAT,"Column FLOAT");
    insert_value(col_float, (COL_TYPE)12.4f);
    insert_value(col_float, (COL_TYPE)14.7f);
    insert_value(col_float, (COL_TYPE)18.99f);

    // Création d'une colonne de type DOUBLE et insertion des valeurs de type DOUBLE
    COLUMN *col_double = create_column(DOUBLE,"Column DOUBLE");
    insert_value(col_double, (COL_TYPE)100.123);
    insert_value(col_double, (COL_TYPE)200.456);
    insert_value(col_double, (COL_TYPE)300.789);

    // Ajout des colonnes dans le CDataframe
    ajouter_colonne_valeurs_CDataFrame(dataframe, col_int);
    ajouter_colonne_valeurs_CDataFrame(dataframe, col_uint);
    ajouter_colonne_valeurs_CDataFrame(dataframe, col_float);
    ajouter_colonne_valeurs_CDataFrame(dataframe, col_double);
    ajouter_colonne_valeurs_CDataFrame(dataframe, col_char);
    ajouter_colonne_valeurs_CDataFrame(dataframe, col_string);

    // Affichages des colonnes
    print_col(col_int);
    print_col(col_uint);
    print_col(col_string);
    print_col(col_char);
    print_col(col_float);
    print_col(col_double);

    // Affichage du CDataFrame
    afficher_tout_CDATAFRAME(dataframe);

    // Retrouver une valeur en position 2 dans les colonnes des STRING
    COL_TYPE value = val_at_pos(col_string, 2);
    printf("(STRING) Value at position 2 is '%s'\n", convert_value(col_string->column_type,value));

    // Retrouver une valeur en position 1 dans les colonnes des INT
    value = val_at_pos(col_int, 1);
    printf("(INT) Value at position 1 is '%s'\n", convert_value(col_int->column_type,value));

    // Retrouver Nombre d'occurences de la valeur -15 dans les colonnes INT
    int occurences = occu_val(col_int, (COL_TYPE)-15);
    printf("Occurences (INT) %d\n", occurences);
    
    // Retrouver Nombre d'occurences de la valeur 'B - Value 3' dans les colonnes STRING
    occurences = occu_val(col_string, (COL_TYPE)"B - Value 3");
    printf("Occurences (STRING) %d\n", occurences);
    
    // Retrouver Nombre d'occurences de la valeur 'B - Value 3' dans les colonnes STRING
    occurences = occu_val(col_char, (COL_TYPE)'C');
    printf("Occurences (CHAR) %d\n", occurences);

    // Nombre d'élements dans la colonne des INT supérieur à 150
    int v = nb_val_supp(col_uint, (COL_TYPE)150);
    printf("> 150 (UINT) %d\n", v);

    // Nombre d'élements dans la colonne des INT inférieur à 150
    v = nb_val_inf(col_uint, (COL_TYPE)150);
    printf("< 150 (UINT) %d\n", v);

    // Affichage des 2 premières lignes de chaque colonne
    afficher_CDATAFRAME_ligne(dataframe, 2);
    printf("\n");
    
    // Affichage de 2 premières colonnes
    afficher_CDATAFRAME_colonne(dataframe, 2);
    
    // Affichage des noms de chaque colonne
    afficher_nom_colonne_cdataframe(dataframe);
    printf("\n");
    
    // Affiche le nombre de colonnes dans le dataframe
    Afficher_nb_colonnes_Cdataframe(dataframe);
    printf("\n");
    
    // Affiche le nombre de lignes dans le dataframe
    Afficher_nb_lignes_Cdataframe(dataframe);
    printf("\n");
            
    valeurs_egale_x_CdataFrame (dataframe, 100);
    printf("\n");

    valeurs_inf_x_CdataFrame (dataframe, 40);
    printf("\n");

    // Renommer une colonne
    renommer_colonne_CDataFrame (dataframe, "Column UINT", "Column UINT Renommer");
    afficher_nom_colonne_cdataframe(dataframe);
    printf("\n");

    // Vérfier l'exisences des valeurs
    verifier_existence_valeur(dataframe, UINT, (COL_TYPE)100);
    verifier_existence_valeur(dataframe, STRING, (COL_TYPE)"B - Value 3");
    verifier_existence_valeur(dataframe, STRING, (COL_TYPE)"Rien du tout");
    printf("\n");
    
    // Test remplacer valeur puis vérification
    remplacer_valeur_CDataFrame(dataframe, 1, 1, (COL_TYPE)400);
    verifier_existence_valeur(dataframe, UINT, (COL_TYPE)400);
    
    printf("Occurences %d\n", occurence_valeur_Cdataframe(dataframe, INT, (COL_TYPE)-1));
    
    // Destruction des colonnes
    delete_column(col_double);
    delete_column(col_float);
    delete_column(col_char);
    delete_column(col_string);
    delete_column(col_uint);
    delete_column(col_int);
    
    
    
    printf("\nThat's all!\n");
    
    return 0;
}
