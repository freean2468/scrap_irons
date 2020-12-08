/*
CApp�� �������α׷��� �ʱ�ȭ, ��ť��Ʈ�� ���� ���� ���� ����Ѵ�.
���� ������ �ڵ�� ���� �����츦 �����ϴ� AddDocTemplate()�Լ��� �ִ�
�� Ŭ������ �Ϸ��� ���ø����̼��� ��ƾ�� ����Ѵ�.
*/
#ifndef _App_H_
#define _App_H_

// class CApp
// ���� ��ü
class CApp : public CObject{
private:
	// ���� ��ü ������ ���ؼ�
	// �����ڿ� �Ҹ��ڸ� �����ϰ� �Ҵ��� private�̾�� �Ѵ�.
	CApp(const CApp&);
	CApp& operator=(const CApp&);

	static bool bScreen;
protected:
	static char szAppName[];
	HINSTANCE m_hInstance;

	IDirect3DDevice9* Device;  
	D3DPRESENT_PARAMETERS _d3dpp;
public:
	CWnd*		m_pMainWnd;				// ���� ���α׷��� ���� ������ ��ü�� ����Ų��.

public:
	CApp();
	virtual ~CApp();	

	static CApp* Instance(){
		static CApp instance;

		return &instance;
	}

	WPARAM ExitInstance();
	void AddDocTemplate(CRuntimeClass* pRuntimeClass);	// CRuntimeClass ����ü�� �����͸� �����Ƿ�, ���޵Ǵ� ��� ��ü�� ���� ������ �����ϴ�.
	
	bool InitD3D(
		HINSTANCE hInstance,			// [�Է�] ���ø����̼� �ν��Ͻ�
		int width, int height,			// [�Է�] �ĸ� ���� ũ��
		bool windowed,					// [�Է�] ������ (true) Ȥ�� ��ü ȭ�� (false)
		D3DDEVTYPE deviceType,			// [�Է�] HAL Ȥ�� REF
		IDirect3DDevice9** device);		// [���] ������� ��ġ
	int EnterMsgLoop();	

	void InitBaseManager();

	void PreRendering(void);
	void Rendering(float fTimeDelta);
	HRESULT PostRendering(void);
	bool Setup();
	void Cleanup();
	bool Display(float timeDelta);
	void PreReset(void);
	HRESULT RestoreDevice(void);
	void PostReset(void);

	HINSTANCE* GetInstance(){return &m_hInstance;}

	//virtual function
	virtual IDirect3DDevice9*	GetpDevice(){return Device;}	
	virtual IDirect3DDevice9**	GetppDevice(){return &Device;}
	virtual CWnd* GetpWnd(){return m_pMainWnd;}
};//class CApp

// Main�Լ��� Wndproc�� �����Լ��� ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

#define AppMgr CApp::Instance()

#endif