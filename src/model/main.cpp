#include <rend/rend.h>
#include <memory>
#include <SDL2/SDL.h>

#include <iostream>

using namespace rend;

const char* src =
"#ifdef VERTEX                                 \n" \
"                                              \n" \
"attribute vec3 a_Position;                    \n" \
"attribute vec2 a_TexCoord;                    \n" \
"                                              \n" \
"uniform mat4 u_Projection;                    \n" \
"                                              \n" \
"varying vec2 v_TexCoord;                      \n" \
"                                              \n" \
"void main()                                   \n" \
"{                                             \n" \
"  vec3 pos = a_Position + vec3(0, 0, -5);     \n" \
"  gl_Position = u_Projection * vec4(pos, 1);  \n" \
"  v_TexCoord = a_TexCoord;                    \n" \
"}                                             \n" \
"                                              \n" \
"#endif                                        \n" \
"#ifdef FRAGMENT                               \n" \
"                                              \n" \
"varying vec2 v_TexCoord;                      \n" \
"                                              \n" \
"void main()                                   \n" \
"{                                             \n" \
"  gl_FragColor = vec4(v_TexCoord, 0, 1);      \n" \
"}                                             \n" \
"                                              \n" \
"#endif                                        \n";

const char* obj =
"v -1 1 0           \n" \
"v -1 -1 0          \n" \
"v 1 -1 0           \n" \
"v 1 1 0            \n" \
"                   \n" \
"vt 0 1             \n" \
"vt 0 0             \n" \
"vt 1 0             \n" \
"vt 1 1             \n" \
"                   \n" \
"f 1/1 2/2 3/3 4/4  \n" \
"                   \n";

int main()
{
  std::cout << "Rend Model Test" << std::endl;

  SDL_Window* window = SDL_CreateWindow("Rend Model Test",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    800, 600,
    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  if(!window)
  {
    throw Exception("Failed to create window");
  }

  SDL_GLContext glContext = SDL_GL_CreateContext(window);

  if(!glContext)
  {
    throw Exception("Failed to create OpenGL context");
  }

  std::shared_ptr<Context> context = Context::initialize();
  std::shared_ptr<Shader> shader = context->createShader();
  shader->parse(src);

  std::shared_ptr<Mesh> shape = context->createMesh();
  shape->parse(obj);

  bool running = true;
  SDL_Event e = {0};

  while(running)
  {
    while(SDL_PollEvent(&e) != 0)
    {
      if(e.type == SDL_QUIT)
      {
        running = false;
      }
    }

    glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->setUniform("u_Projection", perspective(radians(45.0f), 1.0f, 0.1f, 100.0f));
    shader->setMesh(shape);
    shader->render();

    SDL_GL_SwapWindow(window);
  }

/*
  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();
*/

  return 0;
}

