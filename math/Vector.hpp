#pragma once

#include <iostream>

template <class T = double, int size = 3>
class Vector {
public:
    Vector() {
        data = new T[size];
        for (int i = 0; i < size; i ++) {
            data[i] = T();
        }
    };
    Vector(T val) {
        data = new T[size];
        for (int i = 0; i < size; i ++) {
            data[i] = T(val);
        }
    };
    Vector(std::initializer_list<T> list) {
        data = new T[list.size()];
        int i = 0;
        for (auto& elem : list) {
            data[i] = elem;
            i ++;
        }
    }
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
    Vector& operator=(const Vector<T, size>& vec) {
        if (this == &vec) {
            return *this;
        }
        delete data;
        data = new T[size];
        for (int i = 0; i < size; i ++) {
            data[i] = vec[i];
        }
        return *this;
    }
    Vector& operator=(Vector<T, size>&& vec) {
        if (this == &vec) {
            return *this;
        }
        delete data;
        data = new T[size];
        for (int i = 0; i < size; i ++) {
            data[i] = vec[i];
        }
        return *this;
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
    Vector operator-() const {
        Vector<T, size> res;
        for (int i = 0; i < size; i ++) {
            res[i] = -data[i];
        }
        return res;
    }
    Vector operator+(const Vector<T, size>& other) const {
        Vector<T, size> res;
        for (int i = 0; i < size; i ++) {
            res[i] = data[i] + other[i];
        }
        return res;
    }
    Vector operator-(const Vector<T, size>& other) const {
        return *this + (-other);
    }
    Vector& operator+=(const Vector<T, size> &other) {
        *this = *this + other;
        return *this;
    }
    Vector& operator-=(const Vector<T, size> &other) {
        *this = *this - other;
        return *this;
    }
    template <class D>
    Vector operator*(D&& other) const {
        Vector<T, size> res;
        for (int i = 0; i < size; i ++) {
            res[i] = data[i] * other;
        }
        return res;
    }
    
    T dot(const Vector<T, size>& other) const {
        T res = T();
        for (int i = 0; i < size; i ++) {
            res += data[i] * other[i];
        }
        return res;
    }
    
    auto sqrnorm() const {
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
using Vector2d = Vector<double, 2>;