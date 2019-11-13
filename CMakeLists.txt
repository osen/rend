cmake_minimum_required(VERSION 2.6)
project(REND)

include_directories(
  ${PROJECT_SOURCE_DIR}/src
)

add_definitions(-DSTD_SR1_DEBUG)

add_library(rend
  src/rend/Exception.cpp
  src/rend/Context.cpp
  src/rend/Texture.cpp
  src/rend/RenderTexture.cpp
  src/rend/Shader.cpp
  src/rend/Buffer.cpp
  src/rend/Mesh.cpp
  src/rend/Util.cpp
)
if(MSVC)
  target_link_libraries(rend glew32 opengl32)
else()
  target_link_libraries(rend GLEW GL)
endif()

add_executable(triangle
  src/triangle/main.cpp
)
target_link_libraries(triangle rend SDL2)

add_executable(mesh
  src/mesh/main.cpp
)
target_link_libraries(mesh rend SDL2)

add_executable(model
  src/model/main.cpp
)
target_link_libraries(model rend SDL2)