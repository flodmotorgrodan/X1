/*************************** IOStream.cpp *************************************
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 *
 * Description  : Timer object to fire timer events at regular intervals
 *
 * Input        : Use the Enable() and Interval() methods to change timer frequency
 *                Timer callback function.
 * Output       : None
 * Return       : None
 * Usage        : Create a timer instance and call its doTimerEvent from the
 *                main loop
 *
 *
 *
 *   *Declaring an arry of timers may look like this
 *  TinyTimer Timer[] =
 *  {
 *  	TinyTimer(TinyTimer::en_timer::Slow, 1000, TimerCallback),
 *  	TinyTimer(TinyTimer::en_timer::Fast, 100, TimerCallback)
 *  };
 *
 *
 *
 *   *A callback function template may look like this
 *  void TimerCallback(TinyTimer& timer)
 *  {
 *  	switch (timer.timerId)
 *  	{
 *  		 *Slow timer maintains Access point and IoT server Connection
 *  		case TinyTimer::en_timer::Slow:
 *  		break;
 *  		case TinyTimer::en_timer::Fast:
 *  		break;
 *  	}
 *  }
 *  
 *   *Call from main loop to update an fire timer events
 *  void doTimers()
 *  {
 *  	 *Loop all timers to call their respective 'doTimerEvent'
 *  	for (int i=0;i<=1;i++) Timer[i].doTimerEvent();
 *  }
 *  
 *  
********************************************************************************/

#include "TinyTimer.h"


//Provide an instance of the TinyTimer for main prog to configure

//Constructor, set unique timer number and callback function
//The callback function will be called each intervalMs and receive the timerID as parameter
//For the timer to run call the .doTimerEvent() regularly from the application main loop.
TinyTimer::TinyTimer(en_timer timerID, long intervalMs, timercallback_t timerCallback, bool enabled = true)
: timerId(timerID)
{
	Interval(intervalMs);
	_timerCallback = timerCallback;
	_enabled = enabled;
}

//Assign timer callback function
void TinyTimer::setCallback(timercallback_t timerCallback)
{
	_timerCallback = timerCallback;	
}

void TinyTimer::Enable(int enable)
{
	_enabled = (enable) ? true : false;
}

//Set new timer interval - timer will be prolonged
void TinyTimer::Interval(long intervalMs)
{
	_interval = intervalMs;
	_timeStarted = millis();
}
	
//Check if timer up for an event and set for a new event if expired
bool TinyTimer::doTimerEvent()
{
	//Check if timer interval has elapsed
	//Rollover safe we hope
	//https://arduino.stackexchange.com/questions/12587/how-can-i-handle-the-millis-rollover
	bool retval = (millis() - _timeStarted >= _interval);
	if (retval)
	{
		//Timer trigged - Set new star time
		_timeStarted = millis();
			
		//Try using dedicated callback function
		if (_timerCallback!=NULL && _enabled)
		{
			_timerCallback(*this);
		}
	}
	return retval;
}
