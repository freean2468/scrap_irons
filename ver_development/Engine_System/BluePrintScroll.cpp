#include "../BaseHeader.h"

CBluePrintScroll::CBluePrintScroll(CBluePrint::BluePrintType p_eType, char* p_pType, int p_nIndex):COrganEntity(ID_BLUEPRINTSCROLL){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CBluePrintScroll>(this);

	_index = p_nIndex;
	strcpy(_type, p_pType);
	_deltaY = -(p_nIndex * 65.0f) + 90.0f;

	switch(p_eType){
		case CBluePrint::WAGOO:
			LoadEntityData("./script/UserInterface/BluePrintScroll/WagooWagoo.txt", this);

			_IngredientList.Append(new CItem(CItem::BULB));    _IngredientCount.Append(2);
			_IngredientList.Append(new CItem(CItem::PLYWOOD)); _IngredientCount.Append(5);
			_IngredientList.Append(new CItem(CItem::TIRE));    _IngredientCount.Append(4);
			_IngredientList.Append(new CItem(CItem::REBAR));   _IngredientCount.Append(1);
			_materialCount = 4;
			_eType = CBluePrint::WAGOO;
			break;
		case CBluePrint::WOOWO:
			LoadEntityData("./script/UserInterface/BluePrintScroll/WoowoWoowo.txt", this);

			_IngredientList.Append(new CItem(CItem::PLYWOOD)); _IngredientCount.Append(6);
			_IngredientList.Append(new CItem(CItem::WIRE));   _IngredientCount.Append(2);
			_materialCount = 2;
			_eType = CBluePrint::WOOWO;
			break;
		case CBluePrint::YAWO:
			LoadEntityData("./script/UserInterface/BluePrintScroll/YawoYawo.txt", this);

			_IngredientList.Append(new CItem(CItem::REBAR));   _IngredientCount.Append(3);
			_IngredientList.Append(new CItem(CItem::WIRE));   _IngredientCount.Append(5);
			_materialCount = 2;
			_eType = CBluePrint::YAWO;
			break;
		case CBluePrint::KIRIT:
			LoadEntityData("./script/UserInterface/BluePrintScroll/KiritKirit.txt", this);

			_IngredientList.Append(new CItem(CItem::TIRE));    _IngredientCount.Append(8);
			_materialCount = 1;
			_eType = CBluePrint::KIRIT;
			break;
		case CBluePrint::TINKLE:
			LoadEntityData("./script/UserInterface/BluePrintScroll/TinkleTInkle.txt", this);

			_IngredientList.Append(new CItem(CItem::BULB));    _IngredientCount.Append(6);
			_IngredientList.Append(new CItem(CItem::REBAR));    _IngredientCount.Append(3);
			_materialCount = 2;
			_eType = CBluePrint::TINKLE;
			break;
		default:
			break;
	}

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(BluePrintScrollMinimize->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_pFont = d3d::IniFont(18, 9, 700, false, "맑은 고딕");
}

CBluePrintScroll::~CBluePrintScroll(){
	d3d::Delete< CStateMachine<CBluePrintScroll >* >(m_pStateMachine);

	CDListIterator<CItem*> t_itemItr;
	t_itemItr = _IngredientList.GetIterator();

	// _itemList를 훑으며
	for(t_itemItr.Start(); t_itemItr.Valid();){
		_IngredientList.Remove(t_itemItr);
	}
}

int CBluePrintScroll::GetOurForceTypeID(){
	switch(_eType){
		case CBluePrint::WAGOO:
			return ID_WAGOO;
		case CBluePrint::WOOWO:
			return ID_WOOWO;
		case CBluePrint::YAWO:
			return ID_YAWO;
		case CBluePrint::KIRIT:
			return ID_KIRIT;
		case CBluePrint::TINKLE:
			return ID_TINKLE;
		default:
			return false;
	}
}
