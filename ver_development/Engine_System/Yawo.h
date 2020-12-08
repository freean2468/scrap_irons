////////////////////////////////////////////////////////////////////////////////
// YawoYawo Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Yawo_H_
#define _Yawo_H_

class CYawo : public CCharacterEntity{
public:
	typedef enum YawoAttType {BODY = 0, HEAD, LEGONE, LEGTWO, LEGTHREE, LEGFOUR, LEGFIVE} YAWOATTTYPE;

public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CYawo>* m_pStateMachine;

public:
	CYawo(int id);
	~CYawo();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CYawo>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void RenderOrgan();

	virtual void BoundUpdate();

	virtual void ApplyDamageOurForceToEnemy();
};

#endif