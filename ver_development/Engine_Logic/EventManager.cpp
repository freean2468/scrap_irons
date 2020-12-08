#include "../BaseHeader.h"

CEventStageManager::CEventStageManager(){
	_eventStage = new CEventStage(ID_EVENTSTAGE);
	EntityDB->RegisterEntity(_eventStage);

	_eventWorldMap = new CEventWorldMap(ID_EVENTWORLDMAP);
	EntityDB->RegisterEntity(_eventWorldMap);

	_eventStageing = false;
	InitVariable();
}

CEventStageManager::~CEventStageManager(){
	d3d::Delete<CBaseGameEntity*>(_eventStage);
	d3d::Delete<CBaseGameEntity*>(_eventWorldMap);
}

bool CEventStageManager::ReadText(char* p_pStr){
	_eventStageing = true;

	char t_szString[64];
	char ch;
	int nCount = 0;

	static int i = 0;

	FILE* fp = fopen(p_pStr, "r");
	if(fp==NULL)
		return false;

	while(1){
		nCount = 0;
		fgets(t_szString, 256, fp);
		sscanf(t_szString, "%d", &_idList[i]);

		if(_idList[i] == -100){
			_endIndex = i;
			i = 0;
			break;
		}

		ch = fgetc(fp);		
		while('\n' != ch){	
			strcpy(&_textList[i][nCount++], &ch);
			ch = fgetc(fp);	
		}

		_textList[i][nCount] = '\0';
		i++;
	}
	
	fclose(fp);

	EntityInEvent();

	// 처음 시나리오 진행
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, _idList[0], Msg_Senario, &_textList[0]);

	return true;	// 이벤트 대화 계속
}

void CEventStageManager::InitVariable(){
	for(int i = 0; i < 64; i++){
		_idList[i] = 0;
		_textList[i][i] = '\0'; 
		_index = 0;
	}
}

bool CEventStageManager::NextText(){
	if( ::GetAsyncKeyState(VK_RETURN) == 0xffff8001){
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, _idList[_index], Msg_SenarioEnd, NO_ADDITIONAL_INFO);
	
		_index++;

		if(_index == _endIndex){
			EntityInUsual();
			InitVariable();
			_eventStageing = false;
			return true;
		}

		if(_index != 0){
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, _idList[_index], Msg_Senario, &_textList[_index]);		
			return false;
		}
	}
	return false;
}

void CEventStageManager::EntityInEvent(){
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_HERO, Msg_Event, NO_ADDITIONAL_INFO);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_CART, Msg_Event, NO_ADDITIONAL_INFO);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_FLOWER, Msg_Event, NO_ADDITIONAL_INFO);

	CDListIterator<CCharacterEntity*> itr = AIMgr->GetOurForceList()->GetIterator();

	for(itr.Start(); itr.Valid(); itr.Forth()){
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, itr.Item()->ID(), Msg_Event, NO_ADDITIONAL_INFO);
	}

	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_WORKER, Msg_Event, NO_ADDITIONAL_INFO);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_MINIWORKER, Msg_Event, NO_ADDITIONAL_INFO);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_DUSTKID, Msg_Event, NO_ADDITIONAL_INFO);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_DUSTKING, Msg_Event, NO_ADDITIONAL_INFO);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_GATEKEEPER, Msg_Event, NO_ADDITIONAL_INFO);
}

void CEventStageManager::EntityInUsual(){
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_HERO, Msg_Usual, NO_ADDITIONAL_INFO);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_CART, Msg_Usual, NO_ADDITIONAL_INFO);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_FLOWER, Msg_Usual, NO_ADDITIONAL_INFO);

	CDListIterator<CCharacterEntity*> itr = AIMgr->GetOurForceList()->GetIterator();

	for(itr.Start(); itr.Valid(); itr.Forth()){
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, itr.Item()->ID(), Msg_Usual, NO_ADDITIONAL_INFO);
	}

	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_WORKER, Msg_Ready, NO_ADDITIONAL_INFO);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_MINIWORKER, Msg_Ready, NO_ADDITIONAL_INFO);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_DUSTKID, Msg_Ready, NO_ADDITIONAL_INFO);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_DUSTKING, Msg_Ready, NO_ADDITIONAL_INFO);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_GATEKEEPER, Msg_Ready, NO_ADDITIONAL_INFO);
}