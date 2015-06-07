#include "carte.h"

using namespace std;

Carte::Carte(unsigned int largeur,unsigned int hauteur)
{
    largeur_ = largeur;
    hauteur_ = hauteur;
    data_ = new int[largeur_*hauteur_];
}

Carte::Carte(const string& name, unsigned largeur, unsigned hauteur)
{
    largeur_ = largeur;
    hauteur_ = hauteur;
    nom_fichier_ = "level/"+name;
    data_ = NULL;
    data_ = new int[largeur*hauteur];
    if(data_ == NULL)
    {
        cout<<"In save : malloc fail! "<<endl;
        exit(0);
    }
    setNull();
}

Carte::Carte(const Carte& copie)
{
    largeur_ = copie.largeur_;
    hauteur_ = copie.hauteur_;
    nom_fichier_ = copie.nom_fichier_;
    data_ = new int[largeur_*hauteur_];
    for(int i = 0; i < largeur_*hauteur_; i ++)
    {
	    data_[i] = copie.data_[i];
    }
}

Carte::Carte(const string& name)
{
    nom_fichier_ = "level/"+name;
    load();
}
void Carte::setNull()
{
    for(int i = 0; i < largeur_*hauteur_ ; i++)
        data_[i] = 0;
}
void Carte::setInc()
{
    for(int i = 0 ; i < largeur_*hauteur_ ; i++)
    {
        data_[i] = i;
    }
}

void Carte::save()
{
    ofstream fichier(nom_fichier_.c_str(), ios::out | ios::trunc);
    if(!fichier)
    {
        cerr << "Impossible de sauver le fichier !" << endl;
        return ;
    }
    fichier << largeur_ << "//" << hauteur_ << endl;
    for(int i = 0; i < largeur_*hauteur_; i++)
        fichier << data_[i] << ";";
    fichier.close();  
}
void Carte::load()
{
}
int Carte::getLargeur() const
{
    return largeur_;
}
int Carte::getHauteur() const
{
    return hauteur_;
}
bool Carte::contient(const Point2d& point) const 
{
    if(point.m_x < largeur_ && point.m_y < hauteur_)
        return true;
    return false;
}
int Carte::operator()(unsigned int x, unsigned int y) const
{
    if(x < largeur_ && y < hauteur_)
        return data_[x+y*largeur_];
    else
    {
        abort();
        return 0;
    }
}
int& Carte::operator()(unsigned int x, unsigned int y)
{
    if(x < largeur_ && y < hauteur_)
        return data_[x+y*largeur_];
    else
    {
        abort();
        return data_[0];
    }
}
int Carte::operator()(const Point2d& point) const
{
    int x,y;
    x = point.getX();
    y = point.getY();
    if(x < largeur_ && y < hauteur_)
        return data_[x+y*largeur_];
    else
    {
        abort();
        return 0;
    }
}
int& Carte::operator()(const Point2d& point)
{
    int x,y;
    x = point.getX();
    y = point.getY();
    if(x < largeur_ && y < hauteur_)
        return data_[x+y*largeur_];
    else
    {
        abort();
        return data_[0];
    }
}
Carte::~Carte()
{
    delete data_;
}

