#include <rend/rend.h>
#include <sr1/memory>
#include <SDL2/SDL.h>

#include <iostream>
#include <fstream>

using namespace rend;

const char* src =
"#ifdef VERTEX                                 \n" \
"                                              \n" \
"attribute vec3 a_Position;                    \n" \
"attribute vec2 a_TexCoord;                    \n" \
"attribute vec3 a_Normal;                      \n" \
"                                              \n" \
"uniform mat4 u_Projection;                    \n" \
"uniform mat4 u_Model;                         \n" \
"                                              \n" \
"varying vec3 v_Normal;                        \n" \
"varying vec2 v_TexCoord;                      \n" \
"                                              \n" \
"void main()                                   \n" \
"{                                             \n" \
"  gl_Position = u_Projection *                \n" \
"    u_Model * vec4(a_Position, 1);            \n" \
"                                              \n" \
"  v_Normal = a_Normal;                        \n" \
"  v_TexCoord = a_TexCoord;                    \n" \
"}                                             \n" \
"                                              \n" \
"#endif                                        \n" \
"#ifdef FRAGMENT                               \n" \
"                                              \n" \
"varying vec3 v_Normal;                        \n" \
"varying vec2 v_TexCoord;                      \n" \
"                                              \n" \
"void main()                                   \n" \
"{                                             \n" \
"  gl_FragColor = vec4(v_TexCoord, 0, 1);      \n" \
"  gl_FragColor.z = v_Normal.x;                \n" \
"}                                             \n" \
"                                              \n" \
"#endif                                        \n";

int main()
{
  std::cout << "Rend Rotate Test" << std::endl;

  SDL_Window* window = SDL_CreateWindow("Rend Rotate Test",
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

  std::sr1::shared_ptr<Context> context = Context::initialize();
  std::sr1::shared_ptr<Shader> shader = context->createShader();
  shader->parse(src);

  std::sr1::shared_ptr<Mesh> shape = context->createMesh();

  {
    std::ifstream f("share/rend/samples/curuthers/curuthers.obj");
    std::string obj;
    std::string line;

    while(!f.eof())
    {
      std::getline(f, line);
      obj += line + "\n";
    }

    shape->parse(obj);
  }

  bool running = true;
  SDL_Event e = {0};

  float angle = 0;

  while(running)
  {
    while(SDL_PollEvent(&e) != 0)
    {
      if(e.type == SDL_QUIT)
      {
        running = false;
      }
    }

    angle++;

    glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->setUniform("u_Projection", perspective(radians(45.0f), 1.0f, 0.1f, 100.0f));

    shader->setUniform("u_Model",
      translate(vec3(0, 0, -10)) *
      rotate(radians(angle), vec3(0, 1, 0))
    );

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

