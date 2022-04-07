Breakout est un casse brique simple il faut détruire toutes les briques pour gagner.

Le programme reprend les éléments du TP " mouvement dune unique partiucle".

Il y'a trois éléments principaux : 
- la balle 
- les briques
- le module que le joueur contrôle grâce aux flèches du clavier
- Le score du joueur représenté par le nombre de briques qu'il a détruite

Les diffèrentes procédures et fonctions sont responsables : 
- de l'affichage des éléments 
- du déplacement du module
- des collisions de la balle avec les briques, le module ou les murs
- du mouvement de la balle 

Le module possède deux zones de collision, la moitié gauche du module renvoie la balle avec la trajectoire initaile, la moitié droite renvoie la balle avec l'inverse de sa trajectoire.


Pour augmenter la difficulté on peut modifier les élements suivant :
- la longueur du module ( mi et ma )
- la vitesse de la balle ( const dt )






