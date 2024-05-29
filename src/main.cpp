#include "glcore/buffer.h"
#include "glcore/camera.h"
#include "glcore/texture.h"
#include <bits/types/wint_t.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glcore/app.h>
#include <glcore/shader.h>

class MyApp : public App {

public:
  Shader *shader;
  Buffer *buffer;
  Texture *texture;
  Camera *cam;
  float xcam = 0.f, ycam = 0.f;

  MyApp() : App(3, 3, 800, 600) {}
  void init() override {
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    shader = new Shader(RESOURCES_PATH "shader/vertex.glsl",
                        RESOURCES_PATH "shader/fragment.glsl");

    buffer = new Buffer(
      {-0.5f, -0.5f, 0.f, 0.0f, 0.0f, 0.5f,  -0.5f, 0.f, 1.0f, 0.0f,
       0.5f,  0.5f,  0.f, 1.0f, 1.0f, 0.5f,  0.5f,  0.f, 1.0f, 1.0f,
       -0.5f, 0.5f,  0.f, 0.0f, 1.0f, -0.5f, -0.5f, 0.f, 0.0f, 0.0f});

    texture = new Texture(RESOURCES_PATH "img/container.jpg");
    buffer->addTexture(texture);

    cam = new Camera({.0f, .0f, -5.f}, 1.f, 90.f);
    // cam->distance = 2.f;
    //
  }
  void render() override {
    glViewport(0, 0, width_, height_);
    glClearColor(.2f, .3f, .3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->use();
    glm::mat4 view = cam->view();
    shader->set("view", view);
    glm::mat4 projection = glm::perspective(glm::radians(cam->zoom),
                         ((float)width_) / ((float)height_), 0.1f, 100.0f);
    shader->set("projection", projection);
    shader->set("tex1", 0);
    glm::mat4 model = glm::mat4(1.0f);
    shader->set("model", model);
    buffer->draw();
  }

  bool isFinished() override { return glfwWindowShouldClose(window); }

  void update(float deltaTime) override {
    // cam->update(deltaTime);
  }

  void framebuffer_size_callback(int w, int h) override {
    height_ = h;
    width_ = w;
  }

  void cursor_position_callback(double xpos, double ypos) override {
    cam->cursor_position_callback(xpos, -ypos);
  }

  void key_callback(int key, int scancode, int action, int mods) override {
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

  void finish() override {
    delete shader;
    delete buffer;
    delete texture;
  }
};

int main() {
  MyApp app;
  app.run();
  return 0;
}
