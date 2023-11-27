# Pipelines GStreamer

## Pipeline 1 : Streaming de capture d'écran

Pour mettre en oeuvre ce pipeline il nous faut d'abord un element de capture d'écran. Pour cela nous utilisons l'element `d3d11screencapturesrc` qui permet de capturer l'écran d'un ordinateur. Ensuite, nous redimensionnons l'image avec l'element `videoscale` et changeons le framerate avec `videorate`.

De plus, nous utilisons l'element `timeoverlay` pour afficher l'heure et la date sur la vidéo avec en paramètre `valignment=top` `halignment=center` et `shaded-background=true` pour que l'affichage soit en haut au centre et avec un fond opaque.

Enfin, nous utilisons un tee pour envoyer la vidéo vers un stream et un fichier. Pour le stream nous utilisons l'element `rtpsink` qui permet d'envoyer la vidéo vers un serveur rtp. Pour le fichier nous utilisons l'element `filesink` qui permet d'enregistrer la vidéo dans un fichier `video.avi`.

En bonus nous envoyons aussi la vidéo vers un `autovideosink` pour pouvoir la visualiser en direct.

## Pipeline 2 : Récupération de la vidéo

Pour récupérer la vidéo nous utilisons l'element `rtspsrc` qui permet de récupérer la vidéo depuis un serveur rtmp. Ensuite nous utilisons `decodebin` pour décoder la vidéo et `autovideosink` pour l'afficher.

## Pipeline 3 : Lecture d'une vidéo

Pour lire une vidéo nous utilisons l'element `filesrc` qui permet de lire une vidéo depuis un fichier. Ensuite nous utilisons `decodebin` pour décoder la vidéo et `autovideosink` pour l'afficher.

# Utilisation du projet

Les pipelines sont des fichier `.bat` qui permettent de lancer les pipelines. Pour les lancer il suffit de double cliquer dessus.
Nous avons aussi build le pipeline1 en un executable `main.exe` qui permet de lancer le pipeline1 sous windows et `main` qui permet de lancer le pipeline1 sous linux.
le fichier `main.c` est le fichier source du programme `main.exe` qui contient le code c du programme qui lance le pipeline1.
Lorsque vous lancerez le pipeline1 un fichier `video.avi` sera créé dans le dossier courant. Ce fichier contiendra la vidéo enregistrée par le pipeline1, ouvrez cette video avec [vlc](https://www.videolan.org/vlc/) pour la lire.