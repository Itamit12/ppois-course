#include <gtest/gtest.h>
#include "Vector3D.h"
#include <stdexcept>

TEST(Vector3DTest, DefaultConstructor) {
    Vector3D v;
    EXPECT_DOUBLE_EQ(v.length(), 0.0);
}

TEST(Vector3DTest, ParamConstructor) {
    Vector3D v(1, 2, 3, 4, 5, 6);
    EXPECT_DOUBLE_EQ(v.getX1(), 1.0);
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
}

TEST(Vector3DTest, Length345) {
    Vector3D v(0, 0, 0, 3, 4, 0);
    EXPECT_DOUBLE_EQ(v.length(), 5.0);
}

TEST(Vector3DTest, Addition) {
    Vector3D v1(0, 0, 0, 1, 0, 0);
    Vector3D v2(0, 0, 0, 0, 1, 0);
    Vector3D res = v1 + v2;
    EXPECT_DOUBLE_EQ(res.getX2(), 1.0);
    EXPECT_DOUBLE_EQ(res.getY2(), 1.0);
}

TEST(Vector3DTest, Subtraction) {
    Vector3D v1(0, 0, 0, 1, 1, 1);
    Vector3D v2(0, 0, 0, 1, 0, 0);
    Vector3D res = v1 - v2;
    EXPECT_DOUBLE_EQ(res.getX2(), 0.0);
}

TEST(Vector3DTest, CrossProduct) {
    Vector3D v1(0, 0, 0, 1, 0, 0);
    Vector3D v2(0, 0, 0, 0, 1, 0);
    Vector3D res = v1 * v2;
    EXPECT_DOUBLE_EQ(res.getZ2(), 1.0);
}

TEST(Vector3DTest, ScalarMultiply) {
    Vector3D v(0, 0, 0, 1, 2, 3);
    Vector3D res = v * 2.0;
    EXPECT_DOUBLE_EQ(res.getX2(), 2.0);
    EXPECT_DOUBLE_EQ(res.getY2(), 4.0);
    EXPECT_DOUBLE_EQ(res.getZ2(), 6.0);
}

TEST(Vector3DTest, ScalarDivide) {
    Vector3D v(0, 0, 0, 2, 4, 6);
    Vector3D res = v / 2.0;
    EXPECT_DOUBLE_EQ(res.getX2(), 1.0);
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

TEST(Vector3DTest, CosAngleWithZeroVectorThrows) {
    Vector3D v1(0, 0, 0, 1, 0, 0);
    Vector3D v2;
    EXPECT_THROW(v1.cosAngle(v2), std::invalid_argument);
}

TEST(Vector3DTest, ComparisonGreater) {
    Vector3D v1(0, 0, 0, 3, 4, 0);
    Vector3D v2(0, 0, 0, 1, 0, 0);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v1 < v2);
}

TEST(Vector3DTest, ComparisonEqual) {
    Vector3D v1(0, 0, 0, 3, 4, 0);
    Vector3D v2(0, 0, 0, 0, 5, 0);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST(Vector3DTest, ComparisonLessEqual) {
    Vector3D v1(0, 0, 0, 1, 0, 0);
    Vector3D v2(0, 0, 0, 1, 0, 0);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_TRUE(v1 >= v2);
}

TEST(Vector3DTest, OutputOperator) {
    Vector3D v(1, 2, 3, 4, 5, 6);
    std::ostringstream oss;
    oss << v;
    EXPECT_NE(oss.str().find("1"), std::string::npos);
}

TEST(Vector3DTest, InputOperator) {
    Vector3D v;
    std::istringstream iss("1 2 3 4 5 6");
    iss >> v;
    EXPECT_DOUBLE_EQ(v.getX1(), 1.0);
    EXPECT_DOUBLE_EQ(v.getZ2(), 6.0);
}