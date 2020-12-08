////////////////////////////////////////////////////////////////////////////////
// Inventory 담당 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Inventory_H_
#define _Inventory_H_

#define INVENLIMIT 18

class CInventory : public COrganEntity{
public:
	typedef enum InvenAttType{OVER = 0, UNDER} INVENATTTYPE;

public:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CInventory>* m_pStateMachine;
	CArray<CItem*> _thingsList;		// 소지품
	CArray<int> _thingsCount;		// 각각의 필요한 재료 갯수
	ID3DXFont*	_pFont;				// 폰트 인터페이스 변수
	ID3DXFont*	_pFontForName;		// 폰트 인터페이스 변수
	ID3DXFont*	_pFontForState;		// 폰트 인터페이스 변수

public:
	CInventory(int id);
	~CInventory();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
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