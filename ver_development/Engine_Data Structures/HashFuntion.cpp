#include "../BaseHeader.h"

unsigned long int StringHash(CString p_string){
	unsigned long int hash = 0;
	int i;
	int length = (int)strlen(p_string.m_string);
	for(i = 0; i < length; i++){
		hash += ((i+1) * p_string.m_string[i]);
	}
	return hash;
}