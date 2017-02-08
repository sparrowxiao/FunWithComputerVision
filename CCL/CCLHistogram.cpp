//
//  CCLHistogram.cpp
//  CCL
//
//  Created by ting xiao on 2/24/13.
//  Copyright (c) 2013 ting xiao. All rights reserved.
//

#include "CCLHistogram.h"

CCLHistogram::CCLHistogram(uint8_t* pImg)
{

    pSource = pImg;
    pResutl = NULL;
    gray_level = 256;
    int i=0;
    for (i=0; i<gray_level; i++)
    {
       histogram.insert(pair<int, int>(i,0));
    }
    
}

int CCLHistogram::getHistogram()
{
    /*
    //forground
    int i=0;
    int j=0;
    int index=0;
    int current_gray = 0;
    map<int,int>::iterator it;
    
    
      for (i= 0; i< HEIGHT; i++)//one line y cordinator
    {
        
        for (j=0; j<WIDTH; j++)//one point x cordinator
        {
            index = i*WIDTH+j;
            current_gray= pSource[index];
            
            it=histogram.find(current_gray);
            it->second++;
            
        }//FOR J
    }//FORI
    
    printhistogram();//print to check*/
    return 0;
}

int CCLHistogram::doPeakDection(int local_min,int local_max)
{
    //using the 0 to 255
    
    vector<PAIR> vec;
    int arr_peak[256]={0};
    
    int first_max = arr_peak[0];
    int second_max= arr_peak[1];
    int first_min = arr_peak[255];
    

    
    
    int i=0;
    for (map<int,int>::iterator curr = histogram.begin(); curr != histogram.end(); ++curr)
    {
        i++;
        arr_peak[i-1]=curr->second;
       // vec.push_back(make_pair(curr->first, curr->second));
    }
    //sort(vec.begin(), vec.end(), cmp);
    sort(arr_peak, arr_peak+256, greater<int>());
    
        
    
    return 0;
    
}
int CCLHistogram::doIterativeThreshold()
{
    /*
    //1.average
    vector<PAIR> R1;
    vector<PAIR> R2;
    int sum_T=0;
    int average_T=0;
    
    int sum_R1=0;
    int avg_R1=0;
    int sum_R2=0;
    int avg_R2=0;
    
    int avg_temp=0;
    
   
    
    for (map<int,int>::iterator curr = histogram.begin(); curr != histogram.end(); ++curr)
    {
        
        sum_T=sum_T+curr->second;
    }
    
    average_T = (int)(sum_T/256);
    
    
    while (average_T!=avg_temp) {
        
        average_T=avg_temp;
    //group to class
    for (map<int,int>::iterator curr = histogram.begin(); curr != histogram.end(); ++curr)
    {
        
        if(curr->second<=average_T)
        {
            R1.push_back(make_pair(curr->first, curr->second));
        }
        else
        {
            R2.push_back(make_pair(curr->first, curr->second));
        }
    }
    
    //calculate the avg of each group r1 and r2
    for (vector<PAIR>::iterator it = R1.begin(); it != R1.end(); ++it)
    {
        sum_R1=sum_R1+it->second;
    }
    
    avg_R1=(int)(sum_R1/R1.size());
    
    
    for (vector<PAIR>::iterator it = R2.begin(); it != R2.end(); ++it)
    {
        sum_R2=sum_R2+it->second;
    }
    
    avg_R2=(int)(sum_R2/R2.size());
    
    
    //
    avg_temp=(avg_R1+avg_R2)/2;
    
    
    //while condition
    //average_T!=change keepon
    }
    return avg_temp;*/
    
    return 0;
}
int CCLHistogram::doAdptiveThreshold()
{
    /*
    //divide into 4 area
    //1.alloc 4 memory
    
    uint8_t* pDevide1 = (uint8_t*)malloc(sizeof(uint8_t)*(HEIGHT/2)*(WIDTH/2));
    uint8_t* pDevide2 = (uint8_t*)malloc(sizeof(uint8_t)*(HEIGHT/2)*(WIDTH/2));
    uint8_t* pDevide3 = (uint8_t*)malloc(sizeof(uint8_t)*(HEIGHT/2)*(WIDTH/2));
    uint8_t* pDevide4 = (uint8_t*)malloc(sizeof(uint8_t)*(HEIGHT/2)*(WIDTH/2));
    
    
    int i=0;
    int j=0;
    int index=0;
    //traver the image and copy the pixel to it
    for (i= 0; i< HEIGHT; i++)//one line y cordinator
    {
        
        for (j=0; j<WIDTH; j++)//one point x cordinator
        {
            index = i*WIDTH+j;
            
            if ((i>=0)&&(i<=255)&&(j>=0)&&(j<=255))//R1
            {
                *pDevide1=pSource[index];
                pDevide1++;
            }
            else if ((j>=255)&&(j<=511)&&(i>=0)&&(i<=255))//R2
            {
                *pDevide2=pSource[index];
                pDevide2++;
            }
            else if ((j>=0)&&(j<=255)&&(i>=512)&&(i<=511))//R3
            {
                *pDevide3=pSource[index];
                pDevide3++;
            }
            
            else if ((j>=255)&&(j<=511)&&(i>=255)&&(i<=511))//R4
            {
                *pDevide4=pSource[index];
                pDevide4++;
            }
        }//FOR J
    }//FORI
    
    
    
    //compute the histogram for each of them
    
    
    
    
    
    // using the iterative for each of them
    */
    
    return 0;

}
int CCLHistogram::doDualThreshold()
{
    
    
   
    
    return 0;
}

int CCLHistogram::printhistogram()
{
    for (auto rit = histogram.crbegin(); rit != histogram.crend(); ++rit)
    {
        cout << " [" << rit->first << ':' << rit->second << ']'<<endl;
    }
   
    return 0;
}


