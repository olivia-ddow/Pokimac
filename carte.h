#ifndef CARTE_H
#define CARTE_H

#include <iostream>
#include <string>
#include "dresseur.h"
#include "jeu.h"
//#include "type_base.h"
#include "consoleUtils.hpp"
#include "utils.h"
#include "menu.h"

struct dresseur;



const int hauteur=12;
const int largeur=40;

const int MAX_CAILLOUX=30;

// constantes pour les différents types de cases
const int C_CMURS=0;
const int C_CVIDE=2;
const int C_CCAILLOUX=3;
const int C_CRESSOURCES=4;
const int C_CPOKI=5;

//constantes pour les touches de clavier
const char T_HAUT='z';
const char T_HAUT_MAJ='Z';
const char T_BAS='s';
const char T_BAS_MAJ='S';
const char T_GAUCHE='q';
const char T_GAUCHE_MAJ='Q';
const char T_DROITE='d';
const char T_DROITE_MAJ='D';
const char T_MENU='m';
const char T_MENU_MAJ='M';






void initCase(Case *unecase, int type, int index);
void placer_pokimac(Case tabtab[largeur][hauteur], int maxpoki, pokimac * tabpoki[]);
void placer_ressources(Case tabtab[largeur][hauteur], int maxress);
void placer_cailloux(Case tabtab[largeur][hauteur], int maxcaillou);
//void afficheCarte(char tab[largeur][hauteur]);
void initCarte(T_ptjeu jeu) ;
char charFromCase(const Case *c);
void afficheLaCarte(Case tab[largeur][hauteur]);
void remplirLaCarte(Case tab[largeur][hauteur], T_ptjeu jeu);

void deplacer_dresseur(Position * ptNpos, T_ptjeu jeu, Case ptcarte[largeur][hauteur]);
Case * rend_case(Case ptcarte[largeur][hauteur], Position * ptpos);
int rend_type_case(Case * ptcase);
void prendre_ressources(T_ptjeu jeu, int index, int type);
void rencontre_pokimac(T_ptjeu jeu, Case * ptcase, Case ptcarte[largeur][hauteur]);
void actions_joueur(T_ptjeu jeu, Case tab[largeur][hauteur]);
void afficher_joueur(const dresseur * pt_lejoueur);

void afficher_fenetre_combat(pokimac * ptpoki_envoye, pokimac * ptpoki_sauvage);
void executer_combat(int etat, T_ptjeu jeu, pokimac * poki_envoye, pokimac * poki_sauvage, Case * casepoki);

void deplacer_pokimac(T_ptjeu jeu, Case carte[largeur][hauteur]);
void tester_case_vide(int * nbcasevide, Position * posadj, Position tabcaselibre[4], Case carte[largeur][hauteur]);

void deplacer_haut(T_ptjeu jeu, Position Nouvpos, Case carte[largeur][hauteur]);
void deplacer_bas(T_ptjeu jeu, Position Nouvpos, Case carte[largeur][hauteur]);
void deplacer_gauche(T_ptjeu jeu, Position Nouvpos, Case carte[largeur][hauteur]);
void deplacer_droite(T_ptjeu jeu, Position Nouvpos, Case carte[largeur][hauteur]);



#endif
