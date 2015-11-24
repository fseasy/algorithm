#ifndef CONVEX_HULL_BRUTEFORCE_INCLUDED_H
#define CONVEX_HULL_BRUTEFORCE_INCLUDED_H
#include <iostream>
#include <vector>
#include "point.h"

using namespace std ;

namespace conhul{

void find_convex_hull_brute_force(const vector<Point *> &pnts , vector<Point *> & conhul_pnts)
{
    vector<bool> convex_hull_status(pnts.size() , true) ;  
    for(vector<Point *>::const_iterator iA = pnts.begin() ; iA != pnts.end() ; ++iA)
    {
        for(vector<Point*>::const_iterator iB = pnts.begin() ; iB != pnts.end() ; ++iB)
        {
            if(iB == iA) continue ;
            for(vector<Point*>::const_iterator iC = pnts.begin() ; iC != pnts.end() ; ++iC)
            {
                if(iC == iA || iC == iB) continue ;
                for(size_t test_idx = 0 ; test_idx < pnts.size()  ; ++test_idx)
                {
                    if(iTest == iA || iTest == iB || iTest == iC) continue ;
                    if(convex_hull_status[test_idx] == false) continue ;
                    vector<Point*>::const_iterator iTest = pnts.begin() + test_idx ;
                    if( ! is_in_same_side(*iA , *iB , *iC , *iTest) || ! is_in_same_side(*iA , *iC , *iB , *iTest) 
                       || ! is_in_same_side(*iB , *iC , *iA , *iTest)) convex_hull_status[test_idx] = false ; 
                }

            }
        }
    }
    // copy convex hull pnts to conhul_pnts
    for(size_t i = 0 ; i < pnts.size() ; ++i)
    {
        if(convex_hull_status[i]) conhul_pnts.push_back(pnts[i]) ;
    }
}
/**
 * function name : is_in_same_side(Point *line_p_1 , Point *line_p_2 , Point *test_p_1 , Point *test_p_2)
 * param:line_p_1 , line_p_2 
 *         [in] 
 *         the point in the line . use this to calc the line formula
 *       test_p_1 , test_p_2 
 *         [in]
 *         the point to be tested whether they are in the same side of the line
 * return: [bool]  
**/
bool is_in_same_side(Point *line_p_1 , Point *line_p_2 , Point *test_p_1 , Point *test_p_2)
{
    /**
     * Logic
     * Point(x , y) => X = (x,y)
     * using 2 point , we can get the line formula `WX + b = 0` . Where W is a vector (W_1 , W_2) , and b is a sigular .
     * for WX_1 + b = 0 && WX_2 + b = 0 => W(X_1 - X_2) = 0 => (W_1 , W_2)^T * (x_1 - x_2 , y_1 - y_2) = 0 ;
     * we can assume that `W_1 = - (y_1 - y_2)` , `W_2 = x_1 - x_2` . 
     * then just to calc the `b` value : b = - W * X_1 
     * Now we get the line formula .
     * point to line's distance , we can just using `functional margin` to representation !
     * That is : y = W * X + b , y is the functional margin . positive for the direction of normal vector(法向量) , negative for against
     * if y_1 * y_2 is a positive value , the test points are in the same side ; else on each side
     **/
    // get line formula
    int w_1 , w_2 ;
    w_1 = - (line_p_2->y - line_p_1->y) ;
    w_2 = line_p_1->x - line_p_2->x ;
    b = - ( w_1 * line_p_1->x + w_2 * line_p_1-> y ) ;
    // get functional margin
    y_1 = w_1 * test_p_1->x + w_2 * test_p_1->y + b ;
    y_2 = w_1 * test_p_2->x + w_2 * test_p_2->y + b ;
    // decide by the sign of product y_1 and y_2
    return ( y_1*y_2 >= 0 ) ? true : false ;
}


}

#endif
