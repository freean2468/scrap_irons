////////////////////////////////////////////////////////////////////////////////
// Area Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Area_H_
#define _Area_H_

#include "./Engine_System/BaseManager.h"

class CArea : public COrganEntity{
public:
	typedef enum AreaAttType {CLEAR = 0, QM} AREAATTTYPE;

private:
// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CArea>* m_pStateMachine;

	int _areaNumber;
	bool _clear;

public:
	CArea(int p_nNum, char* p_pStr);
	~CArea();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CArea>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}
	virtual void RenderOrgan();
	
	void SetAreaNumber(int p_nNum){_areaNumber = p_nNum;}
	int GetAreaNumber(){return _areaNumber;}

	void SetClear(bool p_bool){_clear = p_bool;}
	bool GetClear(){return _clear;}
};

#endif