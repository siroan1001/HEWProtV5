#pragma once

#ifndef _____SCENE_BACE_H____
#define _____SCENE_BACE_H____

class SceneBace
{
public:
	SceneBace() {};
	virtual ~SceneBace() {};
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

#endif // !_____SCENE_BACE_H____
