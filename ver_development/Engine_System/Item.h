////////////////////////////////////////////////////////////////////////////////
// Item�� Ư���� ���� Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Item_H_
#define _Item_H_

#include "./Engine_System/BaseManager.h"
class CBluePrint;

class CItem : public COrganEntity{
public:
	typedef enum ItemType {BLUEPRINT = -1, REBAR, BULB, PLYWOOD, WIRE, TIRE, CHARGER} ITEMTYPE;

private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CItem>* m_pStateMachine;
	ITEMTYPE _eItemType;
	char _name[16];
	char _state[64];

public:
	CItem(int id);
	CItem(ITEMTYPE p_eItemType);
	~CItem();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	void RenderOrgan();

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CItem>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CItem>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	ITEMTYPE GetItemType(){return _eItemType;}
	void SetItemType(ITEMTYPE p_eType){_eItemType = p_eType;}

	char* GetName(){return _name;}
	char* GetState(){return _state;}
};

#endif