/*
 Main class to handle the mashshedule
 Example for a scheme: Dipa2,56,15,65,20,70,10,85,30,356,
 Dipa2,27,1,29,1,31,1,95,
*/

#ifndef MashSchedule_h
#define MashSchedule_h

#include "Arduino.h"
#include <Time.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Display.h"
#include "SerialString.h"
#include "Pins.h"

//Defines our Pin
//#define ONE_WIRE_BUS A0
//#define RELAY1 6//the pin where the relay is connected
//#define RELAY2 5//the pin where the relay is connected
//#define RELAY3 4//the pin where the relay is connected
//#define RELAY4 3//the pin where the relay is connected
//#define PUMP 13
//#define SWITCH1 8
//#define SWITCH2 9
//#define SWITCH3 10
//#define SWITCH4 11
//#define SWITCH5 12


class MashSchedule
{
  public:
    void Default();
    void Receive();
    void Start();
    void Pause();
    void AllOn();
    void Random();
    void TurnOff();
  private:

  	Display lcd; //Our display functions
  	SerialString serialStr; //Our Serial functions

  	OneWire oneWire = OneWire(ONE_WIRE_BUS);

  	DallasTemperature sensors = DallasTemperature(&oneWire); //Pass our oneWire reference to Dallas Temperature.

  	//const int maxStep = 32; //The max number of steps that can be received
  	long randNumber;
  	//const int Calibrator = 3.5; //Calibration for the temp-sensor
	int CurrentTemp; //Stores the current temp
	//const char degree = char(223); //To get the right Celcius-symbol
	String name = ""; //The name for the scheme
	int* arr; //Array that stores the values of time and temp 
	int arrSize; //Stores the number of steps in the current scheme
	boolean loaded; //A flag to check if the scheme has been loaded or not 
	int state; //Stores the input if the button is pressed or not
	//const int startButton = 2; //The pin where the button is connected
	//const int stopButton = 7;
	//const int led = 7; //The pin where the led is connected
	
	int stateRelay1;
	int stateRelay2;
	int stateRelay3;
	int stateRelay4;
	int statePump;
	
	time_t totTime; //The total time
	time_t curTime; //The time of the current step
	time_t difTime; //The total time when the current step started
	boolean someFlag=true;
	boolean someFlag_2=true;
	boolean running;
	boolean curStarted; //A flag to check whether the current step has started
	int _temp; //temporary variable for the temperature
	int _time;
	int _step;
	int _steps;
};

#endif
