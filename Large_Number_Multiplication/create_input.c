#include<stdlib.h>
#include<stdio.h>
#define size 100

void create_input(){
	FILE *write;													//*write-> to write to 2 input files
	int num1=0,num2=0;
	write=fopen("a.txt","w");								   
	int n=rand()%10;												//creating random number between 0 and 9
	fprintf(write, "%d ",size);									   // writing number of digits to input file 1
	while(n==0)													   // checking if the 1st random number generated is 0 or not
		n=rand()%10;
	fprintf(write, "%d",n);
	int i=0;
	
	for(i=1;i<size;i++){											// Loop for writing input to the file
		n=rand()%10;												// creating random number between 0 and 9
		fprintf(write, "%d",n);
	}
	fclose(write);													// closing the file
	write=fopen("b.txt","w");
	fprintf(write, "%d ",size);										// writing number of digits to input file 1
	
	n=rand()%10;													//creating random number between 0 and 9
	while(n==0)														// checking if the 1st random number generated is 0 or not
		n=rand()%10;
	fprintf(write, "%d",n);
	for(i=1;i<size;i++){											// Loop for writing input to the file
		n=rand()%10;												// creating random number between 0 and 9
		fprintf(write, "%d",n);										
	}
	fclose(write);
	
}
int main(){
	
	
	create_input();												// Calling function to create input
	return 0;
}

