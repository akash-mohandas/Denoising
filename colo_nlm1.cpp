#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <algorithm>
#include <cmath>using namespace std;

unsigned char Reimage[282][282][3];
unsigned char denoise_Reimage[260][260][3];


double getWeights(int k, int l, int i, int j,int channel){
    double dist;
    double sum = 0.0;
    double G;
    double a= 5.0;
    for(int n1=-3; n1<=3; ++n1){
        for(int n2=-3; n2<=3; ++n2){
            G = exp(-(n1* n1 + n2 *n2)/(2*a*a))/(sqrt(2*M_PI * a*a));
            dist = pow((Reimage[n1+i][n2+j][channel] - Reimage[n1+k][n2+l][channel]),2);
            sum+= (G * dist);
        }
    }
    return sum;
}

unsigned char nlm(int i, int j, int channel){
    double sum = 0.0;
    double w ;
    double h = 15.0;
    //double sigma_s = 10;
    double pix = 0.0;
    for(int N1 = i-10; N1<=i+10; ++N1){
        for(int M1=j-10; M1<=j+10; ++M1){
                w = getWeights(N1,M1,i,j,channel);
                w = exp(-w/(h*h));
                pix+= (Reimage[N1][M1][channel] * w);
                sum+=w;
        }
    }
    return (unsigned char)round(pix/sum);
}

unsigned char median(int i, int j, int channel){
    int arr[25];
    int p=0;
    for (int k= -2; k<=2; ++k){
        for(int l= -2; l<= 2; ++l){
            arr[p] = (int) denoise_Reimage[i+k][j+l][channel];
            //cout<<arr[p]<<endl;
            p+=1;
        }
    }

    sort(arr,arr+25);

    return (unsigned char) arr[12];
}

int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size = 256;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4){		BytesPerPixel = 3; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5){			Size = atoi(argv[4]);		}	}
    int height = Size;
    int width = Size;
    //double linear_filter[5][5] = {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}};
    //double lin_filter[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
    //float linear_fil[7][7] = {{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1},{1,1,1,1,1,1,1}};	// Allocate image data array	unsigned char Imagedata[height][width][BytesPerPixel];
    if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);	fclose(file);

	//double kernal[5][5];
	//double sum = getGaussian(kernal);

    //unsigned char Reimage[260][260][1];

    for(int j=0; j<2; ++j){
        for(int i=2; i<2+width; ++i){
            denoise_Reimage[j][i][0] = Imagedata[2-j][i-2][0];
            denoise_Reimage[j][i][1] = Imagedata[2-j][i-2][1];
            denoise_Reimage[j][i][2] = Imagedata[2-j][i-2][2];
        }
	}
	cout<<"first"<<endl;
	for(int j=0; j<2; ++j){
        for(int i=2; i<2+width; ++i){
            denoise_Reimage[height+j+2][i][0] = Imagedata[height-j-2][i-2][0];
            denoise_Reimage[height+j+2][i][1] = Imagedata[height-j-2][i-2][1];
            denoise_Reimage[height+j+2][i][2] = Imagedata[height-j-2][i-2][2];
        }
	}
    cout<<"second"<<endl;
	for(int i=0; i<2; ++i){
        for(int j=2; j<2+height; ++j){
            denoise_Reimage[j][i][0] = Imagedata[j-2][2-i][0];
            denoise_Reimage[j][i][1] = Imagedata[j-2][2-i][1];
            denoise_Reimage[j][i][2] = Imagedata[j-2][2-i][2];
        }
	}

	for(int i=0; i<2; ++i){
        for(int j=2; j<2+height; ++j){
            denoise_Reimage[j][width+2+i][0] = Imagedata[j-2][width-i-2][0];
            denoise_Reimage[j][width+2+i][1] = Imagedata[j-2][width-i-2][1];
            denoise_Reimage[j][width+2+i][2] = Imagedata[j-2][width-i-2][2];
        }
	}
	cout<<"continued"<<endl;
	denoise_Reimage[0][0][0] = denoise_Reimage[0][4][0];
	denoise_Reimage[0][1][0] = denoise_Reimage[0][3][0];
	denoise_Reimage[0][0][1] = denoise_Reimage[0][4][1];
	denoise_Reimage[0][1][1] = denoise_Reimage[0][3][1];
	denoise_Reimage[0][0][2] = denoise_Reimage[0][4][2];
	denoise_Reimage[0][1][2] = denoise_Reimage[0][3][2];

	denoise_Reimage[1][0][0] = denoise_Reimage[1][4][0];
	denoise_Reimage[1][1][0] = denoise_Reimage[1][3][0];
	denoise_Reimage[1][0][1] = denoise_Reimage[1][4][1];
	denoise_Reimage[1][1][1] = denoise_Reimage[1][3][1];
	denoise_Reimage[1][0][2] = denoise_Reimage[1][4][2];
	denoise_Reimage[1][1][2] = denoise_Reimage[1][3][2];

	denoise_Reimage[0][width+2][0] = denoise_Reimage[0][width][0];
	denoise_Reimage[0][width+3][0] = denoise_Reimage[0][width-1][0];
	denoise_Reimage[0][width+2][1] = denoise_Reimage[0][width][1];
	denoise_Reimage[0][width+3][1] = denoise_Reimage[0][width-1][1];
	denoise_Reimage[0][width+2][2] = denoise_Reimage[0][width][2];
	denoise_Reimage[0][width+3][2] = denoise_Reimage[0][width-1][2];

	denoise_Reimage[1][width+2][0] = denoise_Reimage[1][width][0];
	denoise_Reimage[1][width+3][0] = denoise_Reimage[1][width-1][0];
	denoise_Reimage[1][width+2][1] = denoise_Reimage[1][width][1];
	denoise_Reimage[1][width+3][1] = denoise_Reimage[1][width-1][1];
	denoise_Reimage[1][width+2][2] = denoise_Reimage[1][width][2];
	denoise_Reimage[1][width+3][2] = denoise_Reimage[1][width-1][2];

	denoise_Reimage[height+2][0][0] = denoise_Reimage[height+2][4][0];
	denoise_Reimage[height+2][1][0] = denoise_Reimage[height+2][3][0];
	denoise_Reimage[height+3][0][0] = denoise_Reimage[height+3][4][0];
	denoise_Reimage[height+3][1][0] = denoise_Reimage[height+3][3][0];
	denoise_Reimage[height+2][0][1] = denoise_Reimage[height+2][4][1];
	denoise_Reimage[height+2][1][1] = denoise_Reimage[height+2][3][1];
	denoise_Reimage[height+3][0][1] = denoise_Reimage[height+3][4][1];
	denoise_Reimage[height+3][1][1] = denoise_Reimage[height+3][3][1];
	denoise_Reimage[height+2][0][2] = denoise_Reimage[height+2][4][2];
	denoise_Reimage[height+2][1][2] = denoise_Reimage[height+2][3][2];
	denoise_Reimage[height+3][0][2] = denoise_Reimage[height+3][4][2];
	denoise_Reimage[height+3][1][2] = denoise_Reimage[height+3][3][2];

	denoise_Reimage[height+2][width+2][0] = denoise_Reimage[height+2][width][0];
	denoise_Reimage[height+2][width+3][0] = denoise_Reimage[height+2][width-1][0];
	denoise_Reimage[height+3][width+2][0] = denoise_Reimage[height+3][width][0];
	denoise_Reimage[height+3][width+3][0] = denoise_Reimage[height+3][width-1][0];
	denoise_Reimage[height+2][width+2][1] = denoise_Reimage[height+2][width][1];
	denoise_Reimage[height+2][width+3][1] = denoise_Reimage[height+2][width-1][1];
	denoise_Reimage[height+3][width+2][1] = denoise_Reimage[height+3][width][1];
	denoise_Reimage[height+3][width+3][1] = denoise_Reimage[height+3][width-1][1];
	denoise_Reimage[height+2][width+2][2] = denoise_Reimage[height+2][width][2];
	denoise_Reimage[height+2][width+3][2] = denoise_Reimage[height+2][width-1][2];
	denoise_Reimage[height+3][width+2][2] = denoise_Reimage[height+3][width][2];
	denoise_Reimage[height+3][width+3][2] = denoise_Reimage[height+3][width-1][2];


    for(int j=0; j<height; ++j){
        for(int i=0; i<width; ++i){
            denoise_Reimage[j+2][i+2][0] = Imagedata[j][i][0];
            denoise_Reimage[j+2][i+2][1] = Imagedata[j][i][1];
            denoise_Reimage[j+2][i+2][2] = Imagedata[j][i][2];
        }
    }
    unsigned char OutputImage[256][256][3];
	for(int i=2; i< height+2; ++i){
        for(int j=2; j<width+2; ++j){
            cout<< "run"<<endl;
            OutputImage[i-2][j-2][0] = median(i,j,0);
            OutputImage[i-2][j-2][1] = median(i,j,1);
            OutputImage[i-2][j-2][2] = median(i,j,2);
        }
	}



    // Next part
	for(int j=0; j<13; ++j){
        for(int i=13; i<13+width; ++i){
            Reimage[j][i][0] = OutputImage[13-j][i-13][0];
            Reimage[j][i][1] = OutputImage[13-j][i-13][1];
            Reimage[j][i][2] = OutputImage[13-j][i-13][2];
        }
	}
	cout<<"first"<<endl;
	for(int j=0; j<13; ++j){
        for(int i=13; i<13+width; ++i){
            Reimage[height+j+13][i][0] = OutputImage[height-j-2][i-13][0];
            Reimage[height+j+13][i][1] = OutputImage[height-j-2][i-13][1];
            Reimage[height+j+13][i][2] = OutputImage[height-j-2][i-13][2];
        }
	}
    cout<<"second"<<endl;
	for(int i=0; i<13; ++i){
        for(int j=13; j<13+height; ++j){
            Reimage[j][i][0] = OutputImage[j-13][13-i][0];
            Reimage[j][i][1] = OutputImage[j-13][13-i][1];
            Reimage[j][i][2] = OutputImage[j-13][13-i][2];
        }
	}

	for(int i=0; i<13; ++i){
        for(int j=13; j<13+height; ++j){
            Reimage[j][width+13+i][0] = OutputImage[j-13][width-i-2][0];
            Reimage[j][width+13+i][1] = OutputImage[j-13][width-i-2][1];
            Reimage[j][width+13+i][2] = OutputImage[j-13][width-i-2][2];
        }
	}
	cout<<"continued"<<endl;

	for(int i=0; i<13;++i){
        for(int j=0; j< 13; ++j){
            Reimage[i][j][0] = Reimage[i][26-j][0];
            Reimage[i][j][1] = Reimage[i][26-j][1];
            Reimage[i][j][2] = Reimage[i][26-j][2];
        }
	}
	for(int i=0; i< 13; ++i){
        for(int j= width+13; j< width+26; ++j){
            Reimage[i][j][0] = Reimage[i][width+24-(j-width)][0];
            Reimage[i][j][1] = Reimage[i][width+24-(j-width)][1];
            Reimage[i][j][2] = Reimage[i][width+24-(j-width)][2];
        }
	}
	for(int i=height+13; i< height+26; ++i){
        for(int j=0; j< 13; ++j){
            Reimage[i][j][0] = Reimage[i][26-j][0];
            Reimage[i][j][1] = Reimage[i][26-j][1];
            Reimage[i][j][2] = Reimage[i][26-j][2];
        }
	}
	for(int i=height+13; i< height+26; ++i){
        for(int j=width+13; j<width+26; ++j){
            Reimage[i][j][0] = Reimage[i][width+24-(j-width)][0];
            Reimage[i][j][1] = Reimage[i][width+24-(j-width)][1];
            Reimage[i][j][2] = Reimage[i][width+24-(j-width)][2];
        }
	}

    for(int j=0; j<height; ++j){
        for(int i=0; i<width; ++i){
            Reimage[j+13][i+13][0] = OutputImage[j][i][0];
            Reimage[j+13][i+13][1] = OutputImage[j][i][1];
            Reimage[j+13][i+13][2] = OutputImage[j][i][2];
        }
    }
	// Read image (filename specified by first argument) into image data matrix	unsigned char denoiseImage[256][256][3];

	for(int i=13; i< height+13; ++i){
        for(int j=13; j<width+13; ++j){
            denoiseImage[i-13][j-13][0] = nlm(i,j,0);
            denoiseImage[i-13][j-13][1] = nlm(i,j,1);
            denoiseImage[i-13][j-13][2] = nlm(i,j,2);
        }
	}

	//Reimage for next filter



    if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(denoiseImage, sizeof(unsigned char), (height)*(width)*3, file);	fclose(file);
	return 0;

}


