#include "Vector3D.h"
#include "PostMachine.h"
#include <iostream>
#include <vector>
#include <string>

namespace {
void printVectorMenu() {
    std::cout << "\n--- Вектор ---\n"
              << "1. Длина v1\n2. Сложение\n3. Вычитание\n4. Векторное произведение\n"
              << "5. Умножение на число\n6. Деление на число\n7. Косинус угла\n"
              << "8. Сравнение длин\n0. Назад\nВыбор: ";
}

void printPostMenu() {
    std::cout << "\n--- Машина Поста ---\n"
              << "1. Влево\n2. Вправо\n3. Поставить метку\n4. Удалить метку\n"
              << "5. Проверить метку\n6. Выполнить программу\n0. Назад\nВыбор: ";
}

void runVectorMenu() {
    Vector3D v1, v2;
    std::cout << "Введите первый вектор (x1 y1 z1 x2 y2 z2): ";
    std::cin >> v1;
    std::cout << "Введите второй вектор: ";
    std::cin >> v2;

    int choice = -1;
    while (choice != 0) {
        printVectorMenu();
        std::cin >> choice;
        switch (choice) {
            case 1: std::cout << "Длина: " << v1.length() << "\n"; break;
            case 2: std::cout << "Результат: " << (v1 + v2) << "\n"; break;
            case 3: std::cout << "Результат: " << (v1 - v2) << "\n"; break;
            case 4: std::cout << "Результат: " << (v1 * v2) << "\n"; break;
            case 5: { double s; std::cout << "Число: "; std::cin >> s;
                      std::cout << "Результат: " << (v1 * s) << "\n"; break; }
            case 6: { double s; std::cout << "Число: "; std::cin >> s;
                      try { std::cout << "Результат: " << (v1 / s) << "\n"; }
                      catch (const std::exception& e) { std::cout << "Ошибка: " << e.what() << "\n"; }
                      break; }
            case 7: try { std::cout << "Косинус: " << v1.cosAngle(v2) << "\n"; }
                    catch (const std::exception& e) { std::cout << "Ошибка: " << e.what() << "\n"; }
                    break;
            case 8:
                if (v1 > v2) std::cout << "v1 > v2\n";
                else if (v1 < v2) std::cout << "v1 < v2\n";
                else std::cout << "v1 == v2\n";
                break;
        }
    }
}

void runPostMenu() {
    std::vector<int> tape;
    int n, start;
    std::cout << "Размер ленты: "; std::cin >> n;
    tape.resize(n);
    std::cout << "Лента (0/1): ";
    for (int i = 0; i < n; ++i) std::cin >> tape[i];
    std::cout << "Позиция каретки: "; std::cin >> start;

    PostMachine pm(tape, start);
    int choice = -1;
    while (choice != 0) {
        std::cout << "Лента: " << pm << "\n";
        printPostMenu();
        std::cin >> choice;
        switch (choice) {
            case 1: pm.moveLeft(); break;
            case 2: pm.moveRight(); break;
            case 3: pm.setMark(); break;
            case 4: pm.removeMark(); break;
            case 5: std::cout << (pm.isMarked() ? "Метка есть\n" : "Метки нет\n"); break;
            case 6: { std::string prog;
                      std::cout << "Программа (L,R,V,X,?): "; std::cin >> prog;
                      try { std::cout << (pm.execute(prog) ? "Успешно\n" : "Останов\n"); }
                      catch (const std::exception& e) { std::cout << "Ошибка: " << e.what() << "\n"; }
                      break; }
        }
    }
}
} // namespace

int main() {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== Лабораторная №1 ===\n1. Вектор\n2. Машина Поста\n0. Выход\nВыбор: ";
        std::cin >> choice;
        if (choice == 1) runVectorMenu();
        else if (choice == 2) runPostMenu();
    }
    return 0;
}