//
//  common.h
//  CCL
//
//  Created by ting xiao on 3/9/13.
//  Copyright (c) 2013 ting xiao. All rights reserved.
//

#ifndef __CCL__common__
#define __CCL__common__

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

#define PI 3.1415926



typedef pair<int, int> PAIR;


#endif /* defined(__CCL__common__) */


int CreatLoGWindow(int size);
float conv2vector(vector<int> window_value, vector<float> kernel_value);
vector<float> LogMask(int mask_size, float sigma);
