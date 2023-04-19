#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "liste.h"


using namespace std;

const int TAILLE_TAQUIN = 3;

struct Taquin {
    int grille[TAILLE_TAQUIN][TAILLE_TAQUIN];
    int ligneCaseVide;
    int colonneCaseVide;
    int cost;
    int h; // heuristic value
    int g; // path cost
    int f; // f(n) = g(n) + h(n)
    Taquin* parent; // Pointeur vers le Taquin précédent dans le chemin menant à la solution
};



void lireTaquin(Taquin &t);
void afficherTaquin(const Taquin &t);
int heuristique(const Taquin &t, const Taquin &but);
bool comparerTaquins(const Taquin &t1, const Taquin &t2);
bool estSolvable(const Taquin &taquinDepart, const Taquin &taquinArrivee);
Liste* genererSuccesseurs(Taquin &t, Taquin &but);
Liste* parcoursAStar(Taquin &depart, Taquin &but);
void afficherCheminSolution(Liste* cheminSolution);
void supprimerTete(Liste* liste);
bool estDejaDansListe(Liste* liste, Taquin* taquin);
