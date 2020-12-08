////////////////////////////////////////////////////
// Event�� ���� �پ��� ���� ����
////////////////////////////////////////////////////
#ifndef _EventWorldMap_H_
#define _EventWorldMap_H_

class CEventWorldMap : public COrganEntity{
public:
	typedef enum EventWorldMapAttType{SCRAPMOUNTAIN = 0, FURNACE, CHIMNEY, DUSTBRIDGE, GOODHOPE, ENDING} EVENTWORLDMAPATTTYPE;

private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CEventWorldMap>* m_pStateMachine;

	// ��Ʈ �������̽� ����
	ID3DXFont*	_pFont;		

	// Ÿ�̸�
	CTimer* _timer;

public:
	//Event
	bool _ending;

public:
	CEventWorldMap(int id);
	~CEventWorldMap();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	virtual void RenderOrgan();

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CEventWorldMap>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	void SetTimer(DWORD dwDelayTime){_timer = new CTimer(dwDelayTime);}

	CTimer* GetTimer(){return _timer;}
};

#endif