//
//  CCLComponent.cpp
//  CCL
//
//  Created by ting xiao on 2/10/13.
//  Copyright (c) 2013 ting xiao. All rights reserved.
//

#include "CCLComponent.h"

CCLComponent::CCLComponent(vector<CCLPixel> vect)
{
    pixels.swap(vect);
    dxc = 0.0;
    dyc = 0.0;
    
}


unsigned long CCLComponent::getComponentSize()
{
    unsigned long A = pixels.size();
    return A;
}

/*
vector<CCLPixel> getComponent()
{
    vector<CCLPixel> temp;
    temp.swap(pixels);
    return temp;
}


int CCLComponent::getCentroidofComponent()
{
    

}
float getCoordinatesofBox(int iComponentNo)
{}
float getEccentrictiyofComponent(int iComponentNo){

}
float getPerimeterofComponet(int iComponentNo)
{}
float getCompactnessofComponet(int iComponentNo)
{}*/