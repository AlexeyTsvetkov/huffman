#include <cstddef>
#include <cstdint>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "io.hpp"

BufferedReader::BufferedReader(std::string path): input_(path.c_str(), std::ios::binary),
                                                  bit_num_(0),
                                                  bytes_read_(0),
                                                  byte_(0) {}

bool BufferedReader::FileEmpty() {
  std::streampos pos = input_.tellg();

  input_.seekg(0, std::ios::end);
  std::streampos end_pos = input_.tellg();

  input_.seekg(pos, std::ios::beg);
  if(end_pos == 0) {
    return true;
  }

  return false; 
}

void BufferedReader::Reset() {
  input_.clear();
  input_.seekg(0, std::ios::beg);
  bytes_read_ = 0;
}

bool BufferedReader::ReadByte(unsigned char& val) {
  val = 0;
  for(size_t i = 0; i < kByteSize; i++) {
    bool bit = false;

    if(ReadBit(bit)) {
      if(bit) {
        val |= (1 << i);
      }
    } else {
      return false;
    }
  }

  return true;
}

bool BufferedReader::ReadBit(bool& val) {
  if(bytes_read_ == 0 || bit_num_ == kByteSize) {
    bit_num_ = 0;
    input_.get(byte_);  
    size_t read_count = input_.gcount();    
    bytes_read_ += read_count;
    if(read_count == 0) {
      return false;
    };
  }
  val = (byte_ & (1 << (bit_num_ % kByteSize))) != 0;
  bit_num_++;
  return true;
}

bool BufferedReader::ReadSize(uint64_t& val) {
  val = 0;
  for (uint64_t i = 0; i < sizeof(uint64_t); i++) {
    unsigned char ith_byte;
    if(!ReadByte(ith_byte)) {
      return false;
    }

    val |= ((uint64_t)ith_byte << (kByteSize * i));
  }

  return true;
}

bool BufferedReader::ReadInt(unsigned int& val) {
  val = 0;
  for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
    unsigned char ith_byte;
    if(!ReadByte(ith_byte)) {
      return false;
    }

    val |= ((unsigned int)ith_byte << (kByteSize * i));
  }

  return true;
}

uint64_t BufferedReader::BytesRead() {
  return bytes_read_;
}

BufferedWriter::BufferedWriter(std::string path): output_(path.c_str(), std::ios::binary),
                                                  bit_num_(0),
                                                  byte_(0) {}
BufferedWriter::~BufferedWriter() {
  if (bit_num_ > 0) {
    output_.put(byte_);
  }
}

void BufferedWriter::WriteByte(unsigned char val) {
  for(size_t i = 0; i < kByteSize; i++) {
    bool bit = (val & (1 << i)) != 0;
    WriteBit(bit);
  }
}

void BufferedWriter::WriteBit(bool val) {
  if (bit_num_ == kByteSize) {
    output_.put(byte_);
    byte_ = 0;
    bit_num_ = 0;
  }

  if(val) {
    byte_ |= (1 << (bit_num_ % kByteSize));
  }

  bit_num_++;
}

void BufferedWriter::WriteSize(uint64_t val) {
  for(uint64_t i = 0; i < sizeof(uint64_t); i++) {
    unsigned char ith_byte = (val >> (kByteSize * i)) & 0xff;
    WriteByte(ith_byte);
  }
}

void BufferedWriter::WriteInt(unsigned int val) {
  for(unsigned int i = 0; i < sizeof(unsigned int); i++) {
    unsigned char ith_byte = (val >> (kByteSize * i)) & 0xff;
    WriteByte(ith_byte);
  }
}