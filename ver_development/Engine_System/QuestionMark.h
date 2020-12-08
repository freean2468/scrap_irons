////////////////////////////////////////////////////////////////////////////////
// QuestionMark Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _QuestionMark_H_
#define _QuestionMark_H_

#include "./Engine_System/BaseManager.h"

class CQuestionMark : public CBaseEffect{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CQuestionMark>* m_pStateMachine;

	COrgan* _origin;
	bool _bOnOff; // on = true

public:
	CQuestionMark(COrgan* p_pOrgan);
	~CQuestionMark();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CQuestionMark>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CQuestionMark>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	COrgan* GetOrigin(){return _origin;}
};

#endif