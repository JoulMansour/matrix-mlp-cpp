#include "Matrix.h"
#include <cmath>

#define SIZE_ERROR "Invalid matrix size"
#define SIZES_ERROR "invalid matrix sizes"
#define RANGE_ERROR "given indexes are out of range"
#define DATA_ERROR "not enough data to fill the matrix"
#define READING_ERROR "could not read data"
#define NUM_1 1


Matrix::Matrix(int rows, int cols) : rows{rows}, cols{cols} {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument(SIZE_ERROR);
    }
    data = new float *[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new float[cols];
        for (int j = 0; j < cols; j++) {
            data[i][j] = 0.0f;
        }
    }
}

Matrix::Matrix() : rows{NUM_1}, cols{NUM_1} {
    data = new float *[NUM_1];
    data[0] = new float[NUM_1];
    data[0][0] = 0;
}

Matrix::Matrix(const Matrix &m) : rows{m.rows}, cols{m.cols} {
    data = new float *[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new float[cols];
        for (int j = 0; j < cols; j++) {
            data[i][j] = m.data[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < rows; i++) {
        delete[] data[i];
    }
    delete[] data;
}

int Matrix::get_rows() const {
    return rows;
}

int Matrix::get_cols() const {
    return cols;
}

Matrix &Matrix::transpose() {
    Matrix temp(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            temp.data[j][i] = data[i][j];
        }
    }
    *this = temp;
    return *this;
}

Matrix &Matrix::vectorize() {
    Matrix temp(rows * cols, 1);
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            temp.data[index][0] = data[i][j];
            index++;
        }
    }
    *this = temp;
    return *this;
}

void Matrix::plain_print() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::dot(const Matrix &m) const {
    if (rows != m.rows || cols != m.cols) {
        throw std::invalid_argument(SIZES_ERROR);
    }
    Matrix temp(rows, m.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j<cols; j++) {
            temp.data[i][j] = data[i][j] * m.data[i][j];
        }
    }
    return temp;
}

float Matrix::norm() const {
    float x = 2;
    float norms = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            norms += std::pow(data[i][j], x);
        }
    }
    return std::sqrt(norms);
}

void Matrix::swap_rows(int row1, int row2) {
    if (row1 != row2) {
        std::swap(data[row1], data[row2]);
    }
}

void Matrix::scale_row(int row, float factor) {
    for (int i = 0; i < cols; i++) {
        data[row][i] *= factor;
    }
}

void Matrix::subtract_multiple_of_row(int trgt_row,
    int src_row, float factor) {
    for (int i = 0; i < cols; i++) {
        data[trgt_row][i] -= factor * data[src_row][i];
    }
}

Matrix Matrix::rref() const {
    Matrix temp(*this);
    int place = 0;
    for (int r = 0; r < rows; r++) {
        if (place >= cols) break;
        int i = r;
        while (place < cols && temp.data[i][place] == 0) {
            i++;
            if (i == rows) {
                i = r;
                place++;
                if (place == cols) return temp;
            }
        }
        if (place < cols) temp.swap_rows(i, r);
        float pivot_value = temp.data[r][place];
        if (pivot_value != 0) {
            temp.scale_row(r, 1.0f / pivot_value);
        }
        for (int j = 0; j < rows; j++) {
            if (j != r) {
                float factor = temp.data[j][place];
                temp.subtract_multiple_of_row(j,
                    r, factor);
            }
        }
        place++;
    }
    return temp;
}

int Matrix::argmax() const {
    float max = (*this)[0];
    int index = 0;
    for (int i = 0; i < rows*cols; i++) {
        if ((*this)[i] > max) {
            max = (*this)[i];
            index = i;
        }
    }
    return index;
}

float Matrix::sum() const {
    float sum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum += data[i][j];
        }
    }
    return sum;
}

Matrix& Matrix::operator+=(const Matrix &m) {
    if (rows != m.rows || cols != m.cols) {
        throw std::invalid_argument(SIZES_ERROR);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] += m.data[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &m) const {
    if (rows != m.rows || cols != m.cols) {
        throw std::invalid_argument(SIZES_ERROR);
    }
    Matrix temp(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            temp.data[i][j] = data[i][j] + m.data[i][j];
        }
    }
    return temp;
}

Matrix& Matrix::operator=(const Matrix &m) {
    if (this == &m) {
        return *this;
    }
    for (int i = 0; i < rows; i++) {
        delete[] data[i];
    }
    delete[] data;
    rows = m.rows;
    cols = m.cols;
    data = new float *[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new float[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] = m.data[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix &m) const {
    if (cols != m.rows) {
        throw std::invalid_argument(SIZES_ERROR);
    }
    Matrix temp(rows, m.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            for (int k = 0; k < cols; k++) {
                temp.data[i][j] += data[i][k] * m.data[k][j];
            }
        }
    }
    return temp;
}

Matrix Matrix::operator*(float c) const {
    Matrix temp(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            temp.data[i][j] = data[i][j] * c;
        }
    }
    return temp;
}

Matrix operator*(float c, const Matrix &m) {
    Matrix temp(m.rows, m.cols);
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            temp.data[i][j] = m.data[i][j] * c;
        }
    }
    return temp;
}

float Matrix::operator()(int i, int j) const {
    if (i >= rows || j >= cols || i < 0 || j < 0) {
        throw std::out_of_range(RANGE_ERROR);
    }
    return data[i][j];
}

float& Matrix::operator()(int i, int j) {
    if (i >= rows || j >= cols || i < 0 || j < 0) {
        throw std::out_of_range(RANGE_ERROR);
    }
    return data[i][j];
}

float Matrix::operator[](int k) const {
    if (k >= rows*cols || k < 0) {
        throw std::out_of_range(RANGE_ERROR);
    }
    int row = k/cols;
    int col = k % cols;
    return data[row][col];
}

float& Matrix::operator[](int k) {
    if (k >= rows*cols || k < 0) {
        throw std::out_of_range(RANGE_ERROR);
    }
    int row = k/cols;
    int col = k % cols;
    return data[row][col];
}

std::ostream& operator<<(std::ostream &os, const Matrix &m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            if (m.data[i][j] > 0.1) {
                os << "**";
            } else {
                os << "  ";
            }
        }
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream &is, Matrix &m) {
    std::istream::pos_type start_pos = is.tellg();
    size_t total_elements = m.rows * m.cols;
    size_t total_bytes = total_elements * sizeof(float);
    is.seekg(0, std::ios_base::end);
    std::istream::pos_type end_pos = is.tellg();
    if (end_pos - start_pos < static_cast<std::streamsize>(total_bytes)) {
        throw std::runtime_error(DATA_ERROR);
    }
    is.seekg(start_pos, std::ios_base::beg);
    for (int i = 0; i < m.rows; ++i) {
        if (!is.read(reinterpret_cast<char*>(m.data[i]),
            m.cols * sizeof(float))) {
            throw std::runtime_error(READING_ERROR);
        }
    }
    return is;
}


