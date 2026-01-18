add_library(matrix STATIC
        src/Matrix.cpp
        src/MatrixRenderer.cpp
)

target_include_directories(matrix PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/app/include
)
