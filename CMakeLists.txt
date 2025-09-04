cmake_minimum_required(VERSION 3.15)
project(SFML-Test VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Явно указываем путь к корневой директории SFML
set(SFML_ROOT "C:/SFML-3.0.0")  # Замените на ваш путь
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")

find_package(SFML REQUIRED COMPONENTS graphics window system)

file(GLOB_RECURSE SOURCES source/*.cpp)
file(GLOB_RECURSE HEADERS source/Include/*.h source/Include/*.hpp)

add_executable(SFML-Test ${SOURCES} ${HEADERS})

target_link_libraries(SFML-Test PRIVATE 
    sfml-graphics
    sfml-window
    sfml-system
)

if(MSVC)
    target_compile_options(SFML-Test PRIVATE /W4)
else()
    target_compile_options(SFML-Test PRIVATE -Wall -Wextra)
endif()

target_include_directories(SFML-Test PRIVATE 
    ${SFML_INCLUDE_DIR}
    source/Include
)

# Правильное определение пути к папке bin
set(SFML_BIN_DIR "${SFML_ROOT}/bin")

# Копирование DLL файлов SFML
if(WIN32)
    # Для Debug сборки
    add_custom_command(TARGET SFML-Test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${SFML_BIN_DIR}/sfml-graphics-d-2.dll"
            $<TARGET_FILE_DIR:SFML-Test>
    )
    
    add_custom_command(TARGET SFML-Test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${SFML_BIN_DIR}/sfml-window-d-2.dll"
            $<TARGET_FILE_DIR:SFML-Test>
    )
    
    add_custom_command(TARGET SFML-Test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${SFML_BIN_DIR}/sfml-system-d-2.dll"
            $<TARGET_FILE_DIR:SFML-Test>
    )
    
    # Для Release сборки (опционально)
    add_custom_command(TARGET SFML-Test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${SFML_BIN_DIR}/sfml-graphics-2.dll"
            $<TARGET_FILE_DIR:SFML-Test>
    )
    
    add_custom_command(TARGET SFML-Test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${SFML_BIN_DIR}/sfml-window-2.dll"
            $<TARGET_FILE_DIR:SFML-Test>
    )
    
    add_custom_command(TARGET SFML-Test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${SFML_BIN_DIR}/sfml-system-2.dll"
            $<TARGET_FILE_DIR:SFML-Test>
    )
endif()

# Копирование ресурсов
add_custom_command(TARGET SFML-Test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:SFML-Test>/resources
)

install(TARGETS SFML-Test DESTINATION bin)
install(DIRECTORY source/Include/ DESTINATION include)