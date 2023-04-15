#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>


using namespace std;

const int TAILLE_TAQUIN = 3;

struct Taquin {
    int grille[TAILLE_TAQUIN][TAILLE_TAQUIN];
    int ligneCaseVide;
    int colonneCaseVide;
};
void afficherTaquin(const Taquin &t);
void lireTaquin(Taquin &t);
int heuristique(const Taquin &t, const Taquin &but);
bool comparerTaquins(const Taquin &t1, const Taquin &t2);
bool estSolvable(const Taquin &t, const Taquin &but);
bool comparerTaquins(const Taquin &t, const Taquin &but);
