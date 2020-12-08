////////////////////////////////////////////////////////////////////////////////
// ��ȣ�ۿ� ���� ǥ�� Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _SmallInfo_H_
#define _SmallInfo_H_

class CSmallInfo : public COrganEntity{
public:
	typedef enum SmallInfoAttType {GAGEBODY, BLUE, RED} SmallInfoATTTYPE;

public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CSmallInfo>* m_pStateMachine;

	CCharacterEntity* _origin;

public:
	CSmallInfo(CCharacterEntity* p_pEntity);
	~CSmallInfo();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CSmallInfo>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	CCharacterEntity* GetOrigin(){return _origin;}
};

#endif