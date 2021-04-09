# Introduction :

L'objectif de ce PDP est d'implémenter un addon nommé **"Acousmoscribe"** dans Ossia permettant la création et l'édition de partitions de musique électroacoustique, selon le système de notation mis au point par Pierre Schaeffer et modifié par Jean-Louis Di Santo.


# Installation d'Ossia :

Si vous voulez tester notre addon dans l'état, il faut installer **Ossia**. Voici la marche à suivre :

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

Dans les sources d’Ossia, il existe un dossier "plugins" et un dossier "addons". La différence de nom est due au fait qu’un “plugin” est présent nativement dans Ossia, alors qu’un “addon” a été rajouté par un développeur, mais ils possèdent tous les deux la même architecture. Le dossier “addons” est donc vide par défaut. 

Notre objectif est donc d'ajouter les sources de notre addon dans le dossier "addons" d'Ossia. Le dossier contenant les sources s'appellera "score-addon-acousmoscribe" et sera en partie inspiré par le plugin "Midi" d'Ossia, étant donné que ce plugin offre déjà la possibilité d'écrire des partitions, bien que le système de notation soit différent.

Pour faciliter notre travail sur l'addon, nous avons mis en place un submodule dans le git Savane contenant les sources devant être compilées par Ossia. Nous travaillons donc sur un github contenant les fichiers sources de notre addon. Cela nous permet de push et pull directement depuis le dossier "addons" d'Ossia, sans avoir à faire de copier/coller du dossier à chaque modification.

Ainsi, pour récupérer les sources, il suffit d'exécuter sur le git Savane :

`$ git submodule update --init`

`$ git submodule update --remote`


# Architecture

Nous sommes partis des sources de addon-skeleton (score/src/addon-skeleton) contenant un ensemble de coquilles vides facilitant la création d'un addon. L’architecture de l’addon respecte le pattern MVP (model view presenter), ainsi, on remarque un fichier View.cpp, un fichier Presenter/Presenter.cpp, et un fichier Model/Process.cpp, contenant le “model” de l’addon. 

Il existe également d’autres classes :

* Inspector.cpp -> View contenant l’interface graphique du volet de droite qui apparaît sur Ossia lorsque la boîte est sélectionnée.
* Metadata.hpp -> comme son nom l’indique, contient les métadonnées de l’addon (nom, tags et caractéristiques graphiques). 


# Travail réalisé

## Ajout de l'addon dans la timeline

En premier lieu, nous avons modifié les métadonnées afin de pouvoir “glisser&déposer” notre addon depuis le volet de gauche sur la timeline Ossia. 

De base, l’addon apparaissait sous forme de “scénario”, c’est-à-dire d’une boîte contenant un rectangle nommé “acousmoscribe”. Nous étions limités à ce rectangle pour notre interface graphique.

Nous avons ensuite ajouté un flag “SupportsTemporal” dans les métadonnées, ce qui nous permet non seulement de modifier l’interface graphique de la boîte entière, mais aussi de donner aux Signes un instant de début et une certaine durée, ce qui est primordial pour un addon de partition. A long terme, on pourra également récupérer les informations du signe traversé par le curseur de lecture, ce qui sera utile pour relier notre partition à un VST afin de la jouer.


## View

En ouvrant Ossia, nous pouvons choisir d’afficher les fichiers à l’aide de  l’icône correspondante. En allant dans la partie Other, nous pouvons déposer une piste sur la fenêtre en y faisant glisser la partie Acousmoscribe . Il est possible d’en ajouter en dessous à l’aide de l’icône ‘+’ ou d’en faire glisser d’autres directement. Les pistes sont étirables pour le moment aussi bien verticalement qu’horizontalement. En début de chaque piste nous avons affiché deux rectangles qui contiendront chacun une clé.

En cliquant sur “Acousmoscribe Process”, un menu s’affiche à droite avec la possibilité de sélectionner des clés. 
L’utilisateur ne peut sélectionner qu’un critère parmi les suivants : tonique, inharmonique et bruit. S’il en sélectionne deux, le premier se déselectionne automatiquement. Il en est de même pour les trois critères pauvre, riche et hybride.
S’il décide de sélectionner une clé hybride, trois nouveaux boutons s’affichent pour choisir son paramètre complémentaire. 
La partie menu déroulant est une autre version du choix. 


Voici des captures d'écran de l'interface : 

<a href="https://ibb.co/Rvg6wSN"><img src="https://i.ibb.co/gjrWK7d/Score-15-03.png" alt="Score-15-03" border="0"></a>

<a href="https://ibb.co/Srxb8T4"><img src="https://i.ibb.co/9tv6LXk/Score-15-03-2.png" alt="Score-15-03-2" border="0"></a>

Ici voici deux zooms de la partie de la sélection des clés (avant et après avoir sélectionné clé spectrale hybride):

<a href="https://imgbb.com/"><img src="https://i.ibb.co/H26sX8z/Cle-spectrale2.png" alt="Cle-spectrale2" border="0"></a>

<a href="https://imgbb.com/"><img src="https://i.ibb.co/CJhpm06/Cle-spectral.png" alt="Cle-spectral" border="0"></a>


## Presenter

Étant donné que le Presenter découle en grande partie de la View, nous n’avons pas pu commencer à le développer. Cependant, nous avons déjà établi une liste des méthodes qu’il contiendra, dont la plupart sont en réalités des Commandes (qui feront le lien entre le presenter et le model). La liste de commandes n’est pas encore fixée, car elle dépend de l’implémentation du model, ainsi nous ne la précisons pas pour le moment.


## Model

Le model (dossier “Model”) est constitué de plusieurs fichiers .hpp qui contiennent les variables et prototypes de méthodes des différents éléments de notation de la musique électro-acoustique. 

La classe Sign contient toutes les caractéristiques d’un signe : RythmicProfile, SpectralKey, MelodicKey, MelodicProfile. Les différents éléments qui composent chaque profil sont contenus dans des énumérations. Le profil dynamique (DynamicProfile), quant à lui, est une structure composée de 4 floats. En effet, pour décrire un profil dynamique, il suffit de spécifier la durée de l’attaque, du relâchement (release), ainsi que le volume d’entrée et de sortie.

Le fichier Sign.cpp contient également une structure “SignData” qui comprend toutes les caractéristiques d’un signe. Plus tard, nous nous servirons de cette structure pour exécuter certaines commandes.

Etant donné que la classe Sign est centrale et s’apparente à la classe MidiNote du plugin midi (dans le sens où un signe peut-être déplacé, changé de taille, etc.), nous nous sommes inspirés de l’existant pour cette classe. Ainsi, les fonctions de sérialisation sont déjà implémentées.

