#include <iostream>
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
    printf("Affichage du taquin: \n");
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


Liste* genererSuccesseurs(Taquin &t, Taquin &but) {
    Liste* successeurs = creerListe(0, NULL, NULL); // Créer une liste vide pour les successeurs
    int ligneVide = t.ligneCaseVide;
    int colonneVide = t.colonneCaseVide;

    // Générer les successeurs possibles en déplaçant la case vide dans les quatre directions (haut, bas, gauche, droite)
    if (ligneVide > 0) {
        Taquin* successeurHaut =  new Taquin;
        memcpy(&successeurHaut, &t, sizeof(Taquin)); // Copier l'état du taquin actuel
        successeurHaut->grille[ligneVide][colonneVide] = successeurHaut->grille[ligneVide - 1][colonneVide];
        successeurHaut->grille[ligneVide - 1][colonneVide] = 0;
        successeurHaut->ligneCaseVide = ligneVide - 1;
        successeurHaut->cost = t.cost + 1+ heuristique(t,but);
        insererEnFinDeListe(successeurs, successeurHaut); // Insérer le successeur dans la liste
    }

    if (ligneVide < TAILLE_TAQUIN - 1) {
        Taquin* successeurBas = new Taquin;
        memcpy(&successeurBas, &t, sizeof(Taquin));
        successeurBas->grille[ligneVide][colonneVide] = successeurBas->grille[ligneVide + 1][colonneVide];
        successeurBas->grille[ligneVide + 1][colonneVide] = 0;
        successeurBas->ligneCaseVide = ligneVide + 1;
        successeurBas->cost = t.cost + 1 + heuristique(t,but);
        insererEnFinDeListe(successeurs, successeurBas);
    }

    if (colonneVide > 0) {
        Taquin* successeurGauche = new Taquin;
        memcpy(&successeurGauche, &t, sizeof(Taquin));
        successeurGauche->grille[ligneVide][colonneVide] = successeurGauche->grille[ligneVide][colonneVide - 1];
        successeurGauche->grille[ligneVide][colonneVide - 1] = 0;
        successeurGauche->colonneCaseVide = colonneVide - 1;
        successeurGauche->cost = t.cost + 1+ heuristique(t,but);
        insererEnFinDeListe(successeurs, successeurGauche);
    }

    if (colonneVide < TAILLE_TAQUIN - 1) {
        Taquin* successeurDroit =  new Taquin;
        memcpy(&successeurDroit, &t, sizeof(Taquin));
        successeurDroit->grille[ligneVide][colonneVide] = successeurDroit->grille[ligneVide][colonneVide + 1];
        successeurDroit->grille[ligneVide][colonneVide + 1] =0;
        successeurDroit->colonneCaseVide = colonneVide + 1;
        successeurDroit->cost = t.cost + 1+ heuristique(t,but);
        insererEnFinDeListe(successeurs, successeurDroit);
    }

    return successeurs; // Retourner la liste des successeurs générés
}
void supprimerTete(Liste* liste) {
    if (liste == NULL || liste->premier == NULL) {
        return; // Rien à supprimer si la liste est vide
    }

    Element* supprimer = liste->premier;
    liste->premier = liste->premier->suivant;
    free(supprimer); // Libérer la mémoire de l'élément supprimé
    liste->nbElt--;

    // Si la liste est maintenant vide, mettre le champ 'dernier' à NULL
    if (liste->nbElt == 0) {
        liste->dernier = NULL;
    }
}
bool estDejaDansListe(Liste* liste, Taquin taquin) {
    Element* courant = liste->premier;
    while (courant != NULL) {
        Taquin* t = (Taquin*) courant->reference;
        if (comparerTaquins(*t, taquin)) {
            return true;
        }
        courant = courant->suivant;
    }
    return false;
}



Liste* parcoursAStar(Taquin &depart, Taquin &but) {
    Liste* ouverts = creerListe(0, NULL, NULL);
    Liste* fermes = creerListe(0, NULL, NULL);

    depart.g = 0;
    depart.h = heuristique(depart, but);
    depart.f = depart.g + depart.h;

    insererEnFinDeListe(ouverts, &depart);

    while (!listeVide(ouverts)) {
        Taquin* courant = (Taquin*) extraireEnTeteDeListe(ouverts);
        supprimerTete(ouverts);
        insererEnFinDeListe(fermes, courant);

        if (comparerTaquins(*courant, but)) {
            // Solution trouvée, reconstruire le chemin
            Liste* chemin = creerListe(0, NULL, NULL);
            insererEnTeteDeListe(chemin, courant);

            while (courant->parent != NULL) {
                courant = courant->parent;
                insererEnTeteDeListe(chemin, courant);
            }

            return chemin;
        }

        Liste* successeurs = genererSuccesseurs(*courant, but);
        Liste* successeur = successeurs;

        while (successeur != NULL) {
        Taquin* s = (Taquin*)(successeur->courant);

            int tentative_g = courant->g + 1; // Coût du déplacement = 1

            if (!estDejaDansListe(ouverts, *s) && !estDejaDansListe(fermes, *s)) {
                s->parent = courant;
                s->g = tentative_g;
                s->h = heuristique(*s, but);
                s->f = s->g + s->h;
                insererEnFinDeListe(ouverts, s);
            } else if (tentative_g < s->g) {
                s->parent = courant;
                s->g = tentative_g;
                s->f = s->g + s->h;

                if (estDejaDansListe(fermes, *s)) {
                extraireUnObjet(fermes, s);
                insererEnFinDeListe(ouverts, s);
            }

            }

            successeur = (Liste*)successeur->courant->suivant;
        }

        return successeur;
    }

    return NULL; // Aucune solution trouvée
}


void afficherCheminSolution(Liste* cheminSolution) {
    cout << "Chemin solution : ";
    if (cheminSolution == NULL) {
        cout << "Aucun chemin solution." << endl;
        return;
    }

    Liste* courant = cheminSolution;
    while (courant != NULL) {
        switch (courant->reference) {
            case HAUT:
                cout << "H ";
                break;
            case BAS:
                cout << "B ";
                break;
            case GAUCHE:
                cout << "G ";
                break;
            case DROITE:
                cout << "D ";
                break;
        }
        courant = courant->suivant;
    }

    cout << endl;
}
