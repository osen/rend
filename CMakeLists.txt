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
)
if(MSVC)
  target_link_libraries(rend glew32 opengl32)
else()
  target_link_libraries(rend GLEW GL)
endif()

add_executable(example
  src/example/main.cpp
)
target_link_libraries(example rend SDL2)
