#include <gtest/gtest.h>
#include "PostMachine.h"
#include <stdexcept>

TEST(PostMachineTest, DefaultConstructor) {
    PostMachine pm;
    EXPECT_EQ(pm.getHead(), 0);
    EXPECT_EQ(pm.getTape().size(), 1u);
    EXPECT_FALSE(pm.isMarked());
}

TEST(PostMachineTest, ParamConstructor) {
    PostMachine pm({1, 0, 1}, 1);
    EXPECT_EQ(pm.getHead(), 1);
    EXPECT_FALSE(pm.isMarked());
}

TEST(PostMachineTest, ConstructorWithStartPos) {
    PostMachine pm({1, 0, 1}, 2);
    EXPECT_EQ(pm.getHead(), 2);
    EXPECT_TRUE(pm.isMarked());
}

TEST(PostMachineTest, ConstructorInvalidPosThrows) {
    EXPECT_THROW(PostMachine({1, 0, 1}, 10), std::out_of_range);
    EXPECT_THROW(PostMachine({1, 0, 1}, -1), std::out_of_range);
}

TEST(PostMachineTest, CopyConstructor) {
    PostMachine pm1({1, 0, 1}, 1);
    PostMachine pm2(pm1);
    EXPECT_EQ(pm1, pm2);
}

TEST(PostMachineTest, AssignmentOperator) {
    PostMachine pm1({1, 0, 1}, 1);
    PostMachine pm2;
    pm2 = pm1;
    EXPECT_EQ(pm1, pm2);
}

TEST(PostMachineTest, MoveRight) {
    PostMachine pm({0, 0, 0}, 0);
    pm.moveRight();
    EXPECT_EQ(pm.getHead(), 1);
}

TEST(PostMachineTest, MoveRightExpandsTape) {
    PostMachine pm({0}, 0);
    pm.moveRight();
    EXPECT_EQ(pm.getHead(), 1);
    EXPECT_EQ(pm.getTape().size(), 2u);
}

TEST(PostMachineTest, MoveLeftExpandsTape) {
    PostMachine pm({0, 0, 0}, 0);
    pm.moveLeft();
    EXPECT_EQ(pm.getHead(), 0);
    EXPECT_EQ(pm.getTape().size(), 4u);
}

TEST(PostMachineTest, SetMark) {
    PostMachine pm({0, 0, 0}, 1);
    pm.setMark();
    EXPECT_TRUE(pm.isMarked());
}

TEST(PostMachineTest, RemoveMark) {
    PostMachine pm({1, 1, 1}, 1);
    pm.removeMark();
    EXPECT_FALSE(pm.isMarked());
}

TEST(PostMachineTest, ExecuteSimpleProgram) {
    PostMachine pm({0, 0, 0}, 0);
    EXPECT_TRUE(pm.execute("RVRV"));
    EXPECT_EQ(pm.getTape()[1], 1);
    EXPECT_EQ(pm.getTape()[2], 1);
}

TEST(PostMachineTest, ExecuteStopOnEmpty) {
    PostMachine pm({0, 0, 0}, 0);
    EXPECT_FALSE(pm.execute("?"));
}

TEST(PostMachineTest, ExecuteContinueOnMarked) {
    PostMachine pm({1, 0, 0}, 0);
    EXPECT_TRUE(pm.execute("?"));
}

TEST(PostMachineTest, ExecuteEmptyProgram) {
    PostMachine pm({0, 0, 0}, 0);
    EXPECT_TRUE(pm.execute(""));
}

TEST(PostMachineTest, ExecuteInvalidCommandThrows) {
    PostMachine pm({0, 0, 0}, 0);
    EXPECT_THROW(pm.execute("Z"), std::invalid_argument);
}

TEST(PostMachineTest, EqualityTrue) {
    PostMachine pm1({1, 0, 1}, 1);
    PostMachine pm2({1, 0, 1}, 1);
    EXPECT_TRUE(pm1 == pm2);
}

TEST(PostMachineTest, EqualityFalseAfterMove) {
    PostMachine pm1({1, 0, 1}, 1);
    PostMachine pm2({1, 0, 1}, 1);
    pm2.moveRight();
    EXPECT_TRUE(pm1 != pm2);
}

TEST(PostMachineTest, OutputOperator) {
    PostMachine pm({1, 0, 1}, 1);
    std::ostringstream oss;
    oss << pm;
    EXPECT_NE(oss.str().find("[0]"), std::string::npos);
}

TEST(PostMachineTest, InputOperator) {
    PostMachine pm;
    std::istringstream iss("3 1 0 1 1");
    iss >> pm;
    EXPECT_EQ(pm.getTape().size(), 3u);
    EXPECT_EQ(pm.getHead(), 1);
}