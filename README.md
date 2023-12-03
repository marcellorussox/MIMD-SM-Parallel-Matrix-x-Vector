# MIMD-SM-Parallel-Matrix-x-Vector
Sviluppare un algoritmo per il calcolo del prodotto matrice-vettore, in ambiente di calcolo parallelo su architettura MIMD a memoria condivisa, che utilizzi la libreria OpenMp.

# Indicazioni per compilare su Mac con libreria installata tramite brew
Usare il compilatore di brew al posto di quello di default
`/opt/homebrew/Cellar/gcc/13.2.0/bin/g++-13 main.c utils/* -fopenmp -o test`
