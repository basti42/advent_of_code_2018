#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

/*
  Advent of Code 2018 - DAY 02
  Part 1: Determine the checksum of all boxes by counting
  occurences of characters appear twice and three times in
  a box sequence.

  Part 2: find the two boxes that only differ by 1 character
  in their respective sequences, then return the characters
  common in both their sequences.
*/

// forward declarations
int const checksumPart1(std::string&);
struct CountTwosAndThrees;
CountTwosAndThrees checkLine(std::string&);
class Box;
std::string commonLettersPart2(std::string&);
std::vector<Box> recordInventory(std::string&);
std::pair<Box, Box> findContainingBoxes(std::vector<Box>);

// structs and classes
struct CountTwosAndThrees{
  int twos;
  int threes;
  CountTwosAndThrees():twos(0), threes(0) {}
  CountTwosAndThrees(int twos, int threes):twos(twos), threes(threes) {}
};

class Box {
  private:
    int lineNr;
    std::string sequence;

  public:
    Box(int nr, std::string seq):lineNr(nr), sequence(seq){};
    Box():lineNr(0), sequence(""){};
    std::string getSequence(){ return sequence; }
    // debugging purposes
    void printBox(){
      std::cout << "Box number: " << lineNr << "\tcontent: " << sequence << std::endl;
    }

    ///checks if other box's sequence differs by exactly 1 character from own sequence
    bool differByOne(Box& b){
      int different(0);
      for (int i=0; i<sequence.size(); ++i){
        char own = sequence.at(i);
        char other = b.getSequence().at(i);
        if (own != other) ++different;
      }
      if (different > 1) return false;
      return true;
    }

    /// returns the common characters from this sequence with the other box's sequence
    std::string commonLetters(Box& b){
      std::string common("");
      for (int i=0; i<sequence.size(); ++i){
        char own = sequence.at(i);
        char other = b.getSequence().at(i);
        if (own == other){
          common += own;
        }
      }
      return common;
    }
};

/// MAIN
int main (int argc, char** argv){
  std::string filename ("input.txt");

  int checksum = checksumPart1(filename);
  std::cout << "PART 1: Checksum = " << checksum << std::endl;

  std::string commonLetters = commonLettersPart2(filename);
  std::cout << "PART 2: Common letters = " << commonLetters << std::endl;

  return 0;
}

/// PART 2
/// return common leters of two boxes whose sequences are exactly 1 character apart
std::string commonLettersPart2(std::string& filename){
  std::vector<Box> boxes = recordInventory(filename);

  // std::cout << "Size of boxes = " << boxes.size() << std::endl;
  std::pair<Box, Box> containingBoxes = findContainingBoxes(boxes);
  std::string commonLetters = containingBoxes.first.commonLetters(containingBoxes.second);

  return commonLetters;
}

/// find the two boxes whose sequences are 1 charater apart
std::pair<Box, Box> findContainingBoxes(std::vector<Box> boxes){
  std::pair<Box, Box> contaningBoxes;
  for (int i=0; i<boxes.size(); ++i){
    for (int j=0; j<boxes.size(); ++j){
      // dont check self
      if (i == j) continue;
      // check all others
      bool found = boxes[i].differByOne(boxes[j]);
      if (found) {
        return std::make_pair(boxes[i], boxes[j]);
      }
    }
  }
}

/// read in the entire boxes and make a vector of type Box out of them
std::vector<Box> recordInventory(std::string& filename){
  std::ifstream infile (filename);
  std::string line;
  int lineNr(0);
  std::vector<Box> boxes;

  while (infile >> line){
    Box box (lineNr, line);
    boxes.push_back(std::move(box));
    ++lineNr;
  }
  return boxes;
}

/// PART 1
/// determine the checksum by multiplication of twice and three times appearing characters
int const checksumPart1(std::string& filename){
  std::ifstream infile (filename);
  std::string line;
  CountTwosAndThrees counts;
  int totalTwos(0);
  int totalThrees(0);

  while (infile >> line){
    counts = checkLine(line);
    totalTwos = totalTwos + counts.twos;
    totalThrees = totalThrees + counts.threes;
  }
  return totalTwos * totalThrees;
}

/// count twice and three times occuring characters in current line
CountTwosAndThrees checkLine(std::string& line){
  // make an unordered_map to keep track of the characters
  std::unordered_map<char, int> map;
  // iterate over the line and check each character
  for (char c : line){
    // char not in map
    if (map.find(c) == map.end()){
      map.insert(std::pair<char, int>(c, 1));
    } else {
      // char is in map
      auto it = map.find(c);
      it->second++;
    }
  }
  // iterate over the map and see if any character
  // appears two or three times
  int twos(0);
  int threes(0);
  for (auto it : map){
    int value = it.second;
    if (value == 2) twos = 1;
    if (value == 3) threes = 1;
  }
  return CountTwosAndThrees(twos, threes);
}
