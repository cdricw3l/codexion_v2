


## Un seul coder
```bash
./codexion 1 800 200 200 200 5 100 fifo 
# Burnout à 800–810 ms ; aucune compilation
./codexion 1 800 200 200 200 5 100 edf 
# Burnout à 800–810 ms ; aucune compilation
./codexion 1 100 200 100 100 1 0 fifo 
# Burnout à 100–110 ms
./codexion 1 100 200 100 100 1 0 edf 
# Burnout à 100–110 ms
./codexion 1 3000 100 100 100 1 0 fifo 
# Burnout à 3000–3010 ms ; régression overflow
./codexion 1 3000 100 100 100 1 0 edf 
# Burnout à 3000–3010 ms ; régression overflow
```

## Survie — nombres pairs
```bash
./codexion 2 2000 200 200 200 5 100 fifo 
# Survie, au moins 10 compilations
./codexion 2 2000 200 200 200 5 100 edf 
# Survie, au moins 10 compilations
./codexion 4 3000 200 200 200 10 200 fifo 
# Survie, au moins 40 compilations
./codexion 4 3000 200 200 200 10 200 edf 
# Survie, au moins 40 compilations
./codexion 6 4000 200 200 200 10 200 fifo 
# Survie, au moins 60 compilations
./codexion 6 4000 200 200 200 10 200 edf 
# Survie, au moins 60 compilations
./codexion 8 5000 200 200 200 10 200 fifo 
# Survie, au moins 80 compilations
./codexion 8 5000 200 200 200 10 200 edf 
# Survie, au moins 80 compilations
./codexion 10 6000 200 200 200 10 200 fifo 
# Survie, au moins 100 compilations
./codexion 10 6000 200 200 200 10 200 edf 
# Survie, au moins 100 compilations
./codexion 20 10000 100 100 100 5 100 fifo 
# Survie, au moins 100 compilations
./codexion 20 10000 100 100 100 5 100 edf 
# Survie, au moins 100 compilations
./codexion 50 20000 100 100 100 5 100 fifo 
# Survie, au moins 250 compilations
./codexion 50 20000 100 100 100 5 100 edf 
# Survie, au moins 250 compilations
./codexion 100 30000 100 100 100 3 50 fifo 
# Survie, au moins 300 compilations
./codexion 100 30000 100 100 100 3 50 edf 
# Survie, au moins 300 compilations
./codexion 200 60000 100 100 100 3 50 fifo 
# Survie, au moins 600 compilations
./codexion 200 60000 100 100 100 3 50 edf 
# Survie, au moins 600 compilations
```
# Survie — nombres impairs
```bash
./codexion 3 2000 100 100 100 5 100 fifo 
# Survie, au moins 15 compilations
./codexion 3 2000 100 100 100 5 100 edf 
# Survie, au moins 15 compilations
./codexion 5 3000 200 200 200 10 200 fifo 
# Survie, au moins 50 compilations
./codexion 5 3000 200 200 200 10 200 edf 
# Survie, au moins 50 compilations
./codexion 7 4000 200 200 200 10 200 fifo 
# Survie, au moins 70 compilations
./codexion 7 4000 200 200 200 10 200 edf 
# Survie, au moins 70 compilations
./codexion 9 5000 200 200 200 10 200 fifo 
# Survie, au moins 90 compilations
./codexion 9 5000 200 200 200 10 200 edf 
# Survie, au moins 90 compilations
./codexion 11 6000 200 200 200 10 200 fifo 
# Survie, au moins 110 compilations
./codexion 11 6000 200 200 200 10 200 edf 
# Survie, au moins 110 compilations
./codexion 21 10000 100 100 100 5 100 fifo 
# Survie, au moins 105 compilations
./codexion 21 10000 100 100 100 5 100 edf 
# Survie, au moins 105 compilations
./codexion 51 20000 100 100 100 5 100 fifo 
# Survie, au moins 255 compilations
./codexion 51 20000 100 100 100 5 100 edf 
# Survie, au moins 255 compilations
./codexion 101 30000 100 100 100 3 50 fifo 
# Survie, au moins 303 compilations
./codexion 101 30000 100 100 100 3 50 edf 
# Survie, au moins 303 compilations
./codexion 199 60000 100 100 100 3 50 fifo 
# Survie, au moins 597 compilations
./codexion 199 60000 100 100 100 3 50 edf 
# Survie, au moins 597 compilations
```
## Burnouts obligatoires
```bash
./codexion 2 100 200 100 100 5 0 fifo 
# BURNOUT : une compilation dure plus que B
./codexion 2 100 200 100 100 5 0 edf 
# BURNOUT : une compilation dure plus que B
./codexion 3 100 200 100 100 5 0 fifo 
# BURNOUT : même contrainte, N impair
./codexion 3 100 200 100 100 5 0 edf 
# BURNOUT : même contrainte, N impair
./codexion 4 300 200 200 200 5 0 fifo 
# BURNOUT : cycle individuel de 600 ms > B
./codexion 4 300 200 200 200 5 0 edf 
# BURNOUT : cycle individuel de 600 ms > B
./codexion 5 500 200 200 200 5 0 fifo 
# BURNOUT : cycle individuel de 600 ms > B
./codexion 5 500 200 200 200 5 0 edf 
# BURNOUT : cycle individuel de 600 ms > B
./codexion 2 500 100 100 100 5 1000 fifo 
# BURNOUT : cooldown incompatible avec B
./codexion 2 500 100 100 100 5 1000 edf 
# BURNOUT : cooldown incompatible avec B
./codexion 5 500 100 100 100 5 1000 fifo 
# BURNOUT : cooldown incompatible avec B
./codexion 5 500 100 100 100 5 1000 edf 
# BURNOUT : cooldown incompatible avec B
./codexion 7 150 500 100 100 5 100 fifo 
# BURNOUT : compilation trop longue
./codexion 7 150 500 100 100 5 100 edf 
# BURNOUT : compilation trop longue
```
## Cooldown et durées
```bash
./codexion 2 3000 100 100 100 5 0 fifo 
# SURVIE ; réutilisation immédiate autorisée
./codexion 2 3000 100 100 100 5 0 edf 
# SURVIE ; réutilisation immédiate autorisée
./codexion 3 3000 100 100 100 5 1 fifo 
# SURVIE ; cooldown 1 ms
./codexion 3 3000 100 100 100 5 1 edf 
# SURVIE ; cooldown 1 ms
./codexion 4 3000 100 100 100 5 50 fifo 
# SURVIE ; cooldown 50 ms
./codexion 4 3000 100 100 100 5 50 edf 
# SURVIE ; cooldown 50 ms
./codexion 5 5000 100 100 100 5 500 fifo 
# SURVIE ; cooldown long
./codexion 5 5000 100 100 100 5 500 edf 
# SURVIE ; cooldown long
./codexion 2 10000 100 100 100 2 3000 fifo 
# SURVIE ; conversion 64 bits du cooldown
./codexion 2 10000 100 100 100 2 3000 edf 
# SURVIE ; conversion 64 bits du cooldown
./codexion 3 10000 100 100 100 2 3000 fifo 
# SURVIE ; même régression en impair
./codexion 3 10000 100 100 100 2 3000 edf 
# SURVIE ; même régression en impair
./codexion 4 2000 1 1 1 20 0 fifo 
# SURVIE attendue ; actions très courtes
./codexion 4 2000 1 1 1 20 0 edf 
# SURVIE attendue ; actions très courtes
./codexion 5 3000 1 1 1 20 1 fifo 
# SURVIE attendue ; concurrence intensive
./codexion 5 3000 1 1 1 20 1 edf 
# SURVIE attendue ; concurrence intensive
```
## Quota et arrêt global
```bash
./codexion 2 3000 100 100 100 1 100 fifo 
# SURVIE ; au moins 2 compilations terminées
./codexion 2 3000 100 100 100 1 100 edf 
# SURVIE ; au moins 2 compilations terminées
./codexion 5 3000 100 100 100 1 100 fifo 
# SURVIE ; au moins 5 compilations terminées
./codexion 5 3000 100 100 100 1 100 edf 
# SURVIE ; au moins 5 compilations terminées
./codexion 6 5000 100 100 100 2 100 fifo 
# SURVIE ; au moins 12 compilations
./codexion 6 5000 100 100 100 2 100 edf 
# SURVIE ; au moins 12 compilations
./codexion 7 5000 100 100 100 2 100 fifo 
# SURVIE ; au moins 14 compilations
./codexion 7 5000 100 100 100 2 100 edf 
# SURVIE ; au moins 14 compilations
./codexion 4 5000 20 20 20 100 10 fifo 
# SURVIE ; au moins 400 compilations
./codexion 4 5000 20 20 20 100 10 edf 
# SURVIE ; au moins 400 compilations
./codexion 5 5000 20 20 20 100 10 fifo 
# SURVIE ; au moins 500 compilations
./codexion 5 5000 20 20 20 100 10 edf 
# SURVIE ; au moins 500 compilations
```
## Délais serrés et efficacité du scheduler
```bash
./codexion 4 3000 200 200 200 10 200 fifo 
# SURVIE
./codexion 4 3000 200 200 200 10 200 edf 
# SURVIE
./codexion 4 1200 200 200 200 10 200 fifo 
# SURVIE attendue, mesurer
./codexion 4 1200 200 200 200 10 200 edf 
# SURVIE attendue, mesurer
./codexion 4 900 200 200 200 10 200 fifo 
# LIMITE ; alternance idéale toutes les 400 ms, retour en 800 ms
./codexion 4 900 200 200 200 10 200 edf 
# LIMITE ; alternance idéale toutes les 400 ms, retour en 800 ms
./codexion 4 800 200 200 200 10 200 fifo 
# LIMITE sans marge
./codexion 4 800 200 200 200 10 200 edf 
# LIMITE sans marge
./codexion 5 3000 200 200 200 10 200 fifo 
# SURVIE
./codexion 5 3000 200 200 200 10 200 edf 
# SURVIE
./codexion 5 1500 200 200 200 10 200 fifo 
# SURVIE attendue, mesurer
./codexion 5 1500 200 200 200 10 200 edf 
# SURVIE attendue, mesurer
./codexion 5 1200 200 200 200 10 200 fifo 
# LIMITE
./codexion 5 1200 200 200 200 10 200 edf 
# LIMITE
./codexion 5 1100 200 200 200 10 200 fifo 
# LIMITE
./codexion 5 1100 200 200 200 10 200 edf 
# LIMITE
./codexion 5 1000 200 200 200 10 200 fifo 
# LIMITE ; cycle idéal de 1000 ms sans marge
./codexion 5 1000 200 200 200 10 200 edf 
# LIMITE ; cycle idéal de 1000 ms sans marge
./codexion 5 900 200 200 200 100 200 fifo 
# BURNOUT attendu sur la durée ; capacité insuffisante pour une activité soutenue
./codexion 5 900 200 200 200 100 200 edf 
# BURNOUT attendu sur la durée ; capacité insuffisante pour une activité soutenue
./codexion 5 500 200 200 200 10 200 fifo 
# BURNOUT obligatoire ; cycle individuel > B
./codexion 5 500 200 200 200 10 200 edf 
# BURNOUT obligatoire ; cycle individuel > B
./codexion 7 1500 200 200 200 10 200 fifo 
# LIMITE ; comparer les politiques
./codexion 7 1500 200 200 200 10 200 edf 
# LIMITE ; comparer les politiques
```
## Parallélisme initial et topologie
```bash
./codexion 2 10000 500 100 100 3 0 fifo 
# Survie ; maximum simultané : 1
./codexion 2 10000 500 100 100 3 0 edf 
# Survie ; maximum simultané : 1
./codexion 3 10000 500 100 100 3 0 fifo 
# Survie ; maximum simultané : 1
./codexion 3 10000 500 100 100 3 0 edf 
# Survie ; maximum simultané : 1
./codexion 4 10000 500 100 100 3 0 fifo 
# Survie ; maximum simultané : 2
./codexion 4 10000 500 100 100 3 0 edf 
# Survie ; maximum simultané : 2
./codexion 5 10000 500 100 100 3 0 fifo 
# Survie ; maximum simultané : 2
./codexion 5 10000 500 100 100 3 0 edf 
# Survie ; maximum simultané : 2
./codexion 6 10000 500 100 100 3 0 fifo 
# Survie ; maximum simultané : 3
./codexion 6 10000 500 100 100 3 0 edf 
# Survie ; maximum simultané : 3
./codexion 7 10000 500 100 100 3 0 fifo 
# Survie ; maximum simultané : 3
./codexion 7 10000 500 100 100 3 0 edf 
# Survie ; maximum simultané : 3
./codexion 10 10000 500 100 100 3 0 fifo 
# Survie ; maximum simultané : 5
./codexion 10 10000 500 100 100 3 0 edf 
# Survie ; maximum simultané : 5
./codexion 11 10000 500 100 100 3 0 fifo 
# Survie ; maximum simultané : 5
./codexion 11 10000 500 100 100 3 0 edf 
# Survie ; maximum simultané : 5
```
## Régression integer overflow
```bash
./codexion 5 1000 100 100 100 3 50 fifo 
# Survie, au moins 15 compilations ; aucun burnout immédiat
./codexion 5 1000 100 100 100 3 50 edf 
# Survie, au moins 15 compilations ; aucun burnout immédiat
./codexion 5 2000 100 100 100 3 50 fifo 
# Survie, au moins 15 compilations ; aucun burnout immédiat
./codexion 5 2000 100 100 100 3 50 edf 
# Survie, au moins 15 compilations ; aucun burnout immédiat
./codexion 5 2147 100 100 100 3 50 fifo 
# Survie, au moins 15 compilations ; aucun burnout immédiat
./codexion 5 2147 100 100 100 3 50 edf
 # Survie, au moins 15 compilations ; aucun burnout immédiat
./codexion 5 2148 100 100 100 3 50 fifo 
# Survie, au moins 15 compilations ; aucun burnout immédiat
./codexion 5 2148 100 100 100 3 50 edf 
# Survie, au moins 15 compilations ; aucun burnout immédiat
./codexion 5 3000 100 100 100 3 50 fifo 
# Survie, au moins 15 compilations ; aucun burnout immédiat
./codexion 5 3000 100 100 100 3 50 edf 
# Survie, au moins 15 compilations ; aucun burnout immédiat
./codexion 5 10000 100 100 100 3 50 fifo 
# Survie, au moins 15 compilations ; aucun burnout immédiat
./codexion 5 10000 100 100 100 3 50 edf 
# Survie, au moins 15 compilations ; aucun burnout immédiat
```
## Parsing

```bash
./codexion 
# Rejet propre
./codexion 5 1000 200 200 200 10 200 
# Rejet propre
./codexion 5 1000 200 200 200 10 200 fifo extra 
# Rejet propre
./codexion -5 1000 200 200 200 10 200 fifo 
# Rejet propre
./codexion 5 -1000 200 200 200 10 200 fifo 
# Rejet propre
./codexion 5 1000 -200 200 200 10 200 fifo 
# Rejet propre
./codexion 5 1000 200 -200 200 10 200 fifo 
# Rejet propre
./codexion 5 1000 200 200 -200 10 200 fifo 
# Rejet propre
./codexion 5 1000 200 200 200 -10 200 fifo 
# Rejet propre
./codexion 5 1000 200 200 200 10 -200 fifo 
# Rejet propre
./codexion 5 1000 200 200 200 10 200 EDF 
# Rejet propre
./codexion 5 1000 200 200 200 10 200 random 
# Rejet propre
./codexion 5 1000 200 200 200 10 200 "" 
# Rejet propre
./codexion abc 1000 200 200 200 10 200 fifo 
# Rejet propre
./codexion 5 1000.5 200 200 200 10 200 fifo 
# Rejet propre
./codexion 5 1000 200abc 200 200 10 200 fifo 
# Rejet propre
./codexion 5 1000 200 200 200 10 "" fifo 
# Rejet propre
./codexion 5 999999999999999999999 200 200 200 10 200 fifo  ---->>> a manager ERREUR
# Rejet propre
./codexion 5 2147483648 200 200 200 10 200 fifo 
# Rejet propre
./codexion 0 1000 200 200 200 10 100 fifo 
# Rejet recommandé : le sujet décrit un ou plusieurs coders
./codexion 5 0 200 200 200 10 100 fifo 
# Rejet si B doit être positif ; sinon burnout immédiat
./codexion 5 1000 0 100 100 3 0 fifo 
# Si accepté : compilations instantanées, quota atteint
./codexion 5 1000 100 0 100 3 0 fifo 
# Si accepté : debug instantané
./codexion 5 1000 100 100 0 3 0 fifo 
# Si accepté : refactor instantané
./codexion 5 1000 100 100 100 0 0 fifo 
# Si accepté : objectif déjà atteint, arrêt immédiat
./codexion 5 2000 100 100 100 3 0 fifo 
# SURVIE si cooldown nul accepté ; aucun délai de cooldown
./codexion +5 2000 100 100 100 3 0 fifo 
# Selon convention de parsing documentée
./codexion 005 2000 100 100 100 3 0 fifo 
# Selon convention de parsing documentée
```

## Valgrind — mémoire

```bash
valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=99 ./codexion 4 10000 100 100 100 5 100 fifo 
# Survie attendue ; 0 erreur mémoire, 0 fuite
valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=99 ./codexion 5 10000 100 100 100 5 100 edf 
# Survie attendue ; 0 erreur mémoire, 0 fuite
valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=99 ./codexion 1 500 100 100 100 5 0 fifo 
# Burnout attendu ; 0 erreur mémoire, 0 fuite
valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=99 ./codexion 5 100 500 100 100 5 100 edf 
# Burnout attendu ; 0 erreur mémoire, 0 fuite
```

## Helgrind — synchronisation

```bash
valgrind --tool=helgrind --fair-sched=yes --error-exitcode=99 ./codexion 4 10000 100 100 100 5 100 fifo
# Survie attendue ; 0 erreur de synchronisation signalée
valgrind --tool=helgrind --fair-sched=yes --error-exitcode=99 ./codexion 5 10000 100 100 100 5 100 edf
# Survie attendue ; 0 erreur de synchronisation signalée
valgrind --tool=helgrind --fair-sched=yes --error-exitcode=99 ./codexion 1 500 100 100 100 5 0 edf
# Burnout attendu ; 0 erreur de synchronisation signalée
valgrind --tool=helgrind --fair-sched=yes --error-exitcode=99 ./codexion 5 100 500 100 100 5 100 fifo
# Burnout attendu ; 0 erreur de synchronisation signalée
````
