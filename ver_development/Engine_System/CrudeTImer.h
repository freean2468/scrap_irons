////////////////////////////////////////////////////////////
// Sider Engine에서의 현재 시간을 나타내는 클래스
////////////////////////////////////////////////////////////
#ifndef _CrudeTimer_H_
#define _CrudeTimer_H_

// 유일 객체
class CCrudeTimer{
private:
	 //set to the time (in seconds) when class is instantiated
	double m_dStartTime;

	//set the start time
	CCrudeTimer(){m_dStartTime = timeGetTime() * 0.001;}

	//copy ctor and assignment should be private
	CCrudeTimer(const CCrudeTimer&);
	CCrudeTimer& operator=(const CCrudeTimer&);
  
public:

	static CCrudeTimer* Instance(){
		static CCrudeTimer instance;

		return &instance;
	}

	//returns how much time has elapsed since the timer was started
	double GetCurrentTime(){return timeGetTime() * 0.001 - m_dStartTime;}
};

#define Clock CCrudeTimer::Instance()

#endif