/*
 Main class to handle the mashshedule
 Example for a scheme: Dipa2,56,15,65,20,70,10,85,30,356,
 Dipa2,27,1,29,1,31,1,95,
*/

#ifndef Mash_h
#define Mash_h

#include <Time.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#include "Arduino.h"
#include "Display.h"
#include "Pins.h"
#include "Relay.h"

class Mash
{
  public:
    Mash(int* arr, int arrSize);
    boolean Start();
    void Unpause();
    int Uniqe();
    void Random();
    void ProgramFinshed();
  private:
	OneWire oneWire = OneWire(ONE_WIRE_BUS);
  	DallasTemperature sensors = DallasTemperature(&oneWire); //Pass our oneWire reference to Dallas Temperature.
  	
	int CurrentTemp; //Stores the current temp
  	long randNumber; 

	Display lcd; //Our display functions
	
	int* randNum;

	int statePump;
	
	time_t totTime; //The total time
	time_t curTime; //The time of the current step
	time_t difTime; //The total time when the current step started

	boolean someFlag=true;
	boolean someFlag_2=true;
	boolean curStarted; //A flag to check whether the current step has started
	
	int _temp; //temporary variable for the temperature
	int _time;
	int _step;
	int _steps;

	int* tempTime; //Just temporary
};

#endif
