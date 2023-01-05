Pour cet exercice, nul besoin d ecomprendre l'algorithme, on peut avoir directement son résultat en printant la valeur auquel notre entrée est comparée.
Pour se faire, il suffit juste de désactiver ptrace en lui faisant retourner un 0, comme si l'execution s'était bien passée.

(gdb) b *0x080487ba (adresse compare ptrace)
(gdb) b *0x08048866 (adresse compare serial)
(gdb) r
Starting program: /home/users/level06/level06
***********************************
*               level06           *
***********************************
-> Enter Login: coucou
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 1
(gdb) set $eax=0 (retour de ptrace set à 0)
(gdb) c
Continuing.
Breakpoint 2, 0x08048866 in auth ()
(gdb) x/d $ebp-0x10 (affichage serial)
0xffffd658:	6234463 
(gdb) quit

cat /home/users/level07/.pass

GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8