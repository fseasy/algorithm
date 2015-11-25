#ifndef GENERATE_POINTS_INCLUDE_H
#define GENERATE_POINTS_INCLUDE_H

#include <cstdlib>
#include <ctime>
#include <vector>
#include "point.h"

using namespace std ;
using namespace conhul ;

const time_t G_STATIC_SEED = 1314 ;
const time_t G_RANDOM_SEED = time(0) ;

void generate_pnts(int num_pnts , int pnt_x_max , int pnt_y_max , vector<Point*> & pnts ,bool is_static_random=false)
{
    if(!is_static_random) srand(G_RANDOM_SEED) ;
    else srand(G_STATIC_SEED) ;
    for(int i = 0 ; i <num_pnts ; ++i)
    {
        int x = rand() % pnt_x_max ;
        int y = rand() % pnt_y_max ;
        Point *p = new Point(x,y) ;
        pnts.push_back(p) ;
    }
}

void print_pnts(const vector<Point *> & pnts)
{
    if(pnts.size() == 0) return ;
    cout << *pnts[0] ;
    for(vector<Point *>::const_iterator ite = pnts.begin() + 1; ite != pnts.end() ; ++ite)
    {
        cout << " " << *(*ite) ;
    }
    cout << endl ;
}

void clear_pnts(vector<Point *> &pnts)
{
    for(vector<Point*>::iterator ite = pnts.begin() ; ite != pnts.end() ; ++ite)
    {
        delete *ite ;
        *ite = NULL ;
    }
}

#endif
