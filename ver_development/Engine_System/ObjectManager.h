////////////////////////////////////////////////////////////////////////////////
// 엔진의 오브젝트들을 관리하는 Mgr 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _ObjectManager_H_
#define _ObjectManager_H_

// Get&Set 함수를 큰 분류일 때는 ObjectType만 쓰면 알아서 갖고 오도록 하면 어떨까?
// Entity Type을 나누어서 포인터 배열로 관리하자.

class CObjectManager{
private:
	CDLinkedList<COrganEntity*> _entityList;	// Character를 제외한 모든 Entity DataBase
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
	//     오브젝트 충돌체크          //
	// 일반
	bool ComputeBoundEntity(COrganEntity* p_pE1, COrganEntity* p_pE2);
	// 메뉴끼리
	int ComputeBoundMenu();
	// 마우스와 StagePoint
	float ComputeBoundStagePointAndMouse(CSection* pSection);
	// Stage와 주인공
	void ComputeBoundStageHomeAndHero();
	void ComputeGetOutStage(CBaseObject::OWNER p_eBG, CBody* p_pBody);
	// Item과 주인공
	void ComputeBountItemAndHero(CItem* t_pItem);

	////////////////////////////////////
	// 자료 관리는 DB와 LinkedList 두 개를 사용한다.
	// DB는 로직관련 LinkedList는 범용성을 위함
	CBaseGameEntity* GetEntity(int id){return EntityDB->GetEntityFromID(id);}
	COrganEntity* GetEntity(CBaseObject::Owner p_eOwner);

	////////////////////////////////////
	// _itemList 
	CDLinkedList<CItem* >* GetItemList(){return &_itemList;}
	void CreatItem();
	void CreatBluePrint(); // 설계도는 특별한 아이템
	void UpdateItem();
	void InventoryUpdateAndDeleteItem();

	///////////////////////////////////////////////
	void SetStartInfo(COrganEntity* p_entity, float p_fX, CBaseObject::DIRECTION p_eDirection);

	void SetItemCount(int p_nCount){_itemCount = p_nCount;}
};

#define ObjectMgr CObjectManager::Instance()

#endif