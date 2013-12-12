#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>

#include <functional>

class Tree {
public:
  Tree(size_t letter);
  Tree(size_t letter, unsigned int priority);
  Tree(Tree* left, Tree* right);

  bool HasLetter() const;
  size_t GetLetter() const;
  unsigned int GetPriority() const;
  const Tree* GetLeft() const;
  const Tree* GetRight() const;


private:
  Tree& operator=(const Tree other);
  Tree(const Tree& other);

  const Tree* left_;
  const Tree* right_;
  size_t letter_;
  unsigned int priority_;
};

void TreeDelete(const Tree* tree);

struct TreeComp: public std::binary_function<Tree*, Tree*, bool> {
    bool operator()(const Tree* first, const Tree* second) const;
};

#endif