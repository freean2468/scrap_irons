#include "../BaseHeader.h"

CInventory::CInventory(int id):COrganEntity(id){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CInventory>(this);

	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
	LoadEntityData("./script/UserInterface/Inventory/Inventory.txt", this);

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(InventoryMinimize->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_thingsList.Resize(INVENLIMIT);
	_thingsCount.Resize(INVENLIMIT);

	for(int i = 0; i < INVENLIMIT; i++){
		_thingsList.Get(i) = NULL;
		_thingsCount.Get(i) = 0;
	}

	_pFont = d3d::IniFont(11, 7, 200, false, "���� ���");
	_pFontForName = d3d::IniFont(15, 8, 700, false, "���� ���");
	_pFontForState = d3d::IniFont(12, 6, 500, false, "���� ���");
}

CInventory::~CInventory(){
	d3d::Delete< CStateMachine<CInventory >* >(m_pStateMachine);
}

void CInventory::PutItem(CItem* p_pItem){
	// �켱�� �� �������� �κ��丮�� �ִ��� Ȯ��
	for(int i = 0; i < INVENLIMIT; i++){
		if(_thingsList.Get(i)){
			if(_thingsList.Get(i)->GetItemType() == p_pItem->GetItemType()){
				_thingsCount.Get(i)++;				
				return;
			}
		}
	}

	// �κ��丮 ù ĭ���� �ʱ�ȭ
	float t_fX = -122.0f;
	float t_fY = 16.0f;

	// �κ��丮�� ���ٸ� �� ������ ������ ����
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