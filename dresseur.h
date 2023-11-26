#ifndef DRESSEUR_H
#define DRESSEUR_H

#include <iostream>
#include <string>

#include "pokimac.h"
#include "utils.h"
#include "pokimac.h"
#include "jeu.h"
#include "consoleUtils.hpp"

//Création de la structure dresseur
struct dresseur {
    std::string nom;
    std::string sexe;
    int equipe[5];
    int nb_equipier;
    int sac[2];
    Position pos;

};

//initialisation des constantes liées aux ressources
const int MAX_RESS=12;
const int C_POKIBALLS=0;
const int C_POTIONS=1;

const int C_GAIN_PV=40;

//initialisation des constantes pour la touche B
const char T_SAC='b';
const char T_SAC_MAJ='B';

//initialisation des fonctions
void initDresseur(dresseur * dresseur);
void choisirNomDresseur(dresseur * dresseur);
void choisirSexeDresseur(dresseur * le_dresseur);
void initSac(int sac[]);
void competence_poki_base(pokimac * pokis[]);
void choisir_poki_base(dresseur *ptdresseur, pokimac * pokis[]);
void creer_dresseur(dresseur * ptle_dresseur);
void ajouter_Pokimac_Equipe(dresseur * ptlejoueur, pokimac * ptpokichoisi, int indice_poki);
bool peut_capturer_poki(dresseur * ptdress);
bool capturer_poki(pokimac * ptpoki, dresseur * ptdress);
void afficher_sac(dresseur * pt_dresseur);

#endif

