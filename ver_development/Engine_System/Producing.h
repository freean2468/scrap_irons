////////////////////////////////////////////////////////////////////////////////
// Iron ���� �Ϸ� â Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Producing_H_
#define _Producing_H_

class CProducing : public COrganEntity{
public:
	typedef enum ProducingAttType {DOORLEFT = 0, DOORRIGHT, NEEDLE} PRODUCINGATTTYPE;

public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CProducing>* m_pStateMachine;

public:
	CProducing(int id);
	~CProducing();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CProducing>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void RenderOrgan();
};

#endif