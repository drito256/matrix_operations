#include "../include/matrix.h"

#include <iostream>



int main(){

    Matrix a("../inout/a.txt");
    Matrix b("../inout/b.txt");
    Matrix lu_a = a.LU_decomp();
    lu_a.print();
    Matrix sups = lu_a.sups_forward(b);
    sups.print();
    

    return 0;
}
