////////////////////////////////////////////////////////////////////////////////
// Worker Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Worker_H_
#define _Worker_H_

class CWorker : public CCharacterEntity{
public:
	typedef enum WorkerAttType {LEFT = 0, RIGHT, BODY, PIPE, LIGHTONE, LIGHTTWO, MOUSEUNDER, MOUSEOVER} WORKERATTTYPE;

private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CWorker>* m_pStateMachine;

	d3d::BoundingBox _mouseUnder;	// ��
	d3d::BoundingBox _mouseChin;	// ��

public:
	CWorker(int id);
	~CWorker();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CWorker>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void RenderOrgan();

	// ���Լ�	
	d3d::BoundingBox* GetChinBound(){return &_mouseChin;}

	// �浹üũ ����
	virtual void BoundUpdate();
	bool ComputeBoundMouseAndItem();
	virtual void BoundRender();
};

#endif