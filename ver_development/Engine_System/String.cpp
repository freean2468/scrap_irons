#include "../BaseHeader.h"

CString::CString(){ 
	strcpy(m_string, "");
}

CString::CString(char* p_string){
	strcpy(m_string, p_string);
}

bool CString::operator==(const CString& p_right){ 
	return !strcmp(m_string, p_right.m_string); 
}