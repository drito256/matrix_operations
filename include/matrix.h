#ifndef MATRIX_H
#define MATRIX_H

#include "helper.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string_view>
#include <iomanip>

class Matrix{
    public:
        Matrix(size_t rows, size_t columns, std::unique_ptr<double[]> data); // ili mozda shared_ptr?
        Matrix(const std::string& filename);
        Matrix(const Matrix& other);
        Matrix() = delete;
       ~Matrix() = default;

       size_t getRows();
       size_t getColumns();
    
       void print();
       void save(const std::string& filename);
       void read_file(const std::string& filename);

       // ostale metode za supstituciju , dekompoziciju, determinantu
       Matrix transpose();
       Matrix inverse();
       Matrix det();
       Matrix sups_backward();
       Matrix sups_forward();
       Matrix LU_decomp();
       Matrix LUP_decomp();

       // assignment operator
       Matrix& operator=(const Matrix& matrix);

       // arithmetic operators
       Matrix& operator+=(const Matrix& m1);
       Matrix& operator-=(const Matrix& m1);
       Matrix& operator*=(const double scalar);
       Matrix& operator/=(const double scalar);
       
       double operator()(int row, int col) const;
       double& operator()(int row, int col);
       
       // comparison operator
       friend bool operator==(const Matrix& m1, const Matrix& m2);
       
       //arithemtic operators
       friend Matrix operator+(const Matrix& m1, const Matrix& m2);
       friend Matrix operator-(const Matrix& m1, const Matrix& m2);
       friend Matrix operator*(const Matrix& m1, const Matrix& m2);
       friend Matrix operator*(const Matrix& m, const double scalar);

    private:
        size_t m_rows, m_columns;
        std::unique_ptr<double[]> m_data; // mozda shared
};

#endif
