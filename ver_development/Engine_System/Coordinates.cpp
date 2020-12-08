#include "../BaseHeader.h"

CCoordinates::CCoordinates(){
	x = 0.0f;
	y = 0.0f;
}

CCoordinates::~CCoordinates(){

}

CCoordinates& CCoordinates::operator =(float p_ftemp){
	this->x=p_ftemp;
	this->y=p_ftemp;

	return *(this);
}