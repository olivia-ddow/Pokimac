#ifndef MENU_H
#define MENU_H

#include "jeu.h"
#include "pokimac.h"
#include "consoleUtils.hpp"
#include "utils.h"
#include <iostream>
#include <string>

void afficheTitre();
void ligne_vague();
void afficheRegles(dresseur * ptdresseur);
void afficheOptionsMenu();
void MenuAvantPartie(dresseur *lejoueur);
void afficheOptionsMenuPendantPartie();
void MenuPendantPartie(T_ptjeu jeu);

#endif
