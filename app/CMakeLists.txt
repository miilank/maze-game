add_executable(MazeGame
        src/main.cpp
        src/Cell.cpp
        src/FileManager.cpp
        src/Fog.cpp
        src/Game.cpp
        src/Hammer.cpp
        src/Item.cpp
        src/Shield.cpp
        src/Sword.cpp
)

target_include_directories(MazeGame PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(MazeGame PRIVATE matrix)
