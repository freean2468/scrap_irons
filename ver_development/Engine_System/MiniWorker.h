////////////////////////////////////////////////////////////////////////////////
// MiniWorker Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _MiniWorker_H_
#define _MiniWorker_H_

class CMiniWorker : public CCharacterEntity{
public:
	typedef enum MiniWorkerAttType {LEFT = 0, RIGHT, BODY, PIPE, LIGHTONE, LIGHTTWO, MOUSEUNDER, MOUSEOVER} WORKERATTTYPE;

private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CMiniWorker>* m_pStateMachine;

	d3d::BoundingBox _mouseUnder;	// ��
	d3d::BoundingBox _mouseChin;	// ��

public:
	CMiniWorker(int id);
	~CMiniWorker();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CMiniWorker>* GetFSM()const{return m_pStateMachine;}

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