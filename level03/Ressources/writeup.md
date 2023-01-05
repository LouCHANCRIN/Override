Pour accéder à la fonction test, on voit que deux paramètres sont pris en compte, notre variable qu'on va appeler password et une variable de valeur "0x1337d00d".
En allant sur le site suivant, on se rend compte que ce deuxième paramètre ne semble pas être une string, car non printable: https://string-functions.com/hex-string.aspx

On va partir du principe que c'est un int, (322424845 en l'occurence), principe vérifié lors de sa soustraction avec notre entrée dans la fonction test,
entrée qui sera donc un chiffre, comme l'atteste scanf.

Avant même d'essayer de comprendre la fonction decrypt, on se rend compte qu'il ne semble n'y avoir que 22 solutions pour rentrer dans la fonction decrypt,
depuis la fonction test.

Par curiosité, et vu le nombre restreint de solutions, on va le sessayer manuellement pour trouver la solution.
La solution se trouvera entre "322424845" et "322424823".

Très rapidement, en tapant "322424827", un invite de commande se lance.

Il suffira alors de taper la commande:

```cat /home/users/level04/.pass```

Et le mot de passe suivnat s'affiche:

kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf