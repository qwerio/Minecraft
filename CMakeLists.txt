cmake_minimum_required(VERSION 3.0)
project(Minecraft)
   
#find_package(SDL2 2.0.10 REQUIRED)
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

#find_package(SDL2 REQUIRED)
#if (SDL2_FOUND)
#    include_directories(${SDL2_INCLUDE_DIRS})
#    link_libraries(${SDL2_LIBRARIES})
#endif()

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    link_libraries(${OPENGL_LIBRARIES})
endif()

find_package(GLUT REQUIRED)
if (GLUT_FOUND)
    include_directories(${GLUT_INCLUDE_DIRS})
    link_libraries(${GLUT_LIBRARIES})
endif()

find_package(GLM REQUIRED)
if (GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIRS})
    link_libraries(${GLM_LIBRARIES})
endif()

find_package(SOIL REQUIRED)
if (SOIL_FOUND)
    include_directories(${SOIL_INCLUDE_DIRS})
    link_libraries(${SOIL_LIBRARIES})
endif()

add_executable(
	main 
	main.cpp
	Window.cpp
	Window.h
	Renderer.cpp
	Renderer.h
    Application.h
    Application.cpp
    Shader.h
    shaders/vertex.vs
    shaders/fragment.fs
    stb_image.h
    Material.h
    Node.h
)

#target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main)


#cmake_minimum_required(VERSION 3.0)
#project(test)

#find_package(Sqlite3 REQUIRED)

#add_executable(main main.cpp)
#target_link_libraries(main sqlite3)