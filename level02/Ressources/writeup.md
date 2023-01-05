En lisant le code, on peut se rendre compte de plusieurs choses.

- Un read vient lire le contenu d'un fichier contenant le mot de passe.
- Un printf est utilisé quelques instructions plus tard, et prend en paramètres des entrées de l'utilisateur.

La présence de ce printf nous permettra de pouvoir afficher ce qui est lu en mémoire, comme par exemple le contenu de notre read().

On peux taper %p pour afficher les pointeurs contenus dans le programme grâce à l'utilisation de ce printf non sécurisé.
Lorsque le programme nous demande de taper notre login, on va spammer les %p pour afficher ce qui est contenu en mémoire dans notre programme, ce qui donne le résultat suivant:

```
level02@OverRide:~$ ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: %p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p.%p
```

On observe alors la présence des valeurs hexadécimales , en plus de valeurs hexadécimales répétées.
Le site suivnat nous permet de les déchiffrer: https://string-functions.com/hex-string.aspx

Les valeurs hexadécimales répétées ont pour valeur les chaines "%p.%p."
Nos chaînes hexadécimales non répétées ont pour valeur:

756e505234376848 (unPR47hH)
45414a3561733951 (EAJ5as9Q)
377a7143574e6758 (7zqCWNgX)
354a35686e475873 (5J5hnGXs)
48336750664b394d (H3gPfK9M)

Assembler ces chaines de caractères comporte le même nombre de caractère que nos deux derniers flags.
On peut alors raisonnablement penser qu'une combinaison de ces chaînes représente un flag.

Après plusieurs tentatives de combinaison, on se rend compte que pour lire le flag, on doit lire les chaînes de caractère de la première vers la dernière,
et en inversant l'ordre des caractères qu'elles contiennent individuellement (little endian)

Ce qui nous donne le flag:

Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
