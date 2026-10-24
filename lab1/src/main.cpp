#include "Vector3D.h"
#include "PostMachine.h"
#include <iostream>
#include <vector>
#include <string>

namespace {
void printVectorMenu() {
    std::cout << "\n--- Vector ---\n"
              << "1. Length of v1\n"
              << "2. Addition (v1 + v2)\n"
              << "3. Subtraction (v1 - v2)\n"
              << "4. Cross product (v1 * v2)\n"
              << "5. Multiply by scalar\n"
              << "6. Divide by scalar\n"
              << "7. Cosine of angle between v1 and v2\n"
              << "8. Compare lengths\n"
              << "0. Back\n"
              << "Choice: ";
}

void printPostMenu() {
    std::cout << "\n--- Post Machine ---\n"
              << "1. Move left\n"
              << "2. Move right\n"
              << "3. Set mark\n"
              << "4. Remove mark\n"
              << "5. Check mark\n"
              << "6. Execute program\n"
              << "0. Back\n"
              << "Choice: ";
}

void runVectorMenu() {
    Vector3D v1, v2;
    std::cout << "Enter first vector (x1 y1 z1 x2 y2 z2): ";
    std::cin >> v1;
    std::cout << "Enter second vector: ";
    std::cin >> v2;

    int choice = -1;
    while (choice != 0) {
        printVectorMenu();
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Length: " << v1.length() << "\n";
                break;
            case 2:
                std::cout << "Result: " << (v1 + v2) << "\n";
                break;
            case 3:
                std::cout << "Result: " << (v1 - v2) << "\n";
                break;
            case 4:
                std::cout << "Result: " << (v1 * v2) << "\n";
                break;
            case 5: {
                double s;
                std::cout << "Scalar: ";
                std::cin >> s;
                std::cout << "Result: " << (v1 * s) << "\n";
                break;
            }
            case 6: {
                double s;
                std::cout << "Scalar: ";
                std::cin >> s;
                try {
                    std::cout << "Result: " << (v1 / s) << "\n";
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 7:
                try {
                    std::cout << "Cosine: " << v1.cosAngle(v2) << "\n";
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            case 8:
                if (v1 > v2)      std::cout << "v1 > v2\n";
                else if (v1 < v2) std::cout << "v1 < v2\n";
                else              std::cout << "v1 == v2\n";
                break;
            default:
                std::cout << "Unknown option\n";
                break;
        }
    }
}

void runPostMenu() {
    std::vector<int> tape;
    int n, start;
    std::cout << "Tape size: ";
    std::cin >> n;
    tape.resize(n);
    std::cout << "Tape (0/1): ";
    for (int i = 0; i < n; ++i) {
        std::cin >> tape[i];
    }
    std::cout << "Head position: ";
    std::cin >> start;

    PostMachine pm(tape, start);
    int choice = -1;
    while (choice != 0) {
        std::cout << "Tape: " << pm << "\n";
        printPostMenu();
        std::cin >> choice;
        switch (choice) {
            case 1: pm.moveLeft();   break;
            case 2: pm.moveRight();  break;
            case 3: pm.setMark();    break;
            case 4: pm.removeMark(); break;
            case 5:
                std::cout << (pm.isMarked() ? "Cell is marked\n" : "Cell is empty\n");
                break;
            case 6: {
                std::string prog;
                std::cout << "Program (L,R,V,X,?): ";
                std::cin >> prog;
                try {
                    std::cout << (pm.execute(prog) ? "Completed\n" : "Halted (?)\n");
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            default:
                std::cout << "Unknown option\n";
                break;
        }
    }
}
} // namespace

int main() {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== Lab #1 ===\n"
                  << "1. Vector\n"
                  << "2. Post Machine\n"
                  << "0. Exit\n"
                  << "Choice: ";
        std::cin >> choice;
        if (choice == 1)      runVectorMenu();
        else if (choice == 2) runPostMenu();
    }
    return 0;
}