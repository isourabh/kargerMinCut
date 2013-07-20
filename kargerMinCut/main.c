//
//  main.c
//  kargerMinCut
//
//  Created by Yang YanQing on 13-7-20.
//  Copyright (c) 2013年 Yang YanQing. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{
    FILE *fp;
    int x[200][200]={0};
    int x_num[200] = {0};
    if((fp=fopen("kargerMinCut.txt","r"))==NULL) /* 打开一个由argv[1]所指的文件*/
    {
        printf("not open");
        exit(0);
    }
    for (int i = 0 ; i < 200 ; i ++) {
        int temp;
        char ch;
        fscanf(fp, "%d",&temp);
        ch = fgetc(fp);

        if (temp != i+1) {
            printf("error\n");
        }
        printf("%d \n",temp);
        
        while ( '\r' != (ch = fgetc(fp))) {
            fseek(fp, -1, 1);
            fscanf(fp, "%d",&temp);
            x[i][ x_num[i] ] = temp-1;
            x_num[i] ++;
            ch = fgetc(fp);
            printf("%d ",temp);
        }
        printf("\n");
    }
    fclose(fp);

    return 0;
}

