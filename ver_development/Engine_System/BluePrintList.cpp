#include "../BaseHeader.h"

CBluePrintList::CBluePrintList(int id):COrganEntity(id){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CBluePrintList>(this);

	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
	LoadEntityData("./script/UserInterface/BluePrintList/BluePrintList.txt", this);

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(BluePrintListMinimize->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_pFont = d3d::IniFont(18, 9, 300, false, "���� ���");

	_index = 2;
	_count = 0;
	_completeCollection = false;
	_selectionList = false;
	_overap = false;

	CAttachment* t_pUp = GetAttachmentFromType(CBluePrintList::UP);
	CAttachment* t_pDown = GetAttachmentFromType(CBluePrintList::DOWN);

	t_pUp->GetMtrlArray()->Get(t_pUp->GetRow(), t_pUp->GetCol()).Diffuse.b = -1.0f;
	t_pUp->GetMtrlArray()->Get(t_pUp->GetRow(), t_pUp->GetCol()).Diffuse.r = -1.0f;
	t_pUp->GetMtrlArray()->Get(t_pUp->GetRow(), t_pUp->GetCol()).Diffuse.g = -1.0f;

	t_pDown->GetMtrlArray()->Get(t_pDown->GetRow(), t_pDown->GetCol()).Diffuse.b = -1.0f;
	t_pDown->GetMtrlArray()->Get(t_pDown->GetRow(), t_pDown->GetCol()).Diffuse.r = -1.0f;
	t_pDown->GetMtrlArray()->Get(t_pDown->GetRow(), t_pDown->GetCol()).Diffuse.g = -1.0f;
}

CBluePrintList::~CBluePrintList(){
	d3d::Delete< CStateMachine<CBluePrintList >* >(m_pStateMachine);

	CDListIterator<CBluePrintScroll*> t_itemItr;
	t_itemItr = _scrollList.GetIterator();

	// _itemList�� ������
	for(t_itemItr.Start(); t_itemItr.Valid();){
		_scrollList.Remove(t_itemItr);
	}
}

bool CBluePrintList::InsertNewScroll(CBluePrint* p_pBluePrint){
	switch(p_pBluePrint->GetBluePrintType()){
		case CBluePrint::WAGOO:
			_scrollList.Append(new CBluePrintScroll(CBluePrint::WAGOO, "WagooWagoo Iron", _count++));
			return true;
		case CBluePrint::WOOWO:
			_scrollList.Append(new CBluePrintScroll(CBluePrint::WOOWO, "WoowoWoowo Iron", _count++));
			return true;
		case CBluePrint::YAWO:
			_scrollList.Append(new CBluePrintScroll(CBluePrint::YAWO, "YawoYawo Iron", _count++));
			return true;
		case CBluePrint::KIRIT:
			_scrollList.Append(new CBluePrintScroll(CBluePrint::KIRIT, "KiritKirit Iron", _count++));
			return true;
		case CBluePrint::TINKLE:
			_scrollList.Append(new CBluePrintScroll(CBluePrint::TINKLE, "TinkleTinkle Iron", _count++));
			return true;
		default:
			return false;
	}
}