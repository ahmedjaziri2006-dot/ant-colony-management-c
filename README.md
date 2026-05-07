# Simulation de Gestion d'une Colonie de Fourmis

Programme de simulation en C qui modélise le fonctionnement d'une colonie de fourmis sur un cycle annuel complet (365 jours). Le projet simule le cycle de vie des fourmis, la reproduction de la reine, la collecte et la consommation de nourriture, la division du travail, ainsi que l'impact des saisons et d'événements climatiques sur la colonie.

## Contexte

Projet académique réalisé à l'ESIEA (novembre 2024 – janvier 2025) en équipe de 3 personnes, dans le cadre d'un module d'algorithmique et structures de données avancées.

## Modèle simulé

### Cycle de vie

La colonie est composée de plusieurs catégories de fourmis qui évoluent automatiquement :

- **Œufs** : éclosent après 3 jours pour devenir des jeunes
- **Jeunes** : jusqu'à 40 jours, puis deviennent ouvrières
- **Ouvrières** : jusqu'à 60 jours, puis deviennent aînées
- **Aînées** : jusqu'à 70 jours, puis meurent

### Reine et mâle

- La **reine** pond 6 œufs par jour jusqu'à 100 jours, puis est remplacée par une nouvelle reine
- Un **mâle** vit jusqu'à 20 jours et est remplacé à sa mort

### Saisons et collecte de ressources

Le cycle annuel est divisé en quatre saisons :

| Saison | Jours | Taux de collecte |
|---|---|---|
| Printemps | 1 – 93 | élevé (350 – 600 unités/jour) |
| Été | 94 – 183 | élevé (300 – 550 unités/jour) |
| Automne | 184 – 276 | moyen (200 – 350 unités/jour) |
| Hiver | 277 – 365 | faible (50 – 200 unités/jour) |

À l'intérieur de chaque saison, la collecte varie selon une rotation de 3 jours.

### Événements climatiques

Trois événements impactent la colonie au cours de l'année :
- **Jour 130** : sécheresse → 8 aînées meurent
- **Jour 240** : tempête de vent → 15 aînées meurent
- **Jour 320** : tempête de neige → 22 aînées meurent

### Consommation

La colonie consomme 300 unités de nourriture par jour. Si le stock est insuffisant, un avertissement s'affiche.

## Fonctionnalités

- Simulation jour par jour sur un cycle de 365 jours
- Suivi du cycle de vie des fourmis avec transition automatique entre catégories
- Gestion dynamique des œufs via une liste chaînée
- Division du travail : alternance quotidienne entre ouvrières actives et inactives
- Affichage détaillé de l'état de la colonie chaque jour (population, stock, événements)

## Algorithmes et concepts

- **Liste chaînée dynamique** pour la gestion des œufs (allocation/libération mémoire avec `malloc` / `free`)
- **Tableaux statiques** pour le suivi des âges des fourmis dans chaque catégorie
- **Compaction de tableaux** après suppression d'éléments (pattern de filtre in-place)
- **Logique modulaire** basée sur le jour et la saison pour la collecte de ressources
- **Machine à états** implicite pour les transitions de cycle de vie

## Structures de données

```c
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
```

## Stack technique

- **Langage :** C
- **Build :** Makefile (gcc)

## Structure du projet
main.c         - boucle principale de simulation (365 jours)
fonctions.c    - logique de la colonie (cycle de vie, ressources, division du travail)
programme.h    - types, constantes (âges max, taux de collecte, etc.)
Makefile       - configuration de build

## Compilation et exécution

```bash
git clone https://github.com/ahmedjaziri2006-dot/ant-colony-management-c
cd ant-colony-management-c
make
./programme
```

Pour nettoyer les fichiers compilés :

```bash
make clean
```

## Compétences mises en œuvre

- Programmation en C avec gestion manuelle de la mémoire (linked lists, malloc/free sans fuite)
- Modélisation algorithmique d'un système complexe à plusieurs entités interagissantes
- Conception modulaire (séparation entre logique métier et boucle principale)
- Manipulation simultanée de structures de données dynamiques et statiques selon les besoins
- Simulation événementielle sur cycle long (365 itérations)

## Auteurs

Projet réalisé en équipe à l'ESIEA par Ahmed Jaziri et coéquipiers.

## Licence

Projet académique à but pédagogique.
