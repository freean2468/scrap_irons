////////////////////////////////////////////////////////////////////////////////
// ��(�ε鷹) Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Flower_H_
#define _Flower_H_

class CFlower : public CCharacterEntity{
public:
	typedef enum FlowerAttType {ONE = 0, TWO, THREE} FLOWERATTTYPE;

public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CFlower>* m_pStateMachine;

	float _rotVelocity;

public:
	CFlower(int id);
	~CFlower();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	virtual void BoundUpdate();

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CFlower>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	float GetRotVelocity(){return _rotVelocity;}
};

#endif