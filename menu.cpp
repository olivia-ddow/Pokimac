
#include "menu.h"

using namespace std;

void afficheTitre(){
    ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTWHITE);
    cout << "BIENVENUE SUR" <<endl;
    ConsoleUtils::resetColors();

    int rand_color;
    rand_color= rand() % 16;

    ConsoleUtils::setColor(static_cast<ConsoleUtils::Color>(rand_color));

    cout << " _  _  _  _         _  _  _  _      _           _     _  _  _        _           _           _              _  _  _    "<<endl;
    cout << "(_)(_)(_)(_)_     _(_)(_)(_)(_)_   (_)       _ (_)   (_)(_)(_)      (_) _     _ (_)        _(_)_         _ (_)(_)(_) _ "<<endl;
    cout << "(_)        (_)   (_)          (_)  (_)    _ (_)         (_)         (_)(_)   (_)(_)      _(_) (_)_      (_)         (_)"<<endl;
    cout << "(_) _  _  _(_)   (_)          (_)  (_) _ (_)            (_)         (_) (_)_(_) (_)    _(_)     (_)_    (_)            "<<endl;
    cout << "(_)(_)(_)(_)     (_)          (_)  (_)(_) _             (_)         (_)   (_)   (_)   (_) _  _  _ (_)   (_)            "<<endl;
    cout << "(_)              (_)          (_)  (_)   (_) _          (_)         (_)         (_)   (_)(_)(_)(_)(_)   (_)          _ "<<endl;
    cout << "(_)              (_)_  _  _  _(_)  (_)      (_) _     _ (_) _       (_)         (_)   (_)         (_)   (_) _  _  _ (_)"<<endl;
    cout << "(_)                (_)(_)(_)(_)    (_)         (_)   (_)(_)(_)      (_)         (_)   (_)         (_)      (_)(_)(_)   "<<endl;

    ConsoleUtils::resetColors();

    sleep(2000);
    ConsoleUtils::clear();


}

//fonction qui affiche les règles du jeu
void afficheRegles(dresseur * ptdresseur){
    //On met la couleur du texte en lightcyan
    ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTCYAN);
    cout << "REGLES DU JEU POKIMAC" <<endl<<endl;
    ConsoleUtils::resetColors();
    //On met la couleur du texte en lightwhite
    ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTWHITE);
    cout << "L'objectif de ce jeu est de vous promener sur la carte et de rencontrer les pokimacs." << endl
     << "Vous pouvez les combattre et les capturer. Pour les capturer, vous aurez besoin de pokiballs. Vous pourrez en trouver sur le terrain."<<endl<<endl;
    cout << "Lors des combats, vos pokimacs perdront des PV, utilisez des potions pour les restaurer." <<
    "Si un de vos pokimacs n'a plus de PV, il ne pourra plus se battre." <<endl;
    cout << "Au debut du jeu, vous choisirez le pokimac avec qui vous souhaitez commencer cette aventure." << endl <<
    "Vous aurez deja dans votre sac, " << ptdresseur->sac[C_POKIBALLS] << " pokiballs et " << ptdresseur->sac[C_POTIONS] << " potions." << endl;
    cout << "Le jeu se termine lorsqu'il n'y a plus de pokimacs sur la carte ou lorsque vous perdez le combat." <<endl<<endl;
    cout << "Bonne Aventure !" << endl<<endl;
    ligne_vague();
    ConsoleUtils::resetColors();
}


//fonction qui affiche les options du menu avant le début du jeu
void afficheOptionsMenu(){
    cout << "______________________" <<endl;
    cout << "| ";
    ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTCYAN);
    cout<<"      MENU       ";
    ConsoleUtils::resetColors();
    cout <<"  |"<<endl;
    cout << "| 1. jouer           |" <<endl;
    cout << "| 2. modifier profil |" <<endl;
    cout << "| 3. lire les regles |" <<endl;
    cout << "| 4. Quitter         |" <<endl;
    cout << "______________________"<<endl;
}

//fonction qui affiche les options du menu pendant la partie
void afficheOptionsMenuPendantPartie(){
    cout <<endl;
    cout << "______________________" <<endl;
    cout << "| ";
    ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTCYAN);
    cout<<"      MENU       ";
    ConsoleUtils::resetColors();
    cout <<"  |"<<endl;
    cout << "| 1. continuer       |" <<endl;
    cout << "| 2. lire les regles |" <<endl;
    cout << "| ";
    ConsoleUtils::setColor(ConsoleUtils::Color::RED);
    cout << "3. Quitter       ";
    ConsoleUtils::resetColors();
    cout << "  |" <<endl;
    cout << "______________________"<<endl;
}

//fonction qui affiche le menu pendant la partie
void MenuPendantPartie(T_ptjeu jeu){
    cout <<endl;
    int choixMenuPP = 0;
    do{
        afficheOptionsMenuPendantPartie();
        cin >> choixMenuPP;
        choixMenuPP = verifier_entree_int_joueur(&choixMenuPP);

        switch(choixMenuPP){
            case MENU_JEU:  //continuer
            {
                cout << "vous continuez le jeu" <<endl;
            }
            break;
            case MENU_REGLE:
            {
                afficheRegles(jeu->pt_lejoueur); //lire les règles
            }
            break;
            case MENU_QUITJEU:  //quitter;
            {
                string q;
                do{
                    cout << "Etes vous certain de vouloir quitter la partie? Toute progression sera perdue. (O/N)";
                    cin >> q;
                    if(q=="O" || q=="o"){
                        system("cls");

                        cout << "Au revoir !" <<endl;
                        sleep(1000);
                        exit(0);
                    }
                    else if(q=="N" || q=="n"){
                        cout << "Vous continuez le jeu" <<endl;
                    }
                    else{
                        cout <<"Veuillez selectionner O ou N" <<endl;
                    }
                }while(q!="O" && q!="o" && q!="N" && q!="n");

            }
            break;
            default:
            {
                cout << "erreur: veuillez entrer 1,2 ou 3." <<endl;
            }
            break;
        }
    }while (choixMenuPP !=0 && choixMenuPP != MENU_QUITJEU && choixMenuPP != MENU_JEU);
}


//fonction qui affiche le menu d'avant partie
void MenuAvantPartie(dresseur *lejoueur)
{
    int choixMenu=0;
    do{
        afficheOptionsMenu();
        cin >> choixMenu;
        choixMenu = verifier_entree_int_joueur(&choixMenu);
        switch(choixMenu){
            case MENU_JEU:  //jouer;
            {
                system("cls");
                cout << "vous avez lance le jeu" <<endl;
            }
            break;
            case MENUAV_PROFIL:  //modifier profil;
            {
                system("cls");
                int choixProfil = 0;
                do{
                    cout << "1. Nom" <<endl;
                    cout << "2. Sexe" <<endl;
                    cin >> choixProfil;
                    verifier_entree_int_joueur(&choixProfil);
                    if(choixProfil == PROFIL_NOM){
                        system("cls");
                        cout<<endl;
                        cout << "   NOM DU DRESSEUR" <<endl<<endl;
                        choisirNomDresseur(lejoueur);
                    }
                    else if(choixProfil == PROFIL_SEXE){
                        system("cls");
                        cout<<endl;
                        cout << "   SEXE DU DRESSEUR" <<endl<<endl;
                        choisirSexeDresseur(lejoueur);
                    }
                    else{
                        cout << " Veuillez selectionner 1 ou 2"<< endl;

                    }
                }
                while(choixProfil != PROFIL_NOM && choixProfil != PROFIL_SEXE);
            }
            break;
            case MENUAV_REGLE:
            {
                system("cls");
                afficheRegles(lejoueur); //affiche les règles
            }

            break;
            case MENUAV_QUITJEU:  //quitter;
            {
                system("cls");
                cout << "Au revoir !" <<endl;
                sleep(1000);
                exit(0);
            }
            break;
            default:  // clear et réaffiche;
            {
                system("cls");
                cout << "erreur: veuillez entrer 1,2,3 ou 4." <<endl;
            }
            break;
        }
    }while (choixMenu !=0 && choixMenu != MENUAV_QUITJEU && choixMenu != MENU_JEU );
}


