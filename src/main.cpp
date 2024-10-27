#include "../include/matrix.h"

#include <iostream>
#include <stdexcept>



int main(){
    
    // zad2
    std::cout << "============================ZAD2=================================\n";
    Matrix a("../inout/zad2/a.txt");
    Matrix b("../inout/zad2/b.txt");
    Matrix x1(0,0,nullptr);
    Matrix x2(0,0,nullptr);
    try{    
        x1 = a.solve_w_LU(b);
        std::cout << "Solution with LU decomp:\n";
        x1.print();
    }
    catch(std::runtime_error){
        std::cout << "ERROR: Found 0 on pivot element\n";
    }
    try{
        std::cout << "-----------------------------------------------------------------\n";
        x2 = a.solve_w_LUP(b);
        std::cout << "Solution With LUP decomp:\n";
        x2.print();
    }
    catch(std::runtime_error){
        std::cout << "ERROR: Found 0 on pivot element\n";
    }
    std::cout << "=================================================================\n\n";

    
    // zad3
    std::cout << "============================ZAD3=================================\n";
    a.read_file("../inout/zad3/a.txt");
    b.read_file("../inout/zad3/b.txt");
    try{
        Matrix lu = a.LU_decomp();
        std::cout << "LU decomp:\n";
        lu.print();
    }
    catch(std::runtime_error){
        std::cout << "ERROR: Found 0 on pivot element\n";
    }

    try{
        std::pair<Matrix, Matrix> lup = a.LUP_decomp();
        
        std::cout << "-----------------------------------------------------------------\n";
        std::cout << "LUP decomp:\n";
        (lup.first).print();
        std::cout << "-----------------------------------------------------------------\n\n";
    }
    catch(std::runtime_error){
        std::cout << "ERROR: Found 0 on pivot element\n";
    }
    
    try{
    x1 = a.solve_w_LU(b);
    std::cout << "Solution with LU decomp:\n";
    x1.print();
    std::cout << "-----------------------------------------------------------------\n";
    }
    catch(std::runtime_error){
        std::cout << "ERROR: Found 0 on pivot element\n";
    }
    
    try{ 
        x2 = a.solve_w_LUP(b);
        std::cout << "Solution with LUP decomp:\n";
        x2.print();
        std::cout << "=================================================================\n\n";
    }
    catch(std::runtime_error){
        std::cout << "ERROR: Found 0 on pivot element\n";
    }

    // zad4
    std::cout << "============================ZAD4=================================\n";
    a.read_file("../inout/zad4/a.txt");
    b.read_file("../inout/zad4/b.txt");
    try{
        x1 = a.solve_w_LU(b);
        std::cout << "Solution with LU decomp:\n";
        x1.print();

    }catch(std::runtime_error){
        std::cout << "ERROR : Found 0 on pivot element\n";
    }
    try{
        x2 = a.solve_w_LUP(b);
        std::cout << "-----------------------------------------------------------------\n";
        std::cout << "Solution With LUP decomp:\n";
        x2.print();
    }catch(std::runtime_error){
        std::cout << "ERROR: Found 0 on pivot element\n";
    }
    std::cout << "=================================================================\n\n";

    // zad5
    std::cout << "============================ZAD5=================================\n";
    a.read_file("../inout/zad5/a.txt");
    b.read_file("../inout/zad5/b.txt");
    try{
        x1 = a.solve_w_LU(b);
        std::cout << "Solution with LU decomp:\n";
        x1.print();

    }catch(std::runtime_error){
        std::cout << "ERROR: Found 0 on pivot element\n";
    }
    try{
        x2 = a.solve_w_LUP(b);
        std::cout << "-----------------------------------------------------------------\n";
        std::cout << "Solution With LUP decomp:\n";
        x2.print();
    }catch(std::runtime_error){
        std::cout << "ERROR: Found 0 on pivot element\n";
    }
    std::cout << "=================================================================\n\n";

    // zad6
    std::cout << "============================ZAD6=================================\n";
    a.read_file("../inout/zad6/a.txt");
    b.read_file("../inout/zad6/b.txt");
    try{
    x1 = a.solve_w_LU(b);
    std::cout << "Solution with LU decomp:\n";
    x1.print();
    }catch(std::runtime_error){
        std::cout << "ERROR: Found 0 on pivot element\n";
    }
    try{
        x2 = a.solve_w_LUP(b);
        std::cout << "-----------------------------------------------------------------\n";
        std::cout << "Solution With LUP decomp:\n";
        x2.print();
    }catch(std::runtime_error){
        std::cout << "ERROR: Found 0 on pivot element\n";
    }
    std::cout << "=================================================================\n\n";

    // zad7
    std::cout << "============================ZAD7=================================\n";
    a.read_file("../inout/zad7/a.txt");
    Matrix inverse(0,0,nullptr);
    try{
        inverse = a.inverse();
        std::cout << "Matrix inverse:\n";
        inverse.print();
    }catch(std::runtime_error){
        std::cout << "ERROR: Found 0 on pivot element\n";
    }
    std::cout << "=================================================================\n\n";

    // zad8
    std::cout << "============================ZAD8=================================\n";
    a.read_file("../inout/zad8/a.txt");
    try{
        inverse = a.inverse();
        std::cout << "Matrix inverse:\n";
        inverse.print();
    }catch(std::runtime_error){
        std::cout << "ERROR: Found 0 on pivot element\n";
    }
    std::cout << "=================================================================\n\n";

    // zad9
    std::cout << "============================ZAD9=================================\n";
    a.read_file("../inout/zad9/a.txt");
    double det = 0;
    try{
        det = a.det();
        std::cout << "Matrix determinant:\n";
        std::cout << det << "\n";
    }catch(std::runtime_error){
        std::cout << "ERROR: Found 0 on pivot element\n";
    }
    std::cout << "=================================================================\n\n";

    // zad10
    std::cout << "============================ZAD10=================================\n";
    a.read_file("../inout/zad10/a.txt");
    try{
        det = a.det();
        std::cout << "Matrix determinant:\n";
        std::cout << det << "\n";
    }catch(std::runtime_error){
        std::cout << "ERROR: Found 0 on pivot element\n";
    }
    std::cout << "=================================================================\n\n";

    return 0;
}
