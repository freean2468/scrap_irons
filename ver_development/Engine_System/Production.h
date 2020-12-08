////////////////////////////////////////////////////////////////////////////////
// Iron ���� â Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Production_H_
#define _Production_H_

class CProduction : public COrganEntity{
public:
	typedef enum ProductionAttType {CLOSE = 0, BUTTON} PRODUCTIONATTTYPE;

public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CProduction>* m_pStateMachine;
	ID3DXFont*	_pFont;		// ��Ʈ �������̽� ����
	bool _completeState;	// true�� �Ϸ��ư�� ������ �ϴ� ��Ȳ

public:
	CProduction(int id);
	~CProduction();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CProduction>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	ID3DXFont* GetFont(){return _pFont;}
	bool GetCompleteState(){return _completeState;}
	void SetCompleteState(bool p_bool){_completeState = p_bool;}
};

#endif