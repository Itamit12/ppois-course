# ППОИС — Лабораторные работы

Репозиторий с лабораторными работами по курсу «Проектирование программного обеспечения интеллектуальных систем».

## Структура

|      Папка      |            Лабораторная            | Статус |
|-----------------|------------------------------------|--------|
| [lab1](./lab1)  | Основы ООП: Vector3D + PostMachine |   ✅   |
| [lab2](./lab2)  |                  —                 |   ⏳   |
| [lab3](./lab3)  |                  —                 |   ⏳   |
| [lab4](./lab4)  |                  —                 |   ⏳   |

## Сборка и тесты (Windows)

Для работы с проектом на Windows вам понадобится установленный **Visual Studio 2022** (с рабочей нагрузкой «Разработка классических приложений на C++») и **CMake**.

> ⚠️ **Важно:** Все команды необходимо выполнять в **Developer Command Prompt for VS 2022** (или в PowerShell, предварительно запустив `vcvars64.bat`), иначе CMake не сможет найти компилятор `cl.exe`.

### Вариант 1: Сборка с помощью Ninja (рекомендуется)

Если у вас в PATH добавлен `ninja.exe` (он идет в комплекте с Visual Studio), используйте этот вариант. Сборка проходит быстрее, а файлы лежат прямо в папке `build`.

```powershell
#Настройка терминала
cmd /c '"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" && set' | ForEach-Object { if ($_ -match '^(.*?)=(.*)$') { [Environment]::SetEnvironmentVariable($matches[1], $matches[2]) } }

#Очистка
Remove-Item -Recurse -Force lab1/build -ErrorAction SilentlyContinue

# Конфигурация
cmake -S lab1 -B lab1/build -G Ninja -DCMAKE_BUILD_TYPE=Debug

# Сборка
cmake --build lab1/build

# Запуск тестов
ctest --test-dir lab1/build --output-on-failure
