////////////////////////////////////////////////////////////////////////////////
// Ÿ�̸� ����� ���� Ŭ����
////////////////////////////////////////////////////////////////////////////////

#ifndef __TIMER_H__
#define __TIMER_H__

class CTimer{
private:
	DWORD dwOldTime;			// ���� �ð��� ��� �ִ� ����
	DWORD dwDelayTime;			// ������ �ð��� ��� �ִ� ����
	DWORD _delayTime;			// ������ �ð��� ��� �ִ� ����

public:
	CTimer():dwOldTime(-1), dwDelayTime(-1){}
	CTimer(DWORD dwDelayTime);
	~CTimer(){}

	DWORD GetElapseTime();
	BOOL IsElapseTimer();
	BOOL IsValidTimer();
};

#endif







