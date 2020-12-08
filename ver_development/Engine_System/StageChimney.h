////////////////////////////////////////////////////////////////////////////////
// StageChimney Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _StageChimney_H_
#define _StageChimney_H_

class CStageChimney : public COrganEntity{
public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CStageChimney>* m_pStateMachine;

public:
	CStageChimney(int id);
	~CStageChimney();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CStageChimney>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}
};

#endif