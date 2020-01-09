#include <rend/rend.h>
#include <sr1/memory>
#include <SDL2/SDL.h>

#include <iostream>

using namespace rend;

const char* src =
"\n#ifdef VERTEX\n" \
"attribute vec2 a_Position;" \
""\
"uniform mat4 u_Projection;" \
"uniform mat4 u_Model;" \
"" \
"void main()" \
"{" \
"  gl_Position = u_Projection * u_Model * vec4(a_Position, 0, 1);" \
"}" \
"" \
"\n#endif\n" \
"\n#ifdef FRAGMENT\n" \
"" \
"void main()" \
"{" \
"  gl_FragColor = vec4(1, 0, 0, 1);" \
"}" \
"" \
"\n#endif\n";

int main()
{
  std::cout << "Rend GUI Test" << std::endl;

  SDL_Window* window = SDL_CreateWindow("Rend Mesh Test",
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

  std::sr1::shared_ptr<Buffer> buffer = context->createBuffer();
  buffer->add(vec2(0, 0));
  buffer->add(vec2(0, 1));
  buffer->add(vec2(1, 1));

  buffer->add(vec2(1, 1));
  buffer->add(vec2(1, 0));
  buffer->add(vec2(0, 0));
  shape->setBuffer("a_Position", buffer);

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

    shader->setUniform("u_Model", scale(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 1.0f)));
    shader->setUniform("u_Projection", ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f));
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

