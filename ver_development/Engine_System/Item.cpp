#include "../BaseHeader.h"

CItem::CItem(int id):COrganEntity(id){
	// ���±�踦 �����Ѵ�.
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

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(ItemUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	float t_fTemp = 0.0f;
	int t_nTemp = 0;

	//// �ߺ� ��ǥ ���� ����, ��Ŀ ��ġ ���� ����
	//do{
		t_fTemp = (((rand() % 8) + 1) * 100.0f);

		// �ʿ� ������ ��ǥ�� ����
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
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CItem>(this);

	switch(p_eItemType){
		case WIRE:
			LoadEntityData("./script/Item/Wire.txt", this);
			strcpy(_name, "�콼 ���̾�");
			strcpy(_state, "�ݹ��̶� ���簡 �� �� ���� ���� ������ ���̾�.");
			_eItemType = WIRE;
			break;
		case BULB:
			LoadEntityData("./script/Item/Bulb.txt", this);
			strcpy(_name, "���� ����");
			strcpy(_state, "�������ȴ�.");
			_eItemType = BULB;
			break;
		case PLYWOOD:
			LoadEntityData("./script/Item/Plywood.txt", this);
			strcpy(_name, "������ ����");
			strcpy(_state, "���� �� ä ������ �� ����.");
			_eItemType = PLYWOOD;
			break;
		case REBAR:
			LoadEntityData("./script/Item/Rebar.txt", this);
			strcpy(_name, "�콼 ö��");
			strcpy(_state, "���� ���� ������.");
			_eItemType = REBAR;
			break;
		case TIRE:
			LoadEntityData("./script/Item/Tire.txt", this);
			strcpy(_name, "��Ÿ�̾�");
			strcpy(_state, "���� ���� ���۳� Ÿ�̾�.");
			_eItemType = TIRE;
			break;
		default:
			break;
	}

	// ó�� ���¸� �ʱ�ȭ
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