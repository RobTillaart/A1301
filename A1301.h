#pragma once
//
//    FILE: A1301.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2010-07-22
// PURPOSE: Arduino library for A1301 A1302 magnetometer.

//  always check datasheet.
//    PIN    A1301
//    ===============
//     1     GND
//     2     DATA
//     3     VDD +5V


#include "Arduino.h"

#define A1301_LIB_VERSION        (F("0.1.0"))


class A1301
{
public:
  A1301(uint8_t pin);

  //  internal ADC parameters
  void      begin(float voltage, uint16_t steps);

  //  midpoint depends on internal ADC.
  void      setMidPoint(float midPoint);
  float     getMidPoint();

  //  READ
  //  times > 1 ==> more stable read / averaging.
  float     raw(uint8_t times = 1);
  float     Gauss(uint8_t times = 1);
  float     delta(uint8_t times = 1);

  //  ANALYSE
  bool      isNorth();
  bool      isSouth();
  float     lastGauss();

protected:
  uint8_t  _pin       = 0;
  float    _midPoint  = 512;
  float    _lastGauss = 0;
  float    _mVGauss   = 2.5;
  float    _mVStep    = 5000.0 / 1023;
};

////////////////////////////////////////////////////
//
//  DERIVED
//
class A1302 : public A1301
{
public:
  A1302(uint8_t pin);
};


//  -- END OF FILE --


