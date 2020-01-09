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

add_library(re
  src/re/Context.c
  src/re/Renderer.c
  src/re/mathutil.c
  src/re/Buffer.c
  src/re/internal.c
  src/re/Shader.c
)
if(MSVC)
  target_link_libraries(re glew32 opengl32)
else()
  target_link_libraries(re GLEW GL m)
endif()

add_executable(tri
  src/tri/main.c
)
target_link_libraries(tri re SDL2)

add_executable(triangle
  src/triangle/main.cpp
)
target_link_libraries(triangle rend SDL2)

add_executable(mesh
  src/mesh/main.cpp
)
target_link_libraries(mesh rend SDL2)

add_executable(gui
  src/gui/main.cpp
)
target_link_libraries(gui rend SDL2)

add_executable(model
  src/model/main.cpp
)
target_link_libraries(model rend SDL2)

add_executable(rotate
  src/rotate/main.cpp
)
target_link_libraries(rotate rend SDL2)

add_executable(texture
  src/texture/main.cpp
)
target_link_libraries(texture rend SDL2)

add_executable(level
  src/level/main.cpp
)
target_link_libraries(level rend SDL2)

add_executable(collision
  src/collision/main.cpp
  src/collision/tritri.cpp
)
target_link_libraries(collision rend SDL2)
