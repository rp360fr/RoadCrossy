## Projet Shoot’Em Up – Moteur 2D SFML

Ce projet de **Shoot’Em Up** a été réalisé suite à la création d’un **moteur 2D personnalisé en C++**, développé à l’aide de la bibliothèque **SFML**.

L’objectif principal du projet était de concevoir son **propre moteur 2D**, puis de l’exploiter pour créer un Shoot’Em Up intégrant plusieurs **contraintes techniques et mécaniques de jeu**.

---

**! Important : le répertoire du projet doit être en SolutionDir**

## Fonctionnalités principales & technologies utilisées

### Technologies majeures

- **Lecture de fichiers `.txt` pour la création de niveaux**
  - Utilisation de `fstream`
  - Permet la création de **niveaux personnalisés et modulables** sans modifier le code source

- **Système d’inputs et d’événements personnalisés**
  - Utilisation de **fonctions lambda stockées dans des dictionnaires**
  - Basé sur les bibliothèques :
    - `functional`
    - `map`
  - Système très **modulable**, facilitant l’ajout et la gestion d’inputs et d’événements

---

### Architecture du moteur

Le moteur est structuré sous forme d’un **arbre de classes** :

Engine

└── Scene

└── MultipleObjects

└── MultipleComponents

Cette architecture permet :
- Une bonne modularité
- Une meilleure maintenabilité
- Une réutilisation efficace des composants

---

## Utilisation et lancement du jeu

### Lancement

- Lancer l’exécutable
- Cliquer sur **Play** dans le menu principal

### Contrôles

- **Z / Q / S / D** : déplacements
- **Espace (maintenu)** : tirer
- **Échap** : mettre le jeu en pause

### Interface

- Menus avec **boutons cliquables à la souris**
