//
//    FILE: A1301.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2010-07-22
// PURPOSE: Arduino library for A1301 A1302 magnetometer.
//     URL: https://github.com/RobTillaart/A1301


#include "A1301.h"


/////////////////////////////////////////////////////////////////////////////
//
//  CONSTRUCTOR
//
HALL::HALL(uint8_t pin)
{
  _pin         = pin;
  _maxADC      = 1023;
  _mVStep      = 5000.0 / _maxADC;  //  default 10 bit 5V ADC (UNO)
  _midPoint    = _maxADC * 0.5;     //  default middle
  _prevGauss   = 0;
  _lastGauss   = 0;
  _mVGauss     = 2.5;
  _maxGauss    = 500.0;
}


void HALL::begin(float voltage, uint16_t steps)
{
  _maxADC   = steps;
  _mVStep   = voltage / steps;
  _midPoint = steps * 0.5;
}


/////////////////////////////////////////////////////////////////////////////
//
//  MIDPOINT
//
void HALL::setMidPoint(float midPoint)
{
  _midPoint = midPoint;
}


float HALL::getMidPoint()
{
  return _midPoint;
}


/////////////////////////////////////////////////////////////////////////////
//
//  SENSITIVITY
//
void HALL::setSensitivity(float sensitivity)
{
  _mVGauss = sensitivity;
}


float HALL::getSensitivity()
{
  return _mVGauss;
}


/////////////////////////////////////////////////////////////////////////////
//
//  READ
//
float HALL::raw(uint8_t times)
{
  float sum = 0;
  if (times == 0) times = 1;
  for (int i = 0; i < times; i++)
  {
    //  yield();
    sum += analogRead(_pin);
  }
  if (times > 1) sum /= times;
  return sum;
}


float HALL::read(uint8_t times)
{
  float milliVolts = (raw(times) - _midPoint) * _mVStep;
  _prevGauss = _lastGauss;
  _lastGauss = milliVolts / _mVGauss;
  return _lastGauss;
}


float HALL::readExt(float raw)
{
  float milliVolts = (raw - _midPoint) * _mVStep;
  _prevGauss = _lastGauss;
  _lastGauss = milliVolts / _mVGauss;
  return _lastGauss;
}


/////////////////////////////////////////////////////////////////////////////
//
//  ANALYSE
//
bool HALL::isNull()
{
  return (_lastGauss == 0);
}


bool HALL::isNorth()
{
  return (_lastGauss > 0);
}


bool HALL::isSouth()
{
  return (_lastGauss < 0);
}


float HALL::lastGauss()
{
  return _lastGauss;
}


float HALL::prevGauss()
{
  return _prevGauss;
}


/////////////////////////////////////////////////////////////////////////////
//
//  CONVERTORS
//
float HALL::Tesla(float Gauss)
{
  return Gauss * 0.0001;
}


float HALL::mTesla(float Gauss)
{
  return Gauss * 0.1;
}


float HALL::uTesla(float Gauss)
{
  return Gauss * 100;
}


/////////////////////////////////////////////////////////////////////////////
//
//  SATURATION LEVEL
//
void HALL::setMaxGauss(float maxGauss)
{
  _maxGauss = abs(maxGauss);
}


float HALL::getMaxGauss()
{
  return _maxGauss;
}


bool HALL::isSaturated()
{
  return (abs(_lastGauss) >= _maxGauss); 
}


float HALL::saturationLevel()
{
  return 100.0 * abs(_lastGauss / _maxGauss);
}


/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED
//
A1301::A1301(uint8_t pin) : HALL(pin)
{
  _mVGauss   = 2.5;
}

A1302::A1302(uint8_t pin) : HALL(pin)
{
  _mVGauss   = 1.3;
}

A1324::A1324(uint8_t pin) : HALL(pin)
{
  _mVGauss   = 5.0;
}

A1325::A1325(uint8_t pin) : HALL(pin)
{
  _mVGauss   = 3.125;
}

A1326::A1326(uint8_t pin) : HALL(pin)
{
  _mVGauss   = 2.5;
}


//  -- END OF FILE --

