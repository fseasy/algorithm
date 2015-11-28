#ifndef CONVEX_HULL_BRUTEFORCE_INCLUDED_H
#define CONVEX_HULL_BRUTEFORCE_INCLUDED_H
#include <iostream>
#include <vector>
#include <cmath>
#include "point.h"

using namespace std ;

namespace conhul{

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
bool is_in_same_side(Point *line_p_1 , Point *line_p_2 , Point *test_p_1 , Point *test_p_2) ;

void find_convex_hull_brute_force(const vector<Point *> &pnts , vector<Point *> & conhul_pnts)
{
    vector<bool> convex_hull_status(pnts.size() , true) ;  
    for(vector<Point *>::const_iterator iA = pnts.begin() ; iA != pnts.end() ; ++iA)
    {
        if(convex_hull_status[iA - pnts.begin()] == false ) continue ;
        for(vector<Point*>::const_iterator iB = pnts.begin() ; iB != pnts.end() ; ++iB)
        {
            if(iB == iA) continue ;
            if(convex_hull_status[iB - pnts.begin()] == false) continue ;
            for(vector<Point*>::const_iterator iC = pnts.begin() ; iC != pnts.end() ; ++iC)
            {
                if(iC == iA || iC == iB) continue ;
                if(convex_hull_status[iC - pnts.begin()] == false) continue ;
                for(size_t test_idx = 0 ; test_idx < pnts.size()  ; ++test_idx)
                {
                    if(convex_hull_status[test_idx] == false) continue ;
                    vector<Point*>::const_iterator iTest = pnts.begin() + test_idx ;
                    if(iTest == iA || iTest == iB || iTest == iC) continue ;
                    if( is_in_same_side(*iA , *iB , *iC , *iTest) && is_in_same_side(*iA , *iC , *iB , *iTest) 
                       && is_in_same_side(*iB , *iC , *iA , *iTest))
                    {
                        // Test point is in the range of the triangle of ABC , so it is not the convex hull !
                        convex_hull_status[test_idx] = false ; 
                    }
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

void calc_line_param(Point *line_pnt_1 , Point *line_pnt_2 , float &w_1 , float &w_2 , float &b)
{
    /**
     * Logic
     * Point(x , y) => X = (x,y)
     * using 2 point , we can get the line formula `WX + b = 0` . Where W is a vector (W_1 , W_2) , and b is a sigular .
     * for WX_1 + b = 0 && WX_2 + b = 0 => W(X_1 - X_2) = 0 => (W_1 , W_2)^T * (x_1 - x_2 , y_1 - y_2) = 0 ;
     * we can assume that `W_1 = - (y_1 - y_2)` , `W_2 = x_1 - x_2` . 
     * then just to calc the `b` value : b = - W * X_1 
     * Now we get the line formula .
     **/
    w_1 = - (line_pnt_1->y - line_pnt_2->y) ;
    w_2 = line_pnt_1->x - line_pnt_2->x ;
    float norm_factor = max(fabs(w_1) , fabs(w_2)) ;
    w_1 = w_1 / norm_factor ,
    w_2 = w_2 / norm_factor ;
    b = - ( norm_w_1 * line_p_1->x + norm_w_2 * line_p_1-> y ) ;
}

bool is_in_same_side(Point *line_pnt_1 , Point *line_pnt_2 , Point *test_pnt_1 , Point *test_pnt_2)
{
    /**
     * Logic
     * Firstly , we get the line formula .
     * point to line's distance , we can just using `functional margin` to representation !
     * That is : y = W * X + b , y is the functional margin . positive for the direction of normal vector(法向量) , negative for against
     * if y_1 * y_2 is a positive value , the test points are in the same side ; else on each side
     * Addtion !  using normalize to avoid overflow !
     **/
    // get line formula
    float w_1 , w_2 , b ;
    calc_line_param(line_pnt_1 , line_pnt_2 , w_1 , w_2 , b ) ;
    // get functional margin
    float y_1 , y_2 ;
    y_1 = w_1 * test_pnt_1->x + w_2 * test_pnt_1->y + b ;
    y_2 = w_1 * test_pnt_2->x + w_2 * test_pnt_2->y + b ;
    // decide by the sign of product y_1 and y_2
    return ( y_1*y_2 >= 0 ) ? true : false ;
}


}

void sort_convex_hull_in_print_order(vector<Point *> &conhul_pnts)
{
    if(conhul_pnts.size() < 3)
    {
        cerr << __FILE__ << " : convex hull to be sorted 's size is less than 3 . Abort!" << endl ;
        return ;
    }
    vector<Point *> tmp_pnts ;
    // find the min and the max pnt in the x-axis
    Point *left_most = conhul_pnts[0] ;
    Point *right_most = left_most ;
    for(vector<Point *>::const_iterator ite = conhul_pnts.begin() + 1; ite != conhul_pnts.end() ; ++ite)
    {
        if((*ite)->x > right_most->x) right_most = *ite ;
        if((*ite)->x < left_most->x) left_most = *ite ;
    }
    // calc the line for left most point to right most point . 
    // using this line to partition the ponits set S_L , S_U .
    float w_1 , w_2 , b ;
    calc_line_param(left_most , right_most , w_1 , w_2 , b) ;
    vector<Point *> SL , SU ;
    for(vector<Point *>::const_iterator ite = conhul_pnts.begin() ; ite != conhul_pnts.end() ; ++ite)
    {
        Point * cur_pnt = *ite ; 
        if(cur_pnt == left_most || cur_pnt == right_most) continue ;
        float funcional_margin = w_1 * cur_pnt->x + w_2 * cur_pnt->y + b ;
        if(functional_margin > 0) SU.push_back(cur_pnt) ;
        else SL.push_back(cur_pnt) ;
    }
    
}
#endif
