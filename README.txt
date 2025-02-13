-- Game of Life di Conway --

Implementazione base del GoL di Conway.
- main.py
  Involucro del programma. Inizializza la griglia con numpy e predispone
  la resa grafica con matplotlib.

- state_transition.c
  Il calcolo del nuovo stato della griglia viene gestito da una
  funzione in C.
  La griglia, rappresentata da un *array, è equipaggiata con una struttura
  toroidale (toroidal_wrap).
