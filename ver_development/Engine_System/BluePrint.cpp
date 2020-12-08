#include "../BaseHeader.h"

CBluePrint::CBluePrint(BLUEPRINTTYPE p_eBluePrintType):CItem(ID_ITEM){
	// ���±�踦 �����Ѵ�.
	SetFSM(new CStateMachine<CItem>(this));

	LoadEntityData("./script/Item/BluePrint.txt", this);
	SetItemType(BLUEPRINT);

	switch(p_eBluePrintType){
		case WAGOO:			
			_eBluePrintType = WAGOO;
			break;
		case WOOWO:			
			_eBluePrintType = WOOWO;
			break;
		case YAWO:
			_eBluePrintType = YAWO;
			break;
		case KIRIT:
			_eBluePrintType = KIRIT;
			break;
		case TINKLE:
			_eBluePrintType = TINKLE;
			break;
		default:
			break;
	}

	// ó�� ���¸� �ʱ�ȭ
	GetFSM()->SetCurrentState(ItemUsual->Instance());

	GetFSM()->CurrentState()->Enter(this);

	GetFSM()->SetGlobalState(NULL);
}

CBluePrint::~CBluePrint(){

}