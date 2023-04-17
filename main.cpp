#include <iostream>
#include "taquin.h"
using namespace std;

int main() {
    Taquin taquinDepart;
    Taquin taquinArrivee;
    lireTaquin(taquinDepart);
    lireTaquin(taquinArrivee);

    if (!estSolvable(taquinDepart, taquinArrivee)) {
        cout << "Le taquin de depart n'est pas solvable par rapport au taquin d'arrivee." << endl;
        return 0;
    }

    cout << "Taquin de depart :" << endl;
    afficherTaquin(taquinDepart);
    cout << "Taquin d'arrivee :" << endl;
    afficherTaquin(taquinArrivee);

    Liste* cheminSolution = parcoursAStar(taquinDepart, taquinArrivee);

    if (cheminSolution == NULL) {
        cout << "Aucune solution trouvee." << endl;
    } else {
        cout << "Chemin solution :" << endl;
        afficherCheminSolution(cheminSolution);
        detruireListe(cheminSolution);
    }

    return 0;
}
