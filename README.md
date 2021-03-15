# Introduction :

L'objectif de ce PDP est d'implémenter un addon nommé "Acousmoscribe" dans Ossia permettant la création et l'édition de partitions de musique électroacoustique, selon le système de notation mis au point par Pierre Schaeffer et modifié par Jean-Louis Di Santo.


# Installation d'Ossia :

Si vous voulez tester notre addon dans l'état, il faut installer Ossia. Voici la marche à suivre :

* Cloner le dépôt sur votre machine :

`$ git clone --recursive https://github.com/ossia/score.git`

* Il faut ensuite se déplacer dans le dossier score puis ensuite construire une première fois le répertoire build ainsi que les fichiers nécessaires pour la suite (Ce build ne fonctionne pas et c'est normal) :

`$ ./build.sh `

* Il faut aller dans le dossier build puis il faut lancer ici la compilation du programme :

`$ cmake . -DCMAKE_BUILD_TYPE=Debug`

* Il faut retourner dans le dossier score et build une dernière fois :

`$ ./build.sh`

* A ce stade si tout est bon, Ossia se lance à partir du dossier build avec la commande :

`$ ./run.sh`


# Notre Addon

Dans Ossia, il existe déjà des "plugins" qui sont semblables aux "addons" à la différence qu'ils sont présents nativement. Dans les fichiers sources d'Ossia, il existe donc deux dossiers, "plugins" et "addons", "plugins" contenant des outils pour l'édition Midi, la lecture de fichiers audio, etc. et "addons" étant vide par défaut. 

Notre objectif est donc d'ajouter les sources de notre addon dans le dossier "addons" d'Ossia. Ce dossier s'appellera "score-addon-acousmoscribe" et sera en partie inspiré par le plugin "Midi" d'Ossia, étant donné qu'il offre déjà la possibilité d'écrire des partitions, bien que le système de notation soit différent.

Pour faciliter notre travail sur l'addon nous avons mis en place un submodule dans le git Savane contenant les source devant être compilées par Ossia. Cela nous permet de push et pull directement depuis le dossier "addons" d'Ossia.

Ainsi, pour récupérer les sources, il suffit d'exécuter :

`$ git submodule update --remote`


# Architecture

Nous sommes partis des sources de addon-skeleton (score/src/addon-skeleton) contenant un ensemble de coquilles vides facilitant la création d'un addon. L’architecture de l’addon respecte le pattern MVP (model view presenter), ainsi, on remarque un fichier View.cpp, un fichier Presenter.cpp, et un fichier Process.cpp, contenant le “model” de l’addon. 

Il existe également d’autres classes :

* Inspector.cpp -> View contenant l’interface graphique du volet de droite qui apparaît sur Ossia lorsque la boîte est sélectionnée.
* Metadata.hpp -> comme son nom l’indique, contient les métadonnées de l’addon (nom, tags et caractéristiques graphiques). 


# Travail réalisé

## Interface graphique : 

En premier lieu, nous avons modifié les métadonnées afin de pouvoir “glisser&déposer” notre addon depuis le volet de gauche sur la timeline Ossia à la manière des autres pluggins d'Ossia. 

Au début, l’addon apparaissait sous forme de “scénario”, c’est-à-dire d’une boîte contenant un rectangle nommé “acousmoscribe”, et nous étions limités à ce rectangle pour notre interface graphique. Nous avons ensuite ajouté un flag “SupportsTemporal” dans les métadonnées (Metadata.hpp), ce qui nous permet de modifier l’interface graphique de la boîte entière.

