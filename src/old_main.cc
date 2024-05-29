#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glcore/camera.h"
#include <glcore/app.h>
#include <glcore/buffer.h>
#include <glcore/shader.h>
#include <glcore/texture.h>

#include <iostream>
#include <vector>

int width = 800;
int height = 600;
void framebuffer_size_callback(GLFWwindow *window, int w, int h) {
  // std::cout << width << " " << height << std::endl;
  width = w;
  height = h;
}

Camera *cam;
float xcam = 0.f;
float ycam = 0.f;
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  if (action == GLFW_PRESS) {
    if (key == GLFW_KEY_W) {
      ycam += 1.f;
    }
    if (key == GLFW_KEY_S) {
      ycam -= 1.f;
    }
    if (key == GLFW_KEY_D) {
      xcam += 1.f;
    }
    if (key == GLFW_KEY_A) {
      xcam -= 1.f;
    }
    if (key == GLFW_KEY_ESCAPE)
      glfwSetWindowShouldClose(window, 1);
  }
  if (action == GLFW_RELEASE) {
    if (key == GLFW_KEY_W) {
      ycam -= 1.f;
    }
    if (key == GLFW_KEY_S) {
      ycam += 1.f;
    }
    if (key == GLFW_KEY_D) {
      xcam -= 1.f;
    }
    if (key == GLFW_KEY_A) {
      xcam += 1.f;
    }
  }
  cam->key_callback(xcam, ycam);
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
  cam->cursor_position_callback(xpos, -ypos);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  cam->scroll_callback(yoffset);
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  GLFWwindow *window =
      glfwCreateWindow(width, height, "Learn OpenGL", NULL, NULL);
  if (window == NULL) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);
  glfwSetScrollCallback(window, scroll_callback);

  Shader *sh = new Shader(RESOURCES_PATH "shader/vertex.glsl",
                          RESOURCES_PATH "shader/fragment.glsl");
  Buffer *buf = new Buffer(
      {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
       0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
       -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

       -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
       -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

       -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
       -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
       -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

       0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
       0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
       0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

       -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
       0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
       -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

       -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f});

  Texture *container = new Texture(RESOURCES_PATH "img/container.jpg");
  Texture *face = new Texture(RESOURCES_PATH "img/awesomeface.png");
  Texture *green = new Texture({0, 255, 0}, 1, 1, 3);

  cam = new Camera;
  cam->speed = 2.f;
  cam->distance = 2.f;

  buf->addTexture(container);
  buf->addTexture(face);

  glEnable(GL_DEPTH_TEST);

  glm::vec3 cubePositions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

  float deltaTime = 0.f;
  float lastFrame = 0.f;

  while (!glfwWindowShouldClose(window)) {

    // logic
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    cam->update(deltaTime);

    // rendering
    glViewport(0, 0, width, height);
    glClearColor(.2f, .3f, .3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sh->use();
    const float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    glm::mat4 view = cam->view();
    sh->set("view", view);
    glm::mat4 projection;
    projection =
        glm::perspective(glm::radians(cam->zoom),
                         ((float)width) / ((float)height), 0.1f, 100.0f);
    sh->set("projection", projection);
    sh->set("tex1", 0);
    sh->set("tex2", 1);
    for (size_t i = 0; i < 10; i++) {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      model =
          glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      sh->set("model", model);
      buf->draw();
    }
    // check events
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
  delete cam;
  delete sh;
  delete buf;
  delete container;
  delete green;
  delete face;
  glfwTerminate();
  return 0;
}
