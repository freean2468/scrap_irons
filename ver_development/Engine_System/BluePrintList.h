////////////////////////////////////////////////////////////////////////////////
// BluePrintList ��� Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _BluePrintList_H_
#define _BluePrintList_H_

class CBluePrintScroll;

class CBluePrintList : public COrganEntity{
public:
	typedef enum BluePrintList{UP = 0, DOWN} BLUEPRINTLIST;

public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CBluePrintList>* m_pStateMachine;
	CDLinkedList<CBluePrintScroll*> _scrollList;// ���� ���赵
	int _selectIndex;							// ���õ� ���赵�� �ε���
	int _index;									// ���赵 �ε��� ������ �˸��� ���� �����ϴ� ����
	int _count;									// ���赵 ����
	ID3DXFont*	_pFont;							// ��Ʈ �������̽� ����
	bool _completeCollection;					// ���õ� ���赵�� ��ᰡ ��� ���������
	bool _selectionList;						// ���赵�� �����ߴ��� ����

	bool _overap;								// AI�ߺ� ���� üũ

public:
	CBluePrintList(int id);
	~CBluePrintList();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
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