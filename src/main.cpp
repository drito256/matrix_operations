#include "../include/matrix.h"

#include <iostream>



int main(){

    Matrix a("../inout/a.txt");
    Matrix b("../inout/b.txt");
    Matrix lup_a = a.LUP_decomp();
    (a * b).print();

//    lup_a.print();
    /*Matrix sups = lu_a.sups_forward(b);
    sups.print();
    Matrix sups2 = lu_a.sups_backward(sups);
    sups2.print();*/

//    a.solve_w_LU();
    

    return 0;
}
