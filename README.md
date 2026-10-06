\# ППОИС — Лабораторные работы



Репозиторий с лабораторными работами по курсу «Проектирование программного обеспечения интеллектуальных систем».



\## Структура



| Папка | Лабораторная | Статус |

|---|---|---|

| \[lab1](./lab1) | Основы ООП: Vector3D + PostMachine | ✅ |

| \[lab2](./lab2) | — | ⏳ |

| \[lab3](./lab3) | — | ⏳ |

| \[lab4](./lab4) | — | ⏳ |



\## Сборка и тесты (Windows)



```powershell

cmake -S lab1 -B lab1/build -DCMAKE\_TOOLCHAIN\_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake

cmake --build lab1/build --config Debug --parallel

ctest --test-dir lab1/build -C Debug --output-on-failure

