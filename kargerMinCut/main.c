//
//  main.c
//  kargerMinCut
//
//  Created by Yang YanQing on 13-7-20.
//  Copyright (c) 2013年 Yang YanQing. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define vertices 200
//#define DDD 0
//#define DDD1 0

int main(int argc, const char * argv[])
{
    time_t t;
    srand((unsigned) time(&t));
    FILE *fp;
    int x[vertices][vertices]={0};
    int x_num[vertices] = {0};
    if((fp=fopen("kargerMinCut.txt","r"))==NULL) /* 打开一个由argv[1]所指的文件*/
    {
        printf("not open\n");
        exit(0);
    }
    for (int i = 0 ; i < vertices ; i ++) {
        int temp;
        char ch;
        fscanf(fp, "%d",&temp);
        ch = fgetc(fp);
        
        if (temp != i+1) {
            printf("error\n");
        }
        //while ( '\n' != (ch = fgetc(fp))) {
        while ( '\r' != (ch = fgetc(fp))) {
            fseek(fp, -1, 1);
            fscanf(fp, "%d",&temp);
            x[i][ x_num[i] ] = temp-1;
            x_num[i] ++;
            ch = fgetc(fp);
        }
    }
    fclose(fp);
    int matrix_original[vertices][vertices]={0};
    int matrix[vertices][vertices];
    //    int matrix[vertices][vertices] = {0};
    
    //put matrix to matrix_original
    for (int i = 0 ; i < vertices ; i ++) {
        for (int j = 0; j < x_num[i] ; j ++) {
            matrix_original[i][ x[i][j] ] = 1;
        }
    }
    
    int times = vertices * vertices ;
    int small_answer = vertices;
    
    while ( times -- > 0 ) {
        memset(matrix, 0, vertices*vertices*4 );
        for (int i = 0; i < vertices; i ++) {
            for (int j = 0 ; j < vertices; j ++) {
                matrix[i][j] = matrix_original[i][j];
            }
        }
        
        
#ifdef DDD
        for (int i = 0; i < vertices; i ++) {
            for (int j = 0; j < vertices; j ++) {
                printf("%d ",matrix[i][j]);
            }
            printf("\n");
        }
#endif

        
        for (int i = 0 ; i < vertices -2 ; i ++) {

            int small = rand()%(vertices-i);
            int big = rand()%(vertices-i);
            while (big == small || matrix[big][small] == 0) {
                big ++;
                big = big%(vertices-i);
            }
            if (small > big) {
                int temp = small;
                small= big;
                big=temp;
            }
#ifdef DDD1
            printf("small :%d  big:%d\n",small,big);
#endif
            matrix[big][small]=0;
            matrix[big][big]=0;
            matrix[small][big]=0;
            matrix[small][small]=0;
            
            for (int column = 0 ; column < vertices-i ; column ++) {
                matrix[small][column] += matrix[big][column];
                matrix[column][small] = matrix[small][column];
            }
            
            
#ifdef DDD
            printf("ouput merger \n");
            for (int temp1 = 0 ; temp1 < vertices-i; temp1 ++) {
                for (int temp2 = 0 ; temp2 < vertices-i ; temp2 ++) {
                    printf("%d ",matrix[temp1][temp2]);
                }
                printf("\n");
            }
#endif
            
            
            for (int column = 0; column < vertices-i ; column ++) {
                matrix[big][column] =  matrix[vertices-i-1][column];
                matrix[column][big] = matrix[column][vertices-1-i];
            }
            
            
#ifdef DDD
            printf("ouput swap \n");
            for (int temp1 = 0 ; temp1 < vertices-1-i; temp1 ++) {
                for (int temp2 = 0 ; temp2 < vertices-1-i ; temp2 ++) {
                    printf("%d ",matrix[temp1][temp2]);
                }
                printf("\n");
            }
#endif
        }
        if (matrix[0][1] < small_answer) {
            small_answer = matrix[0][1];
        }
        printf("times %d :this: %d small answer is %d\n",times ,matrix[0][1],small_answer);
        if (matrix[0][1] < 0) {
            printf("wrong number\n");
            break;
        }
    }
    printf("final answer is %d\n" ,small_answer);
    return 0;
}

