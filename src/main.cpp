#include "../include/matrix.h"

#include <iostream>



int main(){

    Matrix a("../inout/b.txt");
    a.print();
    a.save("../inout/b.txt");

    return 0;
}
