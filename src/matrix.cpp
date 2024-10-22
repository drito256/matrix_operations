#include "../include/matrix.h"
#include <stdexcept>

Matrix::Matrix(size_t rows, size_t columns, std::unique_ptr<double[]> data)
            : m_rows(rows)
            , m_columns(columns)
            , m_data(std::move(data))
{
}

Matrix::Matrix(const std::string& filename){
    read_file(filename);
}
  
// Copy constructor (deep copy)
Matrix::Matrix(const Matrix& other) : m_rows(other.m_rows), m_columns(other.m_columns), 
                              m_data(std::make_unique<double[]>(other.m_rows * other.m_columns)) {
    // Copy the data from the other matrix
    for (int i = 0; i < m_rows * m_columns; ++i) {
        m_data[i] = other.m_data[i];
    }
}

void Matrix::read_file(const std::string& filename){
    std::ifstream input_file(filename);

    if(!input_file.is_open()){
        std::cerr << "ERROR: couldn't open file\n";
        std::exit(1);
    }

    std::string line;
    size_t rows = 0;
    size_t columns = 0;
    std::vector<double> file_data;
        
    while(getline(input_file, line)){

        std::vector line_data = split_line(line);
        columns = line_data.size();
        for(int i=0;i<line_data.size();i++){
            file_data.push_back(line_data[i]);
        }
        rows++;
    }

    this->m_columns = columns;
    this->m_rows = rows;
    this->m_data = std::make_unique<double[]>(file_data.size());
    
    for(int i=0;i<file_data.size();i++){
        m_data[i] = file_data[i];
    }

}

size_t Matrix::getRows() const{
    return this->m_rows;
}
size_t Matrix::getColumns() const{
    return this->m_columns;
}

double Matrix::operator()(int row, int col) const{
    return m_data[m_columns * row + col];

}
double& Matrix::operator()(int row, int col){
    return m_data[m_columns * row + col];
}

void Matrix::print() const{
    for(int i=0;i<m_rows;i++){
        std::cout << "|";
        for(int j=0;j<m_columns;j++){
            std::cout << std::setw(5) << this->m_data[i * m_columns + j] << " ";
        }
        std::cout << "|\n";
    }
}

void Matrix::save(const std::string& filename){
    std::ofstream output_file(filename);
    if(!output_file.is_open()){
        std::cerr << "ERROR: couldnt open file\n";
    }
    for(int i=0;i<m_rows;i++){
        for(int j=0;j<m_columns;j++){
            output_file << this->m_data[i * m_columns + j] << " ";
        }
        output_file << "\n";
    }

}

Matrix& Matrix::operator=(const Matrix& matrix){
    // Check for self-assignment
    if (this == &matrix) {
        return *this;
    }

    // If the dimensions are different, reallocate memory
    if (m_rows != matrix.m_rows || m_columns != matrix.m_columns) {
        // Resize the matrix by allocating new memory for the data
        m_rows = matrix.m_rows;
        m_columns = matrix.m_columns;
        m_data = std::make_unique<double[]>(m_rows * m_columns);
    }

    // Copy the elements from the source matrix
    for (int i = 0; i < m_rows * m_columns; ++i) {
        m_data[i] = matrix.m_data[i];
    }

    return *this;  // Return *this to allow chained assignments
}

bool operator==(const Matrix &m1 ,const Matrix& m2){
    if(m1.m_rows != m2.m_rows || m1.m_columns != m2.m_columns){
        throw std::invalid_argument("Matrices must be same dimension");
    }

    for(int i=0;i<m1.m_rows;i++){
        for(int j=0;j<m1.m_columns;j++){
            if(m1.m_data[i*m1.m_columns + j] != m2.m_data[i*m2.m_columns + j]){
                return false;
            }
        }
    }
    return true;
}

Matrix operator+(const Matrix& m1, const Matrix& m2){
    if(m1.m_rows != m2.m_rows || m1.m_columns != m2.m_columns){
        throw std::invalid_argument("Matrices must be same dimension");
    }

    Matrix result(m1.m_rows, m1.m_columns, std::make_unique<double[]>(m1.m_rows * m1.m_columns));

    for(int i=0;i<m1.m_rows;i++){
        for(int j=0;j<m1.m_columns;j++){
            result.m_data[i * m1.m_columns + j] = m1.m_data[i * m1.m_columns + j] + 
                                                  m2.m_data[i * m2.m_columns + j];
        }
    }
    return result;
}

Matrix operator-(const Matrix& m1, const Matrix& m2){
    if(m1.m_rows != m2.m_rows || m1.m_columns != m2.m_columns){
        throw std::invalid_argument("Matrices must be same dimension");
    }

    Matrix result(m1.m_rows, m1.m_columns, std::make_unique<double[]>(m1.m_rows * m1.m_columns));

    for(int i=0;i<m1.m_rows;i++){
        for(int j=0;j<m1.m_columns;j++){
            result.m_data[i*m1.m_columns + j] = m1.m_data[i*m1.m_rows + j];
        }
    }
    return result;
}

Matrix operator*(const Matrix& m1, const double scalar){
    Matrix result(m1.m_rows, m1.m_columns, std::make_unique<double[]>(m1.m_rows * m1.m_columns));

    for(int i=0;i<m1.m_rows;i++){
        for(int j=0;j<m1.m_columns;j++){
            result.m_data[i*m1.m_columns + j] = m1.m_data[i*m1.m_rows + j] * scalar;
        }
    }
    return result;
}

Matrix& Matrix::operator+=(const Matrix& m){
    if(m_rows != m.m_rows || m_columns != m.m_columns){
        throw std::invalid_argument("Matrices must be same dimenstion");
    }

    for(int i=0;i<m_rows * m_columns;i++){
        m_data[i] += m.m_data[i];
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m){
    if(m_rows != m.m_rows || m_columns != m.m_columns){
        throw std::invalid_argument("Matrices must be same dimenstion");
    }

    for(int i=0;i<m_rows * m_columns;i++){
        m_data[i] -= m.m_data[i];
    }
    return *this;

}

Matrix& Matrix::operator*=(const double scalar){
      for(int i=0;i<m_rows * m_columns;i++){
        m_data[i] *= scalar;
    }
    return *this;
}

Matrix& Matrix::operator/=(const double scalar){
      for(int i=0;i<m_rows * m_columns;i++){
        m_data[i] /= scalar;
    }
    return *this;
}

Matrix operator*(const Matrix& m1, const Matrix& m2){
    if(m1.m_columns != m2.m_rows){
        throw std::invalid_argument("Matrices dimensions don't match");
    }

    Matrix result(m1.m_rows, m2.m_columns, std::make_unique<double[]>(m1.m_rows * m2.m_columns));
    for(int i=0;i<m1.m_rows;i++){
        for(int j=0;j<m2.m_columns;j++){
            result(i,j) = 0;
            for(int k=0;k<m1.m_columns;k++){
                result(i,j) += m1(i,k) * m2(k,j);
            }
        }
    }
    return result;
}

Matrix Matrix::transpose() const{
    Matrix res(this->m_rows, this->m_columns, std::make_unique<double[]>(this->m_rows * 
                                                                         this->m_columns));


    for (int i = 0; i < this->m_rows; i++) {
           for (int j = 0; j < this->m_columns; j++) {
               res.m_data[j * this->m_rows + i] = this->m_data[i * this->m_columns + j];
           }
    }

    return res;
}

Matrix Matrix::LU_decomp() const{
    if(this->m_rows != this->m_columns){
        throw std::invalid_argument("Matrix must be square");
    }
    Matrix res(this->m_rows, this->m_columns, std::make_unique<double[]>(this->m_rows * 
                                                                         this->m_columns));
    for(int i=0;i<m_rows * m_columns;i++){
        res.m_data[i] = this->m_data[i];
    }

    int n = m_columns; // or m_rows, doesnt matter
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            res(j,i) /= res(i,i); 
            for(int k=i+1;k<n;k++){
                res(j,k) -= res(j,i) * res(i,k);
            }
        }
    }
    return res;
}

Matrix Matrix::sups_forward(const Matrix& b) const{
    if(this->m_rows != this->m_columns){
        throw std::invalid_argument("Matrix must be square");
    }

    Matrix L(this->m_rows, this->m_columns, std::make_unique<double[]>(this->m_rows * 
                                                                       this->m_columns));
    Matrix res(this->m_rows, 1, std::make_unique<double[]>(this->m_rows));

    // extract L matrix
    int column_counter = 1;
    for(int i=0;i<m_rows;i++){
        for(int j=0;j<m_columns;j++){
            if(j < column_counter){
                L(i,j) = this->m_data[i * this->m_columns+ j];
            }
            else{
                L(i,j) = 0;
            }
        }
        column_counter++;
    }

    int n = m_columns;
    for(int i=0;i<n;i++){
        res.m_data[i] = b.m_data[i];

        for(int j=0;j<i;j++){
            res.m_data[i] -= L(i,j) * res.m_data[j];
        }
    }

    return res;
}
