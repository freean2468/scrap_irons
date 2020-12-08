////////////////////////////////////////////////////
// UserInterface�� ���õ� ������ ��� ���� Ŭ����
////////////////////////////////////////////////////
#ifndef _UIManager_H_
#define _UIManager_H_

class CUIManager{
private:
	CDLinkedList<COrganEntity*> _UIList;	// Entity DataBase
	CInventory* _inventory;	// �κ��丮 Ŭ����
	CBluePrintList* _bluePrintList; // ���赵 ��� Ŭ����

	CDLinkedList<CSmallInfo*> _smallInfoList;

	// ������ 
	CCommander* _commander;

	ID3DXFont*	_pFont;							// ��Ʈ �������̽� ����

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

	// UI ������Ʈ
	void UIUpdate();

	// Production �޴� Ȱ��ȭ
	bool ActivateProduction();

	// Interact ǥ��
	void ActivateInteract(float p_fX, float p_fY);

	// Inventory ��� ����
	void PutItemInInventory(CItem* p_pItem);
	
	// BluePrintList ��� ����
	void GetAndActivatedBluePrint(CBluePrint* p_pBluePrint);
	
	// Commander
	void ActiveCommander();
	void MinimizeCommander();

	// SmallInfo
	void SmallInfoUpdate();

	// UI �浹üũ //
	// ���콺�� Production CloseButton
	bool ComputeBoundProductionCloseAndMouse();
	// ���콺�� BluePrintScroll Up Down
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