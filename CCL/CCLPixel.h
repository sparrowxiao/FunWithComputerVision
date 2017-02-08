/************************************************************************
 *	File name	: CCLPixel.h
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

#ifndef __CCL__CCLPixel__
#define __CCL__CCLPixel__

#include <iostream>
#include <set>

using namespace std;

#endif /* defined(__CCL__CCLPixel__) */
class CCLPixel
{
    public:
    CCLPixel();
    void setPosition(int ix, int iy);
    void setColor(uint8_t icolor);
    void setLable(int ilable);
    void setEquivalenceSet(int ilabel);
    void setDistance(int ivalue_f);//#001 add
    void setConvolution(float convolution_result);
    void setEdge(int edge_value);
    
    uint8_t getColor();
    int getLable();
    int getX();
    int getY();
    set<int> getEquivalenceSet();
    int getDistance();//#001 add
    float getConvolution();
    int getEdge();
    
    private:
        int x;
        int y;
        uint8_t color;
        int label;
        set<int> equivalenceSet;
        int value_f;//#001 add
        float convolution_f;//#003 add
        int edge;//#003 add
};