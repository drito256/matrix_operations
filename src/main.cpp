#include "../include/matrix.h"

#include <iostream>



int main(){

    Matrix a("../inout/a.txt");
    a.print();
    Matrix b("../inout/b.txt");
    b.print();

    Matrix c = a * b;
    
    c.print();
    Matrix t = c.transpose();
    t.print();
    std::cout << c(2,2) << std::endl;

    return 0;
}
