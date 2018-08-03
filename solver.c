#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int  sudoku_solved[9][9];
int  sudoku[9][9];
int error_count = 0;

//print sudoku
void printsudoku(){
	printf("\x1B[32m\nSolution:\n");					
	printf("\x1B[32m___________________________________\n");
	for(int y=0; y<9; y++){
		for(int x=0; x<9; x++){	
			if(sudoku[x][y] == 0){		
			printf("\x1B[32m| \x1B[31m%d ",sudoku_solved[x][y]);
			}
			else{
			printf("\x1B[32m| \x1B[37m%d ",sudoku_solved[x][y]);
			}
		}
		printf("\x1B[32m\n-----------------------------------\n");
	}


}

//check if correct
int check(int x, int y , int value){
	int correct=1;

	//check verticaal
	for(int i=0; i<9; i++){
		if(sudoku_solved[x][i] == value){
			correct=0;
		}
			
	}

	//check horizontaal
	for(int i=0; i<9; i++){
		if(sudoku_solved[i][y] == value){
			correct=0;
		}
			
	}
	
	//check vierkant 3*3
	int x_begin = x;
	int y_begin = y;
	//vind begin vierkant
	while(x_begin%3 !=0 && x_begin != 0){
		x_begin--;
	}
	while(y_begin%3 !=0 && y_begin != 0){
		y_begin--;
	}
	//check vierkant
	for(int i=0;i<3;i++){
		for(int a=0; a<3;a++){
			if(sudoku_solved[i+x_begin][a+y_begin] == value){
				correct=0;
			}
		}
	}
	return correct;

}

//solve sudoku
void solve(){

	int i = 0;

	while(i<81){

		//get coordinates out of i
		int current_y = floor(i/9);
		int current_x = (int) fmod(i,9);

		//check if current location is unknown
		if(sudoku[current_x][current_y] == 0){
		
			for(int x = sudoku_solved[current_x][current_y]; x <= 9; x++){

				if(x==0) {x++;}

				//check if valid
				if(check(current_x,current_y,x)==1){
					sudoku_solved[current_x][current_y]=x;
					i++;
					error_count = 0;
					break;
				}
				
				//non of the numbers is valid
				if(x == 9){

					error_count++;

					if(error_count > 1 ){
						sudoku_solved[current_x][current_y] = 0;						
					}

					i--;

					//go to the previous unknown number
					while(i > 0){
						 current_y = floor(i/9);
						 current_x = (int) fmod(i,9);

						if(sudoku[current_x][current_y] == 0){
							x=10;
						break;
						}

						i--;
					}
				}

			}	

		}else{
			i++;
		}
	}
}

int main(int argc, char *argv[] )
{
	printf("L-SudokuSolver\n\n");
	char * filename;
    if( argc == 2 ) {
      filename = argv[1];
   
		//read file and put it an array
		FILE *file;
		file = fopen(filename,"r");
		for(int y=0; y<9; y++){
			for(int x=0; x<9; x++){
				sudoku_solved[x][y] = fgetc(file) - '0';
				sudoku[x][y] = sudoku_solved[x][y];
			}
		fgetc(file);
		}

		//solve the sudoku
		//clock_t begin = clock();
		solve();
		//clock_t end = clock();
		//double time_spent = (double)(end - begin);
		//printf("Excution time: %f\n", time_spent);
		//print the sudoku
		printsudoku();
	}
    else {
      printf("filename expected.\n");
    }
	return 0;
}
