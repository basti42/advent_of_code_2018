#include <fstream>
#include <iostream>
#include <string>
#include <map>

/*
  Advent of Code 2018 - DAY 01
  Part 1: Starting from a frequency of 0, determine
  the end frequency after a set of mdulations given
  by input.txt file.

  Part 2: Find the first frequency that occurs twice.
*/

// forward declarations
int updateFrequency(std::string&, int, int);
int determineEndfrequency(std::string&, int);
struct Part2;
Part2 determineDoublefrequency(std::string&, int, std::map<int, int>&);

struct Part2 {
  int frequency;
  bool found;
  Part2(int f, bool b):frequency(f), found(b) {}
  Part2():frequency(0), found(false) {}
};


int main (int argc, char** argv){

  // PART 1:
  std::string filename = "input.txt";
  int frequency(0);
  frequency = determineEndfrequency(filename, frequency);
  std::cout << "PART 1: End frequency = " << frequency << std::endl;

  // PART 2:
  filename = "input.txt";
  frequency = 0;
  std::map<int, int> freqs;
  size_t runs(0);
  bool found(false);

  Part2 p;
  while (!found){
    p = determineDoublefrequency(filename, frequency, freqs);
    found = p.found;
    frequency = p.frequency;
  }
  std::cout << "PART 2: Frequency reached twice = " << p.frequency << std::endl;
  return 0;
}

// determines the end frequency after 1 pass through the list
int determineEndfrequency(std::string& inputfile, int frequency){
  std::ifstream infile(inputfile);
  std::string line, sign;
  int modulation;

  while (infile >> line){
    sign = line.at(0);
    modulation = std::stoi(line.substr(1, line.size()));

    // update frequency
    frequency = updateFrequency(sign, frequency, modulation);

    // Testing output
    //std::cout << line << ", Sign: " << sign << ", Value: " << modulation << std::endl;
  }
  return frequency;
}


// determines the end frequency after 1 pass through the list
Part2 determineDoublefrequency(std::string& inputfile, int frequency,
                             std::map<int, int>& freqs ) {

  std::ifstream infile(inputfile);
  std::string line, sign;
  int modulation;
  bool found = false;

  while (infile >> line){
    sign = line.at(0);
    modulation = std::stoi(line.substr(1, line.size()));

    // update frequency and check against vector
    frequency = updateFrequency(sign, frequency, modulation);
    if (freqs.find(frequency) == freqs.end()){
      // frequency not in the map aka not seen before
      freqs.insert(std::pair<int, int>(frequency, 1));
    } else {
      found = true;
      break;
    }
    // Testing output
    //std::cout << line << ", Sign: " << sign << ", Value: " << modulation << std::endl;
  }
  Part2 p2 = Part2(frequency, found);
  return p2;
}

// updates the current frequency by value (modulation) and sign
int updateFrequency(std::string& sign, int currentfrequency, int modulation){
  if (sign == "+"){
    currentfrequency = currentfrequency + modulation;
  } else {
    currentfrequency = currentfrequency - modulation;
  }
  return currentfrequency;
}
