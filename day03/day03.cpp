#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>

#include "Claim.hpp"

/*
  Advent of Code 2018 - Day 03
  Using make_unique and unique_ptr so
  compile using std=c++14, even though
  the functions are compatable with std=c++11
*/

// forward declarations and typedefs
class Claim;
typedef std::vector<std::unique_ptr<Claim>> claimVec;
typedef size_t fabric_field_number;

void getClaims(std::string&, claimVec&);
std::pair<size_t, size_t> splitInput(std::string& string, char ch);
void solvePart1(std::map<size_t, Fabric>&);


int main(int argc, char** argv){

    // PART 1
    claimVec claims;
    std::string filename("input.txt");
    getClaims(filename, claims);
    std::map<size_t, std::vector<size_t>> fabricVector;

    // iterate over all claims, map index of fabric
    // to a Fabric object containing a count of
    // occupants and their claim ID
    std::map<size_t, Fabric> fields;
    for (size_t i=0; i< claims.size(); ++i)
    {
      const std::vector<size_t>& claimedFields = claims[i]->getFields();
      for (size_t field : claimedFields){
        std::map<size_t, Fabric>::iterator it = fields.find(field);
        Fabric fabric = Fabric(1);
        if (it == fields.end()) {
          // not in fields
          fields.insert(std::pair<size_t,Fabric>(field,fabric));
        } else {
          // field is in fields --> increment value at key = field
          it->second.occupationCount++;
          it->second.claimIDs.push_back(claims[i]->getId());
        }
      }
    }
    solvePart1(fields);

}

/// iterate over the map again and count the number
/// of fields occupied more than twice
void solvePart1(std::map<size_t, Fabric>& fields)
{
  size_t countFields(0);
  std::map<size_t, Fabric>::iterator iterator;
  for (iterator = fields.begin(); iterator != fields.end(); iterator++){
    if (iterator->second.occupationCount >= (size_t) 2){
      ++countFields;
    }
  }
  std::cout << "Part 1: Fabric fields occupied more than twice = " << countFields << std::endl;
}

/// read in input and make a vector of claim object from it
/// vector of these objects passed as output parameter
void getClaims(std::string& filename, claimVec& claims){
  std::ifstream infile (filename);
  std::string idstr, tmp, posstr, areastr;

  while (infile >> idstr >> tmp >> posstr >> areastr) {
    size_t id = std::stoi(idstr.substr(1, idstr.size()));
    std::pair<size_t, size_t> pos = splitInput(posstr, ',');
    std::pair<size_t, size_t> area = splitInput(areastr, 'x');
    claims.push_back(
      std::make_unique<Claim>(id, pos.first, pos.second, area.first, area.second)
    );
  }
}

/// split pos and area string on provided char ch
/// return the size_t casted values as pairs
std::pair<size_t, size_t> splitInput(std::string& string, char ch){
  size_t pos = string.find(ch);
  size_t first = std::stoi(string.substr(0, pos));
  size_t second = std::stoi(string.substr(pos+1, string.size()));
  return std::make_pair(first, second);
}
