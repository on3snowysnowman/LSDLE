cmake_minimum_required(VERSION 3.22)
project(LSDLE VERSION "1.0.2")

# Create the static library
add_library(LSDLE STATIC ${SOURCES}
    src/ConsoleOutputHandler.cpp
    src/DelayedTextHandler.cpp
    src/EventSystem.cpp
    src/InputHandler.cpp
    src/LRandom.cpp
    src/LSDLE.cpp
    src/Menu.cpp
    src/MenuHandler.cpp
    src/SpriteHandler.cpp
    src/TextDisplayHandler.cpp
    src/TextureHandler.cpp
    src/Window.cpp

    src/MenuTools/MenuToolChoice.cpp
    src/MenuTools/MenuToolItem.cpp
    src/MenuTools/MenuToolList.cpp
    src/MenuTools/MenuTools.cpp
    src/MenuTools/MenuToolTextList.cpp
    src/MenuTools/MenuToolText.cpp
    src/MenuTools/MenuToolVariable.cpp
)

target_include_directories(LSDLE
    PUBLIC
        $<INSTALL_INTERFACE:include/LSDLE>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/LSDLE>

        $<INSTALL_INTERFACE:include/LSDLE/MenuTools>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/LSDLE/MenuTools>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Find required libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Link required libraries
target_link_libraries(LSDLE
    PUBLIC
        SDL2::SDL2
        SDL2_image
        SDL2_mixer
)

# set(TXT_CONTENT)

file(STRINGS "LSDLE_Path.txt" TXT_CONTENT LIMIT_COUNT 1)

# Install the library
install(TARGETS LSDLE ARCHIVE DESTINATION "${TXT_CONTENT}/LSDLE/lib")

# Install header files and aother dependant files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ DESTINATION "${TXT_CONTENT}/LSDLE/"
    PATTERN "build" EXCLUDE
    PATTERN "src" EXCLUDE
    PATTERN "CMakeLists.txt" EXCLUDE
    PATTERN ".vscode" EXCLUDE
    PATTERN "README.txt" EXCLUDE
    PATTERN "LSDLE_Path.txt" EXCLUDE
    PATTERN ".git" EXCLUDE
    PATTERN ".gitignore" EXCLUDE
    PATTERN ".vscode" EXCLUDE
    PATTERN "clang-tidy" EXCLUDE
    PATTERN "NeedToDocument.txt" EXCLUDE)
