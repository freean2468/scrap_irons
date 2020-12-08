////////////////////////////////////////////////////////////////////////////////
// ������ ������Ʈ���� �����ϴ� Mgr Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _ObjectManager_H_
#define _ObjectManager_H_

// Get&Set �Լ��� ū �з��� ���� ObjectType�� ���� �˾Ƽ� ���� ������ �ϸ� ���?
// Entity Type�� ����� ������ �迭�� ��������.

class CObjectManager{
private:
	CDLinkedList<COrganEntity*> _entityList;	// Character�� ������ ��� Entity DataBase
	CDLinkedList<CItem*> _itemList;				// Item DataBase

	const int _itemLimit;
	int _itemCount;

private:
	CObjectManager();
	CObjectManager(const CObjectManager&);
	CObjectManager& operator =(const CObjectManager&);

public:
	~CObjectManager();
	static CObjectManager* Instance(){
		static CObjectManager instance;

		return &instance;
	}

	////////////////////////////////////
	//     ������Ʈ �浹üũ          //
	// �Ϲ�
	bool ComputeBoundEntity(COrganEntity* p_pE1, COrganEntity* p_pE2);
	// �޴�����
	int ComputeBoundMenu();
	// ���콺�� StagePoint
	float ComputeBoundStagePointAndMouse(CSection* pSection);
	// Stage�� ���ΰ�
	void ComputeBoundStageHomeAndHero();
	void ComputeGetOutStage(CBaseObject::OWNER p_eBG, CBody* p_pBody);
	// Item�� ���ΰ�
	void ComputeBountItemAndHero(CItem* t_pItem);

	////////////////////////////////////
	// �ڷ� ������ DB�� LinkedList �� ���� ����Ѵ�.
	// DB�� �������� LinkedList�� ���뼺�� ����
	CBaseGameEntity* GetEntity(int id){return EntityDB->GetEntityFromID(id);}
	COrganEntity* GetEntity(CBaseObject::Owner p_eOwner);

	////////////////////////////////////
	// _itemList 
	CDLinkedList<CItem* >* GetItemList(){return &_itemList;}
	void CreatItem();
	void CreatBluePrint(); // ���赵�� Ư���� ������
	void UpdateItem();
	void InventoryUpdateAndDeleteItem();

	///////////////////////////////////////////////
	void SetStartInfo(COrganEntity* p_entity, float p_fX, CBaseObject::DIRECTION p_eDirection);

	void SetItemCount(int p_nCount){_itemCount = p_nCount;}
};

#define ObjectMgr CObjectManager::Instance()

#endif