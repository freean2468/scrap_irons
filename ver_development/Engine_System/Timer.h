////////////////////////////////////////////////////////////////////////////////
// 타이머 기능을 가진 클래스
////////////////////////////////////////////////////////////////////////////////

#ifndef __TIMER_H__
#define __TIMER_H__

class CTimer{
private:
	DWORD dwOldTime;			// 지난 시간을 담고 있는 변수
	DWORD dwDelayTime;			// 측정할 시간을 담고 있는 변수
	DWORD _delayTime;			// 측정할 시간을 담고 있는 변수

public:
	CTimer():dwOldTime(-1), dwDelayTime(-1){}
	CTimer(DWORD dwDelayTime);
	~CTimer(){}

	DWORD GetElapseTime();
	BOOL IsElapseTimer();
	BOOL IsValidTimer();
};

#endif







