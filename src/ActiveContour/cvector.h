#ifndef CVECTOR_H
#define CVECTOR_H

#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <cmath>

template <typename T>
class cvector : public std::vector<T>
{
public:
    using std::vector<T>::vector;
    cvector<T> operator+(const cvector<T> &v) const;
    cvector<T> operator+(const T value) const;
    cvector<T> operator-(const cvector<T> &v) const;
    cvector<T> operator-(const T value) const;
    cvector<T> operator*(const cvector<T> &v) const;
    cvector<T> operator*(const T value) const;
    cvector<T> operator/(const cvector<T> &v) const;
    cvector<T> operator/(const T value) const;
    T dot(const cvector<T> &v) const;
    T max() const;
    T min() const;
    cvector<T> abs() const;
    static cvector<double> mag(cvector<T> x, cvector<T> y);
    static cvector<double> phase(cvector<T> x, cvector<T> y);
    cvector<T> range(int start_row, int end_row, int start_col, int end_col) const;
    cvector<cvector<T>> to_2d(size_t rows, size_t cols) const;
    int mean(void) const;
    int median(void);
    friend std::ostream &operator<<(std::ostream &os, const cvector<T> &v)
    {
        os << "{ ";
        for (auto itr = v.begin(); itr != v.end(); itr++)
        {
            os << *itr << " ";
        }
        os << "}";
        return os;
    }
};

template <typename T>
cvector<T> cvector<T>::operator+(const cvector<T> &v) const
{
    if (this->size() != v.size())
    {
        throw "Vectors must have the same size";
    }
    cvector<T> vect;
    for (size_t i = 0; i < this->size(); i++)
    {
        vect.push_back(v[i] + this->operator[](i));
    }
    return vect;
}

template <typename T>
cvector<T> cvector<T>::operator+(const T value) const
{
    cvector<T> vect;
    for (auto itr = this->begin(); itr != this->end(); itr++)
    {
        vect.push_back((*itr) + value);
    }
    return vect;
}

template <typename T>
cvector<T> cvector<T>::operator-(const cvector<T> &v) const
{
    if (this->size() != v.size())
    {
        throw "Vectors must have the same size";
    }
    cvector<T> vect;
    for (size_t i = 0; i < this->size(); i++)
    {
        vect.push_back(v[i] - this->operator[](i));
    }
    return vect;
}

template <typename T>
cvector<T> cvector<T>::operator-(const T value) const
{
    return this->operator+(-value);
}

template <typename T>
cvector<T> cvector<T>::operator*(const cvector<T> &v) const
{
    if (this->size() != v.size())
    {
        throw "Vectors must have the same size";
    }
    cvector<T> vect;
    for (size_t i = 0; i < this->size(); i++)
    {
        vect.push_back(v[i] * this->operator[](i));
    }
    return vect;
}

template <typename T>
cvector<T> cvector<T>::operator*(const T value) const
{
    cvector<T> vect;
    for (auto itr = this->begin(); itr != this->end(); itr++)
    {
        vect.push_back((*itr) * value);
    }
    return vect;
}

template <typename T>
cvector<T> cvector<T>::operator/(const cvector<T> &v) const
{
    if (this->size() != v.size())
    {
        throw "Vectors must have the same size";
    }
    cvector<T> vect;
    for (size_t i = 0; i < this->size(); i++)
    {
        vect.push_back(v[i] / this->operator[](i));
    }
    return vect;
}

template <typename T>
cvector<T> cvector<T>::operator/(const T value) const
{
    return this->operator*(1 / value);
}

template <typename T>
T cvector<T>::dot(const cvector<T> &v) const
{
    if (this->size() != v.size())
    {
        throw "Vectors must have the same size";
    }
    T sum = 0;
    for (size_t i = 0; i < this->size(); i++)
    {
        sum += this->operator[](i) * v[i];
    }
    return sum;
}

template <typename T>
cvector<T> cvector<T>::range(int start_row, int end_row, int start_col, int end_col) const
{
    start_row = start_row < 0 ? 0 : start_row;
    start_col = start_col < 0 ? 0 : start_col;
    end_row = end_row > this->size() ? this->size() : end_row;
    end_col = end_col > this->operator[](0).size() ? this->operator[](0).size() : end_col;
    cvector<T> v;
    for (int i = start_row; i < end_row; i++)
    {
        T row;
        for (int j = start_col; j < end_col; j++)
        {
            row.push_back(this->operator[](i)[j]);
        }
        v.push_back(row);
    }
    return v;
}
template <typename T>
cvector<cvector<T>> cvector<T>::to_2d(size_t rows, size_t cols) const
{
    cvector<cvector<T>> matrix(rows, cvector<T>(cols));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = this->operator[](j + (cols * i));
        }
    }
    return matrix;
}

template <typename T>
cvector<T> cvector<T>::abs() const
{
    cvector<T> vect;
    for (auto itr = this->begin(); itr != this->end(); itr++)
    {
        vect.push_back(std::abs(*itr));
    }
    return vect;
}

template <typename T>
T cvector<T>::max() const
{
    return *std::max_element(this->begin(), this->end());
}

template <typename T>
T cvector<T>::min() const
{
    return *std::min_element(this->begin(), this->end());
}

template <typename T>
cvector<double> cvector<T>::mag(cvector<T> x, cvector<T> y)
{
    if (x.size() != y.size())
    {
        throw "Vectors must have the same size";
    }
    cvector<double> v;
    for (int i = 0; i < x.size(); i++)
    {
        v.push_back(std::sqrt(x[i] * x[i] + y[i] * y[i]));
    }
    return v;
}

template <typename T>
cvector<double> cvector<T>::phase(cvector<T> x, cvector<T> y)
{
    if (x.size() != y.size())
    {
        throw "Vectors must have the same size";
    }
    cvector<double> v;
    for (int i = 0; i < x.size(); i++)
    {
        v.push_back(std::atan2(y[i], x[i]));
    }
    return v;
}

// T cvector<T>::mean() const
template <typename T>
int cvector<T>::mean(void) const
{
    double mean_value = 0 ;
    for (size_t i = 0; i < this->size(); i++)
    {
            mean_value += this->operator[](i);
    }
    mean_value = (mean_value/this->size());
    return (int) mean_value;
}
template <typename T>
int cvector<T>::median(void)
{   int median;
    size_t n = this->size() / 2;
    std::nth_element(this->begin(), this->begin()+n, this->end());
    median = this->operator[](n);
    return median;
}
#endif
