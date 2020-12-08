////////////////////////////////////////////////////////////////////////////////
// MiniWorker 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _MiniWorker_H_
#define _MiniWorker_H_

class CMiniWorker : public CCharacterEntity{
public:
	typedef enum MiniWorkerAttType {LEFT = 0, RIGHT, BODY, PIPE, LIGHTONE, LIGHTTWO, MOUSEUNDER, MOUSEOVER} WORKERATTTYPE;

private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CMiniWorker>* m_pStateMachine;

	d3d::BoundingBox _mouseUnder;	// 입
	d3d::BoundingBox _mouseChin;	// 턱

public:
	CMiniWorker(int id);
	~CMiniWorker();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CMiniWorker>* GetFSM()const{return m_pStateMachine;}

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