# CDataframe

Dans ce projet nous chercherons à creer un CDataFrame, dans une première partie nous nous concentrerons sur un CdataFrame d'entiers.

Nous travaillons sur un projet visant à créer une bibliothèque en langage C qui reproduit les fonctionnalités de la librairie Pandas en Python. Pandas est connu pour sa capacité à manipuler efficacement les données via des structures appelées DataFrames, qui organisent les données en colonnes de types homogènes pour simplifier le traitement.

Notre objectif est de développer un "Dataframe" en C similaire à celui de Pandas. Ce Dataframe sera composé de colonnes contenant des données du même type et sera identifiable par un titre. Il permettra des opérations flexibles telles que l'ajout, la suppression et la modification de colonnes ou de lignes.

Les fonctionnalités prévues comprennent la création d'un Dataframe vide ou alimenté par des données utilisateur ou prédéfinies, l'affichage complet ou partiel des données selon des critères spécifiques, ainsi que des opérations telles que l'ajout et la suppression de lignes et de colonnes, la modification des titres de colonnes, et la recherche et la modification de valeurs par indices.

En outre, la bibliothèque comprendra des fonctions pour l'analyse statistique des données, telles que le comptage des occurrences et la comparaison de valeurs.

Nous nous concentrons sur l'exploration de l'utilisation des structures de données, en particulier les listes chaînées, et sur l'importance d'un tableau de structures ou d'un dataframe dans ce contexte.


Dans une seconde partie on va se diriger Vers un CDataframe encore plus performant

Dans cette étape, notre objectif est d'améliorer le CDataframe précédent en intervenant sur deux fronts principaux :

Amélioration de la structure des colonnes et du CDataframe pour permettre une utilisation plus flexible.

1. Nouvelles structures de données
Afin de rendre le CDataframe capable de stocker des données de types variés, une refonte de la structure des colonnes s'avère nécessaire. Bien que chaque colonne demeure un ensemble de données homogènes, nous aspirons à ce que différentes colonnes puissent contenir des types de données différents.

2. Fonctionnalités avancées
L'expansion des fonctionnalités du CDataframe pourrait s'inspirer des capacités offertes par le "Dataframe" de "Pandas" en Python. Dans cette optique, nous examinerons en détail la fonction de tri des colonnes du CDataframe. 

