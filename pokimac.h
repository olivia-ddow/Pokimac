#ifndef POKIMAC_H
#define POKIMAC_H

#include "utils.h"
#include <iostream>
#include <string>

//initialisation de la structure du pokimac
typedef struct {
    std::string nom;
    std::string asciiArt;
    int vie_de_base;
    int vie_actuelle;
    int attaque;
    bool est_dans_equipe;
} pokimac;

//initialisation des constantes
const int MAX_EQUIPIERS=5;
const int MAX_POKI=9;

struct dresseur;
//initialisation des fonctions
void initPokimac(pokimac *poki, std::string nom, std::string asciiArt, int vie_de_base, int attaque);
pokimac * recherche_pokimac_base(pokimac * tabpokis[], int choixpoki);

bool poki_est_mort(pokimac * ptpoki);
bool poki_doit_soigner(pokimac * ptpokimac, dresseur * ptdress);
void soigner_poki(pokimac * ptpokimac, dresseur * ptdress);
#endif
