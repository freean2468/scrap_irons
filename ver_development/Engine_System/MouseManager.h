////////////////////////////////////////////////////
// Mouse ��� ���� Ŭ����
////////////////////////////////////////////////////
#ifndef _MouseManager_H_
#define _MouseManager_H_

class CMouseManager{
private:
	CBody* _cursor;

	bool _useCursor;

private:
	CMouseManager();
	CMouseManager(const CMouseManager&);
	CMouseManager& operator =(const CMouseManager&);

public:
	~CMouseManager();
	static CMouseManager* Instance(){
		static CMouseManager instance;

		return &instance;
	}

	// Cursor ������Ʈ
	void CursorUpdate();

	void SetUseCursor(bool p_bool){_useCursor = p_bool;}
};

#define MouseMgr CMouseManager::Instance()

#endif