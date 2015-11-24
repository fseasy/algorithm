#ifndef POINT_INCLUDE_D
#define POINT_INCLUDE_D
#include <iostream>

using namespace std ;

namespace conhul{

struct Point
{
    int x ;
    int y ;
    Point(int ix , int iy):x(ix),y(iy){}
    Point():x(0),y(0){} 
    friend ostream& operator<< (ostream &out , const Point &p)
    {
        out << "(" << p.x << "," << p.y << ")" ;
        return out ;
    }
} ;

}
#endif
