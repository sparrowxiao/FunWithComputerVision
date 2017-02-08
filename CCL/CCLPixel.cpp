/************************************************************************
 *	File name	: CCLPixel.cpp
 *	Program name: CCL
 *	Abstract	: Computer Vison
 *	Author		:
 *	Modify record	:
 *	Date		Belong	Charge		Manage No.		Remarks
 *	-------------------------------------------------------------------
 *   2013/02/06		UGA		ting		-			create
 *   2013/02/18		UGA		ting		001		add new feature to implement distance transformation
 *	Remarks			:
 *
 
 ************************************************************************/

#include "CCLPixel.h"

CCLPixel::CCLPixel()
{
    x = 0;
    y = 0;
    color = 0x00;
    label = 0;
    value_f = 0;
    convolution_f=0.0;
    edge=0;//not the edge
    

}
void CCLPixel::setPosition(int ix, int iy)
{
    x= ix;
    y= iy;
}
void CCLPixel::setColor(uint8_t icolor)
{
    color = icolor;
}

uint8_t CCLPixel::getColor()
{
    return color;
}
void CCLPixel::setLable(int ilable)
{
    label = ilable;
}

void CCLPixel::setEquivalenceSet(int ilabel)
{
    equivalenceSet.insert(ilabel);

}


int CCLPixel::getLable()
{
    return label;
}

int CCLPixel::getX()
{
    return x;
}

int CCLPixel::getY()
{
    return y;
}

set<int> CCLPixel::getEquivalenceSet()
{
    return equivalenceSet;
}

void CCLPixel::setDistance(int ivalue_f)//#001 add
{
    value_f=ivalue_f;
}

int CCLPixel::getDistance()//#001 add
{
    return value_f;
}

float CCLPixel::getConvolution()//#001 add
{
    return convolution_f;
}
void CCLPixel::setConvolution(float convolution_result)//#001 add
{
    convolution_f=convolution_result;
}

int CCLPixel::getEdge()//#001 add
{
    return edge;
}
void CCLPixel::setEdge(int edge_value)//#001 add
{
    edge=edge_value;
}