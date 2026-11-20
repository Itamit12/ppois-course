#include <gtest/gtest.h>
#include "Vector3D.h"
#include <sstream>
#include <stdexcept>

// ============ Constructors ============
TEST(Vector3DTest, DefaultConstructor) {
    Vector3D v;
    EXPECT_DOUBLE_EQ(v.getX1(), 0.0);
    EXPECT_DOUBLE_EQ(v.getY1(), 0.0);
    EXPECT_DOUBLE_EQ(v.getZ1(), 0.0);
    EXPECT_DOUBLE_EQ(v.getX2(), 0.0);
    EXPECT_DOUBLE_EQ(v.getY2(), 0.0);
    EXPECT_DOUBLE_EQ(v.getZ2(), 0.0);
    EXPECT_DOUBLE_EQ(v.length(), 0.0);
}

TEST(Vector3DTest, ParamConstructor) {
    Vector3D v(1, 2, 3, 4, 5, 6);
    EXPECT_DOUBLE_EQ(v.getX1(), 1.0);
    EXPECT_DOUBLE_EQ(v.getY1(), 2.0);
    EXPECT_DOUBLE_EQ(v.getZ1(), 3.0);
    EXPECT_DOUBLE_EQ(v.getX2(), 4.0);
    EXPECT_DOUBLE_EQ(v.getY2(), 5.0);
    EXPECT_DOUBLE_EQ(v.getZ2(), 6.0);
}

TEST(Vector3DTest, CopyConstructor) {
    Vector3D v1(1, 2, 3, 4, 5, 6);
    Vector3D v2(v1);
    EXPECT_DOUBLE_EQ(v2.getX1(), 1.0);
    EXPECT_DOUBLE_EQ(v2.getZ2(), 6.0);
}

TEST(Vector3DTest, AssignmentOperator) {
    Vector3D v1(1, 2, 3, 4, 5, 6);
    Vector3D v2;
    v2 = v1;
    EXPECT_DOUBLE_EQ(v2.getX1(), 1.0);
    EXPECT_DOUBLE_EQ(v2.getZ2(), 6.0);
}

TEST(Vector3DTest, SelfAssignment) {
    Vector3D v(1, 2, 3, 4, 5, 6);
    v = v;
    EXPECT_DOUBLE_EQ(v.getX1(), 1.0);
}

// ============ Length ============
TEST(Vector3DTest, Length345) {
    Vector3D v(0, 0, 0, 3, 4, 0);
    EXPECT_DOUBLE_EQ(v.length(), 5.0);
}

TEST(Vector3DTest, Length3D) {
    Vector3D v(0, 0, 0, 1, 2, 2);
    EXPECT_DOUBLE_EQ(v.length(), 3.0);
}

TEST(Vector3DTest, LengthZero) {
    Vector3D v;
    EXPECT_DOUBLE_EQ(v.length(), 0.0);
}

// ============ Addition ============
TEST(Vector3DTest, Addition) {
    Vector3D v1(0, 0, 0, 1, 0, 0);
    Vector3D v2(0, 0, 0, 0, 1, 0);
    Vector3D res = v1 + v2;
    EXPECT_DOUBLE_EQ(res.getX2(), 1.0);
    EXPECT_DOUBLE_EQ(res.getY2(), 1.0);
    EXPECT_DOUBLE_EQ(res.getZ2(), 0.0);
}

TEST(Vector3DTest, AdditionAssign) {
    Vector3D v1(0, 0, 0, 1, 0, 0);
    Vector3D v2(0, 0, 0, 0, 1, 0);
    v1 += v2;
    EXPECT_DOUBLE_EQ(v1.getX2(), 1.0);
    EXPECT_DOUBLE_EQ(v1.getY2(), 1.0);
}

// ============ Subtraction ============
TEST(Vector3DTest, Subtraction) {
    Vector3D v1(0, 0, 0, 1, 1, 1);
    Vector3D v2(0, 0, 0, 1, 0, 0);
    Vector3D res = v1 - v2;
    EXPECT_DOUBLE_EQ(res.getX2(), 0.0);
    EXPECT_DOUBLE_EQ(res.getY2(), 1.0);
    EXPECT_DOUBLE_EQ(res.getZ2(), 1.0);
}

TEST(Vector3DTest, SubtractionAssign) {
    Vector3D v1(0, 0, 0, 1, 1, 1);
    Vector3D v2(0, 0, 0, 1, 0, 0);
    v1 -= v2;
    EXPECT_DOUBLE_EQ(v1.getX2(), 0.0);
}

// ============ Cross product ============
TEST(Vector3DTest, CrossProduct) {
    Vector3D v1(0, 0, 0, 1, 0, 0);
    Vector3D v2(0, 0, 0, 0, 1, 0);
    Vector3D res = v1 * v2;
    EXPECT_DOUBLE_EQ(res.getX2(), 0.0);
    EXPECT_DOUBLE_EQ(res.getY2(), 0.0);
    EXPECT_DOUBLE_EQ(res.getZ2(), 1.0);
}

TEST(Vector3DTest, CrossProductAntiCommutative) {
    Vector3D v1(0, 0, 0, 1, 0, 0);
    Vector3D v2(0, 0, 0, 0, 1, 0);
    Vector3D res1 = v1 * v2;
    Vector3D res2 = v2 * v1;
    EXPECT_DOUBLE_EQ(res1.getZ2(), -res2.getZ2());
}

TEST(Vector3DTest, CrossProductAssign) {
    Vector3D v1(0, 0, 0, 1, 0, 0);
    Vector3D v2(0, 0, 0, 0, 1, 0);
    v1 *= v2;
    EXPECT_DOUBLE_EQ(v1.getZ2(), 1.0);
}

TEST(Vector3DTest, CrossProductParallelIsZero) {
    Vector3D v1(0, 0, 0, 1, 0, 0);
    Vector3D v2(0, 0, 0, 2, 0, 0);
    Vector3D res = v1 * v2;
    EXPECT_DOUBLE_EQ(res.length(), 0.0);
}

// ============ Scalar multiply ============
TEST(Vector3DTest, ScalarMultiply) {
    Vector3D v(0, 0, 0, 1, 2, 3);
    Vector3D res = v * 2.0;
    EXPECT_DOUBLE_EQ(res.getX2(), 2.0);
    EXPECT_DOUBLE_EQ(res.getY2(), 4.0);
    EXPECT_DOUBLE_EQ(res.getZ2(), 6.0);
}

TEST(Vector3DTest, ScalarMultiplyAssign) {
    Vector3D v(0, 0, 0, 1, 2, 3);
    v *= 2.0;
    EXPECT_DOUBLE_EQ(v.getX2(), 2.0);
    EXPECT_DOUBLE_EQ(v.getY2(), 4.0);
    EXPECT_DOUBLE_EQ(v.getZ2(), 6.0);
}

TEST(Vector3DTest, ScalarMultiplyByZero) {
    Vector3D v(0, 0, 0, 1, 2, 3);
    Vector3D res = v * 0.0;
    EXPECT_DOUBLE_EQ(res.length(), 0.0);
}

TEST(Vector3DTest, ScalarMultiplyByNegative) {
    Vector3D v(0, 0, 0, 1, 2, 3);
    Vector3D res = v * -1.0;
    EXPECT_DOUBLE_EQ(res.getX2(), -1.0);
    EXPECT_DOUBLE_EQ(res.getY2(), -2.0);
    EXPECT_DOUBLE_EQ(res.getZ2(), -3.0);
}

// ============ Scalar divide ============
TEST(Vector3DTest, ScalarDivide) {
    Vector3D v(0, 0, 0, 2, 4, 6);
    Vector3D res = v / 2.0;
    EXPECT_DOUBLE_EQ(res.getX2(), 1.0);
    EXPECT_DOUBLE_EQ(res.getY2(), 2.0);
    EXPECT_DOUBLE_EQ(res.getZ2(), 3.0);
}

TEST(Vector3DTest, ScalarDivideAssign) {
    Vector3D v(0, 0, 0, 2, 4, 6);
    v /= 2.0;
    EXPECT_DOUBLE_EQ(v.getX2(), 1.0);
}

TEST(Vector3DTest, DivisionByZeroThrows) {
    Vector3D v(0, 0, 0, 1, 1, 1);
    EXPECT_THROW(
        { auto res = v / 0.0; (void)res; },
        std::invalid_argument
    );
}

TEST(Vector3DTest, DivisionAssignByZeroThrows) {
    Vector3D v(0, 0, 0, 1, 1, 1);
    EXPECT_THROW(
        { v /= 0.0; },
        std::invalid_argument
    );
}

// ============ CosAngle ============
TEST(Vector3DTest, CosAngle90) {
    Vector3D v1(0, 0, 0, 1, 0, 0);
    Vector3D v2(0, 0, 0, 0, 1, 0);
    EXPECT_DOUBLE_EQ(v1.cosAngle(v2), 0.0);
}

TEST(Vector3DTest, CosAngle0) {
    Vector3D v1(0, 0, 0, 1, 0, 0);
    Vector3D v2(0, 0, 0, 2, 0, 0);
    EXPECT_DOUBLE_EQ(v1.cosAngle(v2), 1.0);
}

TEST(Vector3DTest, CosAngle180) {
    Vector3D v1(0, 0, 0, 1, 0, 0);
    Vector3D v2(0, 0, 0, -1, 0, 0);
    EXPECT_DOUBLE_EQ(v1.cosAngle(v2), -1.0);
}

TEST(Vector3DTest, CosAngleWithZeroFirstVectorThrows) {
    Vector3D v1;
    Vector3D v2(0, 0, 0, 1, 0, 0);
    EXPECT_THROW(v1.cosAngle(v2), std::invalid_argument);
}

TEST(Vector3DTest, CosAngleWithZeroSecondVectorThrows) {
    Vector3D v1(0, 0, 0, 1, 0, 0);
    Vector3D v2;
    EXPECT_THROW(v1.cosAngle(v2), std::invalid_argument);
}

TEST(Vector3DTest, CosAngleWithBothZeroThrows) {
    Vector3D v1;
    Vector3D v2;
    EXPECT_THROW(v1.cosAngle(v2), std::invalid_argument);
}

// ============ Comparison ============
TEST(Vector3DTest, ComparisonGreater) {
    Vector3D v1(0, 0, 0, 3, 4, 0);  // len 5
    Vector3D v2(0, 0, 0, 1, 0, 0);  // len 1
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v1 < v2);
    EXPECT_TRUE(v1 >= v2);
    EXPECT_FALSE(v1 <= v2);
    EXPECT_TRUE(v1 != v2);
    EXPECT_FALSE(v1 == v2);
}

TEST(Vector3DTest, ComparisonEqual) {
    Vector3D v1(0, 0, 0, 3, 4, 0);
    Vector3D v2(0, 0, 0, 0, 5, 0);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_TRUE(v1 >= v2);
    EXPECT_FALSE(v1 > v2);
    EXPECT_FALSE(v1 < v2);
}

TEST(Vector3DTest, ComparisonLess) {
    Vector3D v1(0, 0, 0, 1, 0, 0);
    Vector3D v2(0, 0, 0, 3, 4, 0);
    EXPECT_TRUE(v1 < v2);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_FALSE(v1 > v2);
    EXPECT_FALSE(v1 >= v2);
}

// ============ IO ============
TEST(Vector3DTest, OutputOperator) {
    Vector3D v(1, 2, 3, 4, 5, 6);
    std::ostringstream oss;
    oss << v;
    EXPECT_NE(oss.str().find("1"), std::string::npos);
    EXPECT_NE(oss.str().find("6"), std::string::npos);
}

TEST(Vector3DTest, InputOperator) {
    Vector3D v;
    std::istringstream iss("1 2 3 4 5 6");
    iss >> v;
    EXPECT_DOUBLE_EQ(v.getX1(), 1.0);
    EXPECT_DOUBLE_EQ(v.getY1(), 2.0);
    EXPECT_DOUBLE_EQ(v.getZ1(), 3.0);
    EXPECT_DOUBLE_EQ(v.getX2(), 4.0);
    EXPECT_DOUBLE_EQ(v.getY2(), 5.0);
    EXPECT_DOUBLE_EQ(v.getZ2(), 6.0);
}

TEST(Vector3DTest, AllGetters) {
    Vector3D v(1, 2, 3, 4, 5, 6);
    EXPECT_DOUBLE_EQ(v.getX1(), 1.0);
    EXPECT_DOUBLE_EQ(v.getY1(), 2.0);
    EXPECT_DOUBLE_EQ(v.getZ1(), 3.0);
    EXPECT_DOUBLE_EQ(v.getX2(), 4.0);
    EXPECT_DOUBLE_EQ(v.getY2(), 5.0);
    EXPECT_DOUBLE_EQ(v.getZ2(), 6.0);
}