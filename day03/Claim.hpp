#ifndef CLAIM_HPP
#define CLAIM_HPP

#include <vector>
#include <string>
#include <set>
#include <iostream>

struct Fabric
{
  Fabric(size_t occupationCount):
    occupationCount(occupationCount),
    claimIDs(std::vector<size_t>{}){  };
  Fabric() : occupationCount(0) {};
  size_t occupationCount;
  std::vector<size_t> claimIDs;
};

class Claim {
  private:
    size_t id;
    size_t leftDistance, topDistance;
    size_t width, height;
    std::vector<size_t> fields;
    size_t leftBorder, topBorder, rightBorder, bottomBorder;

  public:
    Claim(size_t id, size_t leftDistance,
          size_t topDistance, size_t width, size_t height)
          : id(id),
          leftDistance(leftDistance),
          topDistance(topDistance),
          width(width),
          height(height),
          fields() {
            // initialize the fields array
            // asuming 1000 inches width and height
            size_t row = topDistance;
            size_t col = leftDistance;
            size_t inches(1000); // inches
            for (size_t r=0; r<height; ++r){
              for (size_t c=0; c<width; ++c){
                size_t nr = (r+row)*inches + col + c;
                fields.push_back(std::move(nr));
              }
            }
            leftBorder = leftDistance;
            topBorder = topDistance;
            rightBorder = leftDistance + width;
            bottomBorder = topDistance + height;
          }

    size_t getId() const { return id; }
    size_t getLeftDistance() const { return leftDistance; }
    size_t getTopDistance() const { return topDistance; }
    size_t getWidth() const { return width; }
    size_t getHeight() const { return height; }
    const std::vector<size_t>& getFields() const { return fields; };
    size_t getTop() const { return topBorder; }
    size_t getBot() const { return bottomBorder; }
    size_t getLeft() const { return leftBorder; }
    size_t getRight() const { return rightBorder; }

    /// checks if fields overlap with other Claim
    bool isInOtherClaim(Claim& other){
      // top left in other
      if ( leftBorder > other.getLeft() && leftBorder < other.getRight() ){
        if (topBorder > other.getTop() && topBorder < other.getBot() ){
          return true;
        } // bottom left in other
        else if (bottomBorder < other.getBot() && bottomBorder > other.getTop()) {
          return true;
        }
      // top right in other
      } else if (rightBorder < other.getRight() && rightBorder > other.getLeft()){
        if (topBorder > other.getTop() && topBorder < other.getBot()){
          return true;
        } // bottom right in other
        else if (bottomBorder < other.getBot() && bottomBorder > other.getTop()){
          return true;
        }
      }
      return false;
    }

    bool isUniqueClaim(const std::set<size_t>& occupiedFields){
      bool isUnique (true);
      for (size_t i=0; i<fields.size(); ++i){
        size_t fabric = fields[0];
        if (occupiedFields.find(fabric) != occupiedFields.end()){
          isUnique = false;
          break;
        }
      }
      return isUnique;
    }

    // for debugging purposes
    std::string toString() { return "Claim ID: " + std::to_string(id) +
                            " - pos: (" + std::to_string(leftDistance) + ", " +
                            std::to_string(topDistance) + ") " +
                            " - W =  " + std::to_string(width) +
                            " - H = " + std::to_string(height) +
                            " - size of fields: " + std::to_string(fields.size()); }
};

#endif
