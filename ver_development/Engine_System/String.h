////////////////////////////////////////////////////////////
// STL �� CString �䳻 �Լ�
////////////////////////////////////////////////////////////
#ifndef _String_H_
#define _String_H_

class CString{
public:
	char m_string[128];
	CString();
	CString(char* p_string);
	bool operator==(const CString& p_right);
};

#endif