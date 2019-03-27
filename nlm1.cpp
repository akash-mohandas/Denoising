#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <algorithm>
#include <cmath>using namespace std;

unsigned char Reimage[282][282][1];

double getWeights(int k, int l, int i, int j){
    double dist;
    double sum = 0.0;
    double G;
    double a= 100.0;
    for(int n1=-3; n1<=3; ++n1){
        for(int n2=-3; n2<=3; ++n2){
            G = exp(-(n1* n1 + n2 *n2)/(2*a*a))/(sqrt(2*M_PI * a*a));
            dist = pow((Reimage[n1+i][n2+j][0] - Reimage[n1+k][n2+l][0]),2);
            sum+= (G * dist);
        }
    }
    return sum;
}

unsigned char nlm(int i, int j){
    double sum = 0.0;
    double w ;
    double h = 15.0;
    //double sigma_s = 10;
    double pix = 0.0;
    for(int N1 = i-10; N1<=i+10; ++N1){
        for(int M1=j-10; M1<=j+10; ++M1){
                w = getWeights(N1,M1,i,j);
                w = exp(-w/(h*h));
                pix+= (Reimage[N1][M1][0] * w);
                sum+=w;
        }
    }
    return (unsigned char)round(pix/sum);
}

int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size = 256;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4){		BytesPerPixel = 1; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5){			Size = atoi(argv[4]);		}	}
    int height = Size;
    int width = Size;
    //double linear_filter[5][5] = {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}};
    //double lin_filter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
    //float linear_fil[7][7] = {{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1}};	// Allocate image data array	unsigned char Imagedata[height][width][BytesPerPixel];
    if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);	fclose(file);

	//double kernal[5][5];
	//double sum = getGaussian(kernal);

    //unsigned char Reimage[260][260][1];
	for(int j=0; j<13; ++j){
        for(int i=13; i<13+width; ++i){
            Reimage[j][i][0] = Imagedata[13-j][i-13][0];
        }
	}
	cout<<"first"<<endl;
	for(int j=0; j<13; ++j){
        for(int i=13; i<13+width; ++i){
            Reimage[height+j+13][i][0] = Imagedata[height-j-2][i-13][0];
        }
	}
    cout<<"second"<<endl;
	for(int i=0; i<13; ++i){
        for(int j=13; j<13+height; ++j){
            Reimage[j][i][0] = Imagedata[j-13][13-i][0];
        }
	}

	for(int i=0; i<13; ++i){
        for(int j=13; j<13+height; ++j){
            Reimage[j][width+13+i][0] = Imagedata[j-13][width-i-2][0];
        }
	}
	cout<<"continued"<<endl;

	for(int i=0; i<13;++i){
        for(int j=0; j< 13; ++j){
            Reimage[i][j][0] = Reimage[i][26-j][0];
        }
	}
	for(int i=0; i< 13; ++i){
        for(int j= width+13; j< width+26; ++j){
            Reimage[i][j][0] = Reimage[i][width+24-(j-width)][0];
        }
	}
	for(int i=height+13; i< height+26; ++i){
        for(int j=0; j< 13; ++j){
            Reimage[i][j][0] = Reimage[i][26-j][0];
        }
	}
	for(int i=height+13; i< height+26; ++i){
        for(int j=width+13; j<width+26; ++j){
            Reimage[i][j][0] = Reimage[i][width+24-(j-width)][0];
        }
	}

    for(int j=0; j<height; ++j){
        for(int i=0; i<width; ++i){
            Reimage[j+13][i+13][0] = Imagedata[j][i][0];
        }
    }
	// Read image (filename specified by first argument) into image data matrix	unsigned char denoiseImage[256][256][1];

	for(int i=13; i< height+13; ++i){
        for(int j=13; j<width+13; ++j){
            denoiseImage[i-13][j-13][0] = nlm(i,j);
        }
	}
    if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(denoiseImage, sizeof(unsigned char), (height)*(width)*1, file);	fclose(file);
	return 0;

}


