#ifndef SELECTIONEUR_H
#define SELECTIONEUR_H

#include "../main.h"
#include "../boite2d.h"



class Selectioneur
{
    public:
        Selectioneur()
        {
            m_coteVertical = NULL;
            m_coteHoryzontal = NULL;
            hautDroite.x = 0;
            hautDroite.y = 0;
            hautGauche.x = 0;
            hautGauche.y = 0;
            basDroite.x = 0;
            basDroite.y = 0;
            basGauche.x = 0;
            basGauche.y = 0;
            limite_hautGauche.x = 0;
            limite_hautGauche.y = 0;
            limite_basDroite.x = 0;
            limite_basDroite.y = 0;
        }
        Selectioneur(const Selectioneur& sel)
        {
            m_coteVertical = NULL;
            m_coteHoryzontal = NULL;
            setLimites(sel.limite_hautGauche,sel.limite_basDroite);
            setSelectioneur(sel.hautGauche,sel.basDroite);
        }

        void setLimites(const SDL_Rect& plimite_hautGauche,
                const SDL_Rect& plimite_basDroite)
        {
            limite_hautGauche.x = plimite_hautGauche.x;
            limite_hautGauche.y = plimite_hautGauche.y;
            limite_basDroite.x = plimite_basDroite.x;
            limite_basDroite.y = plimite_basDroite.y;
        }
        void blitSelectioneur(
                SDL_Surface *ecran
                )
        {
            if(m_coteVertical != NULL && m_coteHoryzontal != NULL)
            {
                SDL_BlitSurface(m_coteVertical,NULL,ecran,&hautGauche);
                SDL_BlitSurface(m_coteHoryzontal,NULL,ecran,&hautGauche);
                SDL_BlitSurface(m_coteVertical,NULL,ecran,&hautDroite);
                SDL_BlitSurface(m_coteHoryzontal,NULL,ecran,&basGauche);
            }
        }
        void safeSelection(const SDL_Rect& A,
                const SDL_Rect& B, 
		int taille_case)
        {
            taille_case_ = taille_case;
	        SDL_Rect pcarre_hautGauche;
            SDL_Rect pcarre_basDroite;
            pcarre_hautGauche.x = (A.x < B.x) ? A.x : B.x;
            pcarre_hautGauche.y = (A.y < B.y) ? A.y : B.y; 
            pcarre_basDroite.x = (A.x > B.x) ? A.x : B.x; 
            pcarre_basDroite.y = (A.y > B.y) ? A.y : B.y;
	    pcarre_hautGauche = quelle_case_haute(pcarre_hautGauche,taille_case);
	    pcarre_basDroite = quelle_case_basse(pcarre_basDroite,taille_case);
	    setSelectioneur(pcarre_hautGauche,pcarre_basDroite);
        }
        void setSelectioneur(
                const SDL_Rect& phautGauche,
                const SDL_Rect& pbasDroite)
        {
            if(phautGauche.x != hautGauche.x ||
                    phautGauche.y != hautGauche.y ||
                    pbasDroite.x != basDroite.x ||
                    pbasDroite.y != basDroite.y)
            {
                if(pbasDroite.x <= limite_basDroite.x)
                {
                    hautDroite.x = pbasDroite.x;
                    basDroite.x = pbasDroite.x;
                }
                if(phautGauche.x >= limite_hautGauche.x){
                    hautGauche.x = phautGauche.x;
                    basGauche.x = phautGauche.x;
                }
                if(pbasDroite.y <= limite_basDroite.y)
                {
                    basGauche.y = pbasDroite.y;
                    basDroite.y = pbasDroite.y;
                }
                if(phautGauche.y >= limite_hautGauche.y)
                {
                    hautDroite.y = phautGauche.y;
                    hautGauche.y = phautGauche.y;
                }
                if(m_coteVertical != NULL && m_coteHoryzontal != NULL)
                {
                    SDL_FreeSurface(m_coteVertical);
                    SDL_FreeSurface(m_coteHoryzontal);
                }
                m_coteVertical= SDL_CreateRGBSurface(SDL_HWSURFACE,2,basDroite.y - hautGauche.y + 1,32,0,0,0,0);
                m_coteHoryzontal= SDL_CreateRGBSurface(SDL_HWSURFACE,basDroite.x - hautGauche.x,2,32,0,0,0,0);
                SDL_FillRect(m_coteHoryzontal, NULL, SDL_MapRGB(m_coteHoryzontal->format, 0, 255, 0));
                SDL_FillRect(m_coteVertical, NULL, SDL_MapRGB(m_coteVertical->format, 0, 255, 0));
            }
        }
        ~Selectioneur()
        {
            if(m_coteVertical != NULL && m_coteHoryzontal != NULL)
            {
                SDL_FreeSurface(m_coteVertical);
                SDL_FreeSurface(m_coteHoryzontal);
            }
        }
        SDL_Rect quelle_case_haute(const SDL_Rect& pos,int taille_case)
        {
            unsigned int X,Y;
            SDL_Rect retour;
            X = pos.x - limite_hautGauche.x;
            Y = pos.y - limite_hautGauche.y;
            X = X/taille_case;
            Y = Y/taille_case;
            retour.x = X*taille_case+limite_hautGauche.x;
            retour.y = Y*taille_case+limite_hautGauche.y;
            return retour;
        }

        SDL_Rect quelle_case_basse(const SDL_Rect& pos, int taille_case)
        {
            unsigned int X,Y;
            SDL_Rect retour;
            X = pos.x - limite_hautGauche.x;
            Y = pos.y - limite_hautGauche.y;
            X = (X/taille_case) + 1;
            Y = (Y/taille_case) + 1;
            retour.x = X*taille_case+limite_hautGauche.x;
            retour.y = Y*taille_case+limite_hautGauche.y;
            return retour;
        }

        Point2d cases_selectionnees_begin(int taille_case)
        {
            int X,Y;
            X = hautGauche.x - limite_hautGauche.x;
            Y = hautGauche.y - limite_hautGauche.y;
            X=X/taille_case;
            Y=Y/taille_case;
            return Point2d(X,Y);
        }

        Point2d cases_selectionnees_end(int taille_case)
        {
            int X,Y;
            X = basDroite.x - limite_hautGauche.x;
            Y = basDroite.y - limite_hautGauche.y;
            X=X/taille_case - 1;
            Y=Y/taille_case - 1;
            return Point2d(X,Y);
        }

        Boite2d getBoite2d()
        {
            return Boite2d(cases_selectionnees_begin(taille_case_),cases_selectionnees_end(taille_case_));
        }

    private:
        SDL_Rect hautDroite;
        SDL_Rect hautGauche;
        SDL_Rect basGauche;
        SDL_Rect basDroite;
        int taille_case_;
        SDL_Rect limite_hautGauche;
        SDL_Rect limite_basDroite;

        SDL_Surface* m_coteVertical;
        SDL_Surface* m_coteHoryzontal;

};


#endif

