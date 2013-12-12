#include <cstddef>
#include <cstdlib>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

#include "huffman.hpp"

static bool COMPRESS, DECOMPRESS, INPUT, OUTPUT;
static std::string INPUT_PATH, OUTPUT_PATH;

bool parseArgs(int argc, char** argv);

int main(int argc, char** argv) {
  if(!parseArgs(argc, argv)) {
    std::cerr << "usage: [-c|-d] -i <file> -o <file>" << std::endl;
    exit(EXIT_FAILURE);
  }
  
  Huffman huffman(INPUT_PATH, OUTPUT_PATH);

  if(COMPRESS) {
    huffman.Encode();
  } else {
    huffman.Decode();
  }
  return 0;
}

bool parseArgs(int argc, char** argv) {
  int c;
  extern int optopt, opterr;
  extern char* optarg;
  opterr = 0;

  while((c = getopt(argc, argv, "cdi:o:")) != EOF) {
    switch(c) {
      case 'c':
        COMPRESS = true;
        break;
      case 'd':
        DECOMPRESS = true;
        break;
      case 'i':
        INPUT = true;
        INPUT_PATH.assign(optarg);
        break;
      case 'o':
        OUTPUT = true;
        OUTPUT_PATH.assign(optarg);
        break;
      case '?':
        if(optopt == 'i') {
          std::cerr << "Missing -i <intput path> argument." << std::endl;
        }
        if(optopt == 'o') {
          std::cerr << "Missing -o <output path> argument." << std::endl;
        }
        
        std::cerr << "Unknown option." << std::endl;
        return false;
    }
  } 
  
  if(COMPRESS == DECOMPRESS) {
    std::cerr << "Only -c or only -d must be specified." << std::endl;
    return false;
  }   

  if (!INPUT) {
    std::cerr << "Missing -i option." << std::endl;
    return false;
  }

  if (!OUTPUT) {
    std::cerr << "Missing -o option." << std::endl;
    return false;
  }

  return true;
}