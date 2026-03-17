#ifndef PROGRAMME_H
#define PROGRAMME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_AGE_REINE 100
#define MAX_AGE_MALE 20
#define JEUNE_AGE_MAX 40
#define OUVRIERE_AGE_MAX 60
#define AINEE_AGE_MAX 70
#define MAX_CYCLE 365
#define INITIAL_FOURMIS 350
#define DAILY_CONSUMPTION 300
#define COLLECT_DAY1_SPRING 600
#define COLLECT_DAY2_SPRING 450
#define COLLECT_DAY3_SPRING 350
#define COLLECT_DAY1_SUMMER 550
#define COLLECT_DAY2_SUMMER 400
#define COLLECT_DAY3_SUMMER 300
#define COLLECT_DAY1_AUTUMN 350
#define COLLECT_DAY2_AUTUMN 250
#define COLLECT_DAY3_AUTUMN 200
#define COLLECT_DAY1_WINTER 200
#define COLLECT_DAY2_WINTER 150
#define COLLECT_DAY3_WINTER 50

typedef struct {
    int age_reine;
    int nb_oeufs;
    int vivante;
} reine;

typedef struct oeuf {
    int temps_restant;
    struct oeuf* suivant;
} oeuf;

typedef struct {
    int stock;
} ressources;

typedef struct {
    int jeunes;
    int ouvrieres;
    int ainees;
    int actives;
    int inactives;
    int ages_jeunes[1000];
    int ages_ouvrieres[1000];
    int ages_ainees[1000];
} division_travail;

typedef struct {
    int age;
    int vivant;
} male;

reine creer_reine();
ressources creer_ressources(int stock_initial);
oeuf* creer_oeuf(int temps_restant);
void ajouter_oeuf(oeuf** tete, int temps_restant);
void gerer_oeufs(oeuf** tete, division_travail* division);
void initialiser_fourmis(division_travail* division);
void collecter_ressources_dynamique(ressources* res, int jour);
void gerer_activite(division_travail* division, int jour);
void gerer_division_travail(division_travail* division);
male creer_male();

#endif