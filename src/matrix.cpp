#include "../include/matrix.h"
#include <stdexcept>

Matrix::Matrix(size_t rows, size_t columns, std::unique_ptr<double[]> data)
            : m_rows(rows)
            , m_columns(columns)
            , m_data(std::move(data))
{
    m_swap_count = 0;
}

Matrix::Matrix(const std::string& filename){
    read_file(filename);
    m_swap_count = 0;
}
  
// Copy constructor (deep copy)
Matrix::Matrix(const Matrix& other) : m_rows(other.m_rows), m_columns(other.m_columns), 
                              m_data(std::make_unique<double[]>(other.m_rows * other.m_columns)) {
    // Copy the data from the other matrix
    for (int i = 0; i < m_rows * m_columns; ++i) {
        m_data[i] = other.m_data[i];
    }
    this->m_swap_count = other.m_swap_count;
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
            std::cout 
            << std::setprecision(4) 
            << std::setw(10) 
            <<  this->m_data[i * m_columns + j] << " ";
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
        m_swap_count = matrix.m_swap_count;
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
            if(compare(res(i,i), 0, 1e-9)){
                std::cerr << "Found 0 on pivot element when doing LU decomposition, "
                             "result may be incorrect";
                continue;
            }
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
    int column_counter = 0;
    for(int i=0;i<m_rows;i++){
        for(int j=0;j<m_columns;j++){
            if(j < column_counter){
                L(i,j) = this->m_data[i * this->m_columns+ j];
            }
            else if(j == column_counter){
                L(i,j) = 1;
            }
            else{
                L(i,j) = 0;
            }
        }
        column_counter++;
    }
    // std::cout << "L matrix" << std::endl;
    // L.print();
    

    // init
    for(int i=0;i<m_rows;i++){
        res.m_data[i] = b.m_data[i];
    }

    int n = m_columns;
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            res.m_data[j] -= L(j,i) * res.m_data[i];
        }
    }

    return res;
}

Matrix Matrix::sups_backward(const Matrix& y) const{
    if(this->m_rows != this->m_columns){
        throw std::invalid_argument("Matrix must be square");
    }

    Matrix U(this->m_rows, this->m_columns, std::make_unique<double[]>(this->m_rows * 
                                                                       this->m_columns));
    Matrix res(this->m_rows, 1, std::make_unique<double[]>(this->m_rows));

    // extract U matrix
    int column_counter = 0;
    for(int i=0;i<m_rows;i++){
        for(int j=0;j<m_columns;j++){
            if(j >= column_counter){
                U(i,j) = this->m_data[i * this->m_columns+ j];
            }
            else{
                U(i,j) = 0;
            }
        }
        column_counter++;
    }

//    std::cout << "U matrix" << std::endl;
//    U.print();
    
    // init
    for(int i=0;i<m_rows;i++){
        res.m_data[i] = y.m_data[i];
    }

    int n = m_columns;
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            res.m_data[i] -= U(i, j) * res.m_data[j];
        }
        res.m_data[i] /= U(i, i);
    }
    return res;
}

void Matrix::swap_rows(int row1, int row2){
    if(row1 >= this->m_rows || row2 >= this->m_rows){
        throw std::invalid_argument("One or both row indices specified larger than number of rows"
                                    "in matrix");
    }
    
    std::vector<double> temp_row;
    for(int i=0;i<this->m_columns;i++){
        temp_row.push_back(this->m_data[row1 * this->m_columns + i]);
    }

    for(int j=0;j<this->m_columns;j++){
        this->m_data[this->m_columns * row1 + j] = this->m_data[this->m_columns * row2 + j];
    }
    for(int j=0;j<this->m_columns;j++){
        this->m_data[this->m_columns * row2 + j] = temp_row[j];
    }
}

std::pair<Matrix, Matrix> Matrix::LUP_decomp() {
    if(this->m_rows != this->m_columns){
        throw std::invalid_argument("Matrix must be square");
    }

   
    Matrix LU(this->m_rows, this->m_columns, std::make_unique<double[]>(this->m_rows * 
                                                                         this->m_columns));
    Matrix P(this->m_rows, this->m_columns,std::make_unique<double[]>(this->m_rows *
                                                                      this->m_columns));
    
    for(int i=0;i<this->m_rows * this->m_columns;i++){
        LU.m_data[i] = this->m_data[i];
    }
    // set P to identity
    for(int i=0;i<this->m_rows;i++){
        for(int j=0;j<this->m_columns;j++){
            if(i == j){
                P.m_data[i * this->m_columns + j] = 1;
            }
            else {
                P.m_data[i * this->m_columns + j] = 0;
            }
        }
    }

    int n = m_columns; // or m_rows, doesnt matter since matrix is square
    for (int i = 0; i < n - 1; i++) {
        int pivot_row = i;
        double max_val = std::fabs(LU(i, i));
        for (int j = i + 1; j < n; j++) {
            if (std::fabs(LU(j, i)) > max_val) {
                pivot_row = j;
                max_val = std::fabs(LU(j, i));
            }
        }
        if(compare(max_val, 0, 1e-9)){
            std::cerr << "Found 0 on pivot element when doing LUP decomposition, "
                         "result may be incorrect";
            continue;
        }

        // swap rows
        if (pivot_row != i) {
            this->m_swap_count++;
            LU.swap_rows(i, pivot_row);
            P.swap_rows(i, pivot_row); 
        }

        // LU decomp
        for (int j = i + 1; j < n; j++) {
            LU(j, i) /= LU(i, i); 
            for (int k = i + 1; k < n; k++) {
                LU(j, k) -= LU(j, i) * LU(i, k);
            }
        }
    }
    
    return  std::pair<Matrix, Matrix>(LU,P);
}

Matrix Matrix::extract_L() const{
    Matrix L(this->m_rows, this->m_columns, std::make_unique<double[]>(this->m_rows *
                                                                       this->m_columns));
    for(int i=0;i<this->m_rows;i++){
        for(int j=0;j<this->m_columns;j++){
            if(j > i){
                L(i,j) = 0;
            }
            else if (j == i){
                L(i,j) = 1;
            }
            else{
                L(i,j) = this->m_data[i * this->m_columns + j];
            }
        }
    }
    return L;
}

Matrix Matrix::extract_U() const{
    Matrix U(this->m_rows, this->m_columns, std::make_unique<double[]>(this->m_rows *
                                                                       this->m_columns));

    for(int i=0;i<this->m_rows;i++){
        for(int j=0;j<this->m_columns;j++){
            if(j >= i){
                U(i,j) = this->m_data[i * this->m_columns + j];
            }
            else{
                U(i,j) = 0;
            }
        }
    }

    return U;
}

Matrix Matrix::solve_w_LU(const Matrix& vec)const {
    if(this->m_rows != this->m_columns){
        throw std::invalid_argument("Matrix must be square");
    }

    Matrix lu = LU_decomp();    
    Matrix l = lu.extract_L();
    Matrix u = lu.extract_U();

    Matrix y = l.sups_forward(vec);
    Matrix x = u.sups_backward(y); 
    return x;
}

// TODO
Matrix Matrix::solve_w_LUP(const Matrix& vec) {
    if(this->m_rows != this->m_columns){
        throw std::invalid_argument("Matrix must be square");
    }

    std::pair<Matrix,Matrix> lup = LUP_decomp();    
    Matrix l = lup.first.extract_L();
    Matrix u = lup.first.extract_U();

    Matrix b = lup.second  * vec;
    Matrix y = l.sups_forward(b);
    Matrix x = u.sups_backward(y); 
    return x;
}

double Matrix::det_w_LUP() const{
    double res = 1;

    Matrix u = extract_U();

    for(int i=0;i<u.m_rows;i++){
        res *= u(i,i);
    }

    res *= ((m_swap_count % 2 == 0) ? 1 : -1);
    return res;
}

/*Matrix Matrix::inverse() const{
}*/
