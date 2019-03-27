#include <stdio.h>
#include <algorithm>
#include <cmath>
unsigned char Reimage[260][260][3];
unsigned char denoise_Reimage[260][260][3];

double getGaussian(double kernal[][5]){
    double sigma = 5.0;
    double sum=0;

    for(int i= -2; i<=2 ; ++i){
        for(int j= -2; j<=2; ++j){
            kernal[i+2][j+2] = exp(-(i*i + j*j)/(2*sigma * sigma))/(sqrt((2*M_PI * sigma * sigma)));
            sum+=kernal[i+2][j+2];
        }
    }
    return sum;
}

unsigned char convolution(int i, int j, double kernel[][5], int channel,double sum){
    float pix = 0.0;
    for(int k=i; k<i+5; ++k){
        for(int l=j; l<j+5; ++l){
            pix+= (Reimage[k][l][channel] * kernel[k-i][l-j]);
            //cout<<pix<<endl;
        }
    }
    return (unsigned char)(pix/sum);
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

    int height = Size;
    int width = Size;

    if (!(file=fopen(argv[1],"rb"))) {



	for(int j=0; j<2; ++j){
        for(int i=2; i<2+width; ++i){
            Reimage[j][i][0] = Imagedata[2-j][i-2][0];
            Reimage[j][i][1] = Imagedata[2-j][i-2][1];
            Reimage[j][i][2] = Imagedata[2-j][i-2][2];
        }
	}
	cout<<"first"<<endl;
	for(int j=0; j<2; ++j){
        for(int i=2; i<2+width; ++i){
            Reimage[height+j+2][i][0] = Imagedata[height-j-2][i-2][0];
            Reimage[height+j+2][i][1] = Imagedata[height-j-2][i-2][1];
            Reimage[height+j+2][i][2] = Imagedata[height-j-2][i-2][2];
        }
	}
    cout<<"second"<<endl;
	for(int i=0; i<2; ++i){
        for(int j=2; j<2+height; ++j){
            Reimage[j][i][0] = Imagedata[j-2][2-i][0];
            Reimage[j][i][1] = Imagedata[j-2][2-i][1];
            Reimage[j][i][2] = Imagedata[j-2][2-i][2];
        }
	}

	for(int i=0; i<2; ++i){
        for(int j=2; j<2+height; ++j){
            Reimage[j][width+2+i][0] = Imagedata[j-2][width-i-2][0];
            Reimage[j][width+2+i][1] = Imagedata[j-2][width-i-2][1];
            Reimage[j][width+2+i][2] = Imagedata[j-2][width-i-2][2];
        }
	}
	cout<<"continued"<<endl;
	Reimage[0][0][0] = Reimage[0][4][0];
	Reimage[0][1][0] = Reimage[0][3][0];
	Reimage[0][0][1] = Reimage[0][4][1];
	Reimage[0][1][1] = Reimage[0][3][1];
	Reimage[0][0][2] = Reimage[0][4][2];
	Reimage[0][1][2] = Reimage[0][3][2];

	Reimage[1][0][0] = Reimage[1][4][0];
	Reimage[1][1][0] = Reimage[1][3][0];
	Reimage[1][0][1] = Reimage[1][4][1];
	Reimage[1][1][1] = Reimage[1][3][1];
	Reimage[1][0][2] = Reimage[1][4][2];
	Reimage[1][1][2] = Reimage[1][3][2];

	Reimage[0][width+2][0] = Reimage[0][width][0];
	Reimage[0][width+3][0] = Reimage[0][width-1][0];
	Reimage[0][width+2][1] = Reimage[0][width][1];
	Reimage[0][width+3][1] = Reimage[0][width-1][1];
	Reimage[0][width+2][2] = Reimage[0][width][2];
	Reimage[0][width+3][2] = Reimage[0][width-1][2];

	Reimage[1][width+2][0] = Reimage[1][width][0];
	Reimage[1][width+3][0] = Reimage[1][width-1][0];
	Reimage[1][width+2][1] = Reimage[1][width][1];
	Reimage[1][width+3][1] = Reimage[1][width-1][1];
	Reimage[1][width+2][2] = Reimage[1][width][2];
	Reimage[1][width+3][2] = Reimage[1][width-1][2];

	Reimage[height+2][0][0] = Reimage[height+2][4][0];
	Reimage[height+2][1][0] = Reimage[height+2][3][0];
	Reimage[height+3][0][0] = Reimage[height+3][4][0];
	Reimage[height+3][1][0] = Reimage[height+3][3][0];
	Reimage[height+2][0][1] = Reimage[height+2][4][1];
	Reimage[height+2][1][1] = Reimage[height+2][3][1];
	Reimage[height+3][0][1] = Reimage[height+3][4][1];
	Reimage[height+3][1][1] = Reimage[height+3][3][1];
	Reimage[height+2][0][2] = Reimage[height+2][4][2];
	Reimage[height+2][1][2] = Reimage[height+2][3][2];
	Reimage[height+3][0][2] = Reimage[height+3][4][2];
	Reimage[height+3][1][2] = Reimage[height+3][3][2];

	Reimage[height+2][width+2][0] = Reimage[height+2][width][0];
	Reimage[height+2][width+3][0] = Reimage[height+2][width-1][0];
	Reimage[height+3][width+2][0] = Reimage[height+3][width][0];
	Reimage[height+3][width+3][0] = Reimage[height+3][width-1][0];
	Reimage[height+2][width+2][1] = Reimage[height+2][width][1];
	Reimage[height+2][width+3][1] = Reimage[height+2][width-1][1];
	Reimage[height+3][width+2][1] = Reimage[height+3][width][1];
	Reimage[height+3][width+3][1] = Reimage[height+3][width-1][1];
	Reimage[height+2][width+2][2] = Reimage[height+2][width][2];
	Reimage[height+2][width+3][2] = Reimage[height+2][width-1][2];
	Reimage[height+3][width+2][2] = Reimage[height+3][width][2];
	Reimage[height+3][width+3][2] = Reimage[height+3][width-1][2];


    for(int j=0; j<height; ++j){
        for(int i=0; i<width; ++i){
            Reimage[j+2][i+2][0] = Imagedata[j][i][0];
            Reimage[j+2][i+2][1] = Imagedata[j][i][1];
            Reimage[j+2][i+2][2] = Imagedata[j][i][2];
        }
    }


	double kernal[5][5];
	double sum = getGaussian(kernal);

    for(int i=0; i< height; ++i){
        for(int j=0; j<width; ++j){
            denoiseImage[i][j][0] = median(i,j,0);
            denoiseImage[i][j][1] = median(i,j,1);
            denoiseImage[i][j][2] = median(i,j,2);
        }
	}

    //Reimage for next filter

    for(int j=0; j<2; ++j){
        for(int i=2; i<2+width; ++i){
            denoise_Reimage[j][i][0] = denoiseImage[2-j][i-2][0];
            denoise_Reimage[j][i][1] = denoiseImage[2-j][i-2][1];
            denoise_Reimage[j][i][2] = denoiseImage[2-j][i-2][2];
        }
	}
	cout<<"first"<<endl;
	for(int j=0; j<2; ++j){
        for(int i=2; i<2+width; ++i){
            denoise_Reimage[height+j+2][i][0] = denoiseImage[height-j-2][i-2][0];
            denoise_Reimage[height+j+2][i][1] = denoiseImage[height-j-2][i-2][1];
            denoise_Reimage[height+j+2][i][2] = denoiseImage[height-j-2][i-2][2];
        }
	}
    cout<<"second"<<endl;
	for(int i=0; i<2; ++i){
        for(int j=2; j<2+height; ++j){
            denoise_Reimage[j][i][0] = denoiseImage[j-2][2-i][0];
            denoise_Reimage[j][i][1] = denoiseImage[j-2][2-i][1];
            denoise_Reimage[j][i][2] = denoiseImage[j-2][2-i][2];
        }
	}

	for(int i=0; i<2; ++i){
        for(int j=2; j<2+height; ++j){
            denoise_Reimage[j][width+2+i][0] = denoiseImage[j-2][width-i-2][0];
            denoise_Reimage[j][width+2+i][1] = denoiseImage[j-2][width-i-2][1];
            denoise_Reimage[j][width+2+i][2] = denoiseImage[j-2][width-i-2][2];
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
            denoise_Reimage[j+2][i+2][0] = denoiseImage[j][i][0];
            denoise_Reimage[j+2][i+2][1] = denoiseImage[j][i][1];
            denoise_Reimage[j+2][i+2][2] = denoiseImage[j][i][2];
        }
    }
    unsigned char OutputImage[256][256][3];
	for(int i=2; i< height+2; ++i){
        for(int j=2; j<width+2; ++j){
            cout<< "run"<<endl;
            OutputImage[i-2][j-2][0] = convolution(i,j,kernal,0,sum);
            OutputImage[i-2][j-2][1] = convolution(i,j,kernal,1,sum);
            OutputImage[i-2][j-2][2] = convolution(i,j,kernal,2,sum);
        }
	}
    if (!(file=fopen(argv[2],"wb"))) {
    cout<<"written"<<endl;

}
