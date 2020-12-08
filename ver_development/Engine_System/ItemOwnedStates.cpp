#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CItemUsual::Enter(CItem* pItem){
	
}

void CItemUsual::Execute(CItem* pItem){
	CBody* t_pBody = pItem->GetBody();
	
	if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a < 1.0f)
		t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.02f;

	// 계산
	ObjectMgr->ComputeBountItemAndHero(pItem);

	pItem->RenderOrgan();
}

void CItemUsual::Exit(CItem* pItem){

}

bool CItemUsual::OnMessage(CItem* agent, const Telegram& msg){
	return false;
}

///////////////////////////////////////////////////////////
// Get State
///////////////////////////////////////////////////////////
void CItemGet::Enter(CItem* pItem){
	_fXVelocity = 0.5f;
	_fYVelocity = 0.5f;
	_fVelocity = 0.0f;
}

void CItemGet::Execute(CItem* pItem){
	CBody* t_pCartBody = AIMgr->GetCart()->GetBody();
	CBody* t_pBody = pItem->GetBody();

	_fVelocity += 0.2f;

	// 바디 계산
	if(t_pCartBody->GetPriPos()->x < t_pBody->GetPriPos()->x){
		t_pBody->GetPriPos()->x -= _fXVelocity + _fVelocity;
	}
	else if(t_pCartBody->GetPriPos()->x > t_pBody->GetPriPos()->x){
		t_pBody->GetPriPos()->x += _fXVelocity + _fVelocity;
	}
	t_pBody->GetPriPos()->y += _fYVelocity;

	t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.05f;

	_fXVelocity += 0.001f;
	_fYVelocity += 0.002f;

	// 부속물 계산
	pItem->RenderOrgan();		
}

void CItemGet::Exit(CItem* pItem){
	_fVelocity = 0.0f;
}

bool CItemGet::OnMessage(CItem* agent, const Telegram& msg){
	return false;
}

///////////////////////////////////////////////////////////
// InInven State
///////////////////////////////////////////////////////////
void CItemInInven::Enter(CItem* pItem){

}

void CItemInInven::Execute(CItem* pItem){
	// 바디 계산

	// 부속물 계산
	pItem->RenderOrgan();
}

void CItemInInven::Exit(CItem* pItem){

}

bool CItemInInven::OnMessage(CItem* agent, const Telegram& msg){
	return false;
}

///////////////////////////////////////////////////////////
// Destroyed State
///////////////////////////////////////////////////////////
void CItemDestroyed::Enter(CItem* pItem){
	_fXVelocity = 1.5f;
	_fYVelocity = 1.2f;
}

void CItemDestroyed::Execute(CItem* pItem){
	CBody* t_pBody = pItem->GetBody();
	CBody* t_pWorkerBody;

	// 바디 계산
	if(StageMgr->GetAreaNumber() == 1){
		t_pWorkerBody = AIMgr->GetMiniWorker()->GetBody();

		_fXVelocity += 0.001f;
		_fYVelocity += 0.002f;
	}
	else if(StageMgr->GetAreaNumber() == 2){
		t_pWorkerBody = AIMgr->GetWorker()->GetBody();

		_fXVelocity += 0.002f;
		_fYVelocity += 0.004f;
	}	

	// 바디 계산
	if(t_pWorkerBody->GetPriPos()->x < t_pBody->GetPriPos()->x){
		t_pBody->GetPriPos()->x -= _fXVelocity;
	}
	else if(t_pWorkerBody->GetPriPos()->x > t_pBody->GetPriPos()->x){
		t_pBody->GetPriPos()->x += _fXVelocity;
	}
	t_pBody->GetPriPos()->y += _fYVelocity;

	t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.02f;

	// 부속물 계산
	pItem->RenderOrgan();
}

void CItemDestroyed::Exit(CItem* pItem){

}

bool CItemDestroyed::OnMessage(CItem* agent, const Telegram& msg){
	return false;
}