#include "../BaseHeader.h"

CItem::CItem(int id):COrganEntity(id){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CItem>(this);

	int t_ItemType;

	if(StageMgr->GetAreaNumber() == 0){
		t_ItemType = rand() % 2 + 2;
	}
	else
		t_ItemType = rand() % 5;

	_name[0] = '\0';
	_state[0] = '\0';

	switch(t_ItemType){
		case REBAR:
			LoadEntityData("./script/Item/Rebar.txt", this);
			_eItemType = REBAR;
			break;
		case TIRE:
			LoadEntityData("./script/Item/Tire.txt", this);
			_eItemType = TIRE;
			break;
		case BULB:
			LoadEntityData("./script/Item/Bulb.txt", this);
			_eItemType = BULB;
			break;
		case PLYWOOD:
			LoadEntityData("./script/Item/Plywood.txt", this);
			_eItemType = PLYWOOD;
			break;
		case WIRE:
			LoadEntityData("./script/Item/Wire.txt", this);
			_eItemType = WIRE;
			break;
		default:
			break;
	}

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(ItemUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	float t_fTemp = 0.0f;
	int t_nTemp = 0;

	//// 중복 좌표 생성 방지, 워커 위치 생성 방지
	//do{
		t_fTemp = (((rand() % 8) + 1) * 100.0f);

		// 맵에 랜덤한 좌표에 생성
		t_nTemp = rand() % 10;
		t_fTemp = (float)t_nTemp * 0.1f;

		_body->GetPriPos()->x = ObjectMgr->GetEntity(CBaseObject::STAGEMOUNTAIN)->GetBody()->GetWidthHalf() * t_fTemp;

		if(rand()%2==0)
			_body->GetPriPos()->x *= -1.0f;
	//}while(_body->GetPriPos()->x < AIMgr->GetWorker()->GetBody()->GetPriPos()->x + AIMgr->GetWorker()->GetAttachmentFromType(CWorker::BODY)->GetRight()
	//	&& _body->GetPriPos()->x > AIMgr->GetWorker()->GetBody()->GetPriPos()->x + AIMgr->GetWorker()->GetAttachmentFromType(CWorker::BODY)->GetLeft());

	t_nTemp = (rand() % 5);
	t_fTemp = (float)((float)t_nTemp * 0.1f);

	_body->GetPriPos()->y = StageMgr->GetStageHeight() + _body->GetHeightHalf();
	_body->GetPriRot()->z = t_fTemp;

	_body->GetMtrlArray()->Get(_body->GetRow(), _body->GetCol()).Diffuse.a = 0.01f;
}

CItem::CItem(ITEMTYPE p_eItemType):COrganEntity(ID_ITEM){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CItem>(this);

	switch(p_eItemType){
		case WIRE:
			LoadEntityData("./script/Item/Wire.txt", this);
			strcpy(_name, "녹슨 와이어");
			strcpy(_state, "금방이라도 가루가 될 것 같은 아주 오래된 와이어.");
			_eItemType = WIRE;
			break;
		case BULB:
			LoadEntityData("./script/Item/Bulb.txt", this);
			strcpy(_name, "깨진 전구");
			strcpy(_state, "깨져버렸다.");
			_eItemType = BULB;
			break;
		case PLYWOOD:
			LoadEntityData("./script/Item/Plywood.txt", this);
			strcpy(_name, "조각난 합판");
			strcpy(_state, "조각 난 채 버려진 것 같다.");
			_eItemType = PLYWOOD;
			break;
		case REBAR:
			LoadEntityData("./script/Item/Rebar.txt", this);
			strcpy(_name, "녹슨 철근");
			strcpy(_state, "녹이 많이 슬었다.");
			_eItemType = REBAR;
			break;
		case TIRE:
			LoadEntityData("./script/Item/Tire.txt", this);
			strcpy(_name, "폐타이어");
			strcpy(_state, "공기 빠진 구멍난 타이어.");
			_eItemType = TIRE;
			break;
		default:
			break;
	}

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(ItemInInven->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

}

CItem::~CItem(){
	d3d::Delete< CStateMachine<CItem>* >(m_pStateMachine);
}

void CItem::RenderOrgan(){
	BodySetting();

	if(GetBody())
		GetBody()->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
	
	InitChainVector();

	if(GetAttachmentArray()->GetSize()){
		for(int i = 0; i < GetAttachmentArray()->GetSize(); i++){
			BodySetting();
			GetAttachmentArray()->Get(i)->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
			InitChainVector();
		}
	}

	InitChainVector();

	if(GetMessage()){
		if(GetMessage()->GetUse()){
			BodyOnlyPosSetting();
			GetMessage()->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
			GetMessage()->RenderLine();
		}
	}

	InitChainVector();
}