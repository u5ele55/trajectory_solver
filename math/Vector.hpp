#pragma once

#include <iostream>

template <class T = double, int size = 3>
class Vector {
public:
    Vector() {
        data = new T[size];
        for (int i = 0; i < size; i ++) {
            data[i] = 0;
        }
    };
    Vector(const Vector<T, size>& vec) {
        data = new T[size];
        for (int i = 0; i < size; i ++) {
            data[i] = vec[i];
        }
    }
    Vector(Vector<T, size>&& vec) {
        data = new T[size];
        for (int i = 0; i < size; i ++) {
            data[i] = vec[i];
        }
    }
    Vector operator=(const Vector<T, size>& vec) {
        if (this == &vec) {
            return *this;
        }
        delete data;
        data = new T[size];
        for (int i = 0; i < size; i ++) {
            data[i] = vec[i];
        }
    }
    Vector operator=(Vector<T, size>&& vec) {
        if (this == &vec) {
            return *this;
        }
        delete data;
        data = new T[size];
        for (int i = 0; i < size; i ++) {
            data[i] = vec[i];
        }
    }
    ~Vector() {
        delete [] data;
    }
    T &operator[](int ind) {
        return data[ind];
    }
    T operator[](int ind) const {
        return data[ind];
    }
    Vector operator-(){
        Vector<T, size> res;
        for (int i = 0; i < size; i ++) {
            res[i] = -data[i];
        }
        return res;
    }
    Vector operator+(const Vector<T, size>& other) {
        Vector<T, size> res;
        for (int i = 0; i < size; i ++) {
            res[i] = data[i] + other[i];
        }
        return res;
    }
    Vector operator-(Vector<T, size>& other) {
        return *this + (-other);
    }
    Vector operator*(const Vector<T, size>& other) {
        Vector<T, size> res;
        for (int i = 0; i < size; i ++) {
            res[i] = data[i] * other[i];
        }
        return res;
    }
    auto sqrnorm() {
        auto res = data[0] * data[0];
        for (int i = 1; i < size; i ++) {
            res = res + data[i] * data[i];
        }
        return res;
    }

    friend std::ostream& operator<< (std::ostream& stream, const Vector& vector) {
        stream << "{ ";
        for (int i = 0; i < size; i ++) {
            stream << vector[i] << ' ';
        }
        stream << '}';
        return stream;
    }
private:
    T * data;
};  

using Vector3d = Vector<double, 3>;