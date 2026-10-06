/**
 * @file PostMachine.h
 * @brief Реализация машины Поста.
 */

#ifndef POSTMACHINE_H
#define POSTMACHINE_H

#include <vector>
#include <string>
#include <iostream>

/**
 * @class PostMachine
 * @brief Абстрактная вычислительная машина Поста.
 */
class PostMachine {
public:
    static constexpr int EMPTY = 0; ///< Пустая ячейка
    static constexpr int MARK  = 1; ///< Ячейка с меткой

    explicit PostMachine(const std::vector<int>& initialTape = {}, int startPos = 0);

    void moveLeft();
    void moveRight();
    void setMark();
    void removeMark();
    [[nodiscard]] bool isMarked() const;

    bool execute(const std::string& program);

    [[nodiscard]] std::vector<int> getTape() const;
    [[nodiscard]] int getHead() const;

    bool operator==(const PostMachine& other) const;
    bool operator!=(const PostMachine& other) const;

    friend std::ostream& operator<<(std::ostream& os, const PostMachine& pm);
    friend std::istream& operator>>(std::istream& is, PostMachine& pm);

private:
    std::vector<int> tape_;
    int head_;
    int tapeSize_;

    void expandTape();
};

#endif // POSTMACHINE_H