//#pragma once
#ifndef _____LAYER_H____
#define _____LAYER_H____

class Layer
{
public:
	Layer();
	virtual ~Layer();
	virtual void Update();
	virtual void Draw();

	virtual void Reset() = 0;

private:


};

#endif // !
