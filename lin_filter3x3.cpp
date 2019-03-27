#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <algorithm>using namespace std;
unsigned char convolution(int,int,float [][3],unsigned char[][258][1]);int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size = 256;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4){		BytesPerPixel = 1; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5){			Size = atoi(argv[4]);		}	}
    int height = Size;
    int width = Size;
   // float linear_filter[5][5] = {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}};
    float lin_filter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
    //float linear_fil[7][7] = {{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1}};	// Allocate image data array	unsigned char Imagedata[height][width][BytesPerPixel];
    if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);	fclose(file);

        unsigned char Reimage[258][258][1];
	for(int j=0; j<1; ++j){
        for(int i=1; i<1+width; ++i){
            Reimage[j][i][0] = Imagedata[1-j][i-1][0];
        }
	}
	cout<<"first"<<endl;
	for(int j=0; j<1; ++j){
        for(int i=1; i<1+width; ++i){
            Reimage[height+j+1][i][0] = Imagedata[height-j-2][i-1][0];
        }
	}
    cout<<"second"<<endl;
	for(int i=0; i<1; ++i){
        for(int j=1; j<1+height; ++j){
            Reimage[j][i][0] = Imagedata[j-1][1-i][0];
        }
	}

	for(int i=0; i<1; ++i){
        for(int j=1; j<1+height; ++j){
            Reimage[j][width+1+i][0] = Imagedata[j-1][width-i-2][0];
        }
	}
	cout<<"continued"<<endl;
	Reimage[0][0][0] = Reimage[0][2][0];
	//Reimage[0][1][0] = Reimage[0][3][0];
	//Reimage[0][2][0] = Reimage[0][4][0];
	//Reimage[1][0][0] = Reimage[1][2][0];
	//Reimage[1][1][0] = Reimage[1][3][0];
	//Reimage[1][2][0] = Reimage[1][4][0];
	//Reimage[2][0][0] = Reimage[2][6][0];
	//Reimage[2][1][0] = Reimage[2][5][0];
	//Reimage[2][2][0] = Reimage[2][4][0];
	Reimage[0][width+1][0] = Reimage[0][width-1][0];
	//Reimage[0][width+3][0] = Reimage[0][width-1][0];
	//Reimage[0][width+5][0] = Reimage[0][width-1][0];
	//Reimage[1][width+2][0] = Reimage[1][width][0];
	//Reimage[1][width+3][0] = Reimage[1][width-1][0];
	//Reimage[1][width+5][0] = Reimage[1][width-1][0];
	//Reimage[2][width+3][0] = Reimage[2][width+1][0];
	//Reimage[2][width+4][0] = Reimage[2][width][0];
	//Reimage[2][width+5][0] = Reimage[2][width-1][0];
	Reimage[height+1][0][0] = Reimage[height+1][2][0];
	//Reimage[height+2][1][0] = Reimage[height+2][3][0];
	//Reimage[height+3][0][0] = Reimage[height+3][4][0];
	//Reimage[height+3][1][0] = Reimage[height+3][3][0];
	//Reimage[height+4][1][0] = Reimage[height+4][5][0];
	//Reimage[height+4][2][0] = Reimage[height+4][4][0];
	//Reimage[height+5][0][0] = Reimage[height+5][6][0];
	//Reimage[height+5][1][0] = Reimage[height+5][5][0];
	//Reimage[height+5][2][0] = Reimage[height+5][4][0];
	Reimage[height+1][width+1][0] = Reimage[height+1][width-1][0];
	//Reimage[height+2][width+3][0] = Reimage[height+2][width-1][0];
	//Reimage[height+3][width+2][0] = Reimage[height+3][width][0];
	//Reimage[height+3][width+3][0] = Reimage[height+3][width-1][0];
	//Reimage[height+4][width+4][0] = Reimage[height+4][width][0];
	//Reimage[height+4][width+5][0] = Reimage[height+4][width-1][0];
	//Reimage[height+5][width+3][0] = Reimage[height+5][width+1][0];
	//Reimage[height+5][width+4][0] = Reimage[height+5][width][0];
	//Reimage[height+5][width+5][0] = Reimage[height+5][width-1][0];

    for(int j=0; j<height; ++j){
        for(int i=0; i<width; ++i){
            Reimage[j+1][i+1][0] = Imagedata[j][i][0];
        }
    }
	// Read image (filename specified by first argument) into image data matrix	unsigned char denoiseImage[256][256][1];

	for(int i=0; i< height; ++i){
        for(int j=0; j<width; ++j){
            denoiseImage[i][j][0] = convolution(i,j,lin_filter,Reimage);
        }
	}
    if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(denoiseImage, sizeof(unsigned char), (height)*(width)*1, file);	fclose(file);
	return 0;

}

unsigned char convolution(int i, int j, float kernel[][3], unsigned char image[][258][1]){
    float pix = 0.0;
    for(int k=i; k<i+3; ++k){
        for(int l=j; l<j+3; ++l){
            pix+= (image[k][l][0] * kernel[k-i][l-j]);
            //cout<<pix<<endl;
        }
    }
    return (unsigned char)(pix/9);
}
