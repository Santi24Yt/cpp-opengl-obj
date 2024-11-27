#ifndef MODELO_H
#define MODELO_H

#include <vector>
#include <GL/glew.h>
#include "vecmatriz.h"
#include "objreader.h"
#include "shader.h"

using namespace std;

class Modelo {
  public:
  vector<Vector4> verticesCam;
  vector<pair<int, int>> pixeles;
  vector<vector<int>> caras;
  GLfloat *vertices = nullptr;
  GLuint *indices = nullptr;
  GLuint VAO, VBO, EBO;
  Shader* shader;

  Modelo(Obj* objp)
  {
    this->obj = objp;
    for (Puntof p : (*objp).vertices)
    {
      verticesModelo.push_back(Vector4(p.x, p.y, p.z, p.w));
    }
    verticesCam = verticesModelo;
    pixeles.resize(verticesModelo.size());
    caras = (*objp).caras;
  };

  void toScreen(Matrix4 &vista, int w, int h);
  void restoreVertices();
  void transform(Matrix4 &transform);

  size_t indiceVerticeCara(vector<int> &cara, size_t i);

  void genVertexArray();
  void initgl();
  void rendergl(Vector3 &posCam, Matrix4 &look, Matrix4 &proy, Matrix4 &vista);

  ~Modelo()
  {
    delete [] vertices;
    delete [] indices;

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
  }

  private:
  Obj* obj;
  vector<Vector4> verticesModelo;
};

#endif
