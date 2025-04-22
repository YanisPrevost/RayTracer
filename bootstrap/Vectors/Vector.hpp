/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Vector.hpp
*/

#pragma once
#include <cmath>
#include <iostream>
#include <initializer_list>

namespace Math {
    template<size_t N>
    class Vector {
        private:
            double components[N];
        public:
            Vector();
            Vector(const std::initializer_list<double>& values);
            double& operator[](size_t index);
            const double& operator[](size_t index) const;

            double length() const;
            double dot(const Vector<N>& other) const;

            Vector<N> operator+(const Vector<N>& other) const;
            Vector<N>& operator+=(const Vector<N>& other);

            Vector<N> operator-(const Vector<N>& other) const;
            Vector<N>& operator-=(const Vector<N>& other);

            Vector<N> operator*(const Vector<N>& other) const;
            Vector<N>& operator*=(const Vector<N>& other);

            Vector<N> operator/(const Vector<N>& other) const;
            Vector<N>& operator/=(const Vector<N>& other);

            Vector<N> operator*(double scalar) const;
            Vector<N>& operator*=(double scalar);

            Vector<N> operator/(double scalar) const;
            Vector<N>& operator/=(double scalar);
        };
    template<size_t N>
    Vector<N> operator*(double scalar, const Vector<N>& vector);
}
