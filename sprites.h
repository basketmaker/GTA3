#ifndef SPRITES_H
#define SPRITES_H

#include "main.h"

class Sprites
{
    public: 
        Sprites(unsigned int largeur, unsigned int hauteur, SDL_Surface* sprites)
        {
            SDL_Rect possrc, posdest;
            posdest.x = 0;
            posdest.y = 0;
            largeur_ = largeur;
            hauteur_ = hauteur;
            largeur_sprite_ = sprites->w / largeur_;
            hauteur_sprite_ = sprites->h / hauteur_;
            possrc.w = largeur_sprite_;
            possrc.h = hauteur_sprite_;
            sprites_ = (SDL_Surface**)malloc(sizeof(SDL_Surface*)*largeur_*hauteur_);
            for(int i = 0; i < largeur_; i++)
            {
                for(int j = 0; j < hauteur_; j++)
                {
                    sprites_[i+j*largeur_] = SDL_CreateRGBSurface(0,largeur_sprite_,hauteur_sprite_,32,0,0,0,0);
                    possrc.x = i*largeur_sprite_;
                    possrc.y = j*hauteur_sprite_;
                    SDL_BlitSurface(sprites,&possrc,sprites_[i+j*largeur_],&posdest);
                }
            }
        }
        Sprites(unsigned int largeur, unsigned int hauteur, const std::string& nomFichier)
        {
            SDL_Surface* sprites = IMG_Load(nomFichier.c_str());
            SDL_Rect possrc, posdest;
            posdest.x = 0;
            posdest.y = 0;
            largeur_ = largeur;
            hauteur_ = hauteur;
            largeur_sprite_ = sprites->w / largeur_;
            hauteur_sprite_ = sprites->h / hauteur_;
            possrc.w = largeur_sprite_;
            possrc.h = hauteur_sprite_;
            std::cout << largeur << ";" << hauteur << std::endl;
            sprites_ = (SDL_Surface**)malloc(sizeof(SDL_Surface*)*largeur_*hauteur_);
            for(int i = 0; i < largeur_; i++)
            {
                for(int j = 0; j < hauteur_; j++)
                {
                    sprites_[i+j*largeur_] = SDL_CreateRGBSurface(SDL_HWSURFACE,largeur_sprite_,hauteur_sprite_,32,0,0,0,0);
                    possrc.x = i*largeur_sprite_;
                    possrc.y = j*hauteur_sprite_;
                    SDL_BlitSurface(sprites,&possrc,sprites_[i+j*largeur_],&posdest);
                }
            }
            SDL_FreeSurface(sprites);
        }
        SDL_Surface* operator()(unsigned int i, unsigned int j) const
        {
            if(i < largeur_ && j < hauteur_)
            {
                return sprites_[i+j*largeur_];
            }
            else
            {
                abort();
                return NULL;
            }
        }
        SDL_Surface* operator()(unsigned int i) const
        {
            if(i < largeur_*hauteur_)
            {
                return sprites_[i];
            }
            else
            {
                abort();
                return NULL;
            }
        }
        SDL_Surface* operator()(const Point2d& point) const
        {
            unsigned int i = point.getX();
            unsigned int j = point.getY();
            if(i < largeur_ && j < hauteur_)
            {
                return sprites_[i+j*largeur_];
            }
            else
            {
                abort();
                return NULL;
            }
        }
        unsigned int getLargeurSprite() const
        {
            return largeur_sprite_;
        }
        unsigned int getHauteurSprite() const
        {
            return hauteur_sprite_;
        }
        unsigned int getnLargeur() const
        {
            return largeur_;
        }
        unsigned int getnHauteur() const 
        {
            return hauteur_;
        }

        void resizeSprite(unsigned int taille_largeur)
        {
            double coef_zoom = (double)taille_largeur/(double)largeur_sprite_;
            SDL_Surface *tmp;
            for(int i = 0; i < largeur_*hauteur_; i++)
            {
                tmp =  rotozoomSurface(sprites_[i], 0.0,coef_zoom,1);
                SDL_FreeSurface(sprites_[i]);
                sprites_[i] = tmp;
            }
            largeur_sprite_ = sprites_[0]->w;
            hauteur_sprite_ = sprites_[0]->h;
        }
        void resizeSprite(unsigned int largeur, unsigned int hauteur)
        {
            double coef_largeur = (double)largeur/(double)largeur_sprite_;
            double coef_hauteur = (double)hauteur/(double)hauteur_sprite_;
            SDL_Surface *tmp;
            for(int i = 0; i < largeur_*hauteur_; i++)
            {
                tmp =  rotozoomSurfaceXY(sprites_[i], 0.0, coef_largeur, coef_hauteur,1);
                SDL_FreeSurface(sprites_[i]);
                sprites_[i] = tmp;
            }
            largeur_sprite_ = sprites_[0]->w;
            hauteur_sprite_ = sprites_[0]->h;
        }
    private:
        SDL_Surface **sprites_;
        unsigned int largeur_;
        unsigned int hauteur_;
        unsigned int largeur_sprite_;
        unsigned int hauteur_sprite_;
};


#endif

