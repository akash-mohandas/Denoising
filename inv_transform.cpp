#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <algorithm>
#include <cmath>using namespace std;
int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size = 256;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4){		BytesPerPixel = 1; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5){			Size = atoi(argv[4]);		}	}
    int height = Size;
    int width = Size;
    //float linear_filter[5][5] = {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}};
    //float lin_filter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
    //float linear_fil[7][7] = {{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1}};	// Allocate image data array	unsigned char Imagedata[height][width][BytesPerPixel];
    if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);	fclose(file);

	unsigned char OutputImage [256][256][1];

	for(int i=0; i<256; ++i){
        for( int j=0; j< 256; ++j){
            OutputImage[i][j][0] = (unsigned char) (pow(Imagedata[i][j][0]/2.0,2) - 3/8.0);
        }
	}
     if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(OutputImage, sizeof(unsigned char), (height)*(width)*1, file);	fclose(file);
	return 0;
}
