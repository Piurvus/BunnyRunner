#include "Carrot.h"

D2D_RECT_F Carrot::returnPos()
{
	/*float right = rect.right;
	rect.right = right + width;
	float top = rect.top;
	rect.top = top + height;
	*/

	
	/*float top = rect.bottom;
	rect.bottom = rect.top;
	rect.top = top;
	*/

	return rect;
}

void Carrot::show()
{
	sprite->Draw(rect.left, rect.bottom, size);
}


