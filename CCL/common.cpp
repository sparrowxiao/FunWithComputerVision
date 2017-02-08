//
//  common.cpp
//  CCL
//
//  Created by ting xiao on 2/25/13.
//  Copyright (c) 2013 ting xiao. All rights reserved.
//

#include "common.h"

float conv2vector(vector<int> window_value, vector<float> kernel_value)
{
    float sum = 0.0;
    int index =0;
    for (vector<int>::iterator curr = window_value.begin(); curr != window_value.end(); ++curr)
    {
        
        sum += window_value[index]*kernel_value[index];
        index++;
    }
    
    return sum;
}

vector<float> LogMask(int mask_size, float sigma)
{
    vector<float> template_LoG;//filter
    vector<float> mask;//subimage
    float s2 = sigma * sigma;
    float s4 = sigma * sigma * sigma * sigma;

    for(float x = -4*sigma; x <= 4*sigma; x++)
    {
    
        for(float y = -4*sigma; y <=4*sigma; y++)
        {
        
            float val = (float)(((x * x + y * y)- (2.0f * (s2)))/s4) * (float)exp((-(x * x + y * y) / (2.0f * (s2))));
            template_LoG.push_back(val);
          
        }
     
    }
    
    
    int step = mask_size>>1;
    int template_size = ((int)(8*sigma+1));
    int sample = (int)step*sqrtf(2.0)*sigma+1;

    int min = (template_size>>1)-sample;
    int max = (template_size>>1)+sample;
    
    int index=0;
    float temp=0.;
    for (int xcount= min; xcount<=max; xcount+=sample)
    {
        for (int ycount= min; ycount<=max; ycount+=sample)
        {
            index = xcount*(template_size)+ycount;
            temp=template_LoG[index];
            mask.push_back(temp);
        }
    }
    
    return mask;
}
