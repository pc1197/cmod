#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "conv.h"
#include "filter.h"
#include "input.h"
#include "memoryFree.h"
#include "maxpool.h"

int main()
{
    double ***input;
    double ****conv1filter;
    double ***conv1Result;
    double ***pool1Result;
    double ****conv2filter;
    double ***conv2Result;
    double ***pool2Result;
    double filter1[500][800] = {};
    double filter2[] = {};
    double filter3[10][500] = {}; 
    double outputip1[] = {};
    double outputip2[] = {};

    int k,m,n,i,j,x,y,l;

    FILE *fp1;
    FILE *fp2;
    FILE *fp3;
    FILE *fp4;

    fp1 = fopen("/home/socmgr/caffe/python/conv1_weight.txt","r"); 
    fp2 = fopen("/home/socmgr/caffe/python/conv2_weight.txt","r"); 
    fp3 = fopen("/home/socmgr/caffe/python/fully1_weight.txt","r");
    fp4 = fopen("/home/socmgr/caffe/python/fully2_weight.txt","r");

//layer1 
    input = inputMatrix(1, 28, 28);
//layer1 end
//layer2 conv1
    conv1filter = filter(20, 1, 5, 5);
    for( i = 0 ; i<20 ; i++){
		for( j = 0 ; j<1 ; j++){
			for( k = 0 ; k<5 ; k++){
				for( l=0 ; l<5 ; l++){
					fscanf(fp1, "%lf", &conv1filter[i][j][k][l]);
				}
			}
		}
	}
    conv1Result = convolution(20, 1, 24, 24, 5, 1, input, conv1filter);//out_cha,channel,o_size_rows,o_size_cols,filter_size,stride,***input,****filter
//layer2 end
//layer3
    pool1Result = pooling(20, 12 ,12 ,2 ,2, conv1Result);//(channel, out_rowsize, out_colsize , filter_size, stride, ***input)
//layer3 end
//layer4    
    conv2filter = filter(50, 20, 5, 5);
    for(int z = 0 ; z<50 ; z++){
		for(int c = 0 ; c<20 ; c++){
			for(int v = 0 ; v<5 ; v++){
				for(int b=0 ; b<5 ; b++){
					fscanf(fp2, "%lf", &conv2filter[z][c][v][b]);
				}
			}
		}
	}
    conv2Result = convolution(50, 20, 8, 8, 5, 1,pool1Result,conv2filter);//out_cha,channel,o_size_rows,o_size_cols,filter_size,stride,***input,****filter
//layer4 end
//layer5
    pool2Result = pooling(50,4,4,2,2,conv2Result);//(channel, out_rowsize, out_colsize , filter_size, stride, ***input)
//layer5 end
//출력
    for(int j=0; j<50; j++)
    {
        for(int k=0; k<4; k++)
        {
            for(int l=0; l<4; l++)
            {
               // printf("%.3lf ",pool2Result[j][k][l]);
            }
        }
      //  printf("\n");
    }
//fully
    for(int i=0; i<50; i++)
    {
        for(int j=0; j<4; j++)
        {
            for(int k=0; k<4; k++)
            {
                filter2[i*4*4+j*4+k] = pool2Result[i][j][k];
            }
        }
    }


    for(int i=0; i<500; i++)
    {
        for(int j=0; j<800; j++)
        {
            fscanf(fp3, "%lf", &filter1[i][j]);
        }
    }

    for(int i=0; i<500; i++)
    {
        for(int j=0; j<800; j++)
        {
            outputip1[i] += filter2[j] * filter1[i][j];
        }
    }

    for(int i=0; i<800; i++)
    {
        if(outputip1[i] < 0)
        {
            outputip1[i] = 0;
        } 
        else outputip1[i];
    }

    for(int i=0; i<10; i++)
    {
        for(int j=0; j<500; j++)
        {
            fscanf(fp4, "%lf", &filter3[i][j]);
        }
    }

    for(int i=0; i<10; i++)
    {
        for(int j=0; j<500; j++)
        {
            outputip2[i] += outputip1[j] * filter3[i][j];
        }
    }
    
    for(int i=0; i<10; i++)
    {
        printf("%d: %lf\n",i, outputip2[i]);
    }


            /*double temp=0;
            for(int j=0;j<500;j++)
            {
            for(int i=0;i<800;i++)
            {
            fscanf(fp3, "%lf", &filter2[i*800+j]);
            printf("%.17lf ",filter2[i*800+j]);
            }
            }*/
    memoryFree3d(1, 28, input);//int channel, int rowsize, double ***input
    memoryFree4d(20, 1, 5, conv1filter);//int quantity, int channel, int rowsize, double ****input
    memoryFree3d(20, 24, conv1Result);//int channel, int rowsize, double ***input
    memoryFree3d(20, 12, pool1Result);//int channel, int rowsize, double ***input
    memoryFree4d(50, 20, 5, conv2filter);//int quantity, int channel, int rowsize, double ****input
    memoryFree3d(50 , 8, conv2Result);//int channel, int rowsize, double ***input
    memoryFree3d(50, 4, pool2Result);//int channel, int rowsize, double ***input */
    return 0;
    
}