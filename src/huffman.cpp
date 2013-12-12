#include <cstddef>
#include <cstdint>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "huffman.hpp"
#include "tree.hpp"

Huffman::Huffman(std::string input, std::string output): frequences_(kAlphabetSize), 
                                                         codes_(kAlphabetSize),
                                                         input_(input),
                                                         output_(output) {}

void Huffman::Encode() {
  CalculateFrequences();
  const Tree* code_tree = GetCodeTree(); 
  CalculateCodes(code_tree);

  for (size_t i = 0; i < kAlphabetSize; i++) {
    output_.WriteInt(frequences_[i]);
  }
  output_.WriteSize(input_.BytesRead());

  input_.Reset();

  unsigned char letter;

  while(input_.ReadByte(letter)) {
    std::vector<bool>& code = codes_[letter];

    for(size_t i = 0; i < code.size(); i++) {
      output_.WriteBit(code[i]);
    }
  }

  TreeDelete(code_tree);
}

void Huffman::Decode() {
  if(input_.FileEmpty()) {
    return;
  }

  for (size_t i = 0; i < kAlphabetSize; i++) {
    input_.ReadInt(frequences_[i]);
  }
  const Tree* tree = GetCodeTree(); 

  uint64_t size;
  input_.ReadSize(size);
  for(uint64_t i = 0; i < size; i++) {
    const Tree* node = tree;
    bool bit;
    while(!node->HasLetter()) {
      input_.ReadBit(bit);
      node = bit ? node->GetRight() : node->GetLeft();
    }
    output_.WriteByte(node->GetLetter());
  }

  TreeDelete(tree);
}

void Huffman::CalculateFrequences() {
  std::fill(frequences_.begin(), frequences_.end(), 0);

  unsigned char index;        
  while(input_.ReadByte(index)) {
    frequences_[index] += 1;
  }
}

Tree* Huffman::GetCodeTree() {
  std::priority_queue<Tree*, std::vector<Tree*>, TreeComp> code_trees;
  
  for(size_t i = 0; i < kAlphabetSize; i++) {
    code_trees.push(new Tree(i, frequences_[i]));
  }

  while(code_trees.size() > 1) {
    Tree* tree_1 = code_trees.top();
    code_trees.pop();
    Tree* tree_2 = code_trees.top();
    code_trees.pop();

    code_trees.push(new Tree(tree_1, tree_2));
  }

  Tree* result_tree_ptr = code_trees.top();

  return result_tree_ptr;
}

void Huffman::CalculateCodes(const Tree* tree, std::vector<bool> code) {
  if(tree->HasLetter()) {
    codes_[tree->GetLetter()] = code;
    return;
  } 

  code.push_back(false);
  CalculateCodes(tree->GetLeft(), code);

  code.back() = true;
  CalculateCodes(tree->GetRight(), code);
}