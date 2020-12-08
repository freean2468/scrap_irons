////////////////////////////////////////////////////////////////////////////////
// ���ΰ� Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Hero_H_
#define _Hero_H_

class CHero : public CCharacterEntity{
public:
	typedef enum HeroAttType {ARM = 0, PUPIL} HEROATTTYPE;

private:
	float _bodyRotVelocity;
	float _armRotVelocity;
	float _pupilRotVelocity;

public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CHero>* m_pStateMachine;

	// Ÿ�̸�
	CTimer* _timer;
public:
	CHero(int id);
	~CHero();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CHero>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void BoundUpdate();

	void SetTimer(DWORD dwDelayTime){_timer = new CTimer(dwDelayTime);}

	CTimer* GetTimer(){return _timer;}

	virtual void CalculationOrgan(float timeDelta){}

	float GetBodyRotVelocity(){return _bodyRotVelocity;}
	float GetArmRotVelocity(){return _armRotVelocity;}
	float GetPupilRotVelocity(){return _pupilRotVelocity;}
};

#endif