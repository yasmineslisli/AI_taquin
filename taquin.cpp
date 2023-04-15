#include "taquin.h"

void lireTaquin(Taquin &t) {
    cout << "Entrez les éléments du taquin (" << TAILLE_TAQUIN << "x" << TAILLE_TAQUIN << ") :" << endl;
    for (int i = 0; i < TAILLE_TAQUIN; i++) {
        for (int j = 0; j < TAILLE_TAQUIN; j++) {
            cin >> t.grille[i][j];
            if (t.grille[i][j] == 0) {
                t.ligneCaseVide = i;
                t.colonneCaseVide = j;
            }
        }
    }
}

void afficherTaquin(const Taquin &t) {
    printf("Affichage du taquin: \n")
    for (int i = 0; i < TAILLE_TAQUIN; i++) {
        for (int j = 0; j < TAILLE_TAQUIN; j++) {
            cout << t.grille[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int heuristique(const Taquin &t, const Taquin &but) {
    int nbCasesMalPlacees = 0;

    for (int i = 0; i < TAILLE_TAQUIN; i++) {
        for (int j = 0; j < TAILLE_TAQUIN; j++) {
            if (t.grille[i][j] != but.grille[i][j]) {
                nbCasesMalPlacees++;
            }
        }
    }

    return nbCasesMalPlacees;
}

bool comparerTaquins(const Taquin &t1, const Taquin &t2) {
    for (int i = 0; i < TAILLE_TAQUIN; i++) {
        for (int j = 0; j < TAILLE_TAQUIN; j++) {
            if (t1.grille[i][j] != t2.grille[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool estSolvable(const Taquin &taquinDepart, const Taquin &taquinArrivee) {
    // Convertir les taquins en tableaux linéaires pour faciliter le calcul
    int linearArrayDepart[9];
    int linearArrayArrivee[9];
    int index = 0;
    for (int i = 0; i < TAILLE_TAQUIN; i++) {
        for (int j = 0; j < TAILLE_TAQUIN; j++) {
            linearArrayDepart[index] = taquinDepart.grille[i][j];
            linearArrayArrivee[index] = taquinArrivee.grille[i][j];
            index++;
        }
    }

    // Calculer les nombres d'inversions pour les taquins de départ et d'arrivée
    int inversionCountDepart = 0;
    int inversionCountArrivee = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (linearArrayDepart[j] && linearArrayDepart[i] && linearArrayDepart[i] > linearArrayDepart[j]) {
                inversionCountDepart++;
            }
            if (linearArrayArrivee[j] && linearArrayArrivee[i] && linearArrayArrivee[i] > linearArrayArrivee[j]) {
                inversionCountArrivee++;
            }
        }
    }

    // Vérifier si les nombres d'inversions sont de même parité
    // Si oui, le taquin est solvable, sinon il ne l'est pas
    return (inversionCountDepart % 2 == 0) == (inversionCountArrivee % 2 == 0);
}

bool comparerTaquins(const Taquin &taquin1, const Taquin &taquin2) {
    for (int i = 0; i < TAILLE_TAQUIN; i++) {
        for (int j = 0; j < TAILLE_TAQUIN; j++) {
            if (taquin1.grille[i][j] != taquin2.grille[i][j]) {
                return false; // S'ils diffèrent, les taquins ne sont pas identiques
            }
        }
    }
    return true; // Si toutes les cases sont identiques, les taquins sont identiques
}

