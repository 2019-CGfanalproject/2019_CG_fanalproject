#pragma once

// 프로그램 진입
// 타이틀
// 플레이
// 엔딩


// 씬 흐름도
//					
// 진입 -> 타이틀 -> 플레이 -> 엔딩 -> 타이틀

class CScene
{
public:
	CScene();
	~CScene();

	virtual void draw();

	virtual void update();

};

