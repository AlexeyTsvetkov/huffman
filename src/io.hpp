#ifndef IO_HPP
#define IO_HPP

#include <cstddef>
#include <cstdint>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class BufferedReader {
public: 
  BufferedReader(std::string path);

  bool FileEmpty();
  void Reset();
  bool ReadByte(unsigned char& val);
  bool ReadBit(bool& val);
  bool ReadSize(uint64_t& val);
  bool ReadInt(unsigned int& val);

  uint64_t BytesRead();

  static const size_t kByteSize = 8;
private:
  BufferedReader(const BufferedReader& other);
  BufferedReader& operator=(BufferedReader& other);

  std::ifstream input_;
  size_t bit_num_;
  uint64_t bytes_read_;
  char byte_;
};

class BufferedWriter {
public: 
  BufferedWriter(std::string path);
  ~BufferedWriter();

  void WriteByte(unsigned char val);
  void WriteBit(bool val);
  void WriteSize(uint64_t val);
  void WriteInt(unsigned int val);

  static const uint64_t kByteSize = 8;
private:
  BufferedWriter(const BufferedWriter& other);
  BufferedWriter& operator=(BufferedWriter& other);

  std::ofstream output_;
  size_t bit_num_;
  char byte_;
};

#endif