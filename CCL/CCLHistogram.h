//
//  CCLHistogram.h
//  CCL
//
//  Created by ting xiao on 2/24/13.
//  Copyright (c) 2013 ting xiao. All rights reserved.
//

#ifndef __CCL__CCLHistogram__
#define __CCL__CCLHistogram__

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
#endif /* defined(__CCL__CCLHistogram__) */

#define PEAK_DETECT         1
#define ITERATIVE_THRES     2
#define ADPTIVE_THRES       3
#define DUAL_THRES          4
#define HEIGHT              512
#define WIDTH               512

typedef pair<int, int> PAIR;



class CCLHistogram
{
 public:
    CCLHistogram(uint8_t* pImg);//construction
    int getHistogram();//
    
    int doPeakDection(int local_min,int local_max);//to give a range
    int doIterativeThreshold();
    int doAdptiveThreshold();
    int doDualThreshold();
    
    int printhistogram();
    
 private:
    int gray_level;
    uint8_t* pSource;
    uint8_t* pResutl;
    map<int,int> histogram;
    
    
    
};