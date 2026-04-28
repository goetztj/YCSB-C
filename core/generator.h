//
//  generator.h
//  YCSB-C
//
//  Created by Jinglei Ren on 12/6/14.
//  Copyright (c) 2014 Jinglei Ren <jinglei@ren.systems>.
//
// Adapted by Tobias Götz

#ifndef YCSB_C_GENERATOR_H_
#define YCSB_C_GENERATOR_H_

#include <cstdint>
#include <string>

namespace ycsbc {

template <typename Value>
class Generator {
 public:
  virtual Value Next() = 0;
  virtual Value Last() = 0;
  virtual Value Next(uint64_t txn_id) {
    return Next();
  };
  virtual ~Generator() { }
};

} // ycsbc

#endif // YCSB_C_GENERATOR_H_
