#include "programme.h"

reine creer_reine() {
    reine r = {0, 0, 1};
    return r;
}

ressources creer_ressources(int stock_initial) {
    ressources res = {stock_initial};
    return res;
}

oeuf* creer_oeuf(int temps_restant) {
    oeuf* nouvel_oeuf = malloc(sizeof(oeuf));
    nouvel_oeuf->temps_restant = temps_restant;
    nouvel_oeuf->suivant = NULL;
    return nouvel_oeuf;
}

void ajouter_oeuf(oeuf** tete, int temps_restant) {
    oeuf* nouvel_oeuf = creer_oeuf(temps_restant);
    nouvel_oeuf->suivant = *tete;
    *tete = nouvel_oeuf;
}

void gerer_oeufs(oeuf** tete, division_travail* division) {
    oeuf* courant = *tete;
    oeuf* precedent = NULL;

    while (courant) {
        courant->temps_restant--;

        if (courant->temps_restant <= 0) {
            division->jeunes++;
            if (precedent) {
                precedent->suivant = courant->suivant;
            } else {
                *tete = courant->suivant;
            }
            free(courant);
            courant = (precedent) ? precedent->suivant : *tete;
        } else {
            precedent = courant;
            courant = courant->suivant;
        }
    }
}

void initialiser_fourmis(division_travail* division) {
    for (int i = 0; i < 80; i++) {
        division->ages_jeunes[i] = 5;
    }
    for (int i = 80; i < 130; i++) {
        division->ages_jeunes[i] = 15;
    }
    for (int i = 130; i < 170; i++) {
        division->ages_jeunes[i] = 25;
    }
    for (int i = 170; i < 200; i++) {
        division->ages_jeunes[i] = 30;
    }
    division->jeunes = 200;

    for (int i = 0; i < 40; i++) {
        division->ages_ouvrieres[i] = 45;
    }
    for (int i = 40; i < 75; i++) {
        division->ages_ouvrieres[i] = 50;
    }
    for (int i = 75; i < 100; i++) {
        division->ages_ouvrieres[i] = 55;
    }
    division->ouvrieres = 100;

    for (int i = 0; i < 30; i++) {
        division->ages_ainees[i] = 62;
    }
    for (int i = 30; i < 45; i++) {
        division->ages_ainees[i] = 65;
    }
    for (int i = 45; i < 50; i++) {
        division->ages_ainees[i] = 68;
    }
    division->ainees = 50;

    division->actives = division->ouvrieres / 2;
    division->inactives = division->ouvrieres / 2;
}

void collecter_ressources_dynamique(ressources* res, int jour) {
    int quantite;
    if (jour >= 1 && jour <= 93) {
        quantite = (jour % 3 == 1) ? COLLECT_DAY1_SPRING : (jour % 3 == 2) ? COLLECT_DAY2_SPRING : COLLECT_DAY3_SPRING;
    } else if (jour >= 94 && jour <= 183) {
        quantite = (jour % 3 == 1) ? COLLECT_DAY1_SUMMER : (jour % 3 == 2) ? COLLECT_DAY2_SUMMER : COLLECT_DAY3_SUMMER;
    } else if (jour >= 184 && jour <= 276) {
        quantite = (jour % 3 == 1) ? COLLECT_DAY1_AUTUMN : (jour % 3 == 2) ? COLLECT_DAY2_AUTUMN : COLLECT_DAY3_AUTUMN;
    } else {
        quantite = (jour % 3 == 1) ? COLLECT_DAY1_WINTER : (jour % 3 == 2) ? COLLECT_DAY2_WINTER : COLLECT_DAY3_WINTER;
    }
    res->stock += quantite;
    printf("Unité collectée aujourd'hui : %d\n", quantite);
}

void gerer_activite(division_travail* division, int jour) {
    if (jour % 2 == 0) {
        division->actives = division->ouvrieres / 2;
        division->inactives = division->ouvrieres - division->actives;
    } else {
        division->inactives = division->ouvrieres / 2;
        division->actives = division->ouvrieres - division->inactives;
    }
    printf("Ouvrières actives : %d, Inactives : %d\n", division->actives, division->inactives);
}

void gerer_division_travail(division_travail* division) {
    int nouvelles_ouvrieres = 0;
    int nouvelles_ainees = 0;
    int mortes = 0;

    for (int i = 0; i < division->jeunes; i++) {
        division->ages_jeunes[i]++;
        if (division->ages_jeunes[i] > JEUNE_AGE_MAX) {
            nouvelles_ouvrieres++;
            division->ages_jeunes[i] = -1;
        }
    }
    int index_jeunes = 0;
    for (int i = 0; i < division->jeunes; i++) {
        if (division->ages_jeunes[i] != -1) {
            division->ages_jeunes[index_jeunes++] = division->ages_jeunes[i];
        }
    }
    division->jeunes = index_jeunes;
    division->ouvrieres += nouvelles_ouvrieres;

    for (int i = 0; i < division->ouvrieres; i++) {
        division->ages_ouvrieres[i]++;
        if (division->ages_ouvrieres[i] > OUVRIERE_AGE_MAX) {
            nouvelles_ainees++;
            division->ages_ouvrieres[i] = -1;
        }
    }
    int index_ouvrieres = 0;
    for (int i = 0; i < division->ouvrieres; i++) {
        if (division->ages_ouvrieres[i] != -1) {
            division->ages_ouvrieres[index_ouvrieres++] = division->ages_ouvrieres[i];
        }
    }
    division->ouvrieres = index_ouvrieres;
    division->ainees += nouvelles_ainees;

    for (int i = 0; i < division->ainees; i++) {
        division->ages_ainees[i]++;
        if (division->ages_ainees[i] > AINEE_AGE_MAX) {
            mortes++;
            division->ages_ainees[i] = -1;
        }
    }
    int index_ainees = 0;
    for (int i = 0; i < division->ainees; i++) {
        if (division->ages_ainees[i] != -1) {
            division->ages_ainees[index_ainees++] = division->ages_ainees[i];
        }
    }
    division->ainees = index_ainees;

    if (nouvelles_ouvrieres > 0) {
        printf("%d jeunes sont devenus ouvrières aujourd'hui.\n", nouvelles_ouvrieres);
    }
    if (nouvelles_ainees > 0) {
        printf("%d ouvrières sont devenues aînées aujourd'hui.\n", nouvelles_ainees);
    }
    if (mortes > 0) {
        printf("%d aînées sont mortes aujourd'hui.\n", mortes);
    }
}

male creer_male() {
    male m = {0, 1};
    return m;
}