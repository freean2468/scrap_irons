////////////////////////////////////////////////////////////////////////////////
// BluePrintScroll 담당 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _BluePrintScroll_H_
#define _BluePrintScroll_H_

class CBluePrint;

class CBluePrintScroll : public COrganEntity{
public:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CBluePrintScroll>* m_pStateMachine;
	CDLinkedList<CItem*> _IngredientList;	// 구성요소 리스트
	CDLinkedList<int> _IngredientCount;		// 구성요소 필요 갯수
	ID3DXFont*	_pFont;		// 폰트 인터페이스 변수
	char _type[32];			// Title String
	float _deltaY;			// Title 출력에 사용할 Y좌표

	CBluePrint::BLUEPRINTTYPE _eType;		// AI 캐릭터 Type
	int _materialCount;				// 구성 재료의 갯수
	int _index;

public:
	CBluePrintScroll(CBluePrint::BluePrintType p_eType, char* p_pType, int p_nIndex);
	~CBluePrintScroll();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CBluePrintScroll>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	float GetDeltaY(){return _deltaY;}
	void SetDeltaY(float p_float){_deltaY = p_float;}
	char* GetTitle(){return _type;}
	ID3DXFont* GetFont(){return _pFont;}
	int GetIndex(){return _index;}
	void SetIndex(int p_nIndex){_index = p_nIndex;}
	CBluePrint::BLUEPRINTTYPE GetOurForceType(){return _eType;}
	int GetOurForceTypeID();
	int GetMaterialCount(){return _materialCount;}

	CDLinkedList<CItem*>* GetIngredients(){return &_IngredientList;}
	CDLinkedList<int>* GetIngredientsCount(){return &_IngredientCount;}
};

#endif