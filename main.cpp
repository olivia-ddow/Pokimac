#include "carte.h"
#include "jeu.h"
#include "dresseur.h"
#include "pokimac.h"
#include "consoleUtils.hpp"
#include "menu.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <string>
using namespace std;

int main()
{

srand (time(NULL));

//affichage du titre du jeu
afficheTitre();

//Creation des objets + variable du jeu
T_jeu * jeu = new T_jeu;
jeu->pt_lejoueur = new dresseur;
jeu->compteur_de_pokibattus = 0;
jeu->compteur_de_capture= 0;
jeu->Fin_jeu = false;

// initialisation du dresseur
initDresseur(jeu->pt_lejoueur);

// creation des objets pokimacs
for (int i=0; i<MAX_POKI; i++){
    jeu->tout_poki[i]=new pokimac;
}
//initialisation des Pokimacs

/*Pokimac de base*/
initPokimac(jeu->tout_poki[0], "Salasmet",R"(                                ``
                             ...``....`
                           `-`       ``-`
                          `-.. `        ..
                          :-d+--       -:s
                         -.o(O)        (O)
                         :./+++        -ds`
        `.               : ..``        `..-
       --/               : -+-..` . ```-.-:
       : ./.`            `- .-. `...--/:-.
      -/-  /`            .:  .--..../:..
     :` :  /-    ```.....     `-::-.`...`
    `+` .-:.--  .-``         -.   `-:   `..-.
     --     .-  -..-       `-       :-     .-`
     .:-: ..-      ...:..`..         /.....-
      `.-+:`         -`  `-          :
         o`-.       -`   :           :
         -:``.```  -.    :          .-..
          -:. ```.:`     `-        `-  `-
           .--.``..       :      `..    ..
             `.--+       .- ```.-.`     ..
                 :`    `--.``````:`    .:-`
                -/.`` `-`        ``...--://`
               `./-/:..                `.``       )", 50, 30);
initPokimac(jeu->tout_poki[1], "Cherriapuce",R"(
           `........`
        `.-.        `--.
       -.              `-.
      /-          :/.    :`
     -/m         /.NN:    /
     /NM.        NNMyo    /:.
     /oo         +o//:.`  /./-.`
     :-.``  `     ```/.:.:o / `--
  /-:-:::/-.--..----/`  ``-..:-.-:`
  :`-   ``-+-------:::     `:./.``/
  .-`      /``       :-      / /  `-
    `-``   /`..-/----.:-`` `.+ /   /
      `.-.+-    /      `.+:-/. /   /    `````
          ::-   :`     `:`  /  /   +  .-.```.-.
          `:.:.``/`````:`   .: :. -s`-`       .-
           `:/``..+.....-. ``-/ :-+o-    `..`  .-
            .:-`  `:`    .:...::`/+-    :-`./` `:
           --  `--``/-```/      +/`     +   .  /
           /     `-:o---/-      +`      /-` `--`
           .-      `:...-:      +........:-..
            /.     `/    :      /
            .:......     /.` .--/
                           .-`                    )" , 90, 10);
initPokimac(jeu->tout_poki[2], "Robillzard", R"(

                        `..-------......../-`
                       `--`    `..----::::-`.+:
                       :`    `--`            //
                      :`    `:`              :-.
         .-.` ```.---./     :`               / -.
       `:--::-/.`    `+- .  /                /  :`
     `-+:/.            /-:-`/                :`  /
    .---`               `.-.:::.`            /   /
   :.      `.              -...`..-.`       --   /
  :`--: --:.+:             -:`     -o/-   --.   `:
  / --  /(O):./              .-.---`--`-/-    -`/
  /     ----:-`                         `:..-:--
 `:                              ..-.     ::--`
 /.-............`  -:`      `  --....`     /
 ``--..````````   -+......  :`:`:.` `/     /
     ``.../:/:`  .:``:.`.:  //  .-``--     /
          +/`.-.-:   ```` `:`+    ``       /
         `+.`  `+       `--` -.``        `:`
         -+//-://:.````---...-:+/::-`..--.`
           `  ``.:--...        ``...```           )", 70, 20);
initPokimac(jeu->tout_poki[3], "DLcarpe",R"(
                `.     :+`.+
                /++` `+-  .o
                :/`o:+`   .+
                `o  /`    -o---/`
               `:s.       ..``/+
          .----+-`:+---.`   -+.
      `-/:.``      /-.-o:::+.
     :/.`  ----.    o-+:  .:/-
   .o-   `+.`.`/:   +  /-   `:o`
  -+//:  /-       )  /-.+`     ++:      `-:/+++s/
   .s+/. `+- (O)   -/ssos++++++s+s:  .:++++-..:/
    +y.+`/:      :os+/::::::/+//:`o:///:.`  ` s`
   .sh.o :o// ./ss+:-....-+:` /` .o+/--:----++
   sho+:  `/+/`.yo/:.`  :/`   +   s-.`    `/:
   sso/-.`  +o  `-:+:. `o    --  /+      :/.
   yo -/:::.+:.   -:-o:-+   .:`-:s+.    -+
   /s/  -:o/s-/--:-`--`-:``:o/://o`/-   +.
    /y:    .s:s:////--//:---`   s// -/. o.
     :h-    /:o        :/`      .oo- `-+o
      +y.  `so:- ``     `+.      .oo.`:/`
       ys  `/-+++/+-  /:-`//      `+ss`
       oy`    .oo- -++- `-:/        .:
       so      `/o+-`.
      ./         ./o+/-`
                    ::/o:                         )", 50, 10);
initPokimac(jeu->tout_poki[4], "Novetali",R"(
       -.:
      :` :
     :.``:                 ``...
    :-```:            `....```:`
   `/..../          .-:-.    -`
   :``   :        `-:.` .- `-`                 `.`
   /    :`       -.  `-` .:.                `.-./
   :   --````` `-`     /..`               `-.` -.
   / `--.````.:-    ``-.`               `:.`   :
  `/-:/.-    ..``....`                `--.`.-`-`
 `:--::`-     `../                   `-.`.-  ::
 : ::-.: ``.-    -`                 `:    `:`:
 / ....`-(O) :     :                `:      :-
 .-    :`__--     :`              `:     --`
  /    ....        /-.       ``   :   `--
  -/.``-...`          .......``.-:.`.-`
     `..`.-                       `:.
          :                         `-`
          /    `                      :`
          :  ` -       `           ..` :
          `- `./   ..`:......`    -`:--/
           -` `- `---+.`:` ``.:`  ..-:-+-
            : :``:-/:/   ..   :..``..-/./.
            `:- -`+:.     :   -.``..--.. `:
            `:  `:-      `-  ..      `-`  -`
           .-  `:-    `---` -.         :   :
         `-.  `::`    :/--`-`         `/`  :
        :/`. `:-`      ````          `/:-`.-
        .:--..                        `.```       )", 30, 40);

/* pokimac shiny*/
initPokimac(jeu->tout_poki[5], "Hellpika",R"(
                                    .+hNN-
                                  -/:mMMs
                                ./-` hMy`
                              `::`   hs`
 ``...```                    `/.   `//
`ymmmd-.--:--.`````.--:::--.-/`   ./.  ``
 `:ydNy.     `..:-..`     `-/   `:-  `:--:.`
    `.::------:                :/` `-:`   .-:.`
            `o..`      `.:-    .+`-:`        .::`
            /.(O)      +:(O).    :/.            .o.
           `o +s- .    .syo..`  ./          `---`
           o/`  ``- ``   `: `:` -:        `:-`
           +/.  `..-.    `:.-:  /`      `+:
            /:                  o-`       .---`
             `:/`               +`.--::       :+
              `+-                +  ::`   `--:`
              :.   `     `      -++o.    //`
              s    +    :`    : ../--:-:` `---
             `h.   o    +    .-    o `:/  .-:-
             /-+   o   `/   `/   `+o/:-+::.`
             + o...+   -:` .:     `.o-:.`
             + `...`   `.---       -/`
             -/`                  `+
              :o-.......-........:o`
             :/..-/+-.` ``...-+-.`+
            `so:-.`           `://s-
                                ./+`              )", 80, 40);
initPokimac(jeu->tout_poki[6], "Rieunoferos",R"(

                          /\          /\
                         / `\        /  )
             `         ` `  .````````````
        `             ``````         ```..
       ```           `` ``          `  ..
     ` ``.          .``.`             `/^\
    .````           .``     (O)    `.`/`./
   ``  .             `.   `  ..`  .`/.-. /
  ``   `         .````````\````   / ____ /
 `.`````        .         .___________ ..
 .    .         `.`        \________/-. .``` `
.     `         .``            ```.``` .    ````
.`    .        `` ``        ```````` . .       .`
.      `     ```    \       \````````.````   ` ```\
.  `````.`   `.     `        .```````..`   \````` .
. ``     ``````` ` ``` ------- ````` `      ------
``.    ``  /`      ``````           .
 ``   .   '`        ``             `` ``
  ``  .   |          .             `    `
    ``.   .          `````        .`     .
      ``  .         `-````.....--. ``   ``
          ```      `.````.....-.        `
          `       ``            \`      .``\
          .`     `.             ------------
         / `` `` /
         -------                                 )", 110, 20);
initPokimac(jeu->tout_poki[7], "Sulaggron",R"(                   `..                 `
      `.`          `-.`               ` ``
      .`.``       ``..`              `    `
      .`.```      ````              ``    ``
       .````      ````             ``    ```
       ```` `------`````            `.    ``  `
        `. ```    `..```          .    `    `
        ```(O)    -(O)``````.    .`   `     `
  ------ ```   ``` `.  `------  `.   `      ``
   \.```  .```` G   ` . ``````\`.   `    ````
   ------.         ``.`--------.```` ````   `
          ``.``-----``     `    ``    `     `
            ` `..`   ` `    `         ` ```
           `    -     ``.    `       `.``
         ``   `` .      ``  ```      `````.
       ```.  ``  ..`     ``````..     ``````
      ````` ``  ``  ```   .```.```      ```.
      .``  ``   `       ``-` `` .``         ``
    ``    `    ```    ``  . ``  .````         `
   ``` ` `    \```` `/    .     `      ``      `
 /``` .  /     ------    ``     `       / ` `  /
 -------               /` `  .  \      --------
                       ----.--- --              )" , 40, 70);

/* pokimac légendaire */
initPokimac(jeu->tout_poki[8], "Mewthematiques",R"(                ````.
             ```   ``
          ```     ``    ````
        ```    ``.``````   ``
       ``  ````..           .
     ``  ``.            ``  ``
    ````````.         `(O)`  ``
  `.``      . `(O)    `..``` .`
 ```        . .`-.     .`.``.```````.............`
```         ````.-       .`--..````             ..
..            ```-.    .`   ``````.`           ``.
..         ```...`.-``.     `.`````          ````
``.........```` `` ````.      ``           ```.`
                 ``    .        ```     ``.``
                       .           ..``.```
                      ..     .      `.``
                      .`      .      .
                      - ``     ```   -`
                      .``..`````..`.` ``
                      .  `.`        .  .
                      ``  ``        .   .
                       .   ``        .   .
                        .  `-        .   ``
                         ..`.        .    .
                                     ``` . .
                                      .-...`      )", 200, 60);

//Affichage des règles du jeu
afficheRegles(jeu->pt_lejoueur);


// création du dresseur selon les choix du joueur
creer_dresseur(jeu->pt_lejoueur);
// Le dresseur choisit son pokimac de base
choisir_poki_base(jeu->pt_lejoueur, jeu->tout_poki);



// afficher le menu du début du jeu
MenuAvantPartie(jeu->pt_lejoueur);

//initalisation de la carte
jouer(jeu);

    /*JOUER*/


    /* Afficher le récapitulatif du joueur */

//On supprime les objets
for (int i=0; i<MAX_POKI; i++){
    delete jeu->tout_poki[i];
}
delete jeu->pt_lejoueur;
delete jeu;

    return 0;
}
