////////////////////////////////////////////////////////////////////////////////
// Intro Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Intro_H_
#define _Intro_H_

class CIntro : public COrganEntity{
public:
	typedef enum IntroAttType {GAGEBODY, BLUE, RED} IntroATTTYPE;

public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CIntro>* m_pStateMachine;

	CCharacterEntity* _origin;

public:
	CIntro(int _id);
	~CIntro();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CIntro>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	CCharacterEntity* GetOrigin(){return _origin;}
};

#endif