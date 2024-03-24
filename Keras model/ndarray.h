/*
 * ****************************************************************************
 *        Copyright (C) 2018-present, AI Technology & Systems, Inc.
 *                           All rights reserved.
 *****************************************************************************
 *
 * You are not permitted to use the Information present in this document
 * without the prior written consent of AI Technology & Systems, Inc.
 *
 * This file has been provided pursuant to a License Agreement containing
 * restrictions on its use. This file contains valuable trade secrets and
 * proprietary information of AI Technology & Systems Inc., and is protected
 * by U.S. and international laws and/or treaties.
 *
 * The copyright notice(s) in this file does not indicate actual or intended
 * publication of this file.
 *
 *
 ******************************************************************************
 */
#pragma once
#if !defined(_DEEPSEA_ON_MCU_)
#include <fstream>
#include <iostream>
#include <sstream>
#endif

namespace deepSea {
#define MAX_DIMENSION 6
template <typename dType> struct ndarray {
  dType *_data = 0x0;
  unsigned short _shape[MAX_DIMENSION] = {0, 0, 0, 0, 0, 0};

  ndarray() {}
  ndarray(dType *data, unsigned short *shape, unsigned short rank) {
    _data = data;
    for (unsigned short i = 0; i < rank; i++)
      _shape[i] = shape[i];
  }
  unsigned int size() {
    unsigned int sz = 1;
    for (short i = 0; i < MAX_DIMENSION; i++) {
      if (_shape[i] <= 0)
        break;
      sz *= _shape[i];
    }
    return sz;
  }
};

#if !defined(_DEEPSEA_ON_MCU_)

template <class T>
bool read_ndarray(T *data, unsigned int data_len, std::string fileName) {

  std::fstream fs;
  fs.open(fileName, std::ios::in);
  // parameter file could not be opened.
  if (!fs.is_open() || fs.fail()) {
    return false;
  }

  std::string typedStr;
  T fNum;
  size_t index = 0;
  while (std::getline(fs, typedStr)) {
    std::stringstream linestream(typedStr);
    while (linestream >> fNum) {
      if (index >= data_len) {
        break;
      }
      data[index++] = fNum;
    }
    if (index >= data_len) {
      break;
    }
  }
  fs.close();

  // parameter file did not have parametres equal to tensor length.
  if (index < data_len) {
    delete[] data;
    return false;
  }

  return true;
}
#endif
} // namespace deepSea
