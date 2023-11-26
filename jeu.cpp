#include "jeu.h"

#include "carte.h"

#include <iostream>
#include <string>
using namespace std;

Position basAttaque;
//fonction qui vérifie si l'entree du joueur est bien un entier et retourne cet entier
int verifier_entree_int_joueur(int * choix){
    while(cin.fail()) {
            cout << "Veuillez entrer un entier propose dans les choix" <<endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> *choix;
    }
    return *choix;
}
// fonction pour lancer le jeu
void jouer(T_ptjeu jeu){


    initCarte(jeu);


    if(jeu->Fin_jeu==true){
        ConsoleUtils::clear();
        cout <<"Vous avez fini la partie."<<endl <<endl;
        sleep(1000);
        afficher_statistiques(jeu);

    }
    sleep(10000);

}
int stat_poki_en_vie(T_ptjeu jeu, int * score){
    /* nombre de pokimacs en vie dans l'équipe à la fin de la partie */
    int nb_poki_en_vie = 0;
    for(int i=0; i<(MAX_POKI); i++){
        if((jeu->tout_poki[i]->est_dans_equipe == true)&&(jeu->tout_poki[i]->vie_actuelle > 0)){
            nb_poki_en_vie++ ;
            // 1 point par pokimacs encore en vie dans l'équipe
            score++;
        }

    }
    return nb_poki_en_vie;
}
void stat_bonus(T_ptjeu jeu, int * score){
    //Points Bonus
    if((jeu->tout_poki[8]->est_dans_equipe == true)|| (jeu->compteur_de_capture==(MAX_POKI-1))){
        ConsoleUtils::setColor(ConsoleUtils::Color::YELLOW);
        cout << "POINTS BONUS" <<endl;
        ConsoleUtils::resetColors();
    }
    if(jeu->tout_poki[8]->est_dans_equipe == true){
        cout << "Bravo vous avez capture le pokimac Legendaire" <<endl;
        ConsoleUtils::setColor(ConsoleUtils::Color::YELLOW);
        cout << "+8 points" <<endl<<endl;
        ConsoleUtils::resetColors();
        // 10 points bonus si on capture le pokimac légendaire
        (*score)=(*score)+8;

    }
    if (jeu->compteur_de_capture==(MAX_POKI-1)){
        cout << "Wow ! Vous avez capture tout les pokimacs du jeu, Bravo!" <<endl;
        ConsoleUtils::setColor(ConsoleUtils::Color::YELLOW);
        cout << "+10 points" <<endl;
        ConsoleUtils::resetColors();
        // 10 points bonus si on capture tous les pokimacs
        (*score)=(*score)+10;

    }
    // 2 points bonus par pokimac shiny battu
        for(int i=5;i<=7;i++){
            if(jeu->tout_poki[i]->vie_actuelle<=0){
                 (*score)=(*score)+2;
                 ConsoleUtils::setColor(ConsoleUtils::Color::YELLOW);
                 cout << "+2 points (shiny battu)" <<endl;
                 ConsoleUtils::resetColors();
            }
        }
}
void stat_poki_battus(T_ptjeu jeu, int * score){
    /* nombre de pokimacs que vous avez battu. */
    if (jeu->compteur_de_pokibattus>0){
        cout << "Bravo, vous avez battu " << jeu->compteur_de_pokibattus << " pokimac(s)" << endl;

        // 2 points par pokimac battu
        (*score)=(*score)+((jeu->compteur_de_pokibattus)*2);
    }else{
    cout << "Vous n'avez pas battu de pokimacs pendant la partie." <<endl;
    }
}

void stat_poki_capture(T_ptjeu jeu, int * score){
    //nombre capturé
    if (jeu->compteur_de_capture>0){
    cout << "Bravo, vous avez capture " << jeu->compteur_de_capture << " pokimac(s)" << endl;
    // 2 points par pokimac capturé
        (*score)=(*score)+((jeu->compteur_de_capture)*3);

    }else{
    cout << "Vous n'avez pas capture de pokimacs pendant la partie." <<endl;
    }
}
void afficher_statistiques(T_ptjeu jeu){

    ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTMAGENTA);
    cout << "   STATISTIQUES    " << endl;
    ConsoleUtils::resetColors();

    int score=0;

    stat_poki_en_vie(jeu,&score);
    stat_poki_battus(jeu,&score);
    stat_poki_capture(jeu,&score);
    stat_bonus(jeu,&score);



    if (stat_poki_en_vie(jeu,&score)>0){
        cout << "Votre equipe se compose de "<<stat_poki_en_vie(jeu,&score) << " pokimac(s) encore en vie!"<< endl<<endl;
    }else{
        cout << "Vous n'avez plus de pokimac en vie, vous avez perdu la partie" <<endl;
        score=0;
    }

    /* récapitulatif:
    cout << endl<<"Pokimacs dans l'équipe : " << nb_poki_en_vie <<endl;
    */
    cout << endl<<endl;
    cout << "Votre score final est de " <<endl;
    cout << score <<endl;
    //ascii

}


//fonction qui retourne le pokimac a envoyé au combat
pokimac * chercher_poki_a_envoye(T_ptjeu jeu){
    pokimac * poki_envoye=NULL;     //on initialise le pokimac a envoyer
    int choix_poki=0;   //on initalise l'entier (entree du joueur)
    int morts=0; //on initalise l'entier (entree du joueur)

    //On parcourt les pokimacs de l'équipe
    for(int i=0; i<jeu->pt_lejoueur->nb_equipier ; i++){
        if(jeu->tout_poki[jeu->pt_lejoueur->equipe[i]]->vie_actuelle==0){
            morts++; //Si des pokimacs ont leur vie actuelle à 0 on incrémente morts
        }
    }
    //Si tous les equipiers sont morts on retourne NULL
    if (morts==jeu->pt_lejoueur->nb_equipier){
        return NULL;
    }
    //Si le joueur un qu'un seul pokimac et qu'il a sa vie actuelle > 0, on envoie le pokimac
    if ((jeu->pt_lejoueur->nb_equipier==1) && (jeu->tout_poki[jeu->pt_lejoueur->equipe[0]]->vie_actuelle>0)){
        poki_envoye= jeu->tout_poki[jeu->pt_lejoueur->equipe[0]];
    }else{
        //Sinon on parcourt toute l'équipe
        cout << "Quel pokimac voulez-vous envoyer au combat ?" <<endl;
        for (int i=0; i<jeu->pt_lejoueur->nb_equipier; i++){
            //Si le pokimac a sa vie actuelle > 0, on affiche le pokimac
            if (jeu->tout_poki[jeu->pt_lejoueur->equipe[i]]->vie_actuelle != 0){
                cout << i+1 << ": " << jeu->tout_poki[jeu->pt_lejoueur->equipe[i]]->nom << endl;
            }
        }
        do{
            cin >> choix_poki;
            choix_poki = verifier_entree_int_joueur(&choix_poki);

            //on regarde si le choix est superieur à 0, compris dans la tranche du nombre d'equipier et si la vie du pokimac choisi est supérieur à 0
            if (choix_poki > 0 && choix_poki<=(jeu->pt_lejoueur->nb_equipier) && jeu->tout_poki[jeu->pt_lejoueur->equipe[choix_poki-1]]->vie_actuelle != 0){
                poki_envoye=jeu->tout_poki[jeu->pt_lejoueur->equipe[choix_poki-1]];
            }else{
                cout << "Ce pokimac ne peut pas se battre. Choississez un autre pokimac." << endl;
            }
        //on demande au joueur d'entrer son choix tant qu'il est inférieur à 1 ou que le chiffre est supérieur au nombre d'équipier ou que la vie du pokimac demandé est égale à 0
        }while(choix_poki < 1 || choix_poki > (jeu->pt_lejoueur->nb_equipier) || jeu->tout_poki[jeu->pt_lejoueur->equipe[choix_poki-1]]->vie_actuelle == 0);

    }
    //On retourne le pokimac envoye
    return poki_envoye;
}

//fonction qui affiche le pokimac envoye
void afficher_poki_envoye(pokimac * poki){
    cout << "GO ";
    //on met la couleur du texte en Jaune
    ConsoleUtils::setColor(ConsoleUtils::Color::YELLOW);
    cout << poki->nom ;
    ConsoleUtils::resetColors();
    cout << " !" << endl <<endl;
    sleep(2000);
    ConsoleUtils::clear();
}

//fonction qui attaque le pokimac sauvage
void attaquer_poki(pokimac * ptpoki_dress, pokimac * ptpoki_sauv){

    //Si l'attaque du pokimac du dresseur est sup à la vie actuelle du pokimac sauvage
    if (ptpoki_dress->attaque>ptpoki_sauv->vie_actuelle){
        ptpoki_sauv->vie_actuelle=0; //la vie actuelle du poki sauvage = 0;
    }else{
        //sinon on fait la difference entre la vie actuelle et l'attaque;
        ptpoki_sauv->vie_actuelle=ptpoki_sauv->vie_actuelle-ptpoki_dress->attaque;
    }
}

//fonction qui attaque le pokimac du dresseur
void contreattaquer_poki(pokimac * ptpoki_dress, pokimac * ptpoki_sauv){

    ConsoleUtils::clear();

    if (ptpoki_sauv->attaque > ptpoki_dress->vie_actuelle){
        ptpoki_dress->vie_actuelle=0;
    }else{
        ptpoki_dress->vie_actuelle=ptpoki_dress->vie_actuelle-ptpoki_sauv->attaque;
    }
}


//fonction qui affiche les choix d'actions du joueur
void afficher_choix_action(){
    cout << "Que voulez vous faire ?" << endl;
    cout << C_ATTAQ << " : Attaquer" << endl;
    cout << C_CAPT << " : Capturer" << endl;
    cout << C_CHANG << " : Changer de Pokimac" << endl;
    cout << C_SOIN << " : Soigner" << endl;
    cout << C_FUITE << " : Fuire" << endl;


}
void afficher_ascii_combat(string asciiArt){

    ConsoleUtils::setColor(ConsoleUtils::Color::RED);
    cout <<"Votre adversaire :"<<endl;
    ConsoleUtils::resetColors();
    cout << asciiArt<<endl;

}
//fonction qui retourne si le dresseur fuit ou non
bool a_fuit_combat(){
    float fuite;
    fuite=(float) rand()/RAND_MAX;
    if (fuite<0.5){
        return false;
    }
    return true;
}

//fonction qui affiche la fin du combat
void afficher_fin_combat(){
    cout << "combat termine !" << endl;
}



