#ifndef GUARD_HPP
#define GUARD_HPP

#include <map>

struct SleepingGuard
{
  size_t id;
  size_t totalTimeSlept;
  size_t minuteMostAsleep;
  SleepingGuard(size_t id, size_t slept, size_t mins)
    : id(id), totalTimeSlept(slept), minuteMostAsleep(mins) {};
  SleepingGuard()
    : id(0), totalTimeSlept(0), minuteMostAsleep(0) {};

  void display_part1() const
  {
    std::cout << "Guard ID: #" << id << ", total time asleep: " << totalTimeSlept
              << ", minute most aslep: " << minuteMostAsleep
              << " -> " << minuteMostAsleep*id << std::endl;
  }
};


struct Guard
{
  size_t id;
  std::vector<int> fallsAsleep;
  std::vector<int> wakesUp;
  size_t totalSleepTime;
  size_t minAsleep;
  size_t minCounter;
  Guard(size_t id) : id(id), totalSleepTime(0), minAsleep(0), minCounter(0) {};
  Guard() : id(0), totalSleepTime(0), minAsleep(0), minCounter(0) {};

  size_t getTotalSleepTime() const
  {
    size_t total(0);
    for (size_t i=0; i<fallsAsleep.size(); ++i){
      if (fallsAsleep.size() != wakesUp.size()){
        std::cout << "sleep times do not match! ("
        << fallsAsleep.size() << " " << wakesUp.size() << ")" << std::endl;
        return 0;
      }
      int start = fallsAsleep[i];
      int stop = wakesUp[i];
      if (stop < start){
        std::cout << "Guard #" << id << "wakes up before he falls asleep" << std::endl;
      }
      total += (stop-start);
    }
    return total;
  }

  size_t minMostAsleep() const
  {
    std::map<size_t, size_t> minutes;
    for (size_t i=0; i<fallsAsleep.size(); ++i){
      size_t start = fallsAsleep[i];
      size_t stop = wakesUp[i];
      for (size_t j=start; j<stop; ++j){
        std::map<size_t, size_t>::iterator it = minutes.find(j);
        if (it == minutes.end()){
          minutes.insert(std::make_pair(j, 1));
        } else {
          it->second++;
        }
      }
    }
    // somehow sort this map and find the minute most asleep
    size_t currentMinute(0);
    size_t currentCount(0);
    std::map<size_t, size_t>::iterator iter;
    for (iter = minutes.begin(); iter != minutes.end(); ++iter){
      size_t min = iter->first;
      size_t count = iter->second;
      if (count > currentCount){
        currentCount = count;
        currentMinute = min;
      }
    }
    return currentMinute;
  }

  std::map<size_t, size_t> getMinuteFrequencyMap() const
  {
    std::map<size_t, size_t> minutes;
    for (size_t i=0; i<fallsAsleep.size(); ++i){
      size_t start = fallsAsleep[i];
      size_t stop = wakesUp[i];
      for (size_t j=start; j<stop; ++j){
        std::map<size_t, size_t>::iterator it = minutes.find(j);
        if (it == minutes.end()){
          minutes.insert(std::make_pair(j, 1));
        } else {
          it->second++;
        }
      }
    }
    return minutes;;
  }


  void to_string() const
  {
    std::cout << "Guard id #" << id << std::endl;
    for (size_t i=0; i<fallsAsleep.size(); ++i){
      std::cout << "\tfalls asleep: " << fallsAsleep[i]
                << ", wakes up: " << wakesUp[i] << std::endl;
    }
  }
};

#endif
