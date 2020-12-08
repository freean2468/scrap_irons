#include "../BaseHeader.h"

IMPLEMENT_DYNCREATE(CView)

// 메시지 맵
BEGIN_MESSAGE_MAP(CView)
	{WM_CREATE,		CView::OnCreate},
	{WM_PAINT,		CView::OnDraw},
	{WM_DESTROY,	CView::OnDestroy},
	{WM_LBUTTONDOWN,CView::OnLButtonDown},
	{WM_LBUTTONUP,	CView::OnLButtonUp},
	{WM_MOUSEMOVE,	CView::OnMouseMove},
	{WM_SIZE,		CView::OnSize},
	{WM_KEYDOWN,	CView::OnKeyDown},
	{WM_KEYUP,		CView::OnKeyUp},
	{WM_MOUSEWHEEL, CView::OnMouseWheel},
	{MM_MCINOTIFY,	CView::OnMciNotify},
END_MESSAGE_MAP()

void CView::OnCreate(WPARAM wParam, LPARAM lParam){
	
}//CView::OnCreate

void CView::OnDraw(WPARAM wParam, LPARAM lParam){
//	CPaintDC dc(this);
//
//	RECT rect;
//
//	GetClientRect(m_hWnd, &rect);
//	dc.DrawText("Sider Engine", -1, &rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
//
////	dc.BitBlt();
}//CView::OnDraw

void CView::OnDestroy(WPARAM wParam, LPARAM lParam){
	PostQuitMessage(0);
}//CView::OnDestroy

void CView::OnLButtonDown(WPARAM wParam, LPARAM lParam){
	EngineMgr->SetLButtonState(-1);

	// 클릭한 스크린 포인트를 이용해 뷰 스페이스 내에 광선을 계산한다.
	d3d::Ray ray = d3d::CalcPickingRay(LOWORD(lParam), HIWORD(lParam));

	// 광선을 월드 스페이스로 변환한다.
	D3DXMATRIX view;
	EngineMgr->GetpDevice()->GetTransform(D3DTS_VIEW, &view);

	D3DXMATRIX viewInverse;
	D3DXMatrixInverse(&viewInverse, 0, &view);

	d3d::TransformRay(&ray, &viewInverse);


	// 맞추었는지를 테스트
//	if(d3d::raySphereIntersectionTest(&ray, &AppMgr->boundingSphere))
//		::MessageBox(AppMgr->m_pMainWnd->GetSafeHwnd(), "Hit!", "HIT", MB_OK);

}//CView::OnCreate

void CView::OnLButtonUp(WPARAM wParam, LPARAM lParam){
	EngineMgr->SetLButtonState(1);
}

// KeyDown 메시지로 입력 받으면 느리기 때문에
// 다른 키체크 함수를 사용하는 것이 좋다.
void CView::OnKeyDown(WPARAM wParam, LPARAM lParam){
	switch(wParam){
		case VK_RETURN:

			break;
		case VK_LEFT:
			
			break;
		case VK_RIGHT:
			
			break;
		case VK_UP:
			
			break;
		case VK_DOWN:
			
			break;
		case 'S':
		case 'W':
		case 'A':
		case 'D':
			
			break;
		case '0':
			break;
		case '1':
			break;
		case '2':
			break;
		case '3':
			break;
		default:
			
			break;
	}
}

void CView::OnKeyUp(WPARAM wParam, LPARAM lParam){
	switch(wParam){
		case VK_ESCAPE:
			//OnDestroy(wParam, lParam);
			break;
		case VK_RETURN:

			break;
		case VK_LEFT:
			
			break;
		case VK_RIGHT:
			
			break;
		case VK_UP:
			
			break;
		case VK_DOWN:
			
			break;
		case 'S':
		case 'W':
		case 'A':
		case 'D':
			CameraMgr->GetCamera()->CallKeyUp();
			break;
		case '0':
			break;
		case '1':
			break;
		case '2':
			break;
		case '3':
			break;
		default:
			
			break;
	}
}

void CView::OnSize(WPARAM wParam, LPARAM lParam){
	
}

void CView::OnMouseMove(WPARAM wParam, LPARAM lParam){
	D3DXVECTOR3 _vTemp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CameraMgr->GetCamera()->GetPosition(&_vTemp);
	// 마우스 상대좌표 전달
	EngineMgr->GetpInformation()->SetAdjustedX((float)(LOWORD(lParam))-(float)(SYSTEMWIDTH/2)+_vTemp.x);
	EngineMgr->GetpInformation()->SetAdjustedY(-((float)(HIWORD(lParam))-(float)(SYSTEMHEIGHT/2))+_vTemp.y);

	// 마우스 절대좌표 전달
	// 중점은 윈도위 좌상단
	EngineMgr->GetpInformation()->SetAbsolutedX((float)(LOWORD(lParam)));
	EngineMgr->GetpInformation()->SetAbsolutedY((float)(HIWORD(lParam)));
}

void CView::OnMouseWheel(WPARAM wParam, LPARAM lParam){
	short tmpDelta;
	tmpDelta = HIWORD(wParam);
	float z;

	switch(tmpDelta){
		case 120:
			z = CameraMgr->GetCamera()->GetZoom();
			z += 10.0f;
			if(z >= -300.0f)
				z = -300.0f;
			CameraMgr->GetCamera()->SetZoom(z);
			break;

		case -120:			
			z = CameraMgr->GetCamera()->GetZoom();
			z -= 10.0f;
			if(z <= -1000.0f)
				z = -1000.0f;
			CameraMgr->GetCamera()->SetZoom(z);
			break;
	}
}	

void CView::OnMciNotify(WPARAM wParam, LPARAM lParam){
	if(LOWORD(lParam) == MusicMgr->GetBGMOpenParam()->wDeviceID){
		switch(wParam){
			case MCI_NOTIFY_SUCCESSFUL:
				mciSendCommand(LOWORD(lParam), MCI_CLOSE, 0, (DWORD)NULL);
				MusicMgr->PlayMP3FileForBGM((char*)MusicMgr->GetBGMOpenParam()->lpstrElementName);
				break;
			/*case MCI_NOTIFY_FAILURE:
			case MCI_NOTIFY_SUPERSEDED:
			case MCI_NOTIFY_ABORTED:
				mciSendCommand(LOWORD(lParam), MCI_CLOSE, 0, (DWORD)NULL);
				break;*/
			default:
				break;
		}
	}
	else{
		mciSendCommand(LOWORD(lParam), MCI_CLOSE, 0, (DWORD)NULL);
		
		CDListIterator<MCI_OPEN_PARMS*> itr;
		CDListIterator<MCI_PLAY_PARMS*> itrPlay;
		
		itr = MusicMgr->GetEffectOpenParam()->GetIterator();
		itrPlay = MusicMgr->GetEffectPlayParam()->GetIterator();

		for(itr.Start(), itrPlay.Start(); itr.Valid(); ){
			if(itr.Item()->wDeviceID == LOWORD(lParam)){
				MusicMgr->GetEffectOpenParam()->Remove(itr);
				MusicMgr->GetEffectPlayParam()->Remove(itrPlay);
				break;
			}
			else{
				itr.Forth();
				itrPlay.Forth();
			}
		}
	}
}