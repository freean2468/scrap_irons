////////////////////////////////////////////////////////////////////////////////
// BluePrintScroll ��� Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _BluePrintScroll_H_
#define _BluePrintScroll_H_

class CBluePrint;

class CBluePrintScroll : public COrganEntity{
public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CBluePrintScroll>* m_pStateMachine;
	CDLinkedList<CItem*> _IngredientList;	// ������� ����Ʈ
	CDLinkedList<int> _IngredientCount;		// ������� �ʿ� ����
	ID3DXFont*	_pFont;		// ��Ʈ �������̽� ����
	char _type[32];			// Title String
	float _deltaY;			// Title ��¿� ����� Y��ǥ

	CBluePrint::BLUEPRINTTYPE _eType;		// AI ĳ���� Type
	int _materialCount;				// ���� ����� ����
	int _index;

public:
	CBluePrintScroll(CBluePrint::BluePrintType p_eType, char* p_pType, int p_nIndex);
	~CBluePrintScroll();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
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