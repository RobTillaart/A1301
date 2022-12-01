//
//    FILE: A1301.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2010-07-22
// PURPOSE: Arduino library for A1301 A1302 magnetometer.


#include "A1301.h"


A1301::A1301(uint8_t pin)
{
  _pin       = pin;
  _midPoint  = 512;
  _lastGauss = 0;
  _mVGauss   = 2.5;
  _mVStep    = 5000.0 / 1023;  //  default 10 bit 5V ADC
}


void A1301::begin(float voltage, uint16_t steps)
{
  _mVStep = voltage / steps;
}


void A1301::setMidPoint(float midPoint)
{
  _midPoint = midPoint;
}


float A1301::getMidPoint()
{
  return _midPoint;
}


/////////////////////////////////////////////////////////////////////////////
//
//  READ
//
float A1301::raw(uint8_t times)
{
  float sum = 0;
  if (times == 0) times = 1;
  for (int i = 0; i < times; i++)
  {
    sum += analogRead(_pin);
  }
  if (times > 1) sum /= times;
  return sum;
}


float A1301::Gauss(uint8_t times)
{
  float milliVolts = (raw(times) - _midPoint) * _mVStep;
  _lastGauss = milliVolts / _mVGauss;
  return _lastGauss;
}

float A1301::delta(uint8_t times)
{
  float lg = _lastGauss;
  return Gauss(times) - lg;
}



/////////////////////////////////////////////////////////////////////////////
//
//  ANALYSE
//
bool A1301::isNorth()
{
  return (_lastGauss > 0);
}


bool A1301::isSouth()
{
  return (_lastGauss < 0);
}


float A1301::lastGauss()
{
  return _lastGauss;
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED
//
A1302::A1302(uint8_t pin) : A1301(pin)
{
  _mVGauss   = 2.5;
}


//  -- END OF FILE --

