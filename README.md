# lem-in

*Résumé: Ce projet a pour but de vous faire coder un gestionaire de fourmillière.*

## Le but du projet
Le but du projet est de trouver le moyen le plus rapide de faire traverser
une fourmilière (de la room start à la room end) par n fourmis.

Par moyen le plus rapide, nous entendons la solution avec le moins de lignes,
respectant le format de sortie décrit ci-après.

#### Évidemment, il y a quelques contraintes :
- il faut prendre le chemin le plus court (et pas forcément pour autant le plus simple),  
- ne pas marcher sur ses congénères et éviter les embouteillages  
Au début du jeu, toutes les fourmis sont sur la salle indiquée par la commande ```##start```.  
Le but est de les amener sur la salle indiquée par la commande ```##end``` en prenant le moins de tours possible.  
Chaque salle peut contenir une seule fourmi à la fois
(__sauf __ ```##start``` __ et __ ```##end``` __ qui peuvent en contenir autant qu’il faut__).  

- On considère que les fourmis sont toutes dans la salle ```##start``` au démarrage  
- On affiche à chaque tour le mouvement des fourmis qui ont bougé  
- Une fourmi ne peu se déplacer qu'une seule fois par tour en suivant un tube (la salle réceptrice doit être libre).
***
## Format de la map
Le programme reçoit sur l’entrée standard la description de la fourmilière sous la forme suivante :  
```
nombre_de_fourmis  
les_salles  
les_tubes  
```  
Présenté comme ceci :  
```
##start   
1 23 3    
2 16 7    
#commentaire  
3 16 3  
4 16 5  
5 9 3  
6 1 5  
7 4 8  
##end  
0 9 5  
0-4  
0-6  
1-3  
4-3  
5-2  
3-5  
#autre commentaire  
4-2  
2-1  
7-6  
7-2  
7-4  
#C'est la fin  
6-5  
#autre commentaire  
```  
Ce qui représente :
```
             _______________  
            /                \  
     ______[5]----[3]----[1]  |  
   /               |     /    |  
  [6]-----[0]----[4]    /     |  
   \    _________/|    /      |
    \  /          [2]/_______/  
     [7]_________/
```
***
## Téléchargement
```git clone https://github.com/manki23/lem-in.git ; cd lem-in ; make```
## Utilisation
```
$>./lem-in < test_files/sujet1.map
3
##start
0 1 0
##end
1 5 0
2 9 0
3 13 0
0-2
2-3
3-1

L1-2
L1-3 L2-2
L1-1 L2-3 L3-2
L2-1 L3-3
L3-1
$>
```

## Option Bonus
```
Usage:	./lem-in [-l] <map>

	-l,		to see the numbers of lines
```
