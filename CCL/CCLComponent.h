//
//  CCLComponent.h
//  CCL
//
//  Created by ting xiao on 2/10/13.
//  Copyright (c) 2013 ting xiao. All rights reserved.
//

#ifndef __CCL__CCLComponent__
#define __CCL__CCLComponent__

#include <iostream>
#include <vector>
#include "CCLPixel.h"

using namespace std;


#endif /* defined(__CCL__CCLComponent__) */
class CCLComponent
{
    public:
        CCLComponent(vector<CCLPixel> vect);
        unsigned long getComponentSize();
        vector<CCLPixel> getComponent();
        int getCentroidofComponent();
        float getCoordinatesofBox(int iComponentNo);
        float getEccentrictiyofComponent(int iComponentNo);
        float getPerimeterofComponet(int iComponentNo);
        float getCompactnessofComponet(int iComponentNo);
    
    private:
        vector<CCLPixel> pixels;
        double dxc;
        double dyc;
    
    
};