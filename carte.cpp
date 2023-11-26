#include "carte.h"

using namespace std;


Position basMap;


//fonction d'initialisation d'une case
void initCase(Case *unecase, int type, int index){
    unecase->type = type;
    unecase->index = index;
}

//fonction qui permet l'affichage des cases
char charFromCase(const Case *c){
    switch (c->type)
    {
    case C_CMURS: // CASE MURS
        switch (c->index)
        {

        case 0:
            return '+' ; // coins
            break;
        case 1:
            return '|'; // verticaux
            break;
        case 2:
            return '-'; // horizontaux
            break;
        default:
            return '?'; // problème d'affichage
            break;
        }
        break;
    case C_CVIDE: // CASE VIDE
            return ' ';
        break;
    case C_CCAILLOUX: // CASE CAILLOUX
        return 'X';
        break;
    case C_CRESSOURCES: // CASE RESSOURCES
        switch (c->index)
        {
        case C_POKIBALLS: // CASE POKIBALLS
            return 'O'; //pokiballs
            break;
        case C_POTIONS:
            return 'O'; //potions
            break;
        default:
            return '?';
            break;
        }
        break;
    case C_CPOKI: // CASE POKIMAC
        return 'P';
        break;
    default:
        return '!';
        break;
    }
}

//fonction qui remplie la carte
void remplirLaCarte(Case tab[largeur][hauteur], T_jeu * jeu){
    for(int i = 0; i<hauteur ; i++){
        for(int j=0; j<largeur; j++){
            if ((i == 0 && j == 0) || (i == hauteur-1 && j == largeur-1) || (i == hauteur-1 && j == 0) || (i == 0 && j == largeur-1)){
                tab[j][i].type=0;
                tab[j][i].index=0;
                //les coins
            }
            else if (i == 0 || i == hauteur-1){
                tab[j][i].type=0;
                tab[j][i].index=2;
                //lignes verticales
            }
            else if (j == 0 || j == largeur-1){
                tab[j][i].type=0;
                tab[j][i].index=1;
                //lignes horizontales
            }
            else{
                tab[j][i].type=C_CVIDE;
                tab[j][i].index=0;
                //les zones vides
            }
        }
    }
    placer_pokimac(tab, MAX_POKI, jeu->tout_poki);
    placer_ressources(tab, MAX_RESS);
    placer_cailloux(tab, MAX_CAILLOUX);
}

//fonction qui place les pokimacs sur la carte
void placer_pokimac(Case tabtab[largeur][hauteur], int maxpoki, pokimac * tabpoki[]){
    int rand_x, rand_y;
    int rand_x_legend;
    //On parcourt jusqu'au nombre max de pokimacs
    for (int i=0; i<maxpoki; i++){
        //Si le pokimac ne fait pas partie de l'équipe
        if (tabpoki[i]->est_dans_equipe == false && i!=(maxpoki-1)){
            do{
                //on cherche une position x et y aléatoirement
                rand_x= rand() % largeur + 1;
                rand_y= rand() % hauteur + 1;
            //on repète tant que la case à la position x et y n'est pas vide
            }while (tabtab[rand_x][rand_y].type!=C_CVIDE || (rand_x==1 && rand_y==10));
            //on change le type de la case pour le type pokimac
            tabtab[rand_x][rand_y].type=C_CPOKI;
            //on change l'index de la case pour l'index du pokimac
            tabtab[rand_x][rand_y].index=i;

        }else if(tabpoki[i]->est_dans_equipe == false && i==(maxpoki-1)){
            //si "i" est égal à maxpoki donc au pokimac légendaire
            do{
                //on cherche une position x et y aléatoirement
                rand_x_legend= rand() % largeur + 1;
                rand_y= rand() % hauteur + 1;

                //On fait en sorte que le pokimac ne s'initialise pas dans la première moitié de la carte.
                if(rand_x_legend<19){
                    rand_x_legend=rand_x_legend+20;
                }else if(rand_x_legend<9){
                    rand_x_legend=rand_x_legend+25;
                }

            //on repète tant que la case à la position x et y n'est pas vide
            }while (tabtab[rand_x_legend][rand_y].type!=C_CVIDE);
            //on change le type de la case pour le type pokimac
            tabtab[rand_x_legend][rand_y].type=C_CPOKI;
            //on change l'index de la case pour l'index du pokimac
            tabtab[rand_x_legend][rand_y].index=i;
        }
    }

}

//fonction qui place les ressources sur la carte
void placer_ressources(Case tabtab[largeur][hauteur], int maxress)
{
    int rand_x, rand_y, ress_index;
    float rand_index;
    //on parcourt du nombre max de ressources à 0
    for (int i=maxress; i>0; i--){
        do{
            //on cherche une position x et y aléatoirement
            rand_x= rand() % largeur + 1;
            rand_y= rand() % hauteur + 1;
        //on repète tant que la case à la position x et y n'est pas vide
        }while (tabtab[rand_x][rand_y].type!=C_CVIDE || (rand_x==1 && rand_y==10));
        //on change le type de la case pour le type ressource
        tabtab[rand_x][rand_y].type=C_CRESSOURCES;

        //on cherche un flottant aléatoire entre 0 et 1;
        rand_index = (float) rand()/RAND_MAX;
        if (rand_index < 0.5){
            ress_index = C_POKIBALLS;
        }
        else{
            ress_index = C_POTIONS;
        }
        //on change l'index de la case pour l'index de la ressource
        tabtab[rand_x][rand_y].index=ress_index;
    }

}

//fonction qui place les cailloux sur la carte
void placer_cailloux(Case tabtab[largeur][hauteur], int maxcaillou)
{
    int rand_x, rand_y;
    for (int i=0; i<maxcaillou; i++){
        do{
            rand_x= rand() % largeur + 1;
            rand_y= rand() % hauteur + 1;
        //on change le type de la case pour le type caillou
        }while ((tabtab[rand_x][rand_y].type!=C_CVIDE) || (rand_x==1 && rand_y==10) || (rand_x==1 && rand_y==9)|| (rand_x==2 && rand_y==10));


        tabtab[rand_x][rand_y].type=C_CCAILLOUX;
        //on change l'index de la case pour l'index du caillou
        tabtab[rand_x][rand_y].index=i;
    }

}

void afficheLaCarte(Case tab[largeur][hauteur])
{
    //On parcourt les deux dimensions de notre tableau
    for (unsigned int i=0; i<hauteur; i++)
    {
        for (unsigned int j=0; j<largeur; j++)
        {
            // Si le type de la case est un mur alors on l'affiche avec une couleur bleu claire
            if( ((tab[j][i].type==C_CMURS) && (tab[j][i].index==0)) ||  ((tab[j][i].type==C_CMURS) && (tab[j][i].index==1)) || ((tab[j][i].type==C_CMURS) && (tab[j][i].index==2)) )
            {
                ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTBLUE);
                cout << charFromCase(&(tab[j][i]));
                ConsoleUtils::resetColors();
            }
            // Si le type de la case est un caillou alors on l'affiche avec une couleur grise
            else if(tab[j][i].type==C_CCAILLOUX)
            {
                ConsoleUtils::setColor(ConsoleUtils::Color::GREY);
                //ConsoleUtils::setBackgroundColor(ConsoleUtils::BackgroundColor::BG_BLUE);
                cout << charFromCase(&(tab[j][i]));
                ConsoleUtils::resetColors();
            }
            // Si le type de la case est un pokimac alors on l'affiche avec une couleur rouge
            else if(tab[j][i].type==C_CPOKI)
            {
                ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTRED);
                cout << charFromCase(&(tab[j][i]));
                ConsoleUtils::resetColors();
            }
            // Si le type de la case est un mur alors on l'affiche avec une couleur blanche lumineuse
            else if(tab[j][i].type==C_CRESSOURCES)
            {
                ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTWHITE);
                cout << charFromCase(&(tab[j][i]));
                ConsoleUtils::resetColors();
            }
            else
            {
                //Sinon on affiche la case sans couleur particulière
                cout << charFromCase(&(tab[j][i]));


            }

        }
        cout << endl;
    }
    cout <<endl;

    // On affiche les commandes que le joueur peut faire pendant sa partie
    cout << T_HAUT << " : haut" <<endl << T_BAS << " : bas"<< endl <<
    T_DROITE << " : droite" << endl << T_GAUCHE << " : gauche" << endl <<
    T_MENU << " : Menu" << endl << T_SAC << " : sac" << endl;
}

//fonction qui deplace les pokimacs
void deplacer_pokimac(T_ptjeu jeu, Case carte[largeur][hauteur]){
    Position pospoki;
    int nb_case_vide=0;
    Case * ptcasepoki;
    Position tabcaselibre[4];   //Tableau de positions des cases libres adjacentes
    Position posadj;
    int sauv_indexpoki=0;
    int pos_case_rand=0;
    Evol_pos tab_evol_pos[MAX_POKI-1]; //Tableau de l'evolution des positions des pokimacs
    int index_tab_evol_pos=0;

    //On parcourt le tableau
    for (int i=1; i<largeur-1; i++){
        for (int j=1; j<hauteur-1; j++){
            pospoki.x=i;
            pospoki.y=j;
            ptcasepoki=rend_case(carte, &pospoki);
            //on regarde si la case est un pokimac
            if (rend_type_case(ptcasepoki)==C_CPOKI){
                nb_case_vide=0; //compteur du nb de case adjacente vide

                posadj.x = pospoki.x-1;
                posadj.y = pospoki.y;
                //on teste si la case du dessus est vide
                tester_case_vide(&nb_case_vide, &posadj, tabcaselibre, carte);


                posadj.x = pospoki.x+1;
                posadj.y = pospoki.y;
                //on teste si la case du dessous est vide
                tester_case_vide(&nb_case_vide, &posadj, tabcaselibre, carte);

                posadj.x = pospoki.x;
                posadj.y = pospoki.y-1;
                //on teste si la case du gauche est vide
                tester_case_vide(&nb_case_vide, &posadj, tabcaselibre, carte);

                posadj.x = pospoki.x;
                posadj.y = pospoki.y+1;
                //on teste si la case du droite est vide
                tester_case_vide(&nb_case_vide, &posadj, tabcaselibre, carte);

                //si il y a au moins une case adj de vide
                if (nb_case_vide!=0){
                    //on cherche un nombre aleatoire entre 0 et le nb de case vide
                    pos_case_rand = rand() % nb_case_vide;
                    //on stocke l'ancienne position du pokimac dans le tableau tab_evol_pos
                    tab_evol_pos[index_tab_evol_pos].anc_pos.x=pospoki.x;
                    tab_evol_pos[index_tab_evol_pos].anc_pos.y=pospoki.y;

                    //on stocke la nouvelle position du pokimac, issue du random, dans le tableau tab_evol_pos
                    tab_evol_pos[index_tab_evol_pos].nouv_pos.x=tabcaselibre[pos_case_rand].x;
                    tab_evol_pos[index_tab_evol_pos].nouv_pos.y=tabcaselibre[pos_case_rand].y;
                    ptcasepoki = rend_case(carte, &(tab_evol_pos[index_tab_evol_pos].nouv_pos));
                    ptcasepoki->type=C_CCAILLOUX; //on reserve la case
                    index_tab_evol_pos++; //on incrémente l'index du tableau d'evol_pos
                }
            }
        }
    }
    //on parcourt jusqu'au nombre max d'index du tab_evol_pos
    for (int i=0; i<index_tab_evol_pos; i++){
        //on récupère l'ancienne case du pokimac
        ptcasepoki=rend_case(carte, &tab_evol_pos[i].anc_pos);
        //on sauvegarde son index
        sauv_indexpoki = ptcasepoki->index;
        //on réinitialise la case à une case vide
        ptcasepoki->type = C_CVIDE;
        ptcasepoki->index = 0;
        //on récupère la nouvelle case du pokimac
        ptcasepoki = rend_case(carte, &tab_evol_pos[i].nouv_pos);
        //on initialise le type de la case avec le type pokimac
        ptcasepoki->type=C_CPOKI;
        //on initialise l'index de la case avec la sauvegarde de l'index du pokimac
        ptcasepoki->index= sauv_indexpoki;
        //Si la position de la nouvelle case correspond à la position du joueur
        if (tab_evol_pos[i].nouv_pos.x == jeu->pt_lejoueur->pos.x && tab_evol_pos[i].nouv_pos.y == jeu->pt_lejoueur->pos.y){
            //cout << "Un poki sauvage vous agresse" <<endl;
            sleep(1000);
            //on lance la rencontre avec le pokimac
            rencontre_pokimac(jeu, ptcasepoki, carte);
        }
    }
}

//fontion qui teste si la case est vide
void tester_case_vide(int * nbcasevide, Position * ptposadj, Position tabcaselibre[4], Case carte[largeur][hauteur]){
    Case * ptcaseadj = rend_case(carte, ptposadj);
    //Si la case est vide
    if (rend_type_case(ptcaseadj)== C_CVIDE){
        //on met la position de la case dans le tableau de case libre
        tabcaselibre[*nbcasevide].x = ptposadj->x;
        tabcaselibre[*nbcasevide].y = ptposadj->y;
        (*nbcasevide)++;
    }
}

//fonction qui deplace le joueur d'une case en haut
void deplacer_haut(T_ptjeu jeu, Position Nouvpos, Case carte[largeur][hauteur]){
    if(jeu->pt_lejoueur->pos.y>1){
        Nouvpos.y = jeu->pt_lejoueur->pos.y;
        Nouvpos.y--;
        Nouvpos.x =jeu->pt_lejoueur->pos.x;
        deplacer_dresseur(&Nouvpos, jeu, carte);
        //Quand le dresseur se déplace les pokimacs aussi
        deplacer_pokimac(jeu, carte);
        //On vide l'affichage de la console et on réaffiche la carte à chaque fois que le joueur rentre une touche pour se déplacer
        ConsoleUtils::clear();
        afficheLaCarte(carte);
    }
}
//fonction qui deplace le joueur d'une case en bas
void deplacer_bas(T_ptjeu jeu, Position Nouvpos, Case carte[largeur][hauteur]){
    if(jeu->pt_lejoueur->pos.y<10){
        Nouvpos.y = jeu->pt_lejoueur->pos.y;
        Nouvpos.y++;
        Nouvpos.x =jeu->pt_lejoueur->pos.x;
        deplacer_dresseur(&Nouvpos, jeu, carte);
        deplacer_pokimac(jeu, carte);

        ConsoleUtils::clear();
        afficheLaCarte(carte);
    }
}
//fonction qui deplace le joueur d'une case à gauche
void deplacer_gauche(T_ptjeu jeu, Position Nouvpos, Case carte[largeur][hauteur]){
    if(jeu->pt_lejoueur->pos.x>1){
        Nouvpos.x =jeu->pt_lejoueur->pos.x;
        Nouvpos.x--;
        Nouvpos.y = jeu->pt_lejoueur->pos.y;
        deplacer_dresseur(&Nouvpos, jeu, carte);
        deplacer_pokimac(jeu, carte);

        ConsoleUtils::clear();
        afficheLaCarte(carte);
    }
}
//fonction qui deplace le joueur d'une case à droite
void deplacer_droite(T_ptjeu jeu, Position Nouvpos, Case carte[largeur][hauteur]){
    if(jeu->pt_lejoueur->pos.x<38){
        Nouvpos.x = jeu->pt_lejoueur->pos.x;
        Nouvpos.x++;
        Nouvpos.y = jeu->pt_lejoueur->pos.y;
        deplacer_dresseur(&Nouvpos, jeu, carte);
        deplacer_pokimac(jeu, carte);

        ConsoleUtils::clear();
        afficheLaCarte(carte);
    }
}


void actions_sur_carte(T_ptjeu jeu, Case tab[largeur][hauteur]){
    //On initialise la variable qui va compter le nombre de pokimacs battus et le nombre pokimacs capturés
    int pokis_capt_battu = 0;

    // Tant que le jeu ne prend pas fin le joueur pourra effectuer ces actions sur la carte
    while (jeu->Fin_jeu != true){
        //On vient chercher la touche saisie par le joueur
        char c = ConsoleUtils::getChar();

        //On initialise oldPos qui va garder en mémoire l'ancienne position du joueur (pour pouvoir effacer et remettre à vide la case)
        //On initialise NouvPos qui va nous permettre de regarder si le joueur peut se rendre sur une case
        Position oldPos;
        Position NouvPos;
        oldPos.x=jeu->pt_lejoueur->pos.x;
        oldPos.y=jeu->pt_lejoueur->pos.y;

        switch (c)
        {
        case T_HAUT:
        case T_HAUT_MAJ:
            //Quand le joueur saisit la touche z il va se déplacer d'une case vers le haut de la carte.
            deplacer_haut(jeu, NouvPos, tab);
            break;
        case T_BAS:
        case T_BAS_MAJ:
            //Quand le joueur saisit la touche s il va se déplacer d'une case vers le bas de la carte .
            deplacer_bas(jeu, NouvPos, tab);
            break;
        case T_GAUCHE:
        case T_GAUCHE_MAJ:
            //Quand le joueur saisit la touche g il va se déplacer d'une case vers la gauche de la carte .
            deplacer_gauche(jeu, NouvPos, tab);
            break;
        case T_DROITE:
        case T_DROITE_MAJ:
            //Quand le joueur saisit la touche d il va se déplacer d'une case vers la droite de la carte .
            deplacer_droite(jeu, NouvPos, tab);
            break;
        case T_MENU:
        case T_MENU_MAJ:
            //Quand le joueur saisit la touche m il affiche le menu après avoir vidé la console.
            ConsoleUtils::clear();
            MenuPendantPartie(jeu);
            //En sortant du menu on réaffiche la carte et le joueur
            ConsoleUtils::clear();
            afficheLaCarte(tab);
            afficher_joueur(jeu->pt_lejoueur);
            break;
        case T_SAC:
        case T_SAC_MAJ:
            // QUand le joueur saisit la touche b on entre dans son sac (bag), on voit son inventaire avec ses potions et ses pokiballs
            ConsoleUtils::clear();
            afficher_sac(jeu->pt_lejoueur);
            //En sortant du menu on réaffiche la carte et le joueur
            ConsoleUtils::clear();
            afficheLaCarte(tab);
            afficher_joueur(jeu->pt_lejoueur);
            break;
        default:
            break;
        }

            // On positionne le curseur sur l'ancienne position du joueur et on affiche l'ancien type de la case c'est à dire une case vide
            ConsoleUtils::setCursorPos(oldPos.x, oldPos.y);
            cout << charFromCase(&tab[oldPos.x][oldPos.y]);
            afficher_joueur(jeu->pt_lejoueur);


            //On place dans la variable pokis_capt_battu le nombre capture et le nombre de pokimacs battus
            pokis_capt_battu = jeu->compteur_de_capture + jeu->compteur_de_pokibattus;
            //Si le nombre de capture et le nombre de pokimacs battus est égal au nombre de pokimac (moins celui de base), on arrete le jeu
            if (pokis_capt_battu == (MAX_POKI-1)){
                jeu->Fin_jeu=true;
                cout << jeu->Fin_jeu <<endl;
            }


    }


}
void afficher_joueur(const dresseur * pt_lejoueur)
{
    //On affiche le joueur en jaune
    ConsoleUtils::setCursorPos(pt_lejoueur->pos.x, pt_lejoueur->pos.y);
    if(pt_lejoueur->sexe == "femme"){
        ConsoleUtils::setColor(ConsoleUtils::Color::YELLOW);
    }else if(pt_lejoueur->sexe == "homme"){
        ConsoleUtils::setColor(ConsoleUtils::Color::GREEN);
    }else{
        ConsoleUtils::setColor(ConsoleUtils::Color::MAGENTA);
    }
    cout << '&'; // apparence joueur
    ConsoleUtils::resetColors();
}


//fonction d'initialisation de la carte
void initCarte(T_ptjeu jeu)
{
    //On intitialise le tableau comme un tableau 2D de cases
    Case tab[largeur][hauteur];
    ConsoleUtils::clear();
    // On rempli les case du tableau
    remplirLaCarte(tab, jeu);
    //On affiche le tableau, le joueur et on active les actions que le joueur peut faire sur la carte
    afficheLaCarte(tab);
    afficher_joueur(jeu->pt_lejoueur);
    actions_sur_carte(jeu, tab);



}

//fonction de deplacement du dresseur
void deplacer_dresseur(Position * ptNpos, T_ptjeu jeu, Case ptcarte[largeur][hauteur]){
    //On récupère la case
    Case * ptcase=rend_case(ptcarte, ptNpos);
    if (ptcase!= NULL){
        //on récupère le type de la case
        ptcase->type= rend_type_case(ptcase);
        //Si la case différente du cailloux
        if (ptcase->type != C_CCAILLOUX){
            //on met la nouvelle position du dresseur dans le dresseur
            jeu->pt_lejoueur->pos.x = ptNpos->x;
            jeu->pt_lejoueur->pos.y = ptNpos->y;

            if (ptcase->type == C_CRESSOURCES){
                prendre_ressources(jeu, ptcase->index, ptcase->type);
                ptcase->type=C_CVIDE;
                ptcase->index=0;
                sleep(1000);
                ConsoleUtils::clear();
                afficheLaCarte(ptcarte);
            }
            if (ptcase->type == C_CPOKI){
                rencontre_pokimac(jeu, ptcase, ptcarte);
            }
        }

    }
}

//fonction qui retourne la case à la position donnée
Case * rend_case(Case ptcarte[largeur][hauteur], Position * ptpos){
    if (ptpos->x < 1){ //on regarde si la case est hors de portée
        return NULL;
    }
    if (ptpos->x > largeur-1){ //on regarde si la case est hors de portée
        return NULL;
    }
    if (ptpos->y < 1){
        return NULL;
    }
    if (ptpos->y > hauteur-1){ //on regarde si la case est hors de portée
        return NULL;
    }
    return &ptcarte[ptpos->x][ptpos->y];
}

//fonction qui retourne le type de la case
int rend_type_case(Case * ptcase){
    if(ptcase != NULL){
        return ptcase->type;
    }
    return 0;
}

//fonction qui prend les ressources
void prendre_ressources(T_ptjeu jeu, int index, int type){

    basMap.x=1;
    basMap.y=19;

    //Si l'index de la case est une pokiball
    if (index == C_POKIBALLS){
        ConsoleUtils::setCursorPos(basMap.x, basMap.y);
        cout << "Vous avez trouve une pokiball !" <<endl;
    }
    else{ //sinon c'est une potion
        ConsoleUtils::setCursorPos(basMap.x, basMap.y);
        cout << "Oh, Vous avez trouve une potion !" << endl;
    }
    //on incrémente l'index de la ressource dans le dresseur
    jeu->pt_lejoueur->sac[index]++;
}

//fonction qui provoque la rencontre avec le pokimac
void rencontre_pokimac(T_ptjeu jeu, Case * ptcase, Case ptcarte[largeur][hauteur])
{
    pokimac * ptpoki_envoye, * ptpoki_sauvage;
    int etat_courant = C_DEMANDE_CHOIX_ACTION; //initalisation d'un état pour le combat
    //cout << "POKI INDEX " << ptcase->index;
    ptpoki_sauvage = jeu->tout_poki[ptcase->index]; //on recupère le pokimac sauvage de la case
    basMap.x=1;
    basMap.y=20;
    ConsoleUtils::setCursorPos(basMap.x, basMap.y);
    cout << "Un pokimac sauvage apparait !" << endl;
    sleep(1000);
    ConsoleUtils::clear();

    //Annonce du pokimac rencontré
    cout << "C'est un " ;
    ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTRED);
    cout << ptpoki_sauvage->nom ;
    ConsoleUtils::resetColors();
    cout <<" !" << endl<<endl;

     afficher_ascii_combat(ptpoki_sauvage->asciiArt);
    // Si c'est le pokimac légendaire on l'annonce au joueur
    if(ptcase->index==8){
        ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTRED);
        cout << "Vous avez trouve le Pokimac Legendaire! Faites attention!" <<endl<<endl;
        ConsoleUtils::resetColors();
    }
    if(ptcase->index>=5 && ptcase->index<=7){
        ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTGREEN);
        cout << "Vous avez trouve un pokimac shiny!" <<endl<<endl;
        ConsoleUtils::resetColors();
    }
    ptpoki_envoye = chercher_poki_a_envoye(jeu);
    afficher_poki_envoye(ptpoki_envoye);
    afficher_fenetre_combat(ptpoki_envoye, ptpoki_sauvage);

    executer_combat(etat_courant, jeu, ptpoki_envoye, ptpoki_sauvage, ptcase);

    ConsoleUtils::clear();
    afficheLaCarte(ptcarte);
}

void afficher_fenetre_combat(pokimac * ptpoki_envoye, pokimac * ptpoki_sauvage)
{

    cout << ptpoki_envoye->nom << endl;
    ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTCYAN);
    cout << ptpoki_envoye->vie_actuelle;
    ConsoleUtils::resetColors();
    ConsoleUtils::setColor(ConsoleUtils::Color::CYAN);
    cout << "/" << ptpoki_envoye->vie_de_base << endl;
    ConsoleUtils::resetColors();
    ;
    cout << "Attaque = " ;
    ConsoleUtils::setColor(ConsoleUtils::Color::YELLOW);
    cout<< ptpoki_envoye->attaque << endl << endl;
    ConsoleUtils::resetColors();


    cout << ptpoki_sauvage->nom << endl;
    ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTCYAN);
    cout << ptpoki_sauvage->vie_actuelle;
    ConsoleUtils::resetColors();
    ConsoleUtils::setColor(ConsoleUtils::Color::CYAN);
    cout << "/" << ptpoki_sauvage->vie_de_base << endl;
    ConsoleUtils::resetColors();

    cout << "Attaque = " ;
    ConsoleUtils::setColor(ConsoleUtils::Color::RED);
    cout << ptpoki_sauvage->attaque << endl << endl;
    ConsoleUtils::resetColors();
}


//fonction qui execute les actions du combat
void executer_combat(int etat, T_ptjeu jeu, pokimac * ptpoki_envoye, pokimac * ptpoki_sauvage, Case * casepoki){
    bool fin_combat=false;
    int etat_suiv;
    int etat_precedant;
    while (fin_combat==false){

        //SI L'ETAT EST l'ATTAQUE DU DRESSEUR
        if (etat == C_ATTAQUE_DRESS){
            //on attaque le pokimac sauvage
            attaquer_poki(ptpoki_envoye, ptpoki_sauvage);
            //si le pokimac sauvage est mort
            if (poki_est_mort(ptpoki_sauvage)==true)
            {
                cout << "Vous avez gagne le combat !" << endl;
                sleep(1500);
                (jeu->compteur_de_pokibattus)++;
                fin_combat=true;
                casepoki->type=C_CVIDE;
                casepoki->index=0;
            }
            else
            {
                afficher_fenetre_combat(ptpoki_envoye, ptpoki_sauvage);
                etat_suiv=C_CONTREATT_POKI; //sinon on change d'etat pour l'état suivant
            }
        }
        //SI L'ETAT EST CONTRE-ATTAQUE DU POKIMAC SAUVAGE
        if (etat == C_CONTREATT_POKI){
            //le pokimac sauvage contreattaque
            if (etat_precedant == C_SOIGNE_POKI){
                ConsoleUtils::clear();
                afficher_fenetre_combat(ptpoki_envoye, ptpoki_sauvage);
                sleep(1000);
                cout << "Votre adversaire vous attaque!" <<endl;
                sleep(1000);
                contreattaquer_poki(ptpoki_envoye, ptpoki_sauvage);
            }else{
                cout << "Votre adversaire vous attaque!" <<endl;
                sleep(2000);
                contreattaquer_poki(ptpoki_envoye, ptpoki_sauvage);
            }

            //si le pokimac du dresseur est mort
            if (poki_est_mort(ptpoki_envoye)==true){
                cout<<"Votre pokimac n'a plus de PV.."<< endl;
                pokimac * ptpokisuiv;
                //on cherche s'il a un autre pokimac
                sleep(1000);
                ptpokisuiv=chercher_poki_a_envoye(jeu);
                if(ptpokisuiv==NULL){ //s'il en a pas
                    cout << "Oh no vous n'avez plus de pokimac qui peuvent encore se battre..." << endl;
                    cout << "Vous avez perdu" << endl;
                    sleep(1000);
                    fin_combat=true;
                    jeu->Fin_jeu=true;


                }
                else{
                    //sinon on met le poki a envoye
                    afficher_poki_envoye(ptpokisuiv);
                    ptpoki_envoye=ptpokisuiv;
                }
            }
            afficher_fenetre_combat(ptpoki_envoye, ptpoki_sauvage);
            etat_suiv=C_DEMANDE_CHOIX_ACTION; //sinon on change d'état pour l'état suivant
        }
        //SI L'ETAT EST DEMANDE DU CHOIX D'ACTION DU JOUEUR
        if (etat == C_DEMANDE_CHOIX_ACTION)
        {
            int choix_action;

            do{
                afficher_choix_action();
                cin >> choix_action;
                choix_action = verifier_entree_int_joueur(&choix_action);
                //on verifie si l'entree du joueur correspond aux constantes données
                if (choix_action==C_ATTAQ){
                    etat_suiv=C_ATTAQUE_DRESS;
                }
                else if (choix_action==C_CAPT){
                    etat_suiv=C_CAPTURE_POKI;
                }
                else if (choix_action==C_CHANG){
                    etat_suiv=C_CHANGE_POKI;
                }
                else if (choix_action==C_SOIN){
                    etat_suiv=C_SOIGNE_POKI;
                }
                else if (choix_action==C_FUITE){
                    etat_suiv=C_FUIT;
                }else{
                    cout << "veuillez entrer 1, 2, 3, 4 ou 5." <<endl;

                }
            }while(choix_action < 1 || choix_action > C_MAX_CHOIX);
        }
        //SI L'ETAT EST CAPTURER LE POKEMON SAUVAGE
        if (etat == C_CAPTURE_POKI){
            //on verifie si le dresseur peut capturer le pokimac
            if (peut_capturer_poki(jeu->pt_lejoueur)==true){
                bool poki_est_capture;
                poki_est_capture=capturer_poki(ptpoki_sauvage, jeu->pt_lejoueur);
                if (poki_est_capture==true){ //si le pokimac a été capturé
                    cout << "Bravo ! Vous avez capture " << ptpoki_sauvage->nom << " !" << endl;
                    ptpoki_sauvage->est_dans_equipe=true; //on l'ajoute dans l'equipe


                    ajouter_Pokimac_Equipe(jeu->pt_lejoueur, ptpoki_sauvage, casepoki->index);
                    // on incrémente le compteur de capture pour les statistiques
                    (jeu->compteur_de_capture)++;
                    sleep(1500);
                    //on réinitialise la case a vide
                    casepoki->type=C_CVIDE;
                    casepoki->index=0;
                    fin_combat=true;
                }
                else{
                    cout << "Oh no, le pokimac s'est libere !" << endl;
                    sleep(1000);
                    etat_suiv=C_CONTREATT_POKI; //sinon on change d'état pour l'état suivant
                }
            }
            else{
                etat_suiv=C_DEMANDE_CHOIX_ACTION; //sinon on change d'état pour l'état suivant
            }
        }
        if (etat == C_CHANGE_POKI){
            pokimac * ptpokichang;
            ptpokichang=chercher_poki_a_envoye(jeu);
            if (ptpokichang==ptpoki_envoye){
                cout << ptpokichang->nom << " est deja au combat !" << endl;
                sleep(1000);
                ConsoleUtils::clear();
                etat_suiv=C_DEMANDE_CHOIX_ACTION;
            }else{
                afficher_poki_envoye(ptpokichang);
                ptpoki_envoye=ptpokichang;
                etat_suiv=C_CONTREATT_POKI;
            }
            afficher_fenetre_combat(ptpoki_envoye, ptpoki_sauvage);
        }
        //SI L'ETAT EST SOIGNER LE POKEMON ENVOYE
        if (etat == C_SOIGNE_POKI)
        {

            //on verifie si l'on peut soigner le pokimac
            if (poki_doit_soigner(ptpoki_envoye, jeu->pt_lejoueur)==true)
            {
                //on soigne le pokimac
                soigner_poki(ptpoki_envoye, jeu->pt_lejoueur);
                etat_suiv=C_CONTREATT_POKI; //on change d'état pour l'état suivant
            }
            else
            {
                etat_suiv=C_DEMANDE_CHOIX_ACTION; //sinon on change d'état pour l'état suivant
            }
        }
        //SI L'ETAT EST FUITE DU JOUEUR
        if (etat == C_FUIT)
        {
            bool a_fuit;
            a_fuit = a_fuit_combat();
            //On verifie si il a fuit ou non
            if (a_fuit==true){
                fin_combat=true;
                cout << "Vous prenez la fuite !" << endl;
                sleep(1000);
            }
            else{
                cout << "Vous n'avez pas reussi a prendre la fuite" << endl;
                sleep(1000);
                etat_suiv=C_CONTREATT_POKI; //sinon on change d'état pour l'état suivant
            }
        }
        etat_precedant = etat; // on garde en mémoire l'état précédant
        etat=etat_suiv; //l'état devient l'état suivant

    }
    afficher_fin_combat();

    sleep(2000);

}




