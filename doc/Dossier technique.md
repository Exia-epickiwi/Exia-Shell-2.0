## Exia Shell 2.0
# Dossier technique
### Projet de fin d'UE

<div class="page-break"></div>
<br/>

![title](img/title.png)

## Le projet

Le projet **Exia Shell 2.0** consiste en la création d'un interpréteur de commandes. Cet interpréteur de commandes doit  bénéficier des fonctionalités suivantes :

* Il doit être lancé lors de la connexion d’un utilisateur au système
* Le shell doit pouvoir être configurable (équivalent .profile). Par exemple, pouvoir configurer le prompt, le mode, la langue.
* 3 modes d’utilisation du shell doivent exister :
    * mode expert, commandes comme le shell classique
    * mode assistant pas à pas
    * mode langage naturel
* Le système doit être capable de comprendre les demandes des utilisateurs dans leur propre langue (et pas seulement des abréviations en anglais).
* Il doit inclure un « easter-eggs » : les tours de Hanoï.
* L’affichage de commandes devra être plus simple et l’interprétation du contenu plus intuitif.
* Le shell tient à jour un fichier log qui trace toutes les commandes lancées par le shell (même celles qui sont erronées).

Cela vise à simplifier l'utilisation d'un shell pour les personnes n'ayant jamais utilisé d'interpreteur de commandes. En effet, les commandes à éxecuter doivent être retenues par l'utilisateur pour permettre de faire une utilisation rapide et efficace de l'interface. Les novices préférons utiliser une interface graphique bien plus simple à utiliser mais aussi beacoup plus gourmande en ressources. Pour trouver un compromis on peut mettre en place un shell qui peut comprendre des instructions plus simples ou par la navigation dans des menus.

<div class="page-break"></div>

## Répartition des tâches

Les tâches du projet on été divisées en plusieurs groupes puis chacun des membres du groupe a été assigné à une tache.

### Nicolas Mazard

|Tâche                   |10/12|11/12|12/12|13/12|14/12|15/12|16/12|17/12|
|------------------------|-----|-----|-----|-----|-----|-----|-----|-----|
|Organisation du projet  |✗   |     |     |     |     |     |     |     |
|Chargement à l'ouverture|     |     |✗   |✗   |     |     |✗   |     |
|Configuration           |     |✗   |     |     |     |     |     |     |
|Mode expert             |     |     |     |✗   |✗   |     |     |     |
|Enregistrement logs     |     |     |     |     |✗   |✗   |     |     |
|Easter Egg              |     |     |     |     |✗   |    |     |     |
|Ajustements/Debug       |     |     |     |     |✗   |✗   |✗   |     |
|Préparations            |     |     |     |     |     |     |    |✗   |

### Baptiste Saclier

|Tâche                   |10/12|11/12|12/12|13/12|14/12|15/12|16/12|17/12|
|------------------------|-----|-----|-----|-----|-----|-----|-----|-----|
|Organisation du projet  |✗   |     |     |     |     |     |     |     |
|Couleurs                |     |✗   |     |     |     |     |     |     |
|Multilangue             |     |✗   |     |     |     |     |     |     |
|Mode expert             |     |     |✗   |     |     |     |     |     |
|Mode assistant          |     |     |✗   |✗   |✗   |     |     |     |
|Mode naturel            |     |     |     |     |✗   |✗   |     |     |
|Easter Egg              |     |     |     |✗   |✗   |     |     |     |
|Ajustements/Debug       |     |     |     |     |✗   |✗   |✗   |     |
|Préparations            |     |     |     |     |     |     |    |✗   |

<div class="page-break"></div>

### Franz Alliod

|Tâche                   |10/12|11/12|12/12|13/12|14/12|15/12|16/12|17/12|
|------------------------|-----|-----|-----|-----|-----|-----|-----|-----|
|Traductions-corrections |     |     |     |     |  ✗  |  ✗ |     |     |
|Preparations            |     |     |     |     |     |     |     | ✗   |
|Codage commandes        |     |     |     |     |     |     | ✗   |     |

## Bilans personnels

### Franz Alliod

Lors de ce projet, j'ai appris comment fonctionnait un interpréteur de commande et comment l'organisé en C.
J'ai été malade et ai commencé le projet seulement à partir du 14/12, malgré mon retard, j'ai contribué au projet dans sa forme en traduisant les commandes du mode naturel, par des corrections d'orthographe et en codant certaines commandes. Par ailleurs, j'ai essayé de rattraper mon retard personnel en essayant de refaire certains modes. ( indépendament du projet )

### Baptiste Saclier

Après les prosits consacrés a la programmation en C le projet et l'aboutissement de cette fin d'année 2015. Ce projet a été une occasion de mettre en pratique les techniques de mise e place d'un programme de manière structurée pour permettre son évolution et sa bonne compréhension par les tiers. Mais aussi de mettre en place un travail de groupe et de diviser la charge pour gagner du temps. Je n'avais jamais travaillé en équipe et cette première expérience fut très probante. L'organisation était optimale grâce a l'utilisation de git et de trello permettant de partager le code et de corriger des bugs plus simplement. En bref, j'ai bien aimé ce projet, car cela m'a permis de découvrir beaucoup d'aspects des projets en équipe. Malgré ces points positifs, le sujet restait assez vague par rapport aux commandes à utiliser ou au travail à effectuer. De plus le groupe etait peut etre surqualifié et les tuteurs trop peu présents et nous avons du aider d'autres groupes.

### Nicolas Mazard

Ce projet m'a apporté beaucoup de connaissances comme l'ouverture de fichier, création entière d'une console en mode expert. Ce projet aussi m'a permis d'apprendre à utiliser des logiciels de gestion de projet comme git pour la programmation en équipe et trello pour la gestion des tâches.
Ensuite avant l'intégration dans l'école Exia.Cesi je n'ai jamais programmé en C (mais en d'autres langage oui). Cela m'a permis de créer de bonne connaissance en langage C.
Le groupe a été modifié au dernier moment et malheuresement, nous avons fini les grosses fonctionnalités en 3-4 jours dû à notre niveau en langage C. Ce qui n'a pas été une vrai gestion de groupe (car on était au début seulement 2 membres).

<u>Description de la réalisation effective du projet :</u>
I] Main
Chargement de la configuration et de la langue
A) Mode expert
1) Enregistrement des commandes (log)
2) Exécution des commandes (exec)

B) Mode assistant
1) Enregistrement des commandes (log)
2) Exécution des commandes (exec)

C) Mode naturel
1) Enregistrement des commandes (log)
2) Exécution des commandes (exec)

II] Exécution des commandes (exec)
1) Commande de cd (recodé de cd)
2) Exécution de jeu: easter-eggs
3) Commande wls (recodé de ls)
4) Commande wcat (recodé de cat)
5) Commande wpwd (recodé de pwd)
6) Commande wmount (recodé de mount)
7) Commande listUser (nouvelle fonction pour Linux)
