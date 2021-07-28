/**
 * @file globals.h
 * @author guttih (gudjonholm@gmail.com)
 * @brief Decleration of global program variables
 * @version 0.1
 * @date 2021-07-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <DisplayMenu.h>

#include "FS.h"

#include <SPI.h>

#include <TFT_eSPI.h> // Hardware-specific library


/*
  Valves openings will be a number from 0-100 where 0 is fully closed and 100 fully open.
  To be able to use the pid to control two valves we need the WaterMixer to understand how to convert 
  desired temperature to a linear opening of the valves.
 */

/**
 * @brief  Values used by the proportional integral derivative controller (PID controller).
 * 
 */
struct PID_STRUCT {
    double input;       // current temperature
    double setpoint;    // desired temperature
    double output;      // suggested temperature from the pid.
                        
    // outputMin and outputMax are the range of values your output can be set to.
    double outputMin;   // outputMin is the lowest value your output can be set to.  (Should use the same units as output)
    double outputMax;   // outputMax is the highest value your output can be set to.  (Should use the same units as output)
    double Kp;          //  proportional gain
    double Ki;          // integral gain
    double Kd;          // derivative gain
};

/**
 * @brief Global variables in the program
 * 
 */
struct GLOBAL_STRUCT {
    double temperature = 0;   // Current temperature read from the Temperature sensor.
    double desiredTemp = 24;  // The desired temperature which should be fed as the setpoint to the PID controller.
    double coldValveFlow = 12.34; // A number from 0 to 100 describing the opening of the COLD valve, 0 is fully closed and 100 fully open.
    double hotValveFlow = 56.78;  // A number from 0 to 100 describing the opening of the HOT  valve, 0 is fully closed and 100 fully open.
    PID_STRUCT pid;
} values;


#define CALIBRATION_FILE "/TouchCalData3"

#define REPEAT_CAL false

TFT_eSPI tft = TFT_eSPI();


DisplayMenu menu = DisplayMenu(&tft);


#endif