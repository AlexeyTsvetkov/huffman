#include <cstddef>

#include <limits>
#include <queue>

#include "tree.hpp"

Tree::Tree(size_t letter): left_(nullptr), 
                           right_(nullptr), 
                           letter_(letter),
                           priority_(0) {}

Tree::Tree(size_t letter, unsigned int priority): left_(nullptr), 
                                                  right_(nullptr),
                                                  letter_(letter),
                                                  priority_(priority) {}

Tree::Tree(Tree* left, Tree* right): left_(left), right_(right),
                                     letter_(std::numeric_limits<std::size_t>::max()),
                                     priority_(left->priority_ + right->priority_) {}

bool Tree::HasLetter() const {
  size_t max = std::numeric_limits<std::size_t>::max();
  return letter_ < max;
}

size_t Tree::GetLetter() const {
  return letter_;
}

unsigned int Tree::GetPriority() const {
  return priority_;
}

const Tree* Tree::GetLeft() const {
  return left_;
}

const Tree* Tree::GetRight() const {
  return right_;
}

void TreeDelete(const Tree* tree) {
  if(tree == nullptr) {
    return;
  }

  TreeDelete(tree->GetLeft());  
  TreeDelete(tree->GetRight());

  delete tree;
}

bool TreeComp::operator()(const Tree* first, const Tree* second) const { 
  return first->GetPriority() > second->GetPriority(); 
}