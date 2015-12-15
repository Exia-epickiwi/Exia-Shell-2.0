## EXSH
# Exia Shell 2.0
### Une nouvelle vision du Shell

<div class="page-break"></div>

## Introduction

Merci d'avoir choisi Exia Shell 2.0 comme shell pour votre ordinateur. Ce guide va vous présenter les fonctionalités de cet interpreteur de commandes qui vous fera changer votre vision du shell.

> Dans la suite de ce mode d'emplois le nom "Exia Shell 2.0" sera remplacé par l'abreviation EXSH

## Sommaire

1. Modes d'utilisation
    1. Mode Expert
    2. Mode Assistant
    3. Mode Naturel
2. Administration
    1. Message de bienvenue
    2. Configuration
    3. Multilangue
    4. Logging
    5. Ajouter des catégories
    6. Etoffer le mode naturel

## Modes d'utilisation

Contrairement aux autres interpreteurs de commande *EXSH* a pour vocation de faciliter au plus l'utilisation d'un shell. Pour ce faire il est composé de 3 modes permettant de l'utiliser sans connaissance des commandes. On dénombre actuellement 3 modes :

**Le mode expert** : Ce mode fonctionne comme un shell classique. L'utilisateur entre les commandes du systeme et celui ci donne un resultat. Ce mode est privilégié par les administrateurs et les personnes desirant un controle plus précis de ce qu'il se passe sur la machine.

**Le mode assistant** : Ce mode présente une suite de catégories puis de sous catégories permettant de trier les commandes de base disponibles a l'utilisateur. Celui ci peut alors naviguer dans des menus et voir un grand nombre de commandes disponibles sur la machine.

**Le mode naturel** : Destiné aux novices, ce mode permet d'ecrir en toutes lettres ce que l'on désire éfféctuer et l'interpreteur ira chercher dans une base de données, composé de fonctions de base, ce que l'utilisateur veux faire.

Vous trouvez ci-dessous un manuel d'utilisation détaillé pour chacun de ces modes.

### Mode expert

Le mode expert est déstiné aux utilisateurs expérimentés ayant déjâ eu une experiance sur un système LINUX. Dans ce mode l'interprèteur de commandes affiche un invité de commandes personnalisable (par defaut `exsh>`) qui donne la permission a l'utilisateur d'entrer une commande.

![expertWelcome](img/expertWelcome.png)

Une commande peut etre ecrite directement si le programme qui la représente est présente dans le dossier `/bin`. Si ce n'est pas le cas il faut préciser un chemin absolu ou relatif vers le programme. Par exemple on peut ecrire `ls` mais on ne peut executer un executable dans un autre dossier en le précédent d'un `./`.

Malgres sa complexitée le mode expert permet d'opèrer de manière précise et les fonctionnalités son tres larges. Ce mode est particulièrement approprié pour les administrateurs.
