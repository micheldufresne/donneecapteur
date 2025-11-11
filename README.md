# Gestion d'une file de données issues d'un capteur

L'objectif est de créer une file contenant des valeurs numériques, toutes du même type, par exemple des uint8_t ou des float, dont le nombre max est connu au départ.
C'est nécessaire si on ne veut pas risquer de remplir la mémoire d'un microcontrôleur.
Une fois l'objet file créé en lui donnant le type des éléments, le nombre ainsi que la valeur de départ (celle qui permet de initialiser ou réinitialiser la file), on peut lui demander de calculer la moyenne, l'amplitude et l'écart type des valeurs
