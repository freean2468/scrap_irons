////////////////////////////////////////////////////////////////////////////////
// DustKing Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _DustKing_H_
#define _DustKing_H_

class CDustKing : public CCharacterEntity{
public:
	typedef enum DustKingAttType {SUB = 0, CORE, EYE, PUPIL, TIARA, HAND} DUSTKIDATTTYPE;

private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CDustKing>* m_pStateMachine;

public:
	CDustKing(int id);
	~CDustKing();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CDustKing>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void RenderOrgan();

	// �浹üũ ����
	void BoundUpdate();
};

#endif