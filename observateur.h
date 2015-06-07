#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H

#include "main.h"
#include "carte.h"
#include "sprites.h"
#include "boite2d.h"

class Observateur
{
    public:
        Observateur(const Carte& map, const Sprites& sprites) :
            map_(map),
            sprites_(sprites)
        {
        }
        void afficher(const Point2d& A, const Point2d& B, SDL_Surface *destination) const
        {
            unsigned int largeur_case = sprites_.getLargeurSprite();
            unsigned int hauteur_case = sprites_.getHauteurSprite();
            SDL_Rect pos;
            Boite2d source(A,B);
            Boite2d dest(source.nlargeur(), source.nhauteur());
            Boite2d_iterateur map_it(source);
            Boite2d_iterateur vue_it(dest);
            for(map_it.start(),vue_it.start(); vue_it.isValid(); map_it.next(),vue_it.next())
            {
                Point2d P = vue_it;
                Point2d N = map_it;
                N.afficher();
                pos.x = P.m_x*largeur_case;
                pos.y = P.m_y*hauteur_case;
                SDL_BlitSurface(sprites_(map_(N)), NULL, destination, &pos);
            }
        }
        void afficher(SDL_Surface *destination)
        {
            afficher(Point2d(0,0),Point2d(map_.getLargeur()-1,map_.getHauteur()-1),destination);
        }
    private:
        const Carte& map_;
        const Sprites& sprites_;
};


#endif  

