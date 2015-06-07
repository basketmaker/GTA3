#ifndef EDITOR_H
#define EDITOR_H

#include "../main.h"
#include "../carte.h"
#include "../sprites.h"
#include "../observateur.h"
#include "selectioneur.h"


#define LARGEUR_EDITOR 1536
#define HAUTEUR_EDITOR 768
#define CHOIX 0
#define CARTE 1
#define NOMBRE_CASES_LARGEUR 32
#define NOMBRE_CASES_HAUTEUR 32


class Editor : public Activite
{
    public:
        Editor();
        void controles(const SDL_Event& event);
        void afficher();
        ~Editor();
    private:

        SDL_Surface *fenetre_choix;
        SDL_Surface *fenetre_blit;
        SDL_Rect position_choix;
        SDL_Rect position_blit;
        Carte map_;
        Carte map_choix_;
        Sprites sprites_choix;
        Sprites sprites_carte;
        Selectioneur selectioneur_choix;
        Selectioneur selectioneur_carte;
        SDL_Rect positionClik_selectioneur;

      
        int focus;
        int appuieSourie;
        int taille_case_choix;
        int taille_case_blit;
        int focusSourie(const SDL_Event& event);
        void selection_choix(const SDL_Event& event);
        void selection_carte(const SDL_Event& event);
};

#endif

