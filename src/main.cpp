#include "../include/matrix.h"

#include <iostream>



int main(){

    Matrix a("../inout/a.txt");
    Matrix b("../inout/b.txt");
//    lup_a.print();
    /*Matrix sups = lu_a.sups_forward(b);
    sups.print();
    Matrix sups2 = lu_a.sups_backward(sups);
    sups2.print();*/

//    a.solve_w_LU();
    a.LU_decomp().print();
    a.LUP_decomp().first.print();
    Matrix res = a.solve_w_LUP(b);
    res.print();

    Matrix lup = a.LUP_decomp().first;
    std::cout << lup.det_w_LUP() << std::endl;;

    (a.inverse()).print();

    return 0;
}
