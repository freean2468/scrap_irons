////////////////////////////////////////////////////////////////////////////////
// Worker 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Worker_H_
#define _Worker_H_

class CWorker : public CCharacterEntity{
public:
	typedef enum WorkerAttType {LEFT = 0, RIGHT, BODY, PIPE, LIGHTONE, LIGHTTWO, MOUSEUNDER, MOUSEOVER} WORKERATTTYPE;

private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CWorker>* m_pStateMachine;

	d3d::BoundingBox _mouseUnder;	// 입
	d3d::BoundingBox _mouseChin;	// 턱

public:
	CWorker(int id);
	~CWorker();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CWorker>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void RenderOrgan();

	// 겟함수	
	d3d::BoundingBox* GetChinBound(){return &_mouseChin;}

	// 충돌체크 관련
	virtual void BoundUpdate();
	bool ComputeBoundMouseAndItem();
	virtual void BoundRender();
};

#endif