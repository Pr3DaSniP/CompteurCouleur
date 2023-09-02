# Compteur de couleur

![Language](https://img.shields.io/badge/Language-C++-blue.svg)
![Librairies](https://img.shields.io/badge/Librairies-OpenCV-green.svg)
![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%202022-red.svg)

Ce jeu est un programme qui permet de compter les couleurs présent dans une image (vidéo ici), et de déplacer un curseur en fonction de la couleur dominante. Le but est de casser des points avec le curseur.

Source: https://youtu.be/aMbPyFoGxdU?si=1x6opiB12yPkK7T1&t=1901

## Installation

###### Il faut une webcam pour jouer.

Dans les paramètres du projet :

C/C++ > Général > Autres répertoires include : Ajouter le chemin vers le dossier include de la bibliothèque OpenCV

Éditeur de liens > Général > Répertoires de bibliothèques supplémentaires : Ajouter le chemin vers le dossier lib de la bibliothèque OpenCV

Éditeur de liens > Entrée > Dépendances supplémentaires : Ajouter les librairies suivantes :

opencv_world460d.lib
opencv_world460.lib

## Démonstration

Les deux fenêtres sur la gauche sont respectivement le masque de la couleur verte et le masque de la couleur bleu. La fenêtre de droite est l'image de la webcam ainsi qu'une fenêtre des curseurs pour régler les paramètres de la détection de couleur.

![Demo](demo.gif)
