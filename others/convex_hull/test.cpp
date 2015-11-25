#include <iostream>
#include <vector>
#include "point.h"
#include "generate_points.h"
#include "convex_hull_bruteforce.h"

using namespace std ;
using namespace conhul ;

int main(int argc , char * argv[])
{
    vector<Point*> pnts ;
    int pnt_nums = 100 ;
    int pnt_x_max = 20 ;
    int pnt_y_max = 200 ;
    generate_pnts(pnt_nums , pnt_x_max , pnt_y_max , pnts , false  ) ;
    vector<Point*> conhul_pnts ;
    find_convex_hull_brute_force(pnts , conhul_pnts) ; 
    //print_pnts(pnts) ; 
    print_pnts(conhul_pnts) ;
    clear_pnts(pnts) ;
    return 0 ;
}
