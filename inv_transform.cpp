#include <stdio.h>
#include <algorithm>
#include <cmath>
int main(int argc, char *argv[])
    int height = Size;
    int width = Size;
    //float linear_filter[5][5] = {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}};
    //float lin_filter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
    //float linear_fil[7][7] = {{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1}};
    if (!(file=fopen(argv[1],"rb"))) {

	unsigned char OutputImage [256][256][1];

	for(int i=0; i<256; ++i){
        for( int j=0; j< 256; ++j){
            OutputImage[i][j][0] = (unsigned char) (pow(Imagedata[i][j][0]/2.0,2) - 3/8.0);
        }
	}
     if (!(file=fopen(argv[2],"wb"))) {

}