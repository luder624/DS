#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define INPUT_FILE "input_2.txt"
#define OUTPUT_FILE "output_2.txt"


FILE *fin,*fout;
int mapnum,N,G;//map總數、size of arrays、evolution generation 
int i,j,k;
const int num = 2;


int main() {
	
	if(!((fout = fopen(OUTPUT_FILE, "r")) == NULL)) {
		fclose(fin);
		printf("File %s has already existed! Overwrite?[Y/n] ", OUTPUT_FILE);
		char Overwrite[10];
		gets(Overwrite);
		int i = 0;
		while(isspace(Overwrite[i])) {
			i++;
		}
		if(!(Overwrite[i] == 'y' || Overwrite[i] == 'Y')) {
			exit(EXIT_SUCCESS);
		}
	}

	
	// input file opened with mode "r"
	if((fin = fopen(INPUT_FILE, "r")) == NULL) {
		printf("Fail to open file %s!", INPUT_FILE);
		exit(EXIT_FAILURE);
	}
	
	// output file opened with mode "w"
	fout = fopen(OUTPUT_FILE, "w");
	
	fscanf(fin,"%d",&mapnum);
	//printf("%d\n",mapnum);
	
	
	for(i=0;i<mapnum;i++){
		
		fscanf(fin,"%d",&N);
		fscanf(fin,"%d",&G);
		
		int map1[N][N]; // = (int(*)[N])malloc(N*N*sizeof(int));//動態建立二維陣列 
		int map2[N][N]; // = (int(*)[N])malloc(N*N*sizeof(int));//一個存當前，一個存下一世代 
		
		for (j = 0; j < N; j++) {
			for (k = 0; k < N; k++){
				fscanf(fin,"%d",&map1[j][k]);//將元素塞進陣列   //每次讀取一個數，fscanf函式遇到空格或者換行結束
				map2[j][k]=0;
			}	
			fscanf(fin,"\n");	
		}
		//map1 & map2
		
		//檢查用 
		/*
		printf("\nN = %d\n",N);
		printf("G = %d\n\n",G);
		for(j=0;j<N;j++){
			for(k=0;k<N;k++){
				printf("%d ",map[j][k]);
			}
			printf("\n");
		}
		*/
		
		for(j=0;j<G;j++){
			produce(map1,map2);
	        copy(map2,map1);
	        //print(map1);
	    }
	    
		int count=0;
		
		for(j=0;j<N;j++){
			for(k=0;k<N;k++){
				if(map1[j][k]!=0){
					count++;
				}
			}
		}
		fprintf(fout,"%d %d %d\n",N,N,count);
		count=0;
		
		for(j=0;j<N;j++){
			for(k=0;k<N;k++){
				if(map1[j][k]!=0){
					count++;
					fprintf(fout,"%d %d %d\n",j,k,neighbors(map1,j,k));
				}
			}
		}   
    }
   
    return 0;
		
	/*陣列已經沒用之後才free 
	free(map1); 
	free(map2);
	}*/
	
	
	// close files
	fclose(fin);
	fclose(fout);
	
	printf("Successfully generate the sparse matrices and store they into %s\n", OUTPUT_FILE);
	
	system("PAUSE");
	
	return 0;
}

void produce(int current[][N], int next[][N]) {
    int row; 
    for(row = 0; row < N; row++) {
        int column;
        for(column = 0; column < N; column++) {
            switch (neighbors(current, row, column)) {
               case 0: case 1: case 4:
                  next[row][column] = 0; break; 
               case 2: 
                  next[row][column] = current[row][column]; break; 
               case 3: 
                  next[row][column] = 1;
            } 
        }
    }
}

int neighbors(int current[][N], int row, int column) {
    int dirs[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1},{1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    int count, i;
    for(count = 0, i = 0; i < 8 && count < 4; i++) {
        int r = row + dirs[i][0];
        int c = column + dirs[i][1];
        if(r > -1 && r < N && c > -1 && c < N && current[r][c]== 1 ) {
            count++;
        }
    }
    return count;
}

void copy(int from[][N], int to[][N]) {
    int row;
    for(row = 0; row < N; row++) {
        int column;
        for(column = 0; column < N; column++) {
            to[row][column] = from[row][column];
            from[row][column] = 0;
        }
    }
}

void print(int current[][N]) {
    printf("Status...\n");
    int row;    
    for(row = 0; row < N; row++) { 
        int column;
        for(column = 0; column < N; column++) {
            printf(" %d",current[row][column]);
        }
        printf("\n");
    }
}

