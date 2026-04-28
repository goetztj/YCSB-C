//
//  INTERVAL_generator.h
//  YCSB-C
//
//  Created by Jinglei Ren on 12/6/14.
//  Copyright (c) 2014 Jinglei Ren <jinglei@ren.systems>.
//

#ifndef YCSB_C_INTERVAL_GENERATOR_H_
#define YCSB_C_INTERVAL_GENERATOR_H_

#include "generator.h"

#include <atomic>
#include <mutex>
#include <random>

namespace ycsbc {

class IntervalGenerator : public Generator<uint64_t> {
 public:
  // Generates an interval of sizedistance and step size s
  IntervalGenerator(uint64_t steps, uint64_t distance, uint64_t max): dist_(0, distance), step_size_(steps), max_(max) { Next(); }
  
  uint64_t Next(uint64_t txn_id) override;
  uint64_t Next();
  uint64_t Last();
  
 private:
  std::mt19937_64 generator_;
  std::uniform_int_distribution<uint64_t> dist_;
  uint64_t last_int_;
  std::mutex mutex_;
  uint64_t step_size_;
  uint64_t max_;
};

inline uint64_t IntervalGenerator::Next(uint64_t txn_id) {
  std::lock_guard<std::mutex> lock(mutex_);
  return last_int_ = ((txn_id * step_size_) + dist_(generator_))%max_;
}

inline uint64_t IntervalGenerator::Next() {
  return Next(0);
}

inline uint64_t IntervalGenerator::Last() {
  std::lock_guard<std::mutex> lock(mutex_);
  return last_int_;
}

} // ycsbc

#endif // YCSB_C_INTERVAL_GENERATOR_H_
