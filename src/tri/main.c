#include <re/re.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#define MOUSE_SENSITIVITY 0.5f;

struct State;

struct Camera
{
  ReVec3 position;
  ReVec3 rotation;
  ref(State) state;
};

struct Object
{
  int id;
  int type;
  ReVec3 position;
  ReVec3 rotation;
  ReVec3 scale;
  ref(State) state;
};

struct State
{
  SDL_Window *window;
  SDL_GLContext glContext;
  ReVec2 keyboard;
  ReVec2 mouse;
  ReVec2 mouseGrab;
  ref(Camera) camera;
  vector(ref(Object)) objects;
};

ref(State) StateCreate();
void StateDestroy(ref(State) ctx);
void CameraUpdate(ref(Camera) ctx);
ReMat4 CameraView(ref(Camera) ctx);
ReMat4 CameraProjection(ref(Camera) ctx);

int main()
{
  ReVec4 col = ReVec4Rgba(1, 0, 0, 0.5f);
  ReMat4 model = ReMat4Identity();
  float rotation = 0;
  ref(State) state = NULL;

  ref(ReContext) context = NULL;
  ref(ReRenderer) renderer = NULL;
  ref(ReBuffer) positions = NULL;
  ref(ReBuffer) normals = NULL;

  state = StateCreate();

  context = ReContextCreate();
  renderer = ReContextCreateRenderer(context);

  positions = ReContextCreateBuffer(context);
  ReBufferAddVec2(positions, ReVec2Xy(0, 0.5f));
  ReBufferAddVec2(positions, ReVec2Xy(-0.5f, -0.5f));
  ReBufferAddVec2(positions, ReVec2Xy(0.5f, -0.5f));

  normals = ReContextCreateBuffer(context);
  ReBufferAddVec3(normals, ReVec3Xyz(0, 0, 1));
  ReBufferAddVec3(normals, ReVec3Xyz(0, 0, 1));
  ReBufferAddVec3(normals, ReVec3Xyz(0, 0, 1));

  int running = 1;
  SDL_Event e = {0};

  while(running)
  {
    while(SDL_PollEvent(&e) != 0)
    {
      if(e.type == SDL_QUIT)
      {
        running = 0;
      }
      else if(e.type == SDL_MOUSEMOTION)
      {
        _(state).mouse = ReVec2Xy(e.motion.x, e.motion.y);
      }
      else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT)
      {
        _(state).mouse = ReVec2Xy(e.button.x, e.button.y);
        _(state).mouseGrab = _(state).mouse;
      }
      else if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT)
      {
        _(state).mouse = ReVec2Xy(e.button.x, e.button.y);
        _(state).mouseGrab = ReVec2Xy(-1, -1);
      }
      else if(e.type == SDL_KEYDOWN)
      {
        if(e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w)
        {
          _(state).keyboard.y = 1;
        }
        else if(e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s)
        {
          _(state).keyboard.y = -1;
        }
        else if(e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)
        {
          _(state).keyboard.x = 1;
        }
        else if(e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)
        {
          _(state).keyboard.x = -1;
        }
      }
      else if(e.type == SDL_KEYUP)
      {
        if(e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w ||
          e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s)
        {
          _(state).keyboard.y = 0;
        }
        else if(e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d ||
          e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)
        {
          _(state).keyboard.x = 0;
        }
      }
    }

    CameraUpdate(_(state).camera);

    col.x += 0.01f;
    rotation += 1;

    if(col.x > 1)
    {
      col.x = 0;
    }

    col.x = 1;

    model = ReMat4Identity();
    model = ReMat4Translate(model, ReVec3Xyz(0, 0, 0));
    model = ReMat4RotateY(model, rotation);
    //model = ReMat4Translate(model, ReVec3Xyz(0, 0, -3));
    //model = ReMat4RotateZ(model, -rotation * 2);

    ReRendererClear(renderer, ReVec4Rgba(0.39f, 0.58f, 0.93f, 1.0f));

    ReRendererSetBackfaceCull(renderer, 0);
    ReRendererSetModel(renderer, model);
    ReRendererSetView(renderer, CameraView(_(state).camera));
    ReRendererSetProjection(renderer, CameraProjection(_(state).camera));
    ReRendererSetColor(renderer, col);
    ReRendererSetPositionBuffer(renderer, positions);
    ReRendererSetNormalBuffer(renderer, normals);
    ReRendererRender(renderer);

    SDL_GL_SwapWindow(_(state).window);
  }

  ReBufferDestroy(positions);
  ReBufferDestroy(normals);
  ReRendererDestroy(renderer);
  ReContextDestroy(context);

  StateDestroy(state);

  return 0;
}

ref(State) StateCreate()
{
  ref(State) rtn = NULL;
  ref(Camera) cam = NULL;

  if(SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    panic("Failed to initialize window system");
  }

  rtn = allocate(State);

  _(rtn).window = SDL_CreateWindow("Re Test",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    800, 600,
    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  if(!_(rtn).window)
  {
    panic("Failed to create window");
  }

  _(rtn).glContext = SDL_GL_CreateContext(_(rtn).window);

  if(!_(rtn).glContext)
  {
    panic("Failed to create OpenGL context");
  }

  _(rtn).camera = allocate(Camera);
  _(rtn).mouseGrab = ReVec2Xy(-1, -1);

  cam = _(rtn).camera;
  _(cam).state = rtn;
  _(cam).position = ReVec3Xyz(0, 10, 10);
  _(cam).rotation = ReVec3Xyz(-45, 0, 0);

  _(rtn).objects = vector_new(ref(Object));

  return rtn;
}

void StateDestroy(ref(State) ctx)
{
  release(_(ctx).camera);
  vector_delete(_(ctx).objects);

  SDL_GL_DeleteContext(_(ctx).glContext);
  SDL_DestroyWindow(_(ctx).window);
  SDL_Quit();

  release(ctx);
}

void CameraUpdate(ref(Camera) ctx)
{
  ref(State) state = NULL;
  ReMat4 m = CameraView(ctx);
  ReVec4 v = {0};
  ReVec2 mouse = {0};
  ReVec2 keyboard = {0};
  ReVec2 mg = {0};

  state = _(ctx).state;
  mg = _(_(ctx).state).mouseGrab;

  if(mg.x != -1)
  {
    SDL_WarpMouseInWindow(_(state).window, mg.x, mg.y);
    mouse = _(state).mouse;
    _(ctx).rotation.x -= (mouse.y - mg.y) * MOUSE_SENSITIVITY;
    _(ctx).rotation.y += (mouse.x - mg.x) * MOUSE_SENSITIVITY;
  }

  keyboard = _(state).keyboard;

  m = ReMat4Inverse(m);
  m = ReMat4Translate(m, ReVec3Xyz(keyboard.x * 0.1f, 0, keyboard.y * -0.1f));
  v = ReMat4MulVec4(m, ReVec4Xyzw(0, 0, 0, 1));
  _(ctx).position = ReVec3Xyz(v.x, v.y, v.z);
}

ReMat4 CameraView(ref(Camera) ctx)
{
  ReMat4 rtn = ReMat4Identity();

  rtn = ReMat4Translate(rtn, _(ctx).position);
  rtn = ReMat4RotateY(rtn, _(ctx).rotation.y);
  rtn = ReMat4RotateX(rtn, _(ctx).rotation.x);
  rtn = ReMat4Inverse(rtn);

  return rtn;
}

ReMat4 CameraProjection(ref(Camera) ctx)
{
  int w = 0;
  int h = 0;

  SDL_GetWindowSize(_(_(ctx).state).window, &w, &h);
  glViewport(0, 0, w, h);

  return ReMat4Perspective(45, (float)w / (float)h, 0.1f, 100.0f);
}

