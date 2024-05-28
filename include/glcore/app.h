#ifndef _APP_H_
#define _APP_H_

class App {
public:
  void run();
  virtual bool isFinished() = 0;
  virtual void render() = 0;
  virtual void logic() = 0;
  virtual void init() = 0;
};

#endif // _APP_H_
