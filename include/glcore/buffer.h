#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "glcore/texture.h"
#include <vector>

class Buffer {
public:
  Buffer();
  Buffer(const std::vector<float> &vertices);
  Buffer(const std::vector<float> &vertices,
         const std::vector<unsigned int> &indices);
  Buffer(Buffer &&) = default;
  Buffer(const Buffer &) = default;
  Buffer &operator=(Buffer &&) = default;
  Buffer &operator=(const Buffer &) = default;
  ~Buffer();

  void addTexture(Texture *texture);
  void draw();

private:
  void bind();
  void unbind();
  void build();
  bool dirty_;
  unsigned int vao_, ebo_, vbo_;
  std::vector<float> vertices_;
  std::vector<unsigned int> indices_;
  std::vector<Texture*> textures_;
};

#endif // _BUFFER_H_
