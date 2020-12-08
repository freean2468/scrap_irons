#include "../BaseHeader.h"

// Ÿ�̸� �ʱ�ȭ
// ó�� �ð��� ������ �� ȣ��
CTimer::CTimer(DWORD dwDelayTime){
	this->dwOldTime = GetTickCount();		// ���� �ð� ����
	this->dwDelayTime = dwDelayTime;
	_delayTime = dwDelayTime;
}

// �ð��� ���
// �ʱ⿡ ������ �ð��� ����Ǿ����� �����ϴ� �Լ�
BOOL CTimer::IsElapseTimer(){	
	// GetTickCount�Լ� : OS�� ���۵� �ĺ��� ��������� �ð��� �и�������(1/1000��) ������ ��ȯ
	DWORD dwCurTime = GetTickCount();
	DWORD dwElapsed = dwCurTime - this->dwOldTime;	

	if (dwElapsed >= this->dwDelayTime){		
		this->dwDelayTime = 0;				// 0���� �ʱ�ȭ
		this->dwOldTime = dwCurTime;			// ���� �ð����� �ʱ�ȭ
		return TRUE;							// ���� �ð��� ����Ǿ����� �˸�.
	}	

	return FALSE;
}

// Ÿ�̸Ӱ� ���� ��ȿ���� �����ϴ� �Լ�
// Timer�� ���������� �˻��ؾ� �Ѵٸ� �� �Լ��� ���
BOOL CTimer::IsValidTimer(){
	if (this->dwDelayTime)
		return TRUE;
	else 
		return FALSE;
}

DWORD CTimer::GetElapseTime(){
	// GetTickCount�Լ� : OS�� ���۵� �ĺ��� ��������� �ð��� �и�������(1/1000��) ������ ��ȯ
	DWORD dwCurTime = GetTickCount();
	DWORD dwElapsed = dwCurTime - this->dwOldTime;	

	if (dwElapsed >= this->_delayTime){			
		return _delayTime;							
	}	
	else{
		return dwElapsed;
	}
}














