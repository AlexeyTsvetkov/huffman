#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <string>
#include <vector>

#include "io.hpp"
#include "tree.hpp"

class Huffman {
public:
  Huffman(std::string input, std::string output);

  void Encode();
  void Decode();

  static size_t const kAlphabetSize = 256;

private:
  Huffman(const Huffman &h);
  Huffman& operator=(const Huffman &h);
  void CalculateFrequences();
  Tree* GetCodeTree();
  void CalculateCodes(const Tree* tree, std::vector<bool> code = std::vector<bool>());

  std::vector<unsigned int> frequences_;
  std::vector<std::vector<bool>> codes_;
  BufferedReader input_;
  BufferedWriter output_;
};

#endif