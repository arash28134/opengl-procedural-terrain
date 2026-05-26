cmake_minimum_required(VERSION 3.15)  # CMake version check
project(opengl_terrain)               # project name
set(CMAKE_CXX_STANDARD 17)            # enable c++17 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find packages
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# add source files
set(SOURCE_FILES 
src/main.cpp 
src/window.cpp 
src/shader.cpp 
src/mesh.cpp 
src/camera.cpp 
src/mesh_utils.cpp 
src/anim_utils.cpp 
src/utils.cpp)

# add executable target with source files listed in SOURCE_FILES variable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glfw GLEW::GLEW glm::glm)

# include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

# OS-Specific handling
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN)
endif()

if(NOT WIN32)
    find_package(Threads REQUIRED)
    target_link_libraries(MyApp PRIVATE ${CMAKE_DL_LIBS} Threads::Threads)
endif()

# Copy /shaders folder
add_custom_command(TARGET opengl_terrain POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders
    $<TARGET_FILE_DIR:opengl_terrain>/shaders
)