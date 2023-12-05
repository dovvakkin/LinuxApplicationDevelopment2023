cmake_minimum_required(VERSION 3.10)
project(guesser C)
include_directories(/usr/local/lib)
link_directories(/opt/homebrew/lib)
set(CMAKE_C_STANDARD 99)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(strbuf lib/strbuf.c)
add_library(roman lib/roman.c)
target_link_libraries(roman strbuf)

add_executable(guesser guesser.c)
target_link_libraries(guesser roman)
target_link_libraries(guesser m)

find_program(CLANG_FORMAT_EXECUTABLE clang-format)
if(CLANG_FORMAT_EXECUTABLE)
  add_custom_target(
    format
    COMMAND ${CLANG_FORMAT_EXECUTABLE} -i guesser.c lib/* include/* --style=file
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running clang-format"
    VERBATIM)
  message(STATUS "clang-format found: ${CLANG_FORMAT_EXECUTABLE}")
else()
  add_custom_target(
    format COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --yellow
                   "clang-format not found, unable to format code")
  message(WARNING "clang-format not found")
endif()

FIND_PACKAGE(Doxygen)
 IF(DOXYGEN_FOUND)
    SET(DOXYGEN_INPUT ${CMAKE_SOURCE_DIR})
    CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf)
    ADD_CUSTOM_TARGET(doc COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf)
 ELSE(DOXYGEN_FOUND)
    MESSAGE(STATUS "WARNING: Doxygen not found - Reference manual will not be created")
ENDIF(DOXYGEN_FOUND)

find_package(Gettext)

set(GETTEXT_DOMAIN ${CMAKE_PROJECT_NAME})
set(POT_FILE ${CMAKE_CURRENT_BINARY_DIR}/po/${GETTEXT_DOMAIN}.pot)

add_definitions(-DLOCALE_PATH="${PROJECT_SOURCE_DIR}/po")
add_definitions(-DGETTEXT_DOMAIN="${GETTEXT_DOMAIN}")

file(GLOB_RECURSE POT_SOURCES ${PROJECT_SOURCE_DIR}/*.c)

add_custom_target(
  ${GETTEXT_DOMAIN}-pot
  COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/po
  COMMENT "Building ${GETTEXT_DOMAIN}.pot file from sources"
  COMMAND xgettext --from-code=UTF-8 --keyword=_ --add-comments
          --output=${POT_FILE} ${POT_SOURCES})

add_custom_target(
  init-translation
  DEPENDS ${GETTEXT_DOMAIN}-pot
  COMMENT "Creating empty .po files"
  COMMAND msginit --no-translator -i ${POT_FILE} -l en_EN -o
          ${CMAKE_SOURCE_DIR}/po/en.po
  COMMAND msginit --no-translator -i ${POT_FILE} -l ru_RU -o
          ${CMAKE_SOURCE_DIR}/po/ru.po)

add_custom_target(
  update-translation
  DEPENDS ${GETTEXT_DOMAIN}-pot
  COMMENT "Updating .po from fresh .pot"
  COMMAND msgmerge -U ${CMAKE_SOURCE_DIR}/po/ru.po ${POT_FILE}
  COMMAND msgmerge -U ${CMAKE_SOURCE_DIR}/po/en.po ${POT_FILE})

add_custom_target(
  translate
  COMMENT "Compiling translation"
  COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/po/ru_RU/LC_MESSAGES
  COMMAND
    msgfmt -o
    ${CMAKE_CURRENT_BINARY_DIR}/po/ru_RU/LC_MESSAGES/${GETTEXT_DOMAIN}.mo
    ${CMAKE_SOURCE_DIR}/po/ru.po
  COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/po/en_EN/LC_MESSAGES
  COMMAND
    msgfmt -o
    ${CMAKE_CURRENT_BINARY_DIR}/po/en_EN/LC_MESSAGES/${GETTEXT_DOMAIN}.mo
    ${CMAKE_SOURCE_DIR}/po/en.po)

add_custom_target(git-clean COMMAND git clean -xfd ${CMAKE_SOURCE_DIR})

add_dependencies(guesser translate)
