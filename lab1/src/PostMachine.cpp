#include "PostMachine.h"
#include <stdexcept>

PostMachine::PostMachine(const std::vector<int>& initialTape, int startPos)
    : tape_(initialTape), head_(startPos), tapeSize_(static_cast<int>(initialTape.size())) {
    if (tape_.empty()) {
        tape_.push_back(EMPTY);
        tapeSize_ = 1;
        head_ = 0;
    }
    if (head_ < 0 || head_ >= tapeSize_) {
        throw std::out_of_range("Start position out of range");
    }
}

void PostMachine::expandTape() {
    if (head_ < 0) {
        tape_.insert(tape_.begin(), EMPTY);
        head_ = 0;
        ++tapeSize_;
    } else if (head_ >= tapeSize_) {
        tape_.push_back(EMPTY);
        ++tapeSize_;
    }
}

void PostMachine::moveLeft()  { --head_; expandTape(); }
void PostMachine::moveRight() { ++head_; expandTape(); }
void PostMachine::setMark()   { tape_[head_] = MARK; }
void PostMachine::removeMark(){ tape_[head_] = EMPTY; }
bool PostMachine::isMarked() const { return tape_[head_] == MARK; }

bool PostMachine::execute(const std::string& program) {
    for (const char cmd : program) {
        switch (cmd) {
            case 'L': moveLeft();  break;
            case 'R': moveRight(); break;
            case 'V': setMark();   break;
            case 'X': removeMark();break;
            case '?': if (!isMarked()) return false; break;
            default: throw std::invalid_argument("Unknown command: " + std::string(1, cmd));
        }
    }
    return true;
}

std::vector<int> PostMachine::getTape() const { return tape_; }
int PostMachine::getHead() const { return head_; }

bool PostMachine::operator==(const PostMachine& other) const {
    return tape_ == other.tape_ && head_ == other.head_;
}
bool PostMachine::operator!=(const PostMachine& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const PostMachine& pm) {
    for (int i = 0; i < pm.tapeSize_; ++i) {
        if (i == pm.head_) os << "[";
        os << (pm.tape_[i] ? "1" : "0");
        if (i == pm.head_) os << "]";
        else os << " ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, PostMachine& pm) {
    int size;
    is >> size;
    pm.tape_.resize(size);
    for (int i = 0; i < size; ++i) is >> pm.tape_[i];
    is >> pm.head_;
    pm.tapeSize_ = size;
    return is;
}