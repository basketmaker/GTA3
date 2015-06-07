#ifndef CARTE_H
#define CARTE_H

#include "main.h"

class Carte
{
    public:
        Carte(const std::string& name, unsigned largeur, unsigned hauteur);
        Carte(const std::string& name);
	    Carte(const Carte& copie);
        Carte(unsigned int largeur, unsigned int hauteur);
        void setNull();
        void setInc();
        void save();
        void load();
        int operator()(unsigned int x, unsigned int y) const;
        int& operator()(unsigned int x, unsigned int y);
        int operator()(const Point2d& point) const;
        int& operator()(const Point2d& point);
        int getLargeur() const;
        int getHauteur() const;
        bool contient(const Point2d& point) const;
        ~Carte();
    private:
        std::string nom_fichier_;
        int *data_;
        int largeur_;
        int hauteur_;
};


#endif

