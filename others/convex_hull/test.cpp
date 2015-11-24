#include <iostream>
#include <vector>
#include "point.h"
#include "generate_points.h"

using namespace std ;
using namespace conhul ;

int main(int argc , char * argv[])
{
    vector<Point*> pnts ;
    int pnt_nums = 10 ;
    int pnt_x_max = 20 ;
    int pnt_y_max = 200 ;
    generate_pnts(pnt_nums , pnt_x_max , pnt_y_max , pnts , false ) ;
    print_pnts(pnts) ; 
    clear_pnts(pnts) ;
    return 0 ;
}
