#include "editor.h"


using namespace std;

Editor::Editor() :
map_("level1",20,20),
map_choix_(32,32),
sprites_choix(32,32,"./ressources/decor.jpg"),
sprites_carte(32,32,"./ressources/decor.jpg") 
{
    appuieSourie=0;
    focus = -1;

    m_ecran = SDL_SetVideoMode(LARGEUR_EDITOR, HAUTEUR_EDITOR, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Editor", NULL);

    /*On place la fenetre des choix */
    sprites_choix.resizeSprite((22));
    map_choix_.setInc();

    position_choix.w = sprites_choix.getLargeurSprite()*sprites_choix.getnLargeur();
    position_choix.h = sprites_choix.getHauteurSprite()*sprites_choix.getnHauteur();
    position_choix.x = m_ecran->w / 2 + m_ecran->w / 4 - position_choix.w / 2;
    position_choix.y = m_ecran->h /2 - position_choix.h / 2;
    fenetre_choix = SDL_CreateRGBSurface(SDL_HWSURFACE, 
                                         position_choix.h+1, 
                                         position_choix.w+1,
                                         32, 0, 0, 0, 0);
    SDL_FillRect(fenetre_choix, NULL, SDL_MapRGB(fenetre_choix->format, 255, 0, 255)); 
    Observateur choix_observateur(map_choix_,sprites_choix);
    choix_observateur.afficher(fenetre_choix);


    /*Le selectioneur des choix*/
    SDL_Rect limite_basse;
    limite_basse.x = position_choix.x + fenetre_choix->w;
    limite_basse.y = position_choix.y + fenetre_choix->h;
    selectioneur_choix.setLimites(position_choix,limite_basse);




    /*On charge en memoire L'affichage de la MAP*/
  
    position_blit.x = 0;
    position_blit.y = 0;
    position_blit.w = m_ecran->w/2;
    position_blit.h = m_ecran->h;

    fenetre_blit = SDL_CreateRGBSurface(SDL_HWSURFACE, 
                                        position_blit.w+1, 
                                        position_blit.h+1, 
                                        32, 0, 0, 0, 0);
    SDL_FillRect(fenetre_blit, NULL, SDL_MapRGB(fenetre_blit->format, 255, 255, 255));
    sprites_carte.resizeSprite(m_ecran->w/sprites_carte.getnLargeur());
}

void Editor::selection_carte(const SDL_Event& event)
{
    SDL_Rect carre_hautGauche, carre_basDroite, eventSouris;
    eventSouris.x = event.motion.x;
    eventSouris.y = event.motion.y;
    Point2d pos_click((event.motion.x - position_blit.x)/sprites_carte.getLargeurSprite(),
                      (event.motion.y - position_blit.y)/sprites_carte.getHauteurSprite() );
    Boite2d box1 = selectioneur_choix.getBoite2d();
    Boite2d_iterateur it_choix(box1);
    Boite2d box2(pos_click,Point2d(pos_click.m_x+box1.nlargeur()-1,
                                   pos_click.m_y+box1.nhauteur()-1));
    Boite2d_iterateur it_carte(box2);
    for(it_carte.start(),it_choix.start() ; it_carte.isValid(); it_choix.next(), it_carte.next())
    {
        Point2d P = it_carte;
        Point2d N = it_choix;
        if(map_.contient(P))
        {
            map_(P) = map_choix_(N);
        }
    }
    Observateur carte_observateur(map_,sprites_carte);
    carte_observateur.afficher(fenetre_blit);

}



void Editor::selection_choix(const SDL_Event& event)
{
    SDL_Rect carre_hautGauche, carre_basDroite, eventSouris;
    eventSouris.x = event.motion.x;
    eventSouris.y = event.motion.y;
    selectioneur_choix.safeSelection(eventSouris,
                                     positionClik_selectioneur,
                                     sprites_choix.getLargeurSprite());   
}


int Editor::focusSourie(const SDL_Event& event)
{
    int X,Y;
    if(event.motion.x >= position_choix.x && 
       event.motion.x <= position_choix.x + fenetre_choix->w &&
       event.motion.y >= position_choix.y &&
       event.motion.y <= position_choix.y + fenetre_choix->h)
    {
        return CHOIX;
    }
    if(event.motion.x >= position_blit.x &&
       event.motion.x <= position_blit.x + fenetre_blit->w &&
       event.motion.y >= position_blit.y &&
       event.motion.y <= position_blit.y + fenetre_blit->h)
    {
        return CARTE;
    }
    return -1;
}

void Editor::controles(const SDL_Event& event)
{
    switch(event.type)
    {
        case SDL_MOUSEBUTTONDOWN:
                appuieSourie = 1;
                focus = focusSourie(event);
                positionClik_selectioneur.x = event.motion.x;
                positionClik_selectioneur.y = event.motion.y;
                
            break;
        case SDL_MOUSEBUTTONUP:
            switch(focus)
            {
                case CARTE:
                    selection_carte(event);
                break;
            }
            appuieSourie = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_s: /* Appui sur la touche d'Enregistrement */
                    map_.save();
                    break;
            }

            break;
    }
    switch(appuieSourie)
    {
        case 1:
            switch(focus)
            {
                case CHOIX:
                    selection_choix(event);
                    break;
            }
            break;
    }


}



void Editor::afficher()
{
    SDL_FillRect(m_ecran, NULL, SDL_MapRGB(m_ecran->format, 0, 0, 0));
    SDL_BlitSurface(fenetre_choix, NULL, m_ecran, &position_choix);
    SDL_BlitSurface(fenetre_blit,NULL,m_ecran,&position_blit);
    selectioneur_choix.blitSelectioneur(m_ecran);
}

Editor::~Editor()
{
    SDL_FreeSurface(fenetre_choix);
    SDL_FreeSurface(fenetre_blit);
    stopActivitee();
}


