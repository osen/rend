#include "internal.h"

const char *vertSrc =
  "attribute vec4 a_Position;              " \
  "uniform mat4 u_Model;                   " \
  "                                        " \
  "void main()                             " \
  "{                                       " \
  "  gl_Position = u_Model * a_Position;   " \
  "}                                       " \
  "                                        ";

const char *fragSrc =
  "uniform vec4 u_Color;                    " \
  "                                         " \
  "void main()                              " \
  "{                                        " \
  "  vec4 col = vec4(1, 1, 1, 1) * u_Color; " \
  "  gl_FragColor = col;                    " \
  "}                                        ";

ref(ReShader) _ReShaderCreate(ref(ReContext) context)
{
  ref(ReShader) rtn = NULL;
  GLuint vertId = 0;
  GLuint fragId = 0;
  int success = 0;
  int length = 0;
  vector(GLchar) infoLog = NULL;

  rtn = allocate(ReShader);
  _(rtn).id = glCreateProgram();
  _RePollForError();

  if(_(rtn).id == 0)
  {
    panic("Failed to create shader program");
  }

  vertId = glCreateShader(GL_VERTEX_SHADER);
  _RePollForError();

  glShaderSource(vertId, 1, &vertSrc, NULL);
  _RePollForError();

  glCompileShader(vertId);
  _RePollForError();

  glGetShaderiv(vertId, GL_COMPILE_STATUS, &success);
  _RePollForError();

  if(!success)
  {
    glGetShaderiv(vertId, GL_INFO_LOG_LENGTH, &length);
    _RePollForError();

    infoLog = vector_new(GLchar);
    vector_resize(infoLog, length);

    glGetShaderInfoLog(vertId, length, NULL, &vector_at(infoLog, 0));
    _RePollForError();

    panic(&vector_at(infoLog, 0));
  }

  fragId = glCreateShader(GL_FRAGMENT_SHADER);
  _RePollForError();

  glShaderSource(fragId, 1, &fragSrc, NULL);
  _RePollForError();

  glCompileShader(fragId);
  _RePollForError();

  glGetShaderiv(fragId, GL_COMPILE_STATUS, &success);
  _RePollForError();

  if(!success)
  {
    glGetShaderiv(fragId, GL_INFO_LOG_LENGTH, &length);
    _RePollForError();

    infoLog = vector_new(GLchar);
    vector_resize(infoLog, length);

    glGetShaderInfoLog(fragId, length, NULL, &vector_at(infoLog, 0));
    _RePollForError();

    panic(&vector_at(infoLog, 0));
  }

  glAttachShader(_(rtn).id, vertId);
  _RePollForError();

  glAttachShader(_(rtn).id, fragId);
  _RePollForError();

  glBindAttribLocation(_(rtn).id, 0, "a_Position");
  _RePollForError();

  glLinkProgram(_(rtn).id);
  _RePollForError();

  glGetProgramiv(_(rtn).id, GL_LINK_STATUS, &success);
  _RePollForError();

  if(!success)
  {
    glGetProgramiv(_(rtn).id, GL_INFO_LOG_LENGTH, &length);
    _RePollForError();

    infoLog = vector_new(GLchar);
    vector_resize(infoLog, length);

    glGetProgramInfoLog(_(rtn).id, length, NULL, &vector_at(infoLog, 0));
    _RePollForError();

    panic(&vector_at(infoLog, 0));
  }

  glDetachShader(_(rtn).id, vertId);
  _RePollForError();

  glDetachShader(_(rtn).id, fragId);
  _RePollForError();

  glDeleteShader(vertId);
  _RePollForError();

  glDeleteShader(fragId);
  _RePollForError();

  _(rtn).colorLoc = glGetUniformLocation(_(rtn).id, "u_Color");
  _RePollForError();
  if(_(rtn).colorLoc == -1) panic("Shader did not provide specified uniform");

  _(rtn).modelLoc = glGetUniformLocation(_(rtn).id, "u_Model");
  _RePollForError();
  if(_(rtn).modelLoc == -1) panic("Shader did not provide specified uniform");

  return rtn;
}

void _ReShaderDestroy(ref(ReShader) ctx)
{
  glDeleteProgram(_(ctx).id);
  release(ctx);
}

GLuint _ReShaderId(ref(ReShader) ctx)
{
  return _(ctx).id;
}

GLint _ReShaderColorLoc(ref(ReShader) ctx)
{
  return _(ctx).colorLoc;
}

GLint _ReShaderModelLoc(ref(ReShader) ctx)
{
  return _(ctx).modelLoc;
}
