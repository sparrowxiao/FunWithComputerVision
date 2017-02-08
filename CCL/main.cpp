//
//  main.cpp
//  CCL
//
//  Created by ting xiao on 3/3/13.
//  Copyright (c) 2013 ting xiao. All rights reserved.
//

#include <iostream>
#include "CCLImage.h"
#include "common.h"

using namespace std;

int main(int argc, const char * argv[])
{
    //get file path from the argv[]:ras or img//
    //only support the ras image file
    char infile[256];//input file url
    
    
    //get the input parameter from the command -line
    strcpy(infile,argv[1]);
       
    
    //using the ras image path to create the object of the CCLImage object
    CCLImage* image =  new CCLImage(infile);
    image->readImage();
    image->doLoG(3,5.0f);
    //image->doMultiScaleLoG(3,5.0f,0.5f);
    
   
    
   
  
    return 0;
}

