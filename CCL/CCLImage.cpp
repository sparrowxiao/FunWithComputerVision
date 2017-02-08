/************************************************************************
 *	File name	: CCLImage.cpp
 *	Program name: CCL
 *	Abstract	: Computer Vison
 *	Author		:
 *	Modify record	:
 *	Date		Belong	Charge		Manage No.		Remarks
 *	-------------------------------------------------------------------
 *   2013/02/06		UGA		ting		-			create
 *   2013/02/18		UGA		ting		001         ssignment#2:Distance Transform
 *   2013/02/24		UGA		ting		002         ssignment#3:thresholding ALG
 *	Remarks			:
 *
 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "CCLImage.h"
#include <iostream>
#include <iomanip>
#include <math.h>


using namespace std;


CCLImage::CCLImage(char* inFile)
{
    height = 512;
    width = 512;
    pathSourceImg = inFile;    
    componetlabel = 1;
     
}
CCLImage::~CCLImage()
{
    if (pGrayImg!=NULL)
    {
        free(pGrayImg);
    }
    if (pImgHeader!=NULL)
    {
        free(pImgHeader);
    }
    if (pbinaryImg!=NULL)
    {
        free(pbinaryImg);
    }
}
int CCLImage::getBinaryImage(int ithreshold)
{

    size_t result;
    FILE* pFile;
    int index= 0;
    
    pImgHeader = (uint8_t*)malloc(sizeof(uint8_t)*800);
    if (pImgHeader == NULL) {fputs ("Memory error",stderr); exit (2);}
    pbinaryImg = (uint8_t*)malloc(sizeof(uint8_t)*height*width);
    if (pbinaryImg == NULL) {fputs ("Memory error",stderr); exit (2);}
    
  
    //open the file to prepare read and write
    pFile=fopen(pathSourceImg,"rb");
    if (pFile == NULL)
    {
        fputs ("File error",stderr); exit (1);
        
	}
 
    //read head!
    result = fread(pImgHeader,1,800,pFile);
 
    if (result != 800) {fputs ("Reading error",stderr); exit (3);}

   
    result = fread(pbinaryImg,1,width*height,pFile);
    if (result != width*height) {fputs ("Reading error",stderr); exit (3);}
    fclose(pFile);
    

    
    for (index= 0; index< width*height; index++)
    {
        if(pbinaryImg[index]<ithreshold)
        {
            
            pbinaryImg[index]=0xff;//white-->foreground
        }
        else
        {
            pbinaryImg[index]=0x00;//black-->background
        }
        
    }
    
    FILE* tempFile;
 
    tempFile = fopen("/Users/sparrow/result.ras", "wb");
    fwrite(pImgHeader, 1, sizeof(uint8_t)*800, tempFile);
    fwrite(pbinaryImg, 1, sizeof(uint8_t)*width*height, tempFile);
    
    fclose(tempFile);
   
    return 0;
}

//#003 begin
int CCLImage::readImage()
{
    size_t result;
    FILE* pFile;
    
    pImgHeader = (uint8_t*)malloc(sizeof(uint8_t)*800);
    if (pImgHeader == NULL) {fputs ("Memory error",stderr); exit (2);}
    pGrayImg = (uint8_t*)malloc(sizeof(uint8_t)*height*width);
    if (pGrayImg == NULL) {fputs ("Memory error",stderr); exit (2);}
    
    
    //open the file to prepare read and write
    pFile=fopen(pathSourceImg,"rb");
    if (pFile == NULL)
    {
        fputs ("File error",stderr); exit (1);
        
	}
    
    //read head!
    result = fread(pImgHeader,1,800,pFile);
    
    if (result != 800) {fputs ("Reading error",stderr); exit (3);}

    result = fread(pGrayImg,1,width*height,pFile);
    if (result != width*height) {fputs ("Reading error",stderr); exit (3);}
    fclose(pFile);
    
    return 0;
}



int CCLImage::doLoG(int wind_size,float sigma)
{

    uint8_t *pResultImg = (uint8_t*)malloc(sizeof(uint8_t)*height*width);
    if (pResultImg == NULL) {fputs ("Memory error",stderr); exit (2);}
    
    vector<float>kernel;//filter
    
    kernel = LogMask(wind_size, sigma);
    
    doLogWithImage(kernel,pGrayImg,pResultImg);
    
           
    FILE* tempFile;
    
    tempFile = fopen("/Users/sparrow/result_LOG.ras", "wb");
    fwrite(pImgHeader, 1, sizeof(uint8_t)*800, tempFile);
    fwrite(pResultImg, 1, sizeof(uint8_t)*width*height, tempFile);
    
    fclose(tempFile);
    
    if (pResultImg)
    {
        free(pResultImg);
    }
    return 0;
    

}

int CCLImage::doMultiScaleLoG(int wind_size,float sigma,float delta_sigma)
{
    //step1:get LoG operator
    vector<float>kernel;//filter
    kernel = LogMask(wind_size, sigma);
    
    uint8_t *pEImg = (uint8_t*)malloc(sizeof(uint8_t)*height*width);
    if ( pEImg== NULL) {fputs ("Memory error",stderr); exit (2);}
    
    //step2:get edge map
    doLogWithImage(kernel,pGrayImg,pEImg);
    
    //step3:
    float sigma_new = sigma;
    for (sigma_new =sigma-delta_sigma; sigma_new>0.5; sigma_new-=delta_sigma)
    {
        kernel.clear();
        kernel = LogMask(wind_size, sigma_new);//new LoG operator
        
        //step4:
        uint8_t *pNewEImg = (uint8_t*)malloc(sizeof(uint8_t)*height*width);
        if ( pNewEImg== NULL) {fputs ("Memory error",stderr); exit (2);}
        
        doLogWithEdgeMap(kernel,pGrayImg,pEImg,pNewEImg);
        
        if (pEImg)
        {
            free(pEImg);
        }
        pEImg = pNewEImg;
    }
    
    FILE* tempFile;
    
    tempFile = fopen("/Users/sparrow/result_edgeFocus.ras", "wb");
    fwrite(pImgHeader, 1, sizeof(uint8_t)*800, tempFile);
    fwrite(pEImg, 1, sizeof(uint8_t)*width*height, tempFile);
    
    fclose(tempFile);
    
    if (pEImg)
    {
        free(pEImg);
    }
    
    return 0;
}

int CCLImage::doLogWithEdgeMap(vector<float> kernel_new,uint8_t* pIImg,uint8_t* pEImg,uint8_t* pNewEImg)
{
    //get the winow
    int i=0,j=0;
    int index=0;
    int index1=0;
    int index2=0;
    int index3=0;
    int index4=0;
    int index5=0;
    int index6=0;
    int index7=0;
    int index8=0;
    vector<int>window;
    float result_convolution=0.0;
    
    //step2:
    //traver the image and and get the convolution
    for (i= 0; i< HEIGHT; i++)//one line y cordinator
    {
        for (j=0; j<WIDTH; j++)//one point x cordinator
        {
            index = i*WIDTH+j;
            uint8_t temp =*(pEImg+index);
            
            if ((i==0)||(i==511)||(j==0)||(j==511))
            {
                
                //temp to save the conclution result
                CCLPixel* tempPixel = new CCLPixel();
                tempPixel->setColor(pIImg[index]);
                tempPixel->setPosition(j,i);
                tempPixel->setConvolution(pIImg[index]);
                totolImg.push_back(*tempPixel);
                
            }
            else
            {
                //temp to save the conclution result
                CCLPixel* tempPixel = new CCLPixel();
                tempPixel->setColor(pIImg[index]);
                
                if (temp==255)//e(i,j,sigma)=1
                {
                    //get the window
                    index1= (i-1)*WIDTH+(j-1);
                    window.push_back(pIImg[index1]);
                    index2= (i-1)*WIDTH+j;
                    window.push_back(pIImg[index2]);
                    index3= (i-1)*WIDTH+j+1;
                    window.push_back(pIImg[index3]);
                    index4= i*WIDTH+j-1;
                    window.push_back(pIImg[index4]);
                    index = i*WIDTH+j;
                    window.push_back(pIImg[index]);
                    index5= i*WIDTH+j+1;
                    window.push_back(pIImg[index5]);
                    index6= (i+1)*WIDTH+j-1;
                    window.push_back(pIImg[index6]);
                    index7= (i+1)*WIDTH+j;
                    window.push_back(pIImg[index7]);
                    index8= (i+1)*WIDTH+j+1;
                    window.push_back(pIImg[index8]);
                    result_convolution = conv2vector(window, kernel_new);
                    printf("%f\n",result_convolution);
                    tempPixel->setConvolution(result_convolution);
                    
                    
                    
                }
               
        
                
                tempPixel->setPosition(j,i);
                
                totolImg.push_back(*tempPixel);
                
                
            }
            
            window.clear();
            
        }//for j
        
    }//for i
    
    
    //3)detect the zero crossing
    float neighbor1=0.;
    float neighbor2=0.;
    float neighbor3=0.;
    float neighbor4=0.;
    
    for (index=0; index<WIDTH*HEIGHT-1; index++)
    {
        
        float current = totolImg[index].getConvolution();
        int x_c= totolImg[index].getX();
        int y_c = totolImg[index].getY();
        int position = x_c+y_c*width;
        
        if ((x_c==0)||(x_c==511)||(y_c==0)||(y_c==511))
        {
            pNewEImg[position]= 0;
            
        }
        else
        {
            neighbor1 = totolImg[position-WIDTH].getConvolution();
            neighbor2 = totolImg[position+1].getConvolution();
            neighbor3 = totolImg[position-1].getConvolution();
            neighbor4 = totolImg[position+WIDTH].getConvolution();
            
            if( (neighbor1*neighbor3<0.0)||(neighbor2*neighbor4<0.)
               ||(current*neighbor1<0.)
               ||(current*neighbor2<0.)
               ||(current*neighbor3<0.)
               ||(current*neighbor4<0.)
               )
               
            {
                pNewEImg[position]=255;
                
            }
            else
            {
                pNewEImg[position]=0;
            }
            
        }
        
    }//for
    
    totolImg.clear();
    
    return 0;
}

int CCLImage::doLogWithImage(vector<float> kernel_new,uint8_t* pIImg,uint8_t* pEImg)
{
    //get the winow
    int i=0,j=0;
    int index=0;
    int index1=0;
    int index2=0;
    int index3=0;
    int index4=0;
    int index5=0;
    int index6=0;
    int index7=0;
    int index8=0;
    vector<int>window;
    float result_convolution=0.0;
    
    //step2:
    //traver the image and and get the convolution
    for (i= 0; i< HEIGHT; i++)//one line y cordinator
    {
        for (j=0; j<WIDTH; j++)//one point x cordinator
        {
                index = i*WIDTH+j-1;
                
            
            if ((i==0)||(i==511)||(j==0)||(j==511))
            {
                
                
                
                //temp to save the conclution result
                CCLPixel* tempPixel = new CCLPixel();
                tempPixel->setColor(pIImg[index]);
                tempPixel->setPosition(j,i);
                tempPixel->setConvolution((float)pIImg[index]);
                totolImg.push_back(*tempPixel);

                
            }
            else
            {
                //get the window
                index1= (i-1)*WIDTH+(j-1);
                window.push_back(pIImg[index1]);
                index2= (i-1)*WIDTH+j;
                window.push_back(pIImg[index2]);
                index3= (i-1)*WIDTH+j+1;
                window.push_back(pIImg[index3]);
                index4= i*WIDTH+j-1;
                window.push_back(pIImg[index4]);
                index = i*WIDTH+j;
                window.push_back(pIImg[index]);
                index5= i*WIDTH+j+1;
                window.push_back(pIImg[index5]);
                index6= (i+1)*WIDTH+j-1;
                window.push_back(pIImg[index6]);
                index7= (i+1)*WIDTH+j;
                window.push_back(pIImg[index7]);
                index8= (i+1)*WIDTH+j+1;
                window.push_back(pIImg[index8]);
            
                //
                result_convolution = conv2vector(window, kernel_new);
                printf("%f\n",result_convolution);
                
                //temp to save the conclution result
                CCLPixel* tempPixel = new CCLPixel();
                tempPixel->setColor(pIImg[index]);
                tempPixel->setPosition(j,i);
                tempPixel->setConvolution(result_convolution);
                totolImg.push_back(*tempPixel);
                

            }
           
            window.clear();
            
        }//for j
        
    }//for i
    
    
    //3)detect the zero crossing
    float neighbor1=0.;
    float neighbor2=0.;
    float neighbor3=0.;
    float neighbor4=0.;
    
    for (index=0; index<WIDTH*HEIGHT-1; index++)
    {
        
        float current = totolImg[index].getConvolution();
        int x_c= totolImg[index].getX();
        int y_c = totolImg[index].getY();
        int position = x_c+y_c*width;
        
        if ((x_c==0)||(x_c==511)||(y_c==0)||(y_c==511))
        {
            pEImg[position]= 0;
           
        }
        else
        {
            neighbor1 = totolImg[position-WIDTH].getConvolution();
            neighbor2 = totolImg[position+1].getConvolution();
            neighbor3 = totolImg[position-1].getConvolution();
            neighbor4 = totolImg[position+WIDTH].getConvolution();
            
            if(
               (neighbor1*neighbor3<0.0)||(neighbor2*neighbor4<0.)
               ||(current*neighbor1<0.)
               ||(current*neighbor2<0.)
               ||(current*neighbor3<0.)
               ||(current*neighbor4<0.)
               )
            {
                pEImg[position]=255;
                
            }
            else
            {
                pEImg[position]=0;
            }
            
        
        
        }
        
    }//for
    
    totolImg.clear();
    return 0;
    
}