////////////////////////////////////////////////////////////////////////////////
// GateKeeper Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _GateKeeper_H_
#define _GateKeeper_H_

class CGateKeeper : public CCharacterEntity{
public:
	typedef enum GateKeeperAttType {FIRST = 0, SECOND, THIRD, ARM} GATEKEEPERATTTYPE;

private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CGateKeeper>* m_pStateMachine;

	float _deltaY;	// ���� �

public:
	CGateKeeper(int id);
	~CGateKeeper();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CGateKeeper>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void RenderOrgan();

	// �浹üũ ����
	void BoundUpdate();

	void SetDeltaY(float p_delta){_deltaY = p_delta;}
	float GetDeltaY(){return _deltaY;}
};

#endif