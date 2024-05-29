#include <glcore/app.h>
#include <iostream>

using std::string;

static App *current = nullptr;

static void global_framebuffer_size_callback(GLFWwindow *window, int w, int h) {
  if (window == current->window) {
    current->framebuffer_size_callback(w, h);
  }
}
static void global_key_callback(GLFWwindow *window, int key, int scancode,
                                int action, int mods) {
  if (window == current->window) {
    current->key_callback(key, scancode, action, mods);
  }
}
static void global_cursor_position_callback(GLFWwindow *window, double xpos,
                                            double ypos) {
  if (window == current->window) {
    current->cursor_position_callback(xpos, ypos);
  }
}

// static void global_scroll_callback(GLFWwindow *window, double xoffset,
//                                    double yoffset) {}

App::App(unsigned int glmajor, unsigned int glminor, int width, int height,
         const string &title)
    : width_(width), height_(height) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glmajor);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glmajor);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if (window == NULL) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(-1);
  }

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    glfwTerminate();
    exit(-1);
  }

  glfwSetFramebufferSizeCallback(window, global_framebuffer_size_callback);
  glfwSetKeyCallback(window, global_key_callback);
  glfwSetCursorPosCallback(window, global_cursor_position_callback);
  // glfwSetScrollCallback(window, global_scroll_callback);
}

App::~App() { glfwTerminate(); }

void App::run() {
  init();
  current = this;
  float lastFrame = 0.f;
  while (!isFinished()) {
    float currentFrame = glfwGetTime();
    update(currentFrame-lastFrame);
    render();
    lastFrame = currentFrame;
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
  current = nullptr;
  finish();
}
