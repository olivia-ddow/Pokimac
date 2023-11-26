#include "dresseur.h"

using namespace std;

//fonction d'initialisation du dresseur
void initDresseur(dresseur * ptdresseur){
    ptdresseur->nom="";
    ptdresseur->sexe="";

    ptdresseur->nb_equipier=0;

    ptdresseur->pos.x=1;
    ptdresseur->pos.y=10;
    initSac(ptdresseur->sac);
}

//fonction d'initialisation du sac
 void initSac(int sac[]){
      sac[C_POKIBALLS]=7;
      sac[C_POTIONS]=3;
 }

//fonction de création du dresseur
void creer_dresseur(dresseur * ptle_dresseur){


    cout << "+----------------------------+" <<endl;
    cout << "| ";
    ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTCYAN);
    cout << "Creation de votre dresseur";
    ConsoleUtils::resetColors();
    cout << " |"<<endl;
    cout << "+----------------------------+" <<endl;
    // Le dresseur entre son nom
    choisirNomDresseur(ptle_dresseur);

    // Le dresseur entre son sexe
    choisirSexeDresseur(ptle_dresseur);
    ligne_vague();
    sleep(1000);
    ConsoleUtils::clear();

}
//fonction qui récupère le nom du dresseur
void choisirNomDresseur(dresseur * ptle_dresseur){
    string choixNom;
    cout << "Entrez le nom de votre dresseur de pokimac : ";
    ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTCYAN);
    cin >> choixNom;
    ConsoleUtils::resetColors();
    ptle_dresseur->nom=choixNom;
    cout << "Bonjour " << ptle_dresseur->nom << " ! " <<endl<<endl;
}

//fonction qui récupère le nom du dresseur
void choisir_poki_base(dresseur * ptdresseur, pokimac * pokis[]){
    int choix;
    pokimac * ptpokibase;
    ligne_vague();
    cout << "+-----------------------------------+" <<endl;
    cout << "| ";
    ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTCYAN);
    cout << "Choisissez votre pokimac de base.";
    ConsoleUtils::resetColors();
    cout << " |"<<endl;
    cout << "+-----------------------------------+" <<endl;
    competence_poki_base(pokis);
    do {
        cout << "Entrez 1 pour " << pokis[0]->nom << ", 2 pour " << pokis[1]->nom << " et 3 pour " << pokis[2]->nom << endl;
        cin >> choix;
        verifier_entree_int_joueur(&choix); //verifie si le joueur entre bien un entier
    }while (choix < 1 || choix > 3);
    //on retourne dans le tableau des pokimacs, le pokimac choisi
    ptpokibase = recherche_pokimac_base(pokis, choix);
    //on ajoute le pokimac dans l'equipe
    ajouter_Pokimac_Equipe(ptdresseur, ptpokibase, choix-1);
    ligne_vague();
}
void competence_poki_base(pokimac * pokis[]){
// affichage des compétences des pokimacs de base
    cout << "Competences des 3 pokimacs de base:" <<endl<<endl;
    ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTWHITE);
    cout << pokis[0]->nom <<" :     " << pokis[1]->nom <<" :       " << pokis[2]->nom <<" : "<<endl;
    cout << "attaque = " << pokis[0]->attaque << "   attaque = " << pokis[1]->attaque <<"        attaque = " << pokis[2]->attaque <<endl;
    cout << "vie = " << pokis[0]->vie_de_base << "       vie = " << pokis[1]->vie_de_base <<"            vie = " << pokis[2]->vie_de_base <<endl<<endl;
    ConsoleUtils::resetColors();
};
//fonction d'ajout du pokimac dans l'equipe du dresseur
void ajouter_Pokimac_Equipe(dresseur * ptlejoueur, pokimac * ptpokichoisi, int indice_poki){
    //On regarde si l'equipe est pleine
    if (ptlejoueur->nb_equipier >= MAX_EQUIPIERS){
        cout << "l'equipe de pokimac est complete" << endl;
    }
    else{
        ptpokichoisi->est_dans_equipe=true;
        cout << ptpokichoisi->nom << " a rejoint votre equipe !" << endl;
        //on met l'index du pokemon choisi dans l'equipe
        ptlejoueur->equipe[ptlejoueur->nb_equipier]=indice_poki;
        ptlejoueur->nb_equipier++;
    }
}

//fonction qui récupère le sexe du joueur
void choisirSexeDresseur(dresseur * ptle_dresseur){
    string choixSexe;
    do{
        cout << "Entrez le sexe de votre dresseur.se : ";
        ConsoleUtils::setColor(ConsoleUtils::Color::YELLOW);
        cout << "F";
        ConsoleUtils::resetColors();
        cout << ",";
        ConsoleUtils::setColor(ConsoleUtils::Color::GREEN);
        cout << " H ";
        ConsoleUtils::resetColors();
        cout << "ou";
        ConsoleUtils::setColor(ConsoleUtils::Color::MAGENTA);
        cout << " A";
        ConsoleUtils::resetColors();
        cout << " (Femme, Homme, Autre): ";
        cin >> choixSexe;
        cout << endl;
        //On regarde si l'entrée du joueur est f
        if (choixSexe == "F" || choixSexe == "f"){
            ptle_dresseur->sexe="femme";
            cout << "Votre dresseuse est une ";
            ConsoleUtils::setColor(ConsoleUtils::Color::YELLOW);
            cout << ptle_dresseur->sexe ;
            ConsoleUtils::resetColors();
            cout << ". " <<endl<<endl;
        }
        //On regarde si l'entrée du joueur est h
        else if(choixSexe == "H" || choixSexe == "h"){
            ptle_dresseur->sexe="homme";
            cout << "Votre dresseur est un " ;
            ConsoleUtils::setColor(ConsoleUtils::Color::GREEN);
            cout << ptle_dresseur->sexe ;
            ConsoleUtils::resetColors();
            cout << ". " <<endl<<endl;
        }
        //On regarde si l'entrée du joueur est a
        else if(choixSexe == "A" || choixSexe == "a"){
            ptle_dresseur->sexe="autre";
            cout << "Votre dresseur.se est de sexe ";
            ConsoleUtils::setColor(ConsoleUtils::Color::MAGENTA);
            cout << ptle_dresseur->sexe ;
            ConsoleUtils::resetColors();
            cout << ". " <<endl<<endl;
        }
        else{
            choixSexe="erreur";
            system("cls");
            cout << "Erreur: Veuillez taper uniquement F, H ou A." <<endl;
        }
    }
    while (choixSexe=="erreur");
}

//fonction qui retourne si il y a des pokiballs dans le sac du dresseur ou non
bool peut_capturer_poki(dresseur * ptdress){
    if (ptdress->sac[C_POKIBALLS]==0){
        cout << "Vous n'avez plus de pokiballs !" << endl;
        return false;
    }
    return true;
}

//fonction qui retourne si le dresseur a capture le pokimac ou non
bool capturer_poki(pokimac * ptpoki, dresseur * ptdress){
    float capture=.0;

    ptdress->sac[C_POKIBALLS]--; //On décrémente le nombre de pokiball du sac du joueur
    capture= (float) rand()/RAND_MAX; //random entre 0 et 1
    //cout << "capture : " << capture << endl;
    if (ptpoki->vie_actuelle == ptpoki->vie_de_base){ //Si le pokimac a la totalité de ses PV
        if (capture<0.125){ //Il a 1/8 chance d'être capturé
            return true;
        }
        return false;
    }
    if (ptpoki->vie_actuelle > ptpoki->vie_de_base/4){ //Si le pokimac a plus d'1/4 de ses PVS
        if (ptpoki->vie_actuelle > ptpoki->vie_de_base/2){ //Si le pokimac a plus d'1/2 de ses PVS
            if (capture>0.25){ //il a 1/4 chance d'être capturé
                return false;
            }
        }
        else if (ptpoki->vie_actuelle == ptpoki->vie_de_base/2){ //Si le pokimac a la moitié de ses PVS
            if (capture<0.5){ //il a 1/2 chance d'être capturé
                return false;
            }
        }else{
            if (capture<0.25){ //il a 3/4 chance d'être capturé
                return false;
            }
        }
    }
    return true;
}

void afficher_sac(dresseur * pt_dresseur){
    ConsoleUtils::setColor(ConsoleUtils::Color::GREEN);
    cout << "CONTENU DU SAC" <<endl<<endl;
    ConsoleUtils::resetColors();
    ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTWHITE);
    cout << "pokiballs :" << pt_dresseur->sac[C_POKIBALLS]<<endl;
    cout << "potions :"  << pt_dresseur->sac[C_POTIONS]<<endl;

    cout << "retour au jeu: b" <<endl;
    ConsoleUtils::resetColors();
    char cara = ConsoleUtils::getChar();
    while(cara!=T_SAC && cara!=T_SAC_MAJ){
        cout << "Entrez b pour sortir" <<endl;
    }
    ConsoleUtils::resetColors();
}
