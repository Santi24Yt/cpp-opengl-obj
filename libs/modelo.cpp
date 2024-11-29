#include "modelo.h"
#include <iostream>

void Modelo::toScreen(Matrix4 &vista, int wi, int h)
{
  for (size_t i = 0; i < verticesCam.size(); i++)
  {
    verticesCam[i] = vista.multiplyVector(verticesModelo[i]);
    double w = verticesCam[i].w;
    verticesCam[i] = Vector4(verticesCam[i].x/w, verticesCam[i].y/w, verticesCam[i].z, verticesCam[i].w);

    int x = (verticesCam[i].x + 1)/2 * wi;
    int y = (verticesCam[i].y + 1)/2 * h;
    pair<int, int> pixel(x, y);
    pixeles[i] = pixel;
  }
}

void Modelo::restoreVertices()
{
  for (size_t i = 0; i < (*obj).vertices.size(); i++)
  {
    Puntof p = (*obj).vertices[i];
    verticesModelo[i] = Vector4(p.x, p.y, p.z, p.w);
  }
}

void Modelo::transform(Matrix4 &transform)
{
  for (size_t i = 0; i < verticesCam.size(); i++)
  {
    verticesModelo[i] = transform.multiplyVector(verticesModelo[i]);
  }
}

size_t Modelo::indiceVertice(int i)
{
  long ip1 = i;
  size_t i1 = ip1;

  if (ip1 < 0)
    i1 = 1 + verticesModelo.size() + ip1;

  return i1 - 1;
}

size_t Modelo::indiceNormal(int i)
{
  long ip1 = i;
  size_t i1 = ip1;

  if (ip1 < 0)
    i1 = 1 + normales.size() + ip1;

  return i1 - 1;
}

void Modelo::genVertexArray()
{
  vertices = new GLfloat[verticesModelo.size() * 3 * 2];
  if (caras[0].size() != 3)
  {
    std::cerr << "Caras no triangulares no implementados" << std::endl;
    return;
  }

  for (size_t i = 0, j = 0; i < verticesModelo.size()*3*2; i += 6, j++)
  {
    Vector4 p = verticesModelo[j];
    vertices[i+0] = (GLfloat)p.x;
    vertices[i+1] = (GLfloat)p.y;
    vertices[i+2] = (GLfloat)p.z;

    vertices[i+3] = (GLfloat)0;
    vertices[i+4] = (GLfloat)0;
    vertices[i+5] = (GLfloat)0;
  }

  indices = new GLuint[caras.size() * 3];

  for (size_t i = 0, j = 0; i < caras.size()*3; i += 3, j++)
  {
    vector<int> cara = caras[j];
    indices[i+0] = (GLuint)indiceVertice(cara[0]);
    indices[i+1] = (GLuint)indiceVertice(cara[1]);
    indices[i+2] = (GLuint)indiceVertice(cara[2]);
  }

  for (pair<int, int> p : normIndex)
  {
    int vi = indiceVertice(p.first)*6;
    size_t ni = indiceNormal(p.second);

    if (ni < normales.size())
    {
      Vector3 normal = normales[ni];

      if (vertices[vi+3+0] == (GLfloat)0.0f)
        vertices[vi+3+0] = (GLfloat)normal.x;

      if (vertices[vi+3+1] == (GLfloat)0.0f)
        vertices[vi+3+1] = (GLfloat)normal.y;

      if (vertices[vi+3+2] == (GLfloat)0.0f)
        vertices[vi+3+2] = (GLfloat)normal.z;
    }
  }
}

void Modelo::initgl(string vert, string frag)
{
  shader = new Shader(vert.c_str(), frag.c_str());
  modelmat = Matrix4();

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);


  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, verticesModelo.size()*3*2*sizeof(GLfloat), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, caras.size()*3*sizeof(GLuint), indices, GL_STATIC_DRAW);


  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
}

void Modelo::rendergl(Vector3 &posCam, Matrix4 &look, Matrix4 &proy)
{
  shader->use();

  shader->setVec3("posCam", posCam.glm());
  shader->setMat4x4("model", modelmat.glm());
  shader->setMat4x4("view", look.glm());
  shader->setMat4x4("projection", proy.glm());

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, caras.size()*3, GL_UNSIGNED_INT, 0);
}

void Modelo::update(float t)
{
  float angle = t * (M_PI_4); // 45 grados por segundo
  modelmat = Matrix4::rotateY(angle);
}
