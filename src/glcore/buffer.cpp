#include <glad/glad.h>
#include <glcore/buffer.h>
#include <iostream>

using vec = std::vector<float>;
using uvec = std::vector<unsigned int>;

Buffer::Buffer() : dirty_(false) {
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glGenBuffers(1, &ebo_);
}

Buffer::Buffer(const vec &vertices, const uvec &indices) : Buffer() {
  vertices_ = vertices;
  indices_ = indices;
  build();
}

Buffer::Buffer(const vec &vertices) : Buffer(vertices, uvec()) {}

Buffer::~Buffer() {
  glDeleteVertexArrays(1, &vao_);
  glDeleteBuffers(1, &vbo_);
  glDeleteBuffers(1, &ebo_);
}

void Buffer::addTexture(Texture *texture) {
  textures_.push_back(texture);
}

void Buffer::draw() {
  if (dirty_) {
    build();
  }
  for (size_t i = 0; i < textures_.size(); i++) {
    glActiveTexture(GL_TEXTURE0+i);
    textures_[i]->bind();
  }
  bind();
  glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
  unbind();
}

void Buffer::bind() {
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
}

void Buffer::unbind() {
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Buffer::build() {
  bind();
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_.size(),
               vertices_.data(), GL_STATIC_DRAW);

  if (indices_.size() == 0) {
    for (unsigned int i = 0; i < vertices_.size(); i++) {
      indices_.push_back(i);
    }
  }
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices_.size(),
               indices_.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  unbind();
  dirty_ = false;
}
