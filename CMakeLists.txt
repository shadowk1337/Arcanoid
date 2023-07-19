cmake_minimum_required(VERSION 3.25)
project(Arcanoid)

set(CMAKE_CXX_STANDARD 17)

add_executable(Arcanoid
        Game.cpp
        Engine.cpp

        Entities/Ball.cpp
        Entities/Block.cpp
        Entities/Carriage.cpp
        Entities/Entity.cpp
        Entities/Wall.cpp
        Entities/Bonus.cpp

        Components/Collisions/XYLineCollision.cpp
        Components/Collisions/CubeCollision.cpp

        Components/Meshes/Mesh.cpp
        Components/Meshes/CircleMesh.cpp
        Components/Meshes/XYLineMesh.cpp
        Components/Meshes/CubeMesh.cpp
        Components/Meshes/TextMesh.cpp

        Components/Meshes/font.cpp

        Components/Others/Controller.cpp
        Components/Others/Dynamic.cpp
        Components/Others/Movable.cpp

        Misc/Scrap.cpp
)

set_target_properties(Arcanoid PROPERTIES WIN32_EXECUTABLE TRUE)
