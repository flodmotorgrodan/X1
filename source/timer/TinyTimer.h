// TinyTimer.h
// 000-004

#ifndef _TINYTIMER_h
#define _TINYTIMER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class TinyTimer
{

public:

	// Two timer Id;s - add more if you like
	const enum class en_timer : uint8_t
	{
		Slow = 0, //Slow timer for blinking and state machine clock 1 sec interval
		Fast = 1, //Faster timer for flashing and current sensing approximatively 100ms
	} timerId; 


    //Define a type for the callback signature 
	//Declare once here and used by type name 'TimerCallback_t'
	typedef void (*timercallback_t)(TinyTimer&);
		
private:
	//en_timer _timerId;


	timercallback_t _timerCallback = NULL;
	//void (*_timerCallback)(TinyTimer*) = NULL;
	unsigned long _interval=0;
	unsigned long _timeStarted=0;
	bool _enabled;
	

public:
	//Constructor, set unique timer number and callback function
	//The callback function will be called each intervalMs and receive the timerID as parameter
	//For the timer to run call the .doTimerEvent() regularly from the application main loop.
	TinyTimer(en_timer timerID, long intervalMs, timercallback_t timerCallback, bool enabled = true);

	void Enable(int enable);

	//Set new timer interval - timer will be prolonged
	void Interval(long intervalMs);
	
	//Check if timer up for an event and set for a new event if expired
	 bool doTimerEvent();

	//Assign timer callback function 
	void setCallback(timercallback_t timerCallback);
		

};

//extern TinyTimer TinyTimer[];


#endif

