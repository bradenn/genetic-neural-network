cmake_minimum_required(VERSION 3.25)
project(genes)
set(CMAKE_CXX_STANDARD 20)

set(GLEW_ROOT_DIR "/opt/homebrew/Cellar/glew/2.2.0_1")
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
find_package(Freetype REQUIRED)
find_package(OpenMP)

include_directories(${FREETYPE_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

add_executable(genes main.cpp genetic/ genetic/genome.cpp genetic/genome.h genetic/neuron.h gfx.cpp gfx.h simulator.cpp simulator.h genetic/population.cpp genetic/population.h genetic/random.h genetic/agent.cpp genetic/agent.h genetic/node.h fontRenderer.cpp window/frame.cpp window/frame.h window/pane.cpp window/pane.h genetic/world.cpp genetic/world.h genetic/statistics.cpp genetic/statistics.h)
target_link_libraries(genes glfw ${OPENGL_LIBRARIES} ${FREETYPE_LIBRARIES} OpenMP::OpenMP_CXX)