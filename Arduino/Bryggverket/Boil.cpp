/*
 Main class to handle the boilshedule
*/

#include "Arduino.h"
#include "Boil.h"



Boil::Boil(String* hopsArr, int* timeArr, int totalTime, int steps, int elHeating, int elRandom)
{
	_hopsArr = hopsArr;
	_timeArr = timeArr;

	setTime(0,totalTime,0,0,0,0);
	_totalTime = now();
	_steps = steps;

	setTime(0,_timeArr[0],0,0,0,0);
	_currStep = now();
	totTime = _totalTime;
	curTime = totTime - _currStep;

	setTime(0,0,0,0,0,0);
	_zero = now();
	curStarted = false;
	moreSteps = true;
    _step=1;

    pinMode(BUZZER, OUTPUT);
    lcd.Begin();
    sensors.requestTemperatures();
	CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;

	_elHeating = elHeating;
    _elRandom = elRandom;

    relay.SetRandom(_elRandom);
}

boolean Boil::Start()
{
	if (curStarted)
	{
		_now = now();
		totTime = _totalTime - _now;
		curTime = totTime - difTime;
	}
	
	if(second() % 2 == 0) //Updates the temp every two seconds
	{
		sensors.requestTemperatures();
		CurrentTemp = sensors.getTempCByIndex(0) + Calibrator;
	}

	if(CurrentTemp >= boilingPoint && !curStarted)
	{
		setTime(_zero);
		difTime = _currStep - _zero;
		randomOnce = true;
		curStarted = true;
	}

	lcd.totalTime(totTime);
	lcd.currentTemp(CurrentTemp, curTime, moreSteps);

	
	lcd.step(2, _step, 0, _timeArr[_step-1],_steps);

	if(_step < _steps)
	{
		lcd.step(3, _step+1, 0, _timeArr[_step],_steps);
	}

	if(CurrentTemp < boilingPoint && curStarted)
	{
		relay.Random(randomOnce, _elRandom);
		randomOnce = false;
	}
	else if (CurrentTemp < boilingPoint)
	{
		relay.ReadElements(_elHeating);
	}
	else if(CurrentTemp >= boilingPoint)
	{
		relay.ElementLow();
		randomOnce = true;
	}

	if(hour(totTime) <= 0 && minute(totTime) < _timeArr[_step-1] && _step < _steps && curStarted)
	{
	    _step++;
	    setTime(0,_timeArr[_step-1],0,0,0,0);
	    _currStep = now();
	    difTime = _currStep - _zero;
	    setTime(_now);
	    lcd.currentTemp(CurrentTemp, curTime, false);
	    digitalWrite(BUZZER, HIGH);
	    delay(500);
	    digitalWrite(BUZZER, LOW);
	}

	if(hour(totTime) <= 0 && minute(totTime) < _timeArr[_step-1] && curStarted && _steps == _step)
	{
		_step++;
		moreSteps = false;
		lcd.currentTemp(CurrentTemp, curTime, false);
		digitalWrite(BUZZER, HIGH);
	    delay(500);
	    digitalWrite(BUZZER, LOW);
	}

	if(hour(totTime) <= 0 && minute(totTime) <= 0 && second(totTime) <= 0 && !moreSteps)
	{
		relay.AllLow();
		digitalWrite(BUZZER, HIGH);
		delay(500);
		digitalWrite(BUZZER, LOW);
	    return false;
	}
	return true;

}

void Boil::Unpause()
{
	setTime(_now);
}