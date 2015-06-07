#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


#define HAUTEUR_ECRAN 768
#define LARGEUR_ECRAN 1024

#define FPS 50

class Point2d
{
    public:
        Point2d()
        {
            m_x = 0;
            m_y = 0;
        }
        Point2d(int x, int y)
        {
            m_x = x;
            m_y = y;
        }
        Point2d(const Point2d& point)
        {
            m_x = point.m_x;
            m_y = point.m_y;
        }
        int getX() const
        {
            return m_x;
        }
        int getY() const
        {
            return m_y;
        }
        void setX(int x)
        {
            m_x = x;
        }
        void setY(int y)
        {
            m_y = y;
        }
        bool operator==(const Point2d& point)
        {
            return (m_x == point.m_x && m_y == point.m_y);
        }
        
        void afficher()
        {
            printf("\t X : %d : Y : %d \n", m_x, m_y);
        }
        int m_x;
        int m_y;
};


class Activite
{
    public:
        virtual void afficher() = 0;

        void refresh()
        {
            SDL_Flip(m_ecran);
        }
        /*

        les controles pour quitter, ...

        */




        void run_activity()
        {
            int tempsRafraichissement = 1000 / FPS;
            int continuer = 1;
            int tempsActuel = 0;
            int tempsPrecedent = SDL_GetTicks();
            SDL_Event event;
            while (continuer)
            {
                while(SDL_PollEvent(&event))
                {
                    controles_generaux(event, continuer);
                    controles(event);
                }
                tempsActuel = SDL_GetTicks();
                if((tempsActuel - tempsPrecedent) >= tempsRafraichissement)
                {
                    afficher();
                    SDL_Flip(m_ecran);
                    tempsPrecedent = tempsActuel;
                }
                else
                {
                    SDL_Delay(tempsRafraichissement - (tempsActuel - tempsPrecedent));
                }
            }
        }
        
        void controles_generaux(const SDL_Event& event, int& continuer)
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_KEYDOWN: /* Si appui sur une touche */
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE: /* Appui sur la touche Echap */
                            continuer = 0;
                        break;
                    }
                    break;
            }
        }

        virtual ~Activite()
        {
        }
    protected:      
        void stopActivitee()
        { 
            SDL_FreeSurface(m_ecran);
            SDL_Delay(1000);
        }
        virtual void controles(const SDL_Event& event) = 0;
        SDL_Surface *m_ecran;
};
#endif

