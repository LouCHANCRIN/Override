En lisant la source du programme, on eput se rendre compte que celui ci ouvre un fichier dans le dossier backups, tout en écrivant des logs dans le même dossier, sous la forme d'un fichier .log.

On peut alors raisonnablement penser qu'on peut faire un backup du dossier .pass du level09

Nous sommes cependant limités par le fait que le chemin du level09 dans la racine du dossier, autrement, la lecture est impossible.
On peut contourner ça en créant un lien symbolique dans le dossier, car on peut changer les droits d'écriture dans le dossier du level08.

Pour se faire, on tape les commandes suivantes:

chmod 777 .
ln -s /home/users/level09/.pass test
./level08 test
cat ./backups/test