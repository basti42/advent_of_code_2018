
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <memory>

#include "../Input.hpp"
#include "Guard.hpp"

class Guard;
typedef std::map<size_t, std::unique_ptr<Guard>> guards;
guards getGuards(std::vector<std::string>&);


int main(int argc, char** argv)
{
  std::string filename("4.in");

  // load the data into a list of strings
  // sort the list in ascending order string sorted
  // results list to be sorted by timestamp in acending order
  std::vector<std::string> inputlist = input::getInput(filename);
  std::sort(inputlist.begin(), inputlist.end(), std::less<std::string>());

  // for (std::string s : inputlist){
  //   std::cout << s << std::endl;
  // }

  guards gs = getGuards(inputlist);
  // std::cout << gs.size() << std::endl;

  SleepingGuard sleeper;

  guards::iterator it;
  for (it = gs.begin(); it != gs.end(); ++it){
    // it->second->to_string();
    // std::cout << "total sleep time: " << it->second->getTotalSleepTime() << std::endl;
    size_t guardId = it->second->id;
    size_t totalTimeAsleep = it->second->getTotalSleepTime();
    size_t minute = it->second->minMostAsleep();
    SleepingGuard tmp (guardId, totalTimeAsleep, minute);
    if (tmp.totalTimeSlept > sleeper.totalTimeSlept){
      sleeper = tmp;
    }
  }

  sleeper.display_part1();

  // PART 2:
  // iterate over all guards and their frequency maps
  // to determine the minute and guard id, by highest frequency
  size_t freq(0);
  size_t minute(0);
  size_t gid(0);

  guards::iterator iterator;
  for (iterator = gs.begin(); iterator != gs.end(); ++iterator){
    std::map<size_t, size_t> fmap = iterator->second->getMinuteFrequencyMap();
    std::map<size_t, size_t>::iterator mIt;
    for (mIt = fmap.begin(); mIt != fmap.end(); ++mIt){
      size_t cMin = mIt->first;
      size_t cCount = mIt->second;
      if (cCount > freq){
        freq = cCount;
        minute = cMin;
        gid= iterator->second->id;
      }
    }
  }

  std::cout << "Min= " << minute << " @count= " << freq
            << " from guard ID #" << gid << " -> " << gid * minute << std::endl;

  return 0;
}

// solve part 1
guards getGuards(std::vector<std::string>& list){
  size_t sleepyGuardId(0);
  size_t currentGuardId(0);
  std::unique_ptr<Guard> currentGuard;
  std::vector<std::string> tokens;
  guards gs;
  size_t counter(0);

  while (counter < list.size()){
    boost::algorithm::split(tokens, list[counter], boost::is_any_of(" "));

    if (tokens[2] == "Guard") {
      currentGuardId = std::stoi(tokens[3].substr(1,tokens[3].size()));
      currentGuard = std::make_unique<Guard>(Guard(currentGuardId));
      gs.insert(std::make_pair(currentGuardId, std::move(currentGuard)));
      // ++counter;
    }
    else if(tokens[2] == "falls"){
        std::string timestamp(tokens[1].substr(0,tokens[1].size()-1));
        std::pair<std::string, std::string> time = input::splitTokenOnChar(timestamp, ':');
        size_t hour = std::stoi(time.first);
        size_t min = std::stoi(time.second);
        //std::cout << "Hour: " << hour << ", Minute: " << min << std::endl;
        gs.find(currentGuardId)->second->fallsAsleep.push_back(min);
    }
    else if(tokens[2] == "wakes"){
        std::string timestamp(tokens[1].substr(0,tokens[1].size()-1));
        std::pair<std::string, std::string> time = input::splitTokenOnChar(timestamp, ':');
        size_t hour = std::stoi(time.first);
        size_t min = std::stoi(time.second);
        //std::cout << "Hour: " << hour << ", Minute: " << min << std::endl;
        gs.find(currentGuardId)->second->wakesUp.push_back(min);
    }
    ++counter;
  }
  return gs;
}
