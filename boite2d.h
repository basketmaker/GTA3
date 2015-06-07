#ifndef BOITE2D_H
#define BOITE2D_H

#include "main.h"



class Boite2d
{
    public:
        Boite2d(const Point2d& A,const Point2d& B)
        {
            setCorrectMinMax(A.getX(),B.getX(),A.getY(),B.getY());
        }
        Boite2d(int x1, int y1,int x2, int y2)
        {
            setCorrectMinMax(x1,x2, y1, y2);
        }
        Boite2d(unsigned int largeur, unsigned int hauteur) :
        min_(0,0),
        max_(largeur-1,hauteur-1)
        {
        }
        bool contient(Point2d point) const
        {
            if(min_.getX() <= point.getX() && point.getX() <= max_.getX())
                if(min_.getY() <= point.getY() && point.getY() <= max_.getY())
                    return true;
            return false;
        }
        const Point2d& getMin() const
        {
            return min_;
        }
        const Point2d& getMax() const
        {
            return max_;
        }
        unsigned int nlargeur() const
        {
            return max_.getX() - min_.getX() + 1;
        }
        unsigned int nhauteur() const
        {
            return max_.getY() - min_.getY() + 1;
        }


    private:

        void setCorrectMinMax(int x1,int x2, int y1, int y2)
        {
            int minx = (x1 <= x2)? x1 : x2;
            int maxx = (x1 > x2)?  x1 : x2;
            int miny = (y1 <= y2)? y1 : y2;
            int maxy = (y1 > y2)?  y1 : y2;
            min_.setX(minx);
            max_.setX(maxx);
            min_.setY(miny);
            max_.setY(maxy);
        }
        Point2d min_;
        Point2d max_;
};

class Boite2d_iterateur
{
    public:
        Boite2d_iterateur(const Boite2d& boite) :
            boite_(boite)
    {
    }
        Boite2d_iterateur(const Point2d& A, const Point2d& B) : 
            boite_(A,B)
    {
    }
        void start()
        {
            current_ = boite_.getMin();
        }
        bool isValid()
        {
            return (current_.getY() <= boite_.getMax().getY());
        }
        void next()
        {
            if(not isValid())
                abort();
            current_.m_x += 1;
            if(current_.m_x > boite_.getMax().m_x)
            {
                current_.m_x = boite_.getMin().m_x;
                current_.m_y += 1;
            }
        }
        operator Point2d() const
        {
            return current_;
        }
    private:
        Point2d current_;
        Boite2d boite_;
};

#endif
