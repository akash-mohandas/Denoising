#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <algorithm>
#include <cmath>using namespace std;
float Reimage[260][260][1];

unsigned char convolution(int,int,double [][5],unsigned char[][260][1],double);
double getGaussian(double [][5]);

float convolution(int i, int j, double kernel[][5], float image[][260][1],double sum){
    float pix = 0.0;
    for(int k=i; k<i+5; ++k){
        for(int l=j; l<j+5; ++l){
            pix+= (image[k][l][0] * kernel[k-i][l-j]);
            //cout<<pix<<endl;
        }
    }
    return (pix/sum);
}

double getGaussian(double kernal[][5]){
    double sigma = 1.0;
    double sum=0;

    for(int i= -2; i<=2 ; ++i){
        for(int j= -2; j<=2; ++j){
            kernal[i+2][j+2] = exp(-(i*i + j*j)/(2*sigma * sigma))/(sqrt((2*M_PI * sigma * sigma)));
            sum+=kernal[i+2][j+2];
        }
    }
    return sum;
}
int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size = 256;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4){		BytesPerPixel = 1; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5){			Size = atoi(argv[4]);		}	}
    int height = Size;
    int width = Size;
    //float linear_filter[5][5] = {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}};
    //float lin_filter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
    //float linear_fil[7][7] = {{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1}};	// Allocate image data array	unsigned char Imagedata[height][width][BytesPerPixel];
    if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);	fclose(file);
    float Imagedata_transform [height][width][1];
    for(int i=0; i<height; ++i){
        for(int j=0; j<width; ++j){
            Imagedata_transform[i][j][0] = 2 * sqrt((float)(Imagedata[i][j][0]) + 3/8.0) ;
        }
    }

	double kernal[5][5];
	double sum = getGaussian(kernal);



	for(int j=0; j<2; ++j){
        for(int i=2; i<2+width; ++i){
            Reimage[j][i][0] =  Imagedata_transform[2-j][i-2][0];
        }
	}
	cout<<"first"<<endl;
	for(int j=0; j<2; ++j){
        for(int i=2; i<2+width; ++i){
            Reimage[height+j+2][i][0] =  Imagedata_transform[height-j-2][i-2][0];
        }
	}
    cout<<"second"<<endl;
	for(int i=0; i<2; ++i){
        for(int j=2; j<2+height; ++j){
            Reimage[j][i][0] =  Imagedata_transform[j-2][2-i][0];
        }
	}

	for(int i=0; i<2; ++i){
        for(int j=2; j<2+height; ++j){
            Reimage[j][width+2+i][0] =  Imagedata_transform[j-2][width-i-2][0];
        }
	}
	cout<<"continued"<<endl;
	Reimage[0][0][0] = Reimage[0][4][0];
	Reimage[0][1][0] = Reimage[0][3][0];
	//Reimage[0][2][0] = Reimage[0][4][0];
	Reimage[1][0][0] = Reimage[1][4][0];
	Reimage[1][1][0] = Reimage[1][3][0];
	//Reimage[1][2][0] = Reimage[1][4][0];
	//Reimage[2][0][0] = Reimage[2][6][0];
	//Reimage[2][1][0] = Reimage[2][5][0];
	//Reimage[2][2][0] = Reimage[2][4][0];
	Reimage[0][width+2][0] = Reimage[0][width][0];
	Reimage[0][width+3][0] = Reimage[0][width-1][0];
	//Reimage[0][width+5][0] = Reimage[0][width-1][0];
	Reimage[1][width+2][0] = Reimage[1][width][0];
	Reimage[1][width+3][0] = Reimage[1][width-1][0];
	//Reimage[1][width+5][0] = Reimage[1][width-1][0];
	//Reimage[2][width+3][0] = Reimage[2][width+1][0];
	//Reimage[2][width+4][0] = Reimage[2][width][0];
	//Reimage[2][width+5][0] = Reimage[2][width-1][0];
	Reimage[height+2][0][0] = Reimage[height+2][4][0];
	Reimage[height+2][1][0] = Reimage[height+2][3][0];
	Reimage[height+3][0][0] = Reimage[height+3][4][0];
	Reimage[height+3][1][0] = Reimage[height+3][3][0];
	//Reimage[height+4][1][0] = Reimage[height+4][5][0];
	//Reimage[height+4][2][0] = Reimage[height+4][4][0];
	//Reimage[height+5][0][0] = Reimage[height+5][6][0];
	//Reimage[height+5][1][0] = Reimage[height+5][5][0];
	//Reimage[height+5][2][0] = Reimage[height+5][4][0];
	Reimage[height+2][width+2][0] = Reimage[height+2][width][0];
	Reimage[height+2][width+3][0] = Reimage[height+2][width-1][0];
	Reimage[height+3][width+2][0] = Reimage[height+3][width][0];
	Reimage[height+3][width+3][0] = Reimage[height+3][width-1][0];
	//Reimage[height+4][width+4][0] = Reimage[height+4][width][0];
	//Reimage[height+4][width+5][0] = Reimage[height+4][width-1][0];
	//Reimage[height+5][width+3][0] = Reimage[height+5][width+1][0];
	//Reimage[height+5][width+4][0] = Reimage[height+5][width][0];
	//Reimage[height+5][width+5][0] = Reimage[height+5][width-1][0];

    for(int j=0; j<height; ++j){
        for(int i=0; i<width; ++i){
            Reimage[j+2][i+2][0] =  Imagedata_transform[j][i][0];
        }
    }
	// Read image (filename specified by first argument) into image data matrix	unsigned char denoiseImage[256][256][1];

	for(int i=0; i< height; ++i){
        for(int j=0; j<width; ++j){
            denoiseImage[i][j][0] = convolution(i,j,kernal,Reimage,sum);
        }
	}

	unsigned char OutputImage [256][256][1];

	for(int i=0; i<256; ++i){
        for( int j=0; j< 256; ++j){
            OutputImage[i][j][0] = (unsigned char) (pow(denoiseImage[i][j][0]/2.0,2) - 3/8.0);
        }
	}

    if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(OutputImage, sizeof(unsigned char), (height)*(width)*1, file);	fclose(file);
	return 0;

}


