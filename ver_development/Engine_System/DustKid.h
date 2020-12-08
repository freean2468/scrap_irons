////////////////////////////////////////////////////////////////////////////////
// DustKid Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _DustKid_H_
#define _DustKid_H_

class CDustKid : public CCharacterEntity{
public:
	typedef enum DustKidAttType {SUB = 0, CORE, EYE} DUSTKIDATTTYPE;

private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CDustKid>* m_pStateMachine;

public:
	CDustKid(int id);
	~CDustKid();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CDustKid>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void RenderOrgan();

	// �浹üũ ����
	void BoundUpdate();
};

#endif