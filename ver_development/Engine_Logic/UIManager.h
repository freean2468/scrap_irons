////////////////////////////////////////////////////
// UserInterface와 관련된 정보를 담당 관리 클래스
////////////////////////////////////////////////////
#ifndef _UIManager_H_
#define _UIManager_H_

class CUIManager{
private:
	CDLinkedList<COrganEntity*> _UIList;	// Entity DataBase
	CInventory* _inventory;	// 인벤토리 클래스
	CBluePrintList* _bluePrintList; // 설계도 목록 클래스

	CDLinkedList<CSmallInfo*> _smallInfoList;

	// 리더쉽 
	CCommander* _commander;

	ID3DXFont*	_pFont;							// 폰트 인터페이스 변수

private:
	CUIManager();
	CUIManager(const CUIManager&);
	CUIManager& operator =(const CUIManager&);

public:
	~CUIManager();
	static CUIManager* Instance(){
		static CUIManager instance;

		return &instance;
	}

	// UI 업데이트
	void UIUpdate();

	// Production 메뉴 활성화
	bool ActivateProduction();

	// Interact 표시
	void ActivateInteract(float p_fX, float p_fY);

	// Inventory 기능 지원
	void PutItemInInventory(CItem* p_pItem);
	
	// BluePrintList 기능 지원
	void GetAndActivatedBluePrint(CBluePrint* p_pBluePrint);
	
	// Commander
	void ActiveCommander();
	void MinimizeCommander();

	// SmallInfo
	void SmallInfoUpdate();

	// UI 충돌체크 //
	// 마우스와 Production CloseButton
	bool ComputeBoundProductionCloseAndMouse();
	// 마우스와 BluePrintScroll Up Down
	void ComputeBoundBluePirntScrollUpDown();

	CBaseGameEntity* GetUI(int id){return EntityDB->GetEntityFromID(id);}
	COrganEntity* GetUI(CBaseObject::Owner p_eOwner);
	CCommander* GetCommander(){return _commander;}

	CInventory* GetInventory(){return _inventory;}
	CBluePrintList* GetBluePrintList(){return _bluePrintList;}

	CDLinkedList<CSmallInfo*>* GetSmallInfoList(){return &_smallInfoList;}
};

#define UIMgr CUIManager::Instance()

#endif