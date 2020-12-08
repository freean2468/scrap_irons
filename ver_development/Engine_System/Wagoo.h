////////////////////////////////////////////////////////////////////////////////
// WagooWagoo Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Wagoo_H_
#define _Wagoo_H_

class CWagoo : public CCharacterEntity{
public:
	typedef enum WagooAttType {HEAD = 0, EYE, LEFT, RIGHT} HEROATTTYPE;

public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CWagoo>* m_pStateMachine;

public:
	CWagoo(int id);
	~CWagoo();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CWagoo>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void RenderOrgan();

	virtual void BoundUpdate();
};

#endif