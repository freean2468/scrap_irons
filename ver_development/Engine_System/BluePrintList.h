////////////////////////////////////////////////////////////////////////////////
// BluePrintList 담당 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _BluePrintList_H_
#define _BluePrintList_H_

class CBluePrintScroll;

class CBluePrintList : public COrganEntity{
public:
	typedef enum BluePrintList{UP = 0, DOWN} BLUEPRINTLIST;

public:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CBluePrintList>* m_pStateMachine;
	CDLinkedList<CBluePrintScroll*> _scrollList;// 실제 설계도
	int _selectIndex;							// 선택된 설계도의 인덱스
	int _index;									// 설계도 인덱스 제한을 알리기 위해 존재하는 변수
	int _count;									// 설계도 갯수
	ID3DXFont*	_pFont;							// 폰트 인터페이스 변수
	bool _completeCollection;					// 선택된 설계도의 재료가 모두 모아졌는지
	bool _selectionList;						// 설계도를 선택했는지 여부

	bool _overap;								// AI중복 상태 체크

public:
	CBluePrintList(int id);
	~CBluePrintList();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CBluePrintList>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	ID3DXFont* GetFont(){return _pFont;}

	CDLinkedList<CBluePrintScroll*>* GetScrollList(){return &_scrollList;}
	int GetSelectIndex(){return _selectIndex;}
	void SetSelectIndex(int p_nIndex){_selectIndex = p_nIndex;}
	int GetIndex(){return _index;}
	void SetIndex(int p_nIndex){_index = p_nIndex;}
	int GetCount(){return _count;}
	bool GetCompleteCollection(){return _completeCollection;}
	void SetCompleteCollection(bool p_bool){_completeCollection = p_bool;}
	bool GetSelectionList(){return _selectionList;}
	void SetSelectionList(bool p_bool){_selectionList = p_bool;}
	bool GetOverap(){return _overap;}
	void SetOverap(bool p_bool){_overap = p_bool;}

	bool InsertNewScroll(CBluePrint* p_pBluePrint);
};

#endif