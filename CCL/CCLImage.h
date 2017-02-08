/************************************************************************
 *	File name	: CCLImage.h
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

#ifndef __CCL__CCLImage__
#define __CCL__CCLImage__

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include "CCLPixel.h"
#include "common.h"

using namespace std;

#endif /* defined(__CCL__CCLImage__) */

struct pointer
{
    int x;
    int y;
};
class CCLImage
{
    
    public:
        CCLImage(char* inFile);//construction
        ~CCLImage();
        int getBinaryImage(int ithreshold);//get 2 image with thresholding
        
        //#002 begin
        int readImage();//just read the buffer of  the image file
        int writeImage(char* outFile);// write the buffer to a new file
      
        //#002 end
    
        //#003 do convolution
        int doLoG(int wind_size,float sigma);
        int doLogWithImage(vector<float> kernel_new,uint8_t* pIImg,uint8_t* pEImg);
        int doMultiScaleLoG(int wind_size,float sigma,float delta_sigma);
        int doLogWithEdgeMap(vector<float> kernel_new,uint8_t* pIImg,uint8_t* pEImg,uint8_t* pNewEImg);
    
    private:
        char* pathSourceImg;//the img pixels of the picture
        
        int height;
        int width;
        int sizeFilter;
        int componetlabel;
        uint8_t* pImgHeader;
        uint8_t* pbinaryImg;
        uint8_t* pGrayImg;//gray image of the origin picture
        vector<CCLPixel> totolImg;
    
};

