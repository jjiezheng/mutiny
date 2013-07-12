#include "Gui.h"
#include "Screen.h"
#include "Rect.h"
#include "Material.h"
#include "Shader.h"
#include "Camera.h"
#include "Vector3.h"
#include "Debug.h"

#include <GL/glew.h>

#include <vector>
#include <string>
#include <iostream>

namespace mutiny
{

namespace engine
{

GLuint Gui::positionBufferId = -1;
GLuint Gui::uvBufferId = -1;

Matrix4x4 Gui::getMatrix()
{
  return Matrix4x4::ortho(0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1);
}

bool Gui::button(Rect rect, std::string text)
{
  return false;
}

void Gui::drawTexture(Rect rect, Texture* texture)
{
  float x = (float)rect.x;
  float y = (float)rect.y;
  float xw = (float)rect.x + (float)rect.width;
  float yh = (float)rect.y + (float)rect.height;

  GLfloat positions[] = {
    x, y,
    x, yh,
    xw, yh,
    xw, yh,
    xw, y,
    x, y
  };

  GLfloat uv[] = {
    0, 0,
    0, 1,
    1, 1,
    1, 1,
    1, 0,
    0, 0
  };

  GLuint programId = Material::guiMaterial->getShader()->programId;
  Material::guiMaterial->setMainTexture(texture);
  Material::guiMaterial->setPass(0);

  Material::guiMaterial->setMatrix("in_Projection", getMatrix());
  Material::guiMaterial->setMatrix("in_View", Matrix4x4::getIdentity());
  Material::guiMaterial->setMatrix("in_Model", Matrix4x4::getIdentity());

  GLint positionAttributeId = glGetAttribLocation(programId, "in_Position");
  GLint uvAttributeId = glGetAttribLocation(programId, "in_Uv");

  if(positionAttributeId == -1 ||
     uvAttributeId == -1)
  {
    Debug::logError("Error: Shader does not provide required attributes");
    throw std::exception();
  }

  if(positionBufferId == -1)
  {
    glGenBuffers(1, &positionBufferId);
  }

  glBindBuffer(GL_ARRAY_BUFFER, positionBufferId);
  glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(positions[0]), positions, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(positionAttributeId, 2, GL_FLOAT, GL_FALSE, 0, 0);

  if(uvBufferId == -1)
  {
    glGenBuffers(1, &uvBufferId);
  }

  glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
  glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(uv[0]), uv, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(uvAttributeId, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glEnableVertexAttribArray(positionAttributeId);
  glEnableVertexAttribArray(uvAttributeId);
  glDisable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glCullFace(GL_FRONT);
  glEnable(GL_DEPTH_TEST);
  glDisableVertexAttribArray(positionAttributeId);
  glDisableVertexAttribArray(uvAttributeId);
}

void Gui::box(Rect rect, std::string text)
{
  //drawTexture(rect, NULL);
}

}

}
