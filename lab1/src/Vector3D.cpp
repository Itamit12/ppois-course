#include "Vector3D.h"

Vector3D::Vector3D() : x1_(0), y1_(0), z1_(0), x2_(0), y2_(0), z2_(0) {}

Vector3D::Vector3D(double x1, double y1, double z1, double x2, double y2, double z2)
    : x1_(x1), y1_(y1), z1_(z1), x2_(x2), y2_(y2), z2_(z2) {}

Vector3D::Vector3D(const Vector3D& other) = default;
Vector3D& Vector3D::operator=(const Vector3D& other) = default;

double Vector3D::getX1() const noexcept { return x1_; }
double Vector3D::getY1() const noexcept { return y1_; }
double Vector3D::getZ1() const noexcept { return z1_; }
double Vector3D::getX2() const noexcept { return x2_; }
double Vector3D::getY2() const noexcept { return y2_; }
double Vector3D::getZ2() const noexcept { return z2_; }

double Vector3D::length() const noexcept {
    const double dx = x2_ - x1_;
    const double dy = y2_ - y1_;
    const double dz = z2_ - z1_;
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

double Vector3D::cosAngle(const Vector3D& other) const {
    const double dot = (x2_ - x1_)*(other.x2_ - other.x1_)
                     + (y2_ - y1_)*(other.y2_ - other.y1_)
                     + (z2_ - z1_)*(other.z2_ - other.z1_);
    const double len1 = length();
    const double len2 = other.length();
    if (len1 < EPSILON || len2 < EPSILON) {
        throw std::invalid_argument("Cannot compute angle with zero-length vector");
    }
    return dot / (len1 * len2);
}

Vector3D Vector3D::operator+(const Vector3D& other) const {
    return {x1_, y1_, z1_,
            x2_ + (other.x2_ - other.x1_),
            y2_ + (other.y2_ - other.y1_),
            z2_ + (other.z2_ - other.z1_)};
}
Vector3D& Vector3D::operator+=(const Vector3D& other) {
    x2_ += other.x2_ - other.x1_;
    y2_ += other.y2_ - other.y1_;
    z2_ += other.z2_ - other.z1_;
    return *this;
}

Vector3D Vector3D::operator-(const Vector3D& other) const {
    return {x1_, y1_, z1_,
            x2_ - (other.x2_ - other.x1_),
            y2_ - (other.y2_ - other.y1_),
            z2_ - (other.z2_ - other.z1_)};
}
Vector3D& Vector3D::operator-=(const Vector3D& other) {
    x2_ -= other.x2_ - other.x1_;
    y2_ -= other.y2_ - other.y1_;
    z2_ -= other.z2_ - other.z1_;
    return *this;
}

Vector3D Vector3D::operator*(const Vector3D& other) const {
    const double ax = x2_ - x1_, ay = y2_ - y1_, az = z2_ - z1_;
    const double bx = other.x2_ - other.x1_, by = other.y2_ - other.y1_, bz = other.z2_ - other.z1_;
    return {0, 0, 0,
            ay*bz - az*by,
            az*bx - ax*bz,
            ax*by - ay*bx};
}
Vector3D& Vector3D::operator*=(const Vector3D& other) {
    *this = *this * other;
    return *this;
}

Vector3D Vector3D::operator*(double scalar) const {
    return {x1_, y1_, z1_,
            x1_ + (x2_ - x1_)*scalar,
            y1_ + (y2_ - y1_)*scalar,
            z1_ + (z2_ - z1_)*scalar};
}
Vector3D& Vector3D::operator*=(double scalar) {
    x2_ = x1_ + (x2_ - x1_)*scalar;
    y2_ = y1_ + (y2_ - y1_)*scalar;
    z2_ = z1_ + (z2_ - z1_)*scalar;
    return *this;
}

Vector3D Vector3D::operator/(double scalar) const {
    if (std::abs(scalar) < EPSILON) throw std::invalid_argument("Division by zero");
    return *this * (1.0 / scalar);
}
Vector3D& Vector3D::operator/=(double scalar) {
    if (std::abs(scalar) < EPSILON) throw std::invalid_argument("Division by zero");
    *this *= (1.0 / scalar);
    return *this;
}

bool Vector3D::operator==(const Vector3D& other) const { return std::abs(length() - other.length()) < EPSILON; }
bool Vector3D::operator!=(const Vector3D& other) const { return !(*this == other); }
bool Vector3D::operator< (const Vector3D& other) const { return length() < other.length(); }
bool Vector3D::operator<=(const Vector3D& other) const { return length() <= other.length(); }
bool Vector3D::operator> (const Vector3D& other) const { return length() > other.length(); }
bool Vector3D::operator>=(const Vector3D& other) const { return length() >= other.length(); }

std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
    os << "(" << v.x1_ << ", " << v.y1_ << ", " << v.z1_ << ") -> ("
       << v.x2_ << ", " << v.y2_ << ", " << v.z2_ << ")";
    return os;
}
std::istream& operator>>(std::istream& is, Vector3D& v) {
    is >> v.x1_ >> v.y1_ >> v.z1_ >> v.x2_ >> v.y2_ >> v.z2_;
    return is;
}