/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Vector.tpp
*/

#include "Vector.hpp"

namespace Math {

    template<size_t N>
    Vector<N>::Vector() {
        for (size_t i = 0; i < N; i++) {
            components[i] = 0.0;
        }
    }

    template<size_t N>
    Vector<N>::Vector(const std::initializer_list<double>& values) {
        size_t i = 0;
        for (auto it = values.begin(); it != values.end() && i < N; it++, i++) {
            components[i] = *it;
        }
        for (; i < N; i++) {
            components[i] = 0.0;
        }
    }

    template<size_t N>
    double& Vector<N>::operator[](size_t index) {
        return components[index];
    }

    template<size_t N>
    const double& Vector<N>::operator[](size_t index) const {
        return components[index];
    }

    template<size_t N>
    double Vector<N>::length() const {
        double sum = 0.0;
        for (size_t i = 0; i < N; i++) {
            sum += components[i] * components[i];
        }
        return std::sqrt(sum);
    }

    template<size_t N>
    double Vector<N>::dot(const Vector<N>& other) const {
        double sum = 0.0;
        for (size_t i = 0; i < N; i++) {
            sum += components[i] * other.components[i];
        }
        return sum;
    }

    template<size_t N>
    Vector<N> Vector<N>::operator+(const Vector<N>& other) const {
        Vector<N> result;
        for (size_t i = 0; i < N; i++) {
            result.components[i] = components[i] + other.components[i];
        }
        return result;
    }

    template<size_t N>
    Vector<N>& Vector<N>::operator+=(const Vector<N>& other) {
        for (size_t i = 0; i < N; i++) {
            components[i] += other.components[i];
        }
        return *this;
    }

    template<size_t N>
    Vector<N> Vector<N>::operator-(const Vector<N>& other) const {
        Vector<N> result;
        for (size_t i = 0; i < N; i++) {
            result.components[i] = components[i] - other.components[i];
        }
        return result;
    }

    template<size_t N>
    Vector<N>& Vector<N>::operator-=(const Vector<N>& other) {
        for (size_t i = 0; i < N; i++) {
            components[i] -= other.components[i];
        }
        return *this;
    }

    template<size_t N>
    Vector<N> Vector<N>::operator*(const Vector<N>& other) const {
        Vector<N> result;
        for (size_t i = 0; i < N; i++) {
            result.components[i] = components[i] * other.components[i];
        }
        return result;
    }

    template<size_t N>
    Vector<N>& Vector<N>::operator*=(const Vector<N>& other) {
        for (size_t i = 0; i < N; i++) {
            components[i] *= other.components[i];
        }
        return *this;
    }

    template<size_t N>
    Vector<N> Vector<N>::operator/(const Vector<N>& other) const {
        Vector<N> result;
        for (size_t i = 0; i < N; i++) {
            result.components[i] = components[i] / other.components[i];
        }
        return result;
    }

    template<size_t N>
    Vector<N>& Vector<N>::operator/=(const Vector<N>& other) {
        for (size_t i = 0; i < N; i++) {
            components[i] /= other.components[i];
        }
        return *this;
    }

    template<size_t N>
    Vector<N> Vector<N>::operator*(double scalar) const {
        Vector<N> result;
        for (size_t i = 0; i < N; i++) {
            result.components[i] = components[i] * scalar;
        }
        return result;
    }

    template<size_t N>
    Vector<N>& Vector<N>::operator*=(double scalar) {
        for (size_t i = 0; i < N; i++) {
            components[i] *= scalar;
        }
        return *this;
    }

    template<size_t N>
    Vector<N> Vector<N>::operator/(double scalar) const {
        Vector<N> result;
        for (size_t i = 0; i < N; i++) {
            result.components[i] = components[i] / scalar;
        }
        return result;
    }

    template<size_t N>
    Vector<N>& Vector<N>::operator/=(double scalar) {
        for (size_t i = 0; i < N; i++) {
            components[i] /= scalar;
        }
        return *this;
    }

    template<size_t N>
    Vector<N> operator*(double scalar, const Vector<N>& vector) {
        return vector * scalar;
    }
}
