#include "pokimac.h"
#include "dresseur.h"

using namespace std;

/*fonction d'initialisation du pokimac */
void initPokimac(pokimac *poki, string nom, string asciiArt, int vie_de_base, int attaque){

    poki->nom = nom;
    poki->asciiArt = asciiArt;
    poki->vie_de_base = vie_de_base;
    poki->vie_actuelle = vie_de_base;
    poki->attaque = attaque;
    poki->est_dans_equipe = false;

 }

//fonction qui retourne le pokimac choisi dans le tableau de tous les pokimacs
pokimac * recherche_pokimac_base(pokimac * tabpokis[], int choixpoki){
    return tabpokis[choixpoki-1];
}

//fonction qui retourne si le pokimac à sa vie actuelle à 0 ou non
bool poki_est_mort(pokimac * ptpoki){
    if (ptpoki->vie_actuelle==0){
        return true;
    }
    return false;
}

//fonction qui retourne si un pokimac peut être soigné ou non
bool poki_doit_soigner(pokimac * ptpokimac, dresseur * ptdress){
    //on compare la vie actuelle et la vie de base du pokimac
    if (ptpokimac->vie_actuelle==ptpokimac->vie_de_base){
        cout << ptpokimac->nom << " a deja tous ses PV !" << endl;
        sleep(1000);
        return false;
    }
    //on regarde si le joueur a encore des potions
    if (ptdress->sac[C_POTIONS]==0){
        cout << "Vous n'avez plus de potions pour soigner " << ptpokimac->nom << " !" << endl;
        sleep(1000);
        return false;
    }
    return true;
}

//fonction qui soigne le pokimac
void soigner_poki(pokimac * ptpokimac, dresseur * ptdress){
    //On regarder si la vie actuelle du pokimac + la potion dépasse la vie de base
    if (ptpokimac->vie_actuelle+C_GAIN_PV > ptpokimac->vie_de_base){
        ptpokimac->vie_actuelle =ptpokimac->vie_de_base;
        cout << ptpokimac->nom << " a regagne tous ses PV !" << endl;
        sleep(1000);
    }else{
        ptpokimac->vie_actuelle = ptpokimac->vie_actuelle+C_GAIN_PV;
        cout << ptpokimac->nom << " a regagne "<< C_GAIN_PV << " !" << endl;
        sleep(1000);
    }
    //on décrémente le nombre de potions dans le sac
    ptdress->sac[C_POTIONS]--;
}


