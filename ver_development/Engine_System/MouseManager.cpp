#include "../BaseHeader.h"

CMouseManager::CMouseManager(){
	_cursor = new CBody(0);

	_cursor->InitObject(EngineMgr->GetpDevice(), "./Image/Cursor/Cursor.dds", 40, 40, 1.0f, 0);
	_useCursor = false;
}

CMouseManager::~CMouseManager(){
	
}

void CMouseManager::CursorUpdate(){
	D3DXVECTOR3 t_vPos(0.0f, 0.0f, 0.0f);

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	_cursor->GetPriPos()->x = t_vPos.x + (EngineMgr->GetpInformation()->GetAbsolutedX() - SYSTEMWIDTH/2) + 10.0f;
	_cursor->GetPriPos()->y = t_vPos.y - (EngineMgr->GetpInformation()->GetAbsolutedY() - SYSTEMHEIGHT/2) - _cursor->GetHeightHalf();
	_cursor->GetPriPos()->z = 700 + t_vPos.z;

	if(_useCursor) _cursor->Render(&D3DXVECTOR3(_cursor->GetPriPos()->x, _cursor->GetPriPos()->y, _cursor->GetPriPos()->z),&D3DXVECTOR3(1.0f, 1.0f, 1.0f),&D3DXVECTOR3(0.0f, 0.0f, 0.0f),&D3DXVECTOR3(0.0f, 0.0f, 0.0f));	
}