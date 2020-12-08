#include "../BaseHeader.h"

// Static ���� �ʱ�ȭ
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

// EngineMgr �ʱ�ȭ&����
void CApp::InitBaseManager(){
	EngineMgr->SetpDevice(Device);
	EngineMgr->Sethwnd(m_pMainWnd->GetSafeHwnd());

	EngineMgr->Initialize();
}

// DocTemplate�� �߰�,
// �⺻������ ���� SiderEngine������ Doc�� �ϳ��� ����ϰ� �ִ�.
void CApp::AddDocTemplate(CRuntimeClass* pRuntimeClass){
	// ���޵� CRuntimeClass�� �����, �����͸� ����
	m_pMainWnd = (CWnd*)pRuntimeClass->CreateObject();
	if(m_pMainWnd == NULL) return;

	CREATESTRUCT cs;

	m_pMainWnd->PreCreateWindow(cs);
}//CApp::AddDocTemplate()

// ���� ���ø����̼� ������ �ʱ�ȭ & Direct3D �ʱ�ȭ
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

	// FullScreen ���� ����
	if(IDYES == MessageBox(this->m_pMainWnd->GetSafeHwnd(), "FullScreen?","Scrap Irons",MB_YESNO))
		bScreen = true;
	else
		bScreen = false;

	m_hInstance = hInstance;

	AddDocTemplate(RUNTIME_CLASS(CView));										// �������� ���� ������ ��ü ����

	// ��ũ�� ��忡 ���� window style ����
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

	// VertexProcessing �ϵ���� ���� ���� Ȯ��
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

// �ڿ��� �Ҵ��̳� ��ġ Ư���� Ȯ��, ���ø����̼� ������ ���� ���� ���� �غ� �Լ�
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

// Setup �Լ����� �Ҵ�� �ڿ��� ����
void CApp::Cleanup(){
	// EngineMgr Ŭ���� �Ҹ��ڿ��� ����
}

// PreRendering(����������)
void CApp::PreRendering(void){
	EngineMgr->GetpDevice()->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,	0xffffffff, 1.0f, 0);

	// �׸��⸦ �����Ѵ�.
	EngineMgr->GetpDevice()->BeginScene();

	EngineMgr->GetpDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	EngineMgr->GetpDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	EngineMgr->GetpDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
}

// Rendiring(������)
void CApp::Rendering(float fTimeDelta){
	// Section State�� ���� Update������ �޶�����.
	// ī�޶� ���
	if(StageMgr->GetStage()){
		CameraMgr->GetCamera()->GetPosition(EngineMgr->GetpInformation()->GetCameraPos());
		CameraMgr->CameraMode();
		CameraMgr->LimitDestination();
		CameraMgr->FaceToDestination();
		CameraMgr->GetCamera()->Zoom();
	}

	SectionMgr->GetSection()->Update();		

	MouseMgr->CursorUpdate();

	// ����� �޽��� dispatch
	Dispatch->DispatchDelayedMessages();

	// ���� �׸���
	//EngineMgr->GetpInformation()->DrawInformation(EngineMgr->GetpFont(), EngineMgr->GetpSprite());
}

// Post Rendering(����Ʈ ������)
HRESULT CApp::PostRendering(void){
	// �׸��Ⱑ �������� �˸���.
	EngineMgr->GetpDevice()->EndScene();

	// �׷��� Scene�� ����۷� �����Ѵ�.(������ �̺κп��� ȭ�鿡 �׷�����.)
	return EngineMgr->GetpDevice()->Present(NULL, NULL, NULL, NULL);
}

// ��������
void CApp::PreReset(void){

}

// ����̽� ����
// �ȿ��� ������ ����.
HRESULT CApp::RestoreDevice(void){
	HRESULT Result = Device->TestCooperativeLevel();
	while(Result == D3DERR_DEVICELOST){
		while(Result != D3DERR_DEVICENOTRESET){
			MSG msg;
			Sleep(1000);	// 1�ʰ� ���
			// 1�ʰ� �������� ���� ���� �޽��� ������ƾ�� �ִ´�.
			PeekMessage(&msg, 0, 0, 0, PM_REMOVE);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			Result = Device->TestCooperativeLevel();	// ���¸� �ٽ� �����Ѵ�
		}
		if(FAILED(Device->Reset(&_d3dpp))) Result = D3DERR_DEVICELOST;
	}
	return S_OK;
}

// ����Ʈ ����
void CApp::PostReset(void){

}

// ��� ����� �ڵ带 ����, �� �����Ӹ��� �Ͼ�� �ϴ� �۾��� ����
// ���⼭ �Ķ���� timeDelta�� �������� ���� original timeDelta��
// timeDelta ���ڴ� �� �������� ��� �ð�, �ʴ� �����Ӱ��� �ִϸ��̼� ����ȭ�� �̿�
bool CApp::Display(float timeDelta){
	if( EngineMgr->GetpDevice() ){		
		d3d::SetupMatrices();

#ifndef _Debug
		// ���� ���� ����� ���� ������ ���� timeDelta�� ����Ѵ�
		// Original Frame�� ����ϱ� ����
		EngineMgr->GetpInformation()->CalcInformation(EngineMgr->GetpSystemFrame()->GetTimeDeltaOfOrigin());
#endif		
		if(!EngineMgr->GetpSystemFrame()->IsFrameSkip()){
			EngineMgr->GetpSystemFrame()->CalculationAdjustedTimeDelta();

			// Draw the scene:
			PreRendering();		

			Rendering(timeDelta);

			HRESULT hr;

			// end the scene
			// ����̽��� �Ҿ��� ���� ����Ѵ�.
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
			// ����̽��� �Ҿ��� ���� ����Ѵ�.
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

// ���ø����̼��� �޽��� ������ ����
int CApp::EnterMsgLoop(){
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));
	// Idle time ��ƾ ����
	int bFlag = TRUE;

	while(msg.message != WM_QUIT){
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			bFlag = TRUE;
		}
		if(bFlag){
			// ������ ���� �ҿ� �ð��� ���
			EngineMgr->GetpSystemFrame()->CalculationTimeDeltaOfOrigin();

			if(EngineMgr->GetpSystemFrame()->Update(EngineMgr->GetTimeDelta())){
				AppMgr->Display(EngineMgr->GetTimeDelta());	// ���ø����̼� ���÷��� �Լ��� ȣ���Ѵ�.
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

	// �޽��� �ʿ��� �ش��ϴ� �޽����� �̾ƿ´�.
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

// Global Main �Լ�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow){
	// ���� ���÷��� ������� Direct3D �ʱ�ȭ
	if(!AppMgr->InitD3D(hInstance, SYSTEMWIDTH, SYSTEMHEIGHT, true, D3DDEVTYPE_HAL, AppMgr->GetppDevice())){
		OutputDebugString("InitD3D() - FAILED");
		return 0;
	}

	// BaseManager �� ����
	AppMgr->InitBaseManager();

	// ���ø����̼� ���� �غ� ����
	if(!AppMgr->Setup()){
		OutputDebugString("Setup() - FAILED");
		return 0;
	}

	// �޽��� ���� ����
	AppMgr->EnterMsgLoop();

	// ���ø����̼� ����
	AppMgr->Cleanup();

	// IDirect3DDevice9 ��ü ����
	AppMgr->GetpDevice()->Release();

	return (int)AppMgr->ExitInstance();
}//WimMain()