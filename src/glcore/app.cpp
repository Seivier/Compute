#include <glcore/app.h>


void App::run() {
  init();
  while(!isFinished()) {
    logic();
    render();
  }
}
