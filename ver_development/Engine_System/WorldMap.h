////////////////////////////////////////////////////////////////////////////////
// �������� ��������
////////////////////////////////////////////////////////////////////////////////
#ifndef _WorldMap_H_
#define _WorldMap_H_

#include "./Engine_System/BaseManager.h"

class CWorldMap : public COrganEntity{
public:
	typedef enum WorldMapAttType {STAGEPOINT = 0, TEXT, LIGHT, DUST} WORLDMAPATTTYPE;

private:
// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CWorldMap>* m_pStateMachine;

public:
	CWorldMap(int id);
	~CWorldMap();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CWorldMap>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}
	virtual void RenderOrgan();
};

#endif