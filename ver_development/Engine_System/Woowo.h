////////////////////////////////////////////////////////////////////////////////
// WoowoWoowo Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Woowo_H_
#define _Woowo_H_

class CWoowo : public CCharacterEntity{
public:
	typedef enum WoowoAttType {LEFT = 0, RIGHT, BODY, EYE} WOOWOATTTYPE;

public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CWoowo>* m_pStateMachine;

public:
	CWoowo(int id);
	~CWoowo();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CWoowo>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void RenderOrgan();

	virtual void BoundUpdate();
};

#endif