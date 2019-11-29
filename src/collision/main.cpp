#include <rend/rend.h>
#include <sr1/memory>
#include <SDL2/SDL.h>

#include <iostream>

using namespace rend;

const char* src =
"\n#ifdef VERTEX\n" \
"attribute vec2 a_Position;" \
"" \
"void main()" \
"{" \
"  gl_Position = vec4(a_Position, 0, 1);" \
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

bool triangle_intersect(vec3 a1, vec3 b1, vec3 c1,
                        vec3 a2, vec3 b2, vec3 c2);

int main()
{
  std::cout << "Rend Test" << std::endl;

  SDL_Window* window = SDL_CreateWindow("Rend Test",
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

  vec3 a1 = vec3(0, 0.4f, 0);
  vec3 b1 = vec3(-0.5f, -0.5f, 0);
  vec3 c1 = vec3(0.5f, -0.5f, 0);

  vec3 a2 = vec3(0, 1.5f, 0);
  vec3 b2 = vec3(-0.5f, 0.5f, 0);
  vec3 c2 = vec3(0.5f, 0.5f, 0);

  std::sr1::shared_ptr<Buffer> shape1 = context->createBuffer();
  shape1->add(vec2(a1.x, a1.y));
  shape1->add(vec2(b1.x, b1.y));
  shape1->add(vec2(c1.x, c1.y));

  std::sr1::shared_ptr<Buffer> shape2 = context->createBuffer();
  shape2->add(vec2(a2.x, a2.y));
  shape2->add(vec2(b2.x, b2.y));
  shape2->add(vec2(c2.x, c2.y));

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

    if(triangle_intersect(a1, b1, c1, a2, b2, c2) == true)
    {
      std::cout << "Colliding" << std::endl;
    }

    glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->setAttribute("a_Position", shape1);
    shader->render();

    shader->setAttribute("a_Position", shape2);
    shader->render();

    SDL_GL_SwapWindow(window);
  }

  // These should be called after rend::Context is out of scope
/*
  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();
*/

  return 0;
}

bool triangle_intersect(vec3 a1, vec3 b1, vec3 c1,
                        vec3 a2, vec3 b2, vec3 c2)
{
  int NoDivTriTriIsect(float V0[3],float V1[3],float V2[3],
                       float U0[3],float U1[3],float U2[3]);

  if(NoDivTriTriIsect((float*)&a1, (float*)&b1, (float*)&c1,
                      (float*)&a2, (float*)&b2, (float*)&c2) == 1)
  {
    return true;
  }

  return false;
}
