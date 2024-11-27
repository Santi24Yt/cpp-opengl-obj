#include "modelo.h"
#include <iostream>
#include <iomanip>

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

size_t Modelo::indiceVerticeCara(vector<int> &cara, size_t i)
{
  long ip1 = cara[i];
  size_t i1 = ip1;

  if (ip1 < 0)
    i1 = 1 + verticesModelo.size() + ip1;

  return i1;
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
    // Normales
    vertices[i+3] = 0.0f;
    vertices[i+4] = 0.0f;
    vertices[i+5] = 0.0f;

    // for (int k = 0; k < 6; k++)
    // {
    //   cout << std::fixed << std::setprecision(3);
    //   cout << "vertices[" << (i+k) << "] = " << vertices[i+k] << "f" << endl;
    // }
  }

  indices = new GLuint[caras.size() * 3];

  for (size_t i = 0, j = 0; i < caras.size()*3; i += 3, j++)
  {
    vector<int> cara = caras[j];
    indices[i+0] = (GLuint)(indiceVerticeCara(cara, 0) - 1);
    indices[i+1] = (GLuint)(indiceVerticeCara(cara, 1) - 1);
    indices[i+2] = (GLuint)(indiceVerticeCara(cara, 2) - 1);

    // for (int k = 0; k < 3; k++)
    // {
    //   cout << "indices[" << (i+k) << "] = " << indices[i+k] << endl;
    // }
  }
}

void Modelo::initgl()
{
  shader = new Shader("./shader/cubo.vert", "./shader/cubo.frag");
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
