# PrintCoverage.cmake — печатает таблицу покрытия по Cobertura-отчёту.
#
# Запуск в режиме скрипта:
#   cmake -DCOBERTURA_XML=coverage.xml [-DCOVERAGE_HTML=dir] [-DCOVERAGE_THRESHOLD=90] \
#         -P PrintCoverage.cmake
#
# COVERAGE_THRESHOLD — минимальный процент покрытия строк (0 — проверка отключена).

cmake_minimum_required(VERSION 3.15)

if(NOT DEFINED COBERTURA_XML OR NOT EXISTS "${COBERTURA_XML}")
    message(FATAL_ERROR "Coverage report not found: '${COBERTURA_XML}'")
endif()

# Дополняет строку пробелами справа до заданной ширины.
function(pad_out out_var text width)
    string(LENGTH "${text}" text_len)
    math(EXPR fill "${width} - ${text_len}")
    if(fill GREATER 0)
        string(REPEAT " " ${fill} spaces)
    else()
        set(spaces "")
    endif()
    set(${out_var} "${text}${spaces}" PARENT_SCOPE)
endfunction()

file(READ "${COBERTURA_XML}" xml)

# --- Итоговые цифры из корневого тега <coverage ...> ---
string(REGEX MATCH "<coverage[^>]*>" root_tag "${xml}")
if(NOT root_tag)
    message(FATAL_ERROR "Not a Cobertura report: '${COBERTURA_XML}'")
endif()
string(REGEX REPLACE ".*lines-covered=\"([0-9]+)\".*" "\\1" total_covered "${root_tag}")
string(REGEX REPLACE ".*lines-valid=\"([0-9]+)\".*" "\\1" total_valid "${root_tag}")

# --- Разбор по файлам ---
# Приводим отчёт к одной строке и разбиваем на блоки <class ...>...</class>.
string(REGEX REPLACE "\r?\n" " " flat "${xml}")
string(REPLACE "</class>" "\n" flat "${flat}")
string(REPLACE "<class " "\n<class " flat "${flat}")
string(REPLACE "\n" ";" entries "${flat}")

set(rows "")
foreach(entry IN LISTS entries)
    if(NOT entry MATCHES "^<class ")
        continue()
    endif()

    string(REGEX MATCH "filename=\"([^\"]*)\"" _ "${entry}")
    get_filename_component(file_name "${CMAKE_MATCH_1}" NAME)

    string(REGEX MATCHALL "<line " all_lines "${entry}")
    string(REGEX MATCHALL "<line [^>]*hits=\"0\"" missed_lines "${entry}")
    list(LENGTH all_lines lines_total)
    list(LENGTH missed_lines lines_missed)
    if(lines_total EQUAL 0)
        continue()
    endif()
    math(EXPR lines_covered "${lines_total} - ${lines_missed}")
    math(EXPR percent "(${lines_covered} * 100 + ${lines_total} / 2) / ${lines_total}")

    list(APPEND rows "${file_name}|${lines_total}|${lines_covered}|${percent}")
endforeach()

if(NOT rows)
    message(FATAL_ERROR "No source files measured in '${COBERTURA_XML}'")
endif()
list(SORT rows)

# --- Ширина колонок ---
set(name_width 20)
foreach(row IN LISTS rows)
    string(REGEX REPLACE "^([^|]*)\\|.*$" "\\1" name "${row}")
    string(LENGTH "${name}" name_len)
    if(name_len GREATER name_width)
        set(name_width ${name_len})
    endif()
endforeach()
math(EXPR name_width "${name_width} + 2")

set(rule "")
math(EXPR rule_width "${name_width} + 10 + 11 + 11")
string(REPEAT "-" ${rule_width} rule)

# --- Вывод ---
message("")
message("Coverage report: ${COBERTURA_XML}")
message("")
string(REPEAT " " ${name_width} header_indent)
pad_out(col_total "Lines" 10)
pad_out(col_covered "Covered" 11)
message("  ${header_indent}${col_total}${col_covered}Coverage")
message("  ${rule}")

foreach(row IN LISTS rows)
    string(REGEX MATCH "^([^|]*)\\|([0-9]+)\\|([0-9]+)\\|([0-9]+)$" _ "${row}")
    set(name "${CMAKE_MATCH_1}")
    set(lines "${CMAKE_MATCH_2}")
    set(covered "${CMAKE_MATCH_3}")
    set(percent "${CMAKE_MATCH_4}")

    pad_out(line "${name}" ${name_width})
    pad_out(col_total "${lines}" 10)
    pad_out(col_covered "${covered}" 11)
    message("  ${line}${col_total}${col_covered}${percent}%")
endforeach()

message("  ${rule}")
if(total_valid GREATER 0)
    math(EXPR total_percent "(${total_covered} * 100 + ${total_valid} / 2) / ${total_valid}")
else()
    set(total_percent 0)
endif()
pad_out(line "TOTAL" ${name_width})
pad_out(col_total "${total_valid}" 10)
pad_out(col_covered "${total_covered}" 11)
message("  ${line}${col_total}${col_covered}${total_percent}%")
message("")

if(DEFINED COVERAGE_HTML AND EXISTS "${COVERAGE_HTML}/index.html")
    message("HTML report: ${COVERAGE_HTML}/index.html")
    message("")
endif()

if(DEFINED COVERAGE_THRESHOLD AND COVERAGE_THRESHOLD GREATER 0 AND total_percent LESS COVERAGE_THRESHOLD)
    message(FATAL_ERROR "Line coverage ${total_percent}% is below threshold ${COVERAGE_THRESHOLD}%")
endif()
