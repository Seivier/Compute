#ifndef _APP_H_
#define _APP_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class App {
public:
  GLFWwindow* window;

  App(unsigned int glmajor, unsigned int glminor, int width, int height, const std::string &title = "App");
  ~App(); 
  void run();
  virtual bool isFinished() = 0;
  virtual void render() = 0;
  virtual void update(float deltaTime) = 0;
  virtual void init() = 0;
  virtual void finish() = 0;
  virtual void framebuffer_size_callback(int w, int h) = 0;
  virtual void key_callback(int key, int scancode, int action, int mods) = 0;
  virtual void cursor_position_callback(double xpos, double ypos) = 0;
  // virtual void scroll_callback(double xoffset, double yoffset);
protected:
  int height_;
  int width_;
};

#endif // _APP_H_
