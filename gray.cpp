#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>


using namespace cv;
using namespace std;

int main(){

	FILE *fp1;

    fp1 = fopen("/home/socmgr/workspcae/week6/1/conv2.txt","r"); ///home/socmgr/work/Untitled Folder/
    
    int i,j,k,l;
    
    double ****conv2_weight;
     
    conv2_weight = (double ****)malloc(50*sizeof(double***));
   
	for(i=0; i<50; i++){
		*(conv2_weight+i) = (double***)malloc(20*sizeof(double**));
		for(j=0; j<20; j++){
			*(*(conv2_weight+i)+j) = (double**)malloc(5*sizeof(double*));
			for(k=0; k<5; k++){
				*(*(*(conv2_weight+i)+j)+k) = (double*)malloc(5*sizeof(double));
			}
		}
	}

	for( i = 0 ; i<50 ; i++){
		for( j = 0 ; j<20 ; j++){
			for( k = 0 ; k<5 ; k++){
				for( l=0 ; l<5 ; l++){
					fscanf(fp1, "%lf, ", &conv2_weight[i][j][k][l]);
					printf("%.5lf ", conv2_weight[i][j][k][l]);
				}
			}
		}
	}

	for(i=0; i<50; i++){
		 for(j=0; j<20; j++){
			for(k=0; k<5; k++){
				free(*(*(*(conv2_weight+i)+j)+k));		
			}
			free(*(*(conv2_weight+i)+j));
		}
		free(*(conv2_weight+i));
	}
	free(conv2_weight);

/*
    FILE *fp1;

    fp1 = fopen("/home/socmgr/workspcae/week6/conv1_weight.txt","r"); ///home/socmgr/work/Untitled Folder/
 
    for( i = 0 ; i<20 ; i++){
		for( j = 0 ; j<1 ; j++){
			for( k = 0 ; k<5 ; k++){
				for( l=0 ; l<5 ; l++){
					fscanf(fp1, "%lf, ", &conv1_weight[i][j][k][l]);
					printf("%.5lf ", conv1_weight[i][j][k][l]);
				}
			}
		}
	}
    
    for(i=0; i<20; i++){
		 for(j=0; j<1; j++){
			for(k=0; k<5; k++){
				free(*(*(*(conv1_weight+i)+j)+k));		
			}
			free(*(*(conv1_weight+i)+j));
		}
		free(*(conv1_weight+i));
	}
	free(conv1_weight);


///////////결과확인
Mat result(12,12,0);

	for(k=0;k<20;k++){
		for(x=0;x<12;x++){
			for(y=0;y<12;y++){
				result.at<uchar>(x,y) = pool1Result[k][x][y];
			}
		}
	}
    imwrite("test.png", result);
	*/
    return 0;
}


    
