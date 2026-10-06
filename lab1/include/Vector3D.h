/**
 * @file Vector3D.h
 * @brief Класс для работы с вектором в трёхмерном пространстве.
 * @author Itamit
 * @date 2026
 */

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <cmath>
#include <stdexcept>

/**
 * @class Vector3D
 * @brief Вектор, заданный координатами концов в трёхмерном пространстве.
 */
class Vector3D {
private:
    static constexpr double EPSILON = 1e-9; ///< Точность сравнения
    double x1_, y1_, z1_; ///< Координаты начала
    double x2_, y2_, z2_; ///< Координаты конца

public:
    Vector3D();
    Vector3D(double x1, double y1, double z1, double x2, double y2, double z2);
    Vector3D(const Vector3D& other);
    Vector3D& operator=(const Vector3D& other);
    ~Vector3D() = default;

    [[nodiscard]] double getX1() const noexcept;
    [[nodiscard]] double getY1() const noexcept;
    [[nodiscard]] double getZ1() const noexcept;
    [[nodiscard]] double getX2() const noexcept;
    [[nodiscard]] double getY2() const noexcept;
    [[nodiscard]] double getZ2() const noexcept;

    [[nodiscard]] double length() const noexcept;
    [[nodiscard]] double cosAngle(const Vector3D& other) const;

    Vector3D operator+(const Vector3D& other) const;
    Vector3D& operator+=(const Vector3D& other);
    Vector3D operator-(const Vector3D& other) const;
    Vector3D& operator-=(const Vector3D& other);
    Vector3D operator*(const Vector3D& other) const;
    Vector3D& operator*=(const Vector3D& other);
    Vector3D operator*(double scalar) const;
    Vector3D& operator*=(double scalar);
    Vector3D operator/(double scalar) const;
    Vector3D& operator/=(double scalar);

    bool operator==(const Vector3D& other) const;
    bool operator!=(const Vector3D& other) const;
    bool operator<(const Vector3D& other) const;
    bool operator<=(const Vector3D& other) const;
    bool operator>(const Vector3D& other) const;
    bool operator>=(const Vector3D& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v);
    friend std::istream& operator>>(std::istream& is, Vector3D& v);
};

#endif // VECTOR3D_H