#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "modelo.h"

class Model{
public:

    Shader* shader;
    GLfloat *vertices;
    size_t vn;
    GLuint *indices;
    size_t in;
    float angle;
    glm::mat4 modelmat;
    GLuint VAO, VBO, EBO;

    Model();
    //Model(GLfloat* vertices, GLuint indices);
    Model(Modelo &m);

    void initModel();
    void renderModel(glm::vec3 poscam, glm::mat4 view, glm::mat4 projection);
    void updateModel(float timeValue);
    void finish();


};
