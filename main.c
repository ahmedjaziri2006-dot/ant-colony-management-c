#include "programme.h"

int main() {
    srand(time(NULL));

    reine ma_reine = creer_reine();
    oeuf* liste_oeufs = NULL;
    ressources stock_nourriture = creer_ressources(1000);
    division_travail division = {0, 0, 0, 0, 0, {0}, {0}, {0}};

    initialiser_fourmis(&division);

    male male_fourmi = creer_male();
    int cycle_reine = 0;

    for (int jour = 1; jour <= MAX_CYCLE; jour++) {
        printf("\nJour %d:", jour);
        if (jour <= 93) {
            printf(" c'est le Printemps. \n");
        } else if (jour <= 183) {
            printf(" c'est l'Été. \n");
        } else if (jour <= 276) {
            printf(" c'est l'Automne. \n");
        } else {
            printf(" c'est l'Hiver. \n");
        }

        if (jour == 130) {
            printf("Une sécheresse frappe la colonie, causant la mort de 8 aînées.\n");
            division.ainees -= 8;
            if (division.ainees < 0) division.ainees = 0;
        }
        if (jour == 240) {
            printf("Une tempête de vent frappe la colonie, causant la mort de 15 aînées.\n");
            division.ainees -= 15;
            if (division.ainees < 0) division.ainees = 0;
        }
        if (jour == 320) {
            printf("Une tempête de neige frappe la colonie, causant la mort de 22 aînées.\n");
            division.ainees -= 22;
            if (division.ainees < 0) division.ainees = 0;
        }

        collecter_ressources_dynamique(&stock_nourriture, jour);
        printf("Stock actuel de nourriture : %d unités.\n", stock_nourriture.stock);

        if (ma_reine.vivante && ma_reine.age_reine < MAX_AGE_REINE) {
            ma_reine.age_reine++;
            cycle_reine++;
            for (int i = 0; i < 6; i++) {
                ajouter_oeuf(&liste_oeufs, 3);
            }
            ma_reine.nb_oeufs += 6;
            printf("Reine : Age %d jours, Oeufs pondus %d, Vivante.\n", ma_reine.age_reine, ma_reine.nb_oeufs);
        } else if (ma_reine.vivante && cycle_reine >= MAX_AGE_REINE) {
            printf("La reine est morte. Une nouvelle reine la remplace.\n");
            ma_reine = creer_reine();
            cycle_reine = 0;
        }

        if (male_fourmi.vivant) {
            male_fourmi.age++;
            if (male_fourmi.age >= MAX_AGE_MALE) {
                printf("Le mâle est mort. Un nouveau mâle remplace l'ancien.\n");
                male_fourmi = creer_male();
            }
        }

        gerer_oeufs(&liste_oeufs, &division);
        gerer_division_travail(&division);
        gerer_activite(&division, jour);

        printf("Rôles actuels : Jeunes = %d, Ouvrières = %d, Aînées = %d\n", division.jeunes, division.ouvrieres, division.ainees);

        int consommation_totale = DAILY_CONSUMPTION;
        if (stock_nourriture.stock >= consommation_totale) {
            stock_nourriture.stock -= consommation_totale;
        } else {
            printf("Attention : Pas assez de nourriture pour maintenir la colonie.\n");
            stock_nourriture.stock = 0;
        }
        printf("Consommation totale : %d unités. Stock restant : %d unités.\n", consommation_totale, stock_nourriture.stock);
    }

    printf("\nSimulation terminée. Nombre total de fourmis restantes : %d\n", division.jeunes + division.ouvrieres + division.ainees);
    return 0;
}
