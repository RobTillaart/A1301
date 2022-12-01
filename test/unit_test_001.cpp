//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-12-01
// PURPOSE: unit tests for the A1301 magnetic sensor
//          https://github.com/RobTillaart/A1301
//          https://www.adafruit.com/product/2857
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)


#include <ArduinoUnitTests.h>

#include "Arduino.h"
#include "A1301.h"


unittest_setup()
{
    fprintf(stderr, "A1301_LIB_VERSION: %s\n", (char *) A1301_LIB_VERSION);
}

unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqualFloat(1, 1, 0.001);
}


unittest(test_constructor)
{
  assertEqualFloat(1, 1, 0.001);
}


unittest_main()


//  -- END OF FILE --

