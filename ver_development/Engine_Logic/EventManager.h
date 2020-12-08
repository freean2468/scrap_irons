////////////////////////////////////////////////////
// Event 관리 클래스
////////////////////////////////////////////////////
#ifndef _EventManager_H_
#define _EventManager_H_

class CEventStageManager{
private:
	CEventStage* _eventStage;
	CEventWorldMap* _eventWorldMap;
	
	bool _eventStageing;			// 이벤트 진행 중 여부
	int _index;				// present Senario text line index
	int _endIndex;			// Last text line index
	int _idList[64];
	char _textList[128][128];

private:
	CEventStageManager();
	CEventStageManager(const CEventStageManager&);
	CEventStageManager& operator =(const CEventStageManager&);

public:
	~CEventStageManager();
	static CEventStageManager* Instance(){
		static CEventStageManager instance;

		return &instance;
	}

	CEventStage* GetEventStage(){return _eventStage;}
	CEventWorldMap* GetEventWorldMap(){return _eventWorldMap;}
	bool ReadText(char* p_pStr);

	void InitVariable();
	bool NextText();

	void EntityInEvent();
	void EntityInUsual();

	void SetEventing(bool p_bool){_eventStageing = p_bool;}
	bool GetEventing(){return _eventStageing;}

	int GetIndex(){return _index;}
};

#define EventMgr CEventStageManager::Instance()

#endif