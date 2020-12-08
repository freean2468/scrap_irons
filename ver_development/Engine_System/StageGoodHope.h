////////////////////////////////////////////////////////////////////////////////
// StageGoodHope Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _StageGoodHope_H_
#define _StageGoodHope_H_

class CStageGoodHope : public COrganEntity{
public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CStageGoodHope>* m_pStateMachine;

public:
	CStageGoodHope(int id);
	~CStageGoodHope();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CStageGoodHope>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}
};

#endif