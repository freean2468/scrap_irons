////////////////////////////////////////////////////////////////////////////////
// Inventory ��� Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Inventory_H_
#define _Inventory_H_

#define INVENLIMIT 18

class CInventory : public COrganEntity{
public:
	typedef enum InvenAttType{OVER = 0, UNDER} INVENATTTYPE;

public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CInventory>* m_pStateMachine;
	CArray<CItem*> _thingsList;		// ����ǰ
	CArray<int> _thingsCount;		// ������ �ʿ��� ��� ����
	ID3DXFont*	_pFont;				// ��Ʈ �������̽� ����
	ID3DXFont*	_pFontForName;		// ��Ʈ �������̽� ����
	ID3DXFont*	_pFontForState;		// ��Ʈ �������̽� ����

public:
	CInventory(int id);
	~CInventory();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CInventory>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	CArray<CItem*>* GetThingsList(){return &_thingsList;}
	CArray<int>* GetThingsCount(){return &_thingsCount;}
	ID3DXFont* GetFont(){return _pFont;}
	ID3DXFont* GetFontForName(){return _pFontForName;}
	ID3DXFont* GetFontForState(){return _pFontForState;}

	void PutItem(CItem* p_pItem);
	void DeleteItem();
};

#endif