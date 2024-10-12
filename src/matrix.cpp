#include "../include/matrix.h"

Matrix::Matrix(size_t rows, size_t columns, std::unique_ptr<double[]> data)
            : m_rows(rows)
            , m_columns(columns)
            , m_data(std::move(data))
{
}

Matrix::Matrix(const std::string& filename){
    std::ifstream input_file(filename);

    if(!input_file.is_open()){
        std::cerr << "ERROR : couldn't open file\n";
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

size_t Matrix::getRows(){
    return this->m_rows;
}
size_t Matrix::getColumns(){
    return this->m_columns;
}

void Matrix::print(){
    for(int i=0;i<this->getRows();i++){
        std::cout << "|";
        for(int j=0;j<this->getColumns();j++){
            std::cout << std::setw(5) << this->m_data[i * getColumns() + j] << " ";
        }
        std::cout << "|\n";
    }
}
