#include <stdio.h>
int main(){
	int rows,cols;
	printf("Enter number of rows: ");
	scanf("%d",&rows);
	printf("Enter number of columns: ");
	scanf("%d",&cols);
	int arr[rows][cols]; //declare array
	//initialize the 2d array
	printf("Enter values for the array:\n");
	int i,j;
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			printf("Enter value for position (%d,%d): ",i,j);
			scanf("%d",&arr[i][j]);
		}
	}
	//print updated array
	printf("\n updated 2d array:\n");
	for( i=0;i<rows;i++){
		for( j=0;j<cols;j++){
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}