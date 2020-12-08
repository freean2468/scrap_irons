#include "../BaseHeader.h"

// Static 변수 초기화
char CApp::szAppName[] = "Scrap irons";
bool CApp::bScreen = false;

POINTS g_Keyboard;

//constructor
CApp::CApp(){
	Device = 0;  	
}

//destructor
CApp::~CApp(){
	if(m_pMainWnd != NULL){
		delete m_pMainWnd;
		m_pMainWnd = NULL;
	}//if
}//CApp::~CApp()

// EngineMgr 초기화&셋팅
void CApp::InitBaseManager(){
	EngineMgr->SetpDevice(Device);
	EngineMgr->Sethwnd(m_pMainWnd->GetSafeHwnd());

	EngineMgr->Initialize();
}

// DocTemplate를 추가,
// 기본적으로 현재 SiderEngine에서는 Doc을 하나만 사용하고 있다.
void CApp::AddDocTemplate(CRuntimeClass* pRuntimeClass){
	// 전달된 CRuntimeClass를 만들고, 포인터를 대입
	m_pMainWnd = (CWnd*)pRuntimeClass->CreateObject();
	if(m_pMainWnd == NULL) return;

	CREATESTRUCT cs;

	m_pMainWnd->PreCreateWindow(cs);
}//CApp::AddDocTemplate()

// 메인 애플리케이션 윈도우 초기화 & Direct3D 초기화
bool CApp::InitD3D(HINSTANCE hInstance,
				  int width, int height,
				  bool windowed,
				  D3DDEVTYPE deviceType,
				  IDirect3DDevice9** device)
{
	// Create the main application window.
	WNDCLASS wc;

	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= (WNDPROC)WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor			= LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR2));
	wc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName		= 0;
	wc.lpszClassName	= szAppName;

	if(!RegisterClass(&wc)){
		OutputDebugString("RegisterClass() - FAILED");
		return false;
	}

	// FullScreen 여부 설정
	if(IDYES == MessageBox(this->m_pMainWnd->GetSafeHwnd(), "FullScreen?","Scrap Irons",MB_YESNO))
		bScreen = true;
	else
		bScreen = false;

	m_hInstance = hInstance;

	AddDocTemplate(RUNTIME_CLASS(CView));										// 동적으로 메인 윈도우 객체 생성

	// 스크린 모드에 따른 window style 지정
	if(bScreen){
		m_pMainWnd->m_hWnd = ::CreateWindow(
		szAppName,					 //Window class name
		szAppName,					 //Window caption		
		WS_POPUP,					 //window style
		0,							 //initial x position
		0,							 //initial y position
		width,						 //initial x size
		height,						 //initial y size
		0 /*parent hWnd*/,			 //parent window handle
		0 /* menu */,				 //window menu handle
		m_hInstance,				 //program instance handle
		0 /*extra*/);				 //creation parameters
	}
	else{
		m_pMainWnd->m_hWnd = ::CreateWindow(
		szAppName,					 //Window class name
		szAppName,					 //Window caption
		WS_OVERLAPPEDWINDOW,		 //window style
		0,							 //initial x position
		0,							 //initial y position
		width,						 //initial x size
		height,						 //initial y size
		0 /*parent hWnd*/,			 //parent window handle
		0 /* menu */,				 //window menu handle
		m_hInstance,				 //program instance handle
		0 /*extra*/);				 //creation parameters
	}	

	if(!m_pMainWnd->GetSafeHwnd()){
		OutputDebugString("CreateWindow() - FAILED");
		return false;
	}

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// Init D3D

	HRESULT hr = 0;

	// Step 1 : Create the IDirect3D9 object.

	IDirect3D9* d3d9 = 0;
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	if(!d3d9){
		OutputDebugString("Direct3DCreate9() - FAILED");
		return false;
	}

	// Step 2 : Check for hardware vp.

	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);

	// VertexProcessing 하드웨어 지원 여부 확인
	int vp = 0;
	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// Step 3 : Fill out the D3DPRESENT_PARAMETERS structure.
	_d3dpp.BackBufferWidth				= width;
	_d3dpp.BackBufferHeight				= height;
	_d3dpp.BackBufferFormat				= D3DFMT_A8R8G8B8;
	_d3dpp.BackBufferCount				= 1;
	_d3dpp.MultiSampleType				= D3DMULTISAMPLE_NONE;
	_d3dpp.MultiSampleQuality			= 0;
	_d3dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;
	_d3dpp.hDeviceWindow				= m_pMainWnd->GetSafeHwnd();
	_d3dpp.Windowed						= !bScreen;
	_d3dpp.EnableAutoDepthStencil		= true;
	_d3dpp.AutoDepthStencilFormat		= D3DFMT_D24S8;
	_d3dpp.Flags						= 0;
	_d3dpp.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
	_d3dpp.PresentationInterval			= NULL;

	// Step 4 : Create the device.

	hr = d3d9->CreateDevice(
		D3DADAPTER_DEFAULT,			// primary adapter
		deviceType,					// device type
		m_pMainWnd->GetSafeHwnd(),	// window associated with device
		vp,							// vertex processing
		&_d3dpp,						// present parameters
		device);					// return created device

	if(FAILED(hr)){
		// try again using a 16-bit depth buffer
		_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			deviceType,
			m_pMainWnd->GetSafeHwnd(),
			vp,
			&_d3dpp,
			device);

		if(FAILED(hr)){
			d3d9->Release();	// done with d3d9 object
			OutputDebugString("CreateDevice() - FAILED");
			return false;
		}
	}

	d3d9->Release();	// done with d3d9 object

	return true;
}//CApp::InitInstance

// 자원의 할당이나 장치 특성의 확인, 애플리케이션 상태의 설정 등의 사전 준비 함수
bool CApp::Setup(){
	HRESULT hr = 0;

	srand(unsigned int(time(NULL)));

	// Lights.
	//D3DXVECTOR3 lightDir(0.707f, /*-0.707f*/0.0f, 0.707f);
	//D3DXCOLOR color(1.0f, 1.0f, 1.0f, 1.0f);
	//D3DLIGHT9 light = d3d::InitDirectionalLight(&lightDir, &color);

	D3DLIGHT9 dir;
	::ZeroMemory(&dir, sizeof(dir));
	dir.Type      = D3DLIGHT_DIRECTIONAL;
	dir.Diffuse   = d3d::WHITE;
	dir.Specular  = d3d::WHITE * 0.0f;
	dir.Ambient   = d3d::WHITE * 0.6f;
	dir.Direction = D3DXVECTOR3(0.0f, 0.0f, 0.1f);

	EngineMgr->GetpDevice()->SetLight(0, &dir);
	EngineMgr->GetpDevice()->LightEnable(0, true);

	dir.Direction = D3DXVECTOR3(0.0f, 0.0f, -0.1f);

	EngineMgr->GetpDevice()->SetLight(1, &dir);
	EngineMgr->GetpDevice()->LightEnable(1, true);

	EngineMgr->GetpDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	EngineMgr->GetpDevice()->SetRenderState(D3DRS_SPECULARENABLE, true);

	return true;
}

// Setup 함수에서 할당된 자원을 해제
void CApp::Cleanup(){
	// EngineMgr 클래스 소멸자에서 해제
}

// PreRendering(프리렌더링)
void CApp::PreRendering(void){
	EngineMgr->GetpDevice()->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,	0xffffffff, 1.0f, 0);

	// 그리기를 시작한다.
	EngineMgr->GetpDevice()->BeginScene();

	EngineMgr->GetpDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	EngineMgr->GetpDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	EngineMgr->GetpDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
}

// Rendiring(렌더링)
void CApp::Rendering(float fTimeDelta){
	// Section State에 따라서 Update내용이 달라진다.
	// 카메라 계산
	if(StageMgr->GetStage()){
		CameraMgr->GetCamera()->GetPosition(EngineMgr->GetpInformation()->GetCameraPos());
		CameraMgr->CameraMode();
		CameraMgr->LimitDestination();
		CameraMgr->FaceToDestination();
		CameraMgr->GetCamera()->Zoom();
	}

	SectionMgr->GetSection()->Update();		

	MouseMgr->CursorUpdate();

	// 연기된 메시지 dispatch
	Dispatch->DispatchDelayedMessages();

	// 정보 그리기
	//EngineMgr->GetpInformation()->DrawInformation(EngineMgr->GetpFont(), EngineMgr->GetpSprite());
}

// Post Rendering(포스트 렌더링)
HRESULT CApp::PostRendering(void){
	// 그리기가 끝났음을 알린다.
	EngineMgr->GetpDevice()->EndScene();

	// 그려진 Scene을 백버퍼로 전송한다.(실제로 이부분에서 화면에 그려진다.)
	return EngineMgr->GetpDevice()->Present(NULL, NULL, NULL, NULL);
}

// 프리리셋
void CApp::PreReset(void){

}

// 디바이스 복귀
// 안에서 루프만 돈다.
HRESULT CApp::RestoreDevice(void){
	HRESULT Result = Device->TestCooperativeLevel();
	while(Result == D3DERR_DEVICELOST){
		while(Result != D3DERR_DEVICENOTRESET){
			MSG msg;
			Sleep(1000);	// 1초간 대기
			// 1초간 정지했을 때를 위해 메시지 펌프루틴을 넣는다.
			PeekMessage(&msg, 0, 0, 0, PM_REMOVE);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			Result = Device->TestCooperativeLevel();	// 상태를 다시 조사한다
		}
		if(FAILED(Device->Reset(&_d3dpp))) Result = D3DERR_DEVICELOST;
	}
	return S_OK;
}

// 포스트 리셋
void CApp::PostReset(void){

}

// 모든 드로잉 코드를 구현, 매 프레임마다 일어나야 하는 작업을 수행
// 여기서 파라미터 timeDelta는 조정되지 않은 original timeDelta다
// timeDelta 인자는 각 프레임의 경과 시간, 초당 프레임과의 애니메이션 동기화에 이용
bool CApp::Display(float timeDelta){
	if( EngineMgr->GetpDevice() ){		
		d3d::SetupMatrices();

#ifndef _Debug
		// 각종 정보 계산은 원래 프레임 간의 timeDelta를 사용한다
		// Original Frame을 계산하기 위함
		EngineMgr->GetpInformation()->CalcInformation(EngineMgr->GetpSystemFrame()->GetTimeDeltaOfOrigin());
#endif		
		if(!EngineMgr->GetpSystemFrame()->IsFrameSkip()){
			EngineMgr->GetpSystemFrame()->CalculationAdjustedTimeDelta();

			// Draw the scene:
			PreRendering();		

			Rendering(timeDelta);

			HRESULT hr;

			// end the scene
			// 디바이스를 잃었을 때를 대비한다.
			hr = PostRendering();
			if(hr == D3DERR_DEVICELOST){
				PreReset();
				RestoreDevice();
				PostReset();
			}
			else if(hr == D3DERR_DEVICENOTRESET){
				Device->Reset(&_d3dpp);
			}

			EngineMgr->SetLButtonState(0);
		}
		else if(!EngineMgr->GetpSystemFrame()->IsFrameSkip() || EngineMgr->GetpInformation()->GetFPSofOrgin() < EngineMgr->GetpSystemFrame()->GetLimitFPS()){
			EngineMgr->GetpSystemFrame()->CalculationAdjustedTimeDelta();

			// Draw the scene:
			PreRendering();		

			Rendering(timeDelta);

			// end the scene
			// 디바이스를 잃었을 때를 대비한다.
			if(PostRendering() == D3DERR_DEVICELOST){
				PreReset();
				RestoreDevice();
				PostReset();
			}

			EngineMgr->SetLButtonState(0);
		}
	}
	return true;
}

// 애플리케이션의 메시지 루프를 포장
int CApp::EnterMsgLoop(){
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));
	// Idle time 루틴 설정
	int bFlag = TRUE;

	while(msg.message != WM_QUIT){
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			bFlag = TRUE;
		}
		if(bFlag){
			// 프레임 간의 소요 시간을 계산
			EngineMgr->GetpSystemFrame()->CalculationTimeDeltaOfOrigin();

			if(EngineMgr->GetpSystemFrame()->Update(EngineMgr->GetTimeDelta())){
				AppMgr->Display(EngineMgr->GetTimeDelta());	// 어플리케이션 디스플레이 함수를 호출한다.
			}

			bFlag = false;
		}
	}
	return (int)msg.wParam;
}

WPARAM CApp::ExitInstance(){
	return 0L;	// msg.wParam;
}//CApp::ExitInstance

//Window procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam){
	static CViewFunPointer fpCViewGlobal = NULL;	// pointer to a member function

	int	i = 0;
	CView* p;

	// 메시지 맵에서 해당하는 메시지를 뽑아온다.
	while(CView::messageMap[i].iMsg != 0){
		if(iMsg == CView::messageMap[i].iMsg){
			fpCViewGlobal = CView::messageMap[i].fp;
			p = static_cast<CView*>(AppMgr->m_pMainWnd);
			(p->*fpCViewGlobal)(wParam, lParam);

			return 0;
		}//if
		++i;
	}//while
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}//WndProc()

// Global Main 함수
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow){
	// 메인 디스플레이 윈도우와 Direct3D 초기화
	if(!AppMgr->InitD3D(hInstance, SYSTEMWIDTH, SYSTEMHEIGHT, true, D3DDEVTYPE_HAL, AppMgr->GetppDevice())){
		OutputDebugString("InitD3D() - FAILED");
		return 0;
	}

	// BaseManager 랩 수행
	AppMgr->InitBaseManager();

	// 어플리케이션 사전 준비 수행
	if(!AppMgr->Setup()){
		OutputDebugString("Setup() - FAILED");
		return 0;
	}

	// 메시지 루프 진입
	AppMgr->EnterMsgLoop();

	// 애플리케이션 정리
	AppMgr->Cleanup();

	// IDirect3DDevice9 객체 해제
	AppMgr->GetpDevice()->Release();

	return (int)AppMgr->ExitInstance();
}//WimMain()