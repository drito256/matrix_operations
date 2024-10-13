#include "../include/matrix.h"

#include <iostream>



int main(){

    Matrix a("../inout/b.txt");
    a.print();
    a.save("../inout/b.txt");
    Matrix b = a;
    b.print();

    Matrix c = a + b;
    c += a;
    c.print();
    std::cout << c(2,2) << std::endl;

    return 0;
}
