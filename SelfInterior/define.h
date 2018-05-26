#pragma once
enum DRAW_MODE
{
	NONE = -1,		//옮기기
	WALL_MODE,		//벽 생성
	STRUCTURE_MODE,	//구조물(문, 창문 등) 생성
	INTERIOR_MODE	//인테리어(TV, 냉장고 등) 생성
};

enum STRUCTURE
{
	DOOR_STRUCTURE,
	WINODW_STRUCTURE
};

enum INTERIOR
{
	TV_INTERIOR,
	REFRIGERATOR_INTERIOR
};

