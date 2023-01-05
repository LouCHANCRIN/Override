En lançant le programme, on se rend compte que celui ci attend un mot de passe.
```./level00```

On va regarder les instructions assembleur avec GDB.
```gdb level00```

La syntaxe est de base est horrible, on la change pour plus de lisibilité avec la commande suivante:
```set disassembly-flavor intel```

Comme chaque fonction dispose d'un main, on regarde la fonction main avec la commande:
```disassemble main```

En balayant rapidement du regard les instructions, observe alors trois lignes interessantes qui se succedent:
```
x080484de <+74>:	call   0x80483d0 <__isoc99_scanf@plt>
0x080484e3 <+79>:	mov    eax,DWORD PTR [esp+0x1c]
0x080484e7 <+83>:	cmp    eax,0x149c
```

On comprend alors ligne par ligne que:
- la fonction scanf est appelée
- elle fait appel à un registre eax de taille DWORD, soit de 4 bits. Cela correspond à un int.
- le registre eax est comparé à la valeur '0x149C'

En hexadécimal, '0x149' vaut 5276. On comprend alors que scanf attend de lire notre entrée,
puis va comparer celle ci à la valeur 5276.

On tente de taper "5276" comme mot de passe, et ça fonctionne, un terminal s'ouvre grâce à la fonction system.
Il ne reste plus qu'à trouver le flag avec la commande:

```cat ../level01/.pass```