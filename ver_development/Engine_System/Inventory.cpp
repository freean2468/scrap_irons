#include "../BaseHeader.h"

CInventory::CInventory(int id):COrganEntity(id){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CInventory>(this);

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/UserInterface/Inventory/Inventory.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(InventoryMinimize->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_thingsList.Resize(INVENLIMIT);
	_thingsCount.Resize(INVENLIMIT);

	for(int i = 0; i < INVENLIMIT; i++){
		_thingsList.Get(i) = NULL;
		_thingsCount.Get(i) = 0;
	}

	_pFont = d3d::IniFont(11, 7, 200, false, "맑은 고딕");
	_pFontForName = d3d::IniFont(15, 8, 700, false, "맑은 고딕");
	_pFontForState = d3d::IniFont(12, 6, 500, false, "맑은 고딕");
}

CInventory::~CInventory(){
	d3d::Delete< CStateMachine<CInventory >* >(m_pStateMachine);
}

void CInventory::PutItem(CItem* p_pItem){
	// 우선은 그 아이템이 인벤토리에 있는지 확인
	for(int i = 0; i < INVENLIMIT; i++){
		if(_thingsList.Get(i)){
			if(_thingsList.Get(i)->GetItemType() == p_pItem->GetItemType()){
				_thingsCount.Get(i)++;				
				return;
			}
		}
	}

	// 인벤토리 첫 칸으로 초기화
	float t_fX = -122.0f;
	float t_fY = 16.0f;

	// 인벤토리에 없다면 빈 공간에 아이템 소지
	for(int i = 0; i < INVENLIMIT; i++){
		if(_thingsList.Get(i) == NULL){
			_thingsList.Insert(new CItem(p_pItem->GetItemType()), i);
			_thingsCount.Get(i)++;				
			_thingsList.Get(i)->GetBody()->GetPriPos()->x = t_fX;
			_thingsList.Get(i)->GetBody()->GetPriPos()->y = t_fY;
			_thingsList.Get(i)->GetBody()->GetPriSca()->x = 0.7f;
			_thingsList.Get(i)->GetBody()->GetPriSca()->y = 0.7f;

			return;
		}

		t_fX += 43.0f;
		if(((i+1)%5) == 0){
			t_fX = -122.0f;
			t_fY += 35.0f;
		}
	}
}

void CInventory::DeleteItem(){
	for(int i = 0; i < INVENLIMIT; i++){
		if(_thingsList.Get(i)){
			if(_thingsCount.Get(i) <= 0){
				d3d::Delete<CItem*>(_thingsList.Get(i));	
				_thingsList.Get(i) = NULL;
			}
		}
	}
}