////////////////////////////////////////////////////////////////////////////////
// ���� Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Cart_H_
#define _Cart_H_

class CCart : public CCharacterEntity{
public:
	typedef enum CartAttType {PLANTER = 0, PIPE, LUMBER, NAIL, BODYFRONT, PUPIL, MOUSEOVER, MOUSEUNDER, WHEELLEFT, WHEELRIGHT} CARTATTTYPE;

public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CCart>* m_pStateMachine;

	float _rotVelocity;
public:
	CCart(int id);
	~CCart();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CCart>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void BoundUpdate();

	float GetRotVelocity(){return _rotVelocity;}
};

#endif