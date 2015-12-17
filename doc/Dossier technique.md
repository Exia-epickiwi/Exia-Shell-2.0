## Exia Shell 2.0
# Dossier technique
### Projet de fin d'UE

<div class="page-break"></div>
<br/>

![title](img/title.png)

## Le projet

Le projet **Exia Shell 2.0** consiste en la création d'un interpreteur de commandes. Cet interpreteur de commandes doit  bénéficier des fonctionalités suivantes :

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

Cela vise a symplifier l'utilisation d'un shell pour les personnes n'ayant jamais utilisé d'interpreteur de commandes. En effet, lest commandes a executer doivent etre retenus par l'utilisateur pour permettre de faire une utilisation rapide et efficace de l'interface. Les novices préfèrerons utiliser une interface graphique bien plus simple a utiliser mais aussi beacoup plus gourmande en ressources. Pour trouver un compromis on peut mettre en place un shell qui peut comprendre des instructions plus simples ou par la navigation dans des menus.

<div class="page-break"></div>

## Repartition des taches

Les taches du projet on été divisés en plusieurs groupes puis chacun des membres du groupe a été assigné a une tache.

### Nicolas Mazard

|Tache                   |10/12|11/12|12/12|13/12|14/12|15/12|16/12|17/12|
|------------------------|-----|-----|-----|-----|-----|-----|-----|-----|
|Organisation du projet  |✗   |     |     |     |     |     |     |     |
|Chargement a l'ouverture|     |     |✗   |✗   |     |     |✗   |     |
|Configuration           |     |✗   |     |     |     |     |     |     |
|Mode expert             |     |     |     |✗   |✗   |     |     |     |
|Enregistrement logs     |     |     |     |     |✗   |✗   |     |     |
|Easter Egg              |     |     |     |     |✗   |    |     |     |
|Ajustements/Debug       |     |     |     |     |     |✗   |✗   |     |
|Preparations            |     |     |     |     |     |     |    |✗   |

### Baptiste Saclier

|Tache                   |10/12|11/12|12/12|13/12|14/12|15/12|16/12|17/12|
|------------------------|-----|-----|-----|-----|-----|-----|-----|-----|
|Organisation du projet  |✗   |     |     |     |     |     |     |     |
|Couleurs                |     |✗   |     |     |     |     |     |     |
|Multilangue             |     |✗   |     |     |     |     |     |     |
|Mode expert             |     |     |✗   |     |     |     |     |     |
|Mode assistant          |     |     |✗   |✗   |✗   |     |     |     |
|Mode naturel            |     |     |     |     |✗   |✗   |     |     |
|Easter Egg              |     |     |     |✗   |✗   |     |     |     |
|Ajustements/Debug       |     |     |     |     |     |✗   |✗   |     |
|Preparations            |     |     |     |     |     |     |    |✗   |

<div class="page-break"></div>

### Franz Alliod

|Tache                   |10/12|11/12|12/12|13/12|14/12|15/12|16/12|17/12|
|------------------------|-----|-----|-----|-----|-----|-----|-----|-----|
|Preparations            |     |     |     |     |     |     |     |✗   |
