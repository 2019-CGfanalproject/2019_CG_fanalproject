#pragma once

// 플레이어
// 고정 장애물
// 이동 장애물
// 고정이랑 이동 장애물 다른 클래스로 만들어야 하나?
// 플래그
// 지형
// 바닥 높낮이 있나? 장애물이랑 지형 충돌체크 할 일이 있나..?

class CGameObject
{
public:
	CGameObject();
	~CGameObject();

	virtual void draw();

	virtual void update();
};

