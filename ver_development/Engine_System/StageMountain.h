////////////////////////////////////////////////////////////////////////////////
// Mt.Scrap �������� ��� Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _StageMountain_H_
#define _StageMountain_H_

#include "./Engine_System/BaseManager.h"

class CStageMountain : public COrganEntity{
public:
	typedef enum StageMountainAttType {SMOKE = 0} STAGEMOUNTAINTTTYPE;

private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CStageMountain>* m_pStateMachine;

	// Area
	CArea* _area[3];

public:
	CStageMountain(int id);
	~CStageMountain();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CStageMountain>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}
	virtual void RenderOrgan();

	CArea* GetArea(int p_index){return _area[p_index];}
};

#endif