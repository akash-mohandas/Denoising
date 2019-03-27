#include <stdio.h>
#include <algorithm>
#include <cmath>
unsigned char convolution(int,int,double [][7],unsigned char[][262][1],double);
double getGaussian(double [][7]);
    int height = Size;
    int width = Size;
    //float linear_filter[5][5] = {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}};
    //float lin_filter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
    //float linear_fil[7][7] = {{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1}};
    if (!(file=fopen(argv[1],"rb"))) {

	double kernal[7][7];
	double sum = getGaussian(kernal);

    unsigned char Reimage[262][262][1];
	for(int j=0; j<3; ++j){
        for(int i=3; i<3+width; ++i){
            Reimage[j][i][0] = Imagedata[3-j][i-3][0];
        }
	}
	cout<<"first"<<endl;
	for(int j=0; j<3; ++j){
        for(int i=3; i<3+width; ++i){
            Reimage[height+j+3][i][0] = Imagedata[height-j-2][i-3][0];
        }
	}
    cout<<"second"<<endl;
	for(int i=0; i<3; ++i){
        for(int j=3; j<3+height; ++j){
            Reimage[j][i][0] = Imagedata[j-3][3-i][0];
        }
	}

	for(int i=0; i<3; ++i){
        for(int j=3; j<3+height; ++j){
            Reimage[j][width+3+i][0] = Imagedata[j-3][width-i-2][0];
        }
	}
	cout<<"continued"<<endl;
	Reimage[0][0][0] = Reimage[0][6][0];
	Reimage[0][1][0] = Reimage[0][5][0];
	Reimage[0][2][0] = Reimage[0][4][0];
	Reimage[1][0][0] = Reimage[1][6][0];
	Reimage[1][1][0] = Reimage[1][5][0];
	Reimage[1][2][0] = Reimage[1][4][0];
	Reimage[2][0][0] = Reimage[2][6][0];
	Reimage[2][1][0] = Reimage[2][5][0];
	Reimage[2][2][0] = Reimage[2][4][0];
	Reimage[0][width+3][0] = Reimage[0][width+1][0];
	Reimage[0][width+4][0] = Reimage[0][width][0];
	Reimage[0][width+5][0] = Reimage[0][width-1][0];
	Reimage[1][width+3][0] = Reimage[1][width+1][0];
	Reimage[1][width+4][0] = Reimage[1][width][0];
	Reimage[1][width+5][0] = Reimage[1][width-1][0];
	Reimage[2][width+3][0] = Reimage[2][width+1][0];
	Reimage[2][width+4][0] = Reimage[2][width][0];
	Reimage[2][width+5][0] = Reimage[2][width-1][0];
	Reimage[height+3][0][0] = Reimage[height+3][6][0];
	Reimage[height+3][1][0] = Reimage[height+3][5][0];
	Reimage[height+3][2][0] = Reimage[height+3][4][0];
	Reimage[height+4][0][0] = Reimage[height+4][6][0];
	Reimage[height+4][1][0] = Reimage[height+4][5][0];
	Reimage[height+4][2][0] = Reimage[height+4][4][0];
	Reimage[height+5][0][0] = Reimage[height+5][6][0];
	Reimage[height+5][1][0] = Reimage[height+5][5][0];
	Reimage[height+5][2][0] = Reimage[height+5][4][0];
	Reimage[height+3][width+3][0] = Reimage[height+3][width+1][0];
	Reimage[height+3][width+4][0] = Reimage[height+3][width][0];
	Reimage[height+3][width+5][0] = Reimage[height+3][width-1][0];
	Reimage[height+4][width+3][0] = Reimage[height+4][width+1][0];
	Reimage[height+4][width+4][0] = Reimage[height+4][width][0];
	Reimage[height+4][width+5][0] = Reimage[height+4][width-1][0];
	Reimage[height+5][width+3][0] = Reimage[height+5][width+1][0];
	Reimage[height+5][width+4][0] = Reimage[height+5][width][0];
	Reimage[height+5][width+5][0] = Reimage[height+5][width-1][0];

    for(int j=0; j<height; ++j){
        for(int i=0; i<width; ++i){
            Reimage[j+3][i+3][0] = Imagedata[j][i][0];
        }
    }


	for(int i=0; i< height; ++i){
        for(int j=0; j<width; ++j){
            denoiseImage[i][j][0] = convolution(i,j,kernal,Reimage,sum);
        }
	}
    if (!(file=fopen(argv[2],"wb"))) {


}

unsigned char convolution(int i, int j, double kernel[][7], unsigned char image[][262][1],double sum){
    float pix = 0.0;
    for(int k=i; k<i+7; ++k){
        for(int l=j; l<j+7; ++l){
            pix+= (image[k][l][0] * kernel[k-i][l-j]);
            //cout<<pix<<endl;
        }
    }
    return (unsigned char)(pix/sum);
}

double getGaussian(double kernal[][7]){
    double sigma = 2.0;
    double sum=0;

    for(int i= -3; i<=3 ; ++i){
        for(int j= -3; j<=3; ++j){
            kernal[i+3][j+3] = exp(-(i*i + j*j)/(2*sigma * sigma))/(sqrt((2*M_PI * sigma * sigma)));
            sum+=kernal[i+3][j+3];
        }
    }
    return sum;
}