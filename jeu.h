#ifndef JEU_H
#define JEU_H
#include "dresseur.h"

#include "pokimac.h"
#include "consoleUtils.hpp"
#include "utils.h"

#include <iostream>
#include <string>

typedef struct{
    dresseur * pt_lejoueur;
    pokimac * tout_poki[MAX_POKI];
    int compteur_de_pokibattus;
    int compteur_de_capture;
    bool Fin_jeu;
}T_jeu;

typedef T_jeu * T_ptjeu;

// constantes pour les ETATS d'action du joueur
const int C_DEMANDE_CHOIX_ACTION=0;
const int C_ATTAQUE_DRESS=1;
const int C_CAPTURE_POKI=2;
const int C_CHANGE_POKI=3;
const int C_SOIGNE_POKI=4;
const int C_FUIT=5;
const int C_CONTREATT_POKI=6;

// constantes pour les CHOIX d'action du joueur
const int C_ATTAQ=1;
const int C_CAPT=2;
const int C_CHANG=3;
const int C_SOIN=4;
const int C_FUITE=5;
const int C_MAX_CHOIX=5;

// constantes pour le menu pendant partie
const int MENU_JEU=1;
const int MENU_REGLE=2;
const int MENU_QUITJEU=3;

// constantes pour le menu d'avant partie
const int MENUAV_PROFIL=2;
const int MENUAV_REGLE=3;
const int MENUAV_QUITJEU=4;

//constantes pour le profil
const int PROFIL_NOM=1;
const int PROFIL_SEXE=2;

//initialisation des fonctions

void jouer(T_ptjeu jeu);
pokimac * chercher_poki_a_envoye(T_ptjeu jeu);
void afficher_poki_envoye(pokimac * poki);
void attaquer_poki(pokimac * ptpoki_dress, pokimac * ptpoki_sauv);
void contreattaquer_poki(pokimac * ptpoki_dress, pokimac * ptpoki_sauv);
void afficher_choix_action();
void afficher_ascii_combat(std::string asciiArt);
bool a_fuit_combat();
void afficher_fin_combat();
int verifier_entree_int_joueur(int * choix);
void afficher_statistiques(T_ptjeu jeu);
int stat_poki_en_vie(T_ptjeu jeu, int * score);
void stat_bonus(T_ptjeu jeu, int * score);
void stat_poki_battus(T_ptjeu jeu, int * score);
void stat_poki_capture(T_ptjeu jeu, int * score);



#endif
