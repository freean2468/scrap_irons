////////////////////////////////////////////////////
// Event에 따라서 다양한 로직 구현
////////////////////////////////////////////////////
#ifndef _EventWorldMap_H_
#define _EventWorldMap_H_

class CEventWorldMap : public COrganEntity{
public:
	typedef enum EventWorldMapAttType{SCRAPMOUNTAIN = 0, FURNACE, CHIMNEY, DUSTBRIDGE, GOODHOPE, ENDING} EVENTWORLDMAPATTTYPE;

private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CEventWorldMap>* m_pStateMachine;

	// 폰트 인터페이스 변수
	ID3DXFont*	_pFont;		

	// 타이머
	CTimer* _timer;

public:
	//Event
	bool _ending;

public:
	CEventWorldMap(int id);
	~CEventWorldMap();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	virtual void RenderOrgan();

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CEventWorldMap>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	void SetTimer(DWORD dwDelayTime){_timer = new CTimer(dwDelayTime);}

	CTimer* GetTimer(){return _timer;}
};

#endif