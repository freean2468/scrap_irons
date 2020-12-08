#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// AreaSelection State
///////////////////////////////////////////////////////////
void CStageMountainAreaSelection::Enter(CStageMountain* pStageMountain){
	
}

void CStageMountainAreaSelection::Execute(CStageMountain* pStageMountain){
	float t_fX = EngineMgr->GetpInformation()->GetAdjustedX();
	float t_fY = EngineMgr->GetpInformation()->GetAdjustedY();

	CBody* t_pBody;

	// 즉석 충돌체크와 렌더링
	for(int i = 0; i < 3; i++){
		t_pBody = pStageMountain->GetArea(i)->GetBody();
		if(t_pBody->GetLeft() - 10.0f < t_fX &&	t_pBody->GetRight() - 6.0f > t_fX &&
			t_pBody->GetTop() + 14.0f > t_fY &&	t_pBody->GetBottom() + 13.0f < t_fY){
			if(i == 0){
				if(pStageMountain->GetArea(i)->GetClear()){
					t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a = 1.0f;
					pStageMountain->GetArea(i)->GetAttachmentFromType(CArea::CLEAR)->GetMtrlArray()->Get(0, 0).Diffuse.a = 1.0f;
					pStageMountain->GetArea(i)->GetAttachmentFromType(CArea::QM)->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;
				}
				else
					pStageMountain->GetArea(i)->GetAttachmentFromType(CArea::QM)->GetMtrlArray()->Get(0, 0).Diffuse.a = 1.0f;

				if(EngineMgr->GetLButtonState()){					
					StageMgr->SetAreaNumber(i);							
				}
			}
			else{
				if(pStageMountain->GetArea(i-1)->GetClear()){
					if(pStageMountain->GetArea(i)->GetClear()){
						t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a = 1.0f;
						pStageMountain->GetArea(i)->GetAttachmentFromType(CArea::CLEAR)->GetMtrlArray()->Get(0, 0).Diffuse.a = 1.0f;
						pStageMountain->GetArea(i)->GetAttachmentFromType(CArea::QM)->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;
					}
					else
						pStageMountain->GetArea(i)->GetAttachmentFromType(CArea::QM)->GetMtrlArray()->Get(0, 0).Diffuse.a = 1.0f;

					if(EngineMgr->GetLButtonState()){					
						StageMgr->SetAreaNumber(i);							
					}
				}
				else
					pStageMountain->GetArea(i)->GetAttachmentFromType(CArea::QM)->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.5f;
			}
		}
		else{			
			if(pStageMountain->GetArea(i)->GetClear()){
				t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.5f;
				pStageMountain->GetArea(i)->GetAttachmentFromType(CArea::QM)->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;
				pStageMountain->GetArea(i)->GetAttachmentFromType(CArea::CLEAR)->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.5f;
			}
			else
				pStageMountain->GetArea(i)->GetAttachmentFromType(CArea::QM)->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.5f;
		}

		pStageMountain->GetArea(i)->RenderOrgan();
	}
}

void CStageMountainAreaSelection::Exit(CStageMountain* pStageMountain){

}

bool CStageMountainAreaSelection::OnMessage(CStageMountain* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Area1:
			agent->GetFSM()->ChangeState(StageMountainArea1->Instance());
			return true;
		case Msg_Area2:
			agent->GetFSM()->ChangeState(StageMountainArea2->Instance());
			return true;
		case Msg_Area3:
			agent->GetFSM()->ChangeState(StageMountainArea3->Instance());
			return true;	
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Area1 State
///////////////////////////////////////////////////////////
void CStageMountainArea1::Enter(CStageMountain* pStageMountain){
	MusicMgr->PlayMP3FileForBGM("./Sound/ScrapMountain.mp3");
}

void CStageMountainArea1::Execute(CStageMountain* pStageMountain){
	pStageMountain->RenderOrgan();

	AIMgr->DustKidUpdate();

	if(AIMgr->GetDustKid()->GetLive() == false && EventMgr->GetEventStage()->_dustKidDie == false){
		EventMgr->GetEventStage()->GetFSM()->ChangeState(EventStageDustKidDie->Instance());
		EventMgr->GetEventStage()->_dustKidDie = true;
	}
}

void CStageMountainArea1::Exit(CStageMountain* pStageMountain){
	if(AIMgr->GetDustKid()->GetLive() == false){
		if(pStageMountain->GetArea(0)->GetClear() == false){
			pStageMountain->GetArea(0)->SetClear(true);
		}
	}
}

bool CStageMountainArea1::OnMessage(CStageMountain* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Selection:
			agent->GetFSM()->ChangeState(StageMountainAreaSelection->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Area2 State
///////////////////////////////////////////////////////////
void CStageMountainArea2::Enter(CStageMountain* pStageMountain){
	MusicMgr->PlayMP3FileForBGM("./Sound/ScrapMountain.mp3");
}

void CStageMountainArea2::Execute(CStageMountain* pStageMountain){
	pStageMountain->RenderOrgan();

	AIMgr->MiniWorkerUpdate();
}

void CStageMountainArea2::Exit(CStageMountain* pStageMountain){
	if(AIMgr->GetMiniWorker()->GetLive() == false){
		if(pStageMountain->GetArea(1)->GetClear() == false){
			pStageMountain->GetArea(1)->SetClear(true);
		}
	}
}

bool CStageMountainArea2::OnMessage(CStageMountain* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Selection:
			agent->GetFSM()->ChangeState(StageMountainAreaSelection->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Area3 State
///////////////////////////////////////////////////////////
void CStageMountainArea3::Enter(CStageMountain* pStageMountain){
	MusicMgr->PlayMP3FileForBGM("./Sound/ScrapMountainLast.mp3");
}

void CStageMountainArea3::Execute(CStageMountain* pStageMountain){
	pStageMountain->RenderOrgan();

	// Enemy 그리기
	AIMgr->WorkerUpdate();

	if(AIMgr->GetWorker()->GetLive() == false && EventMgr->GetEventStage()->_workerDie == false){
		EventMgr->GetEventStage()->GetFSM()->ChangeState(EventStageWorkerDie->Instance());
		EventMgr->GetEventStage()->_workerDie = true;
	}
}

void CStageMountainArea3::Exit(CStageMountain* pStageMountain){
	if(AIMgr->GetWorker()->GetLive() == false){
		if(pStageMountain->GetArea(2)->GetClear() == false){
			pStageMountain->GetArea(2)->SetClear(true);
			StageMgr->_scrapMountainClear = true;
		}
	}
}

bool CStageMountainArea3::OnMessage(CStageMountain* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Selection:
			agent->GetFSM()->ChangeState(StageMountainAreaSelection->Instance());
			return true;
		default:
			return false;
	}
}