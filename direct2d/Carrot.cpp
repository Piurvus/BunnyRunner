#include "Carrot.h"

D2D_RECT_F Carrot::returnPos()
{
	return rect;
}

void Carrot::show()
{
	sprite->Draw(rect.left-20, rect.top, size);
}


