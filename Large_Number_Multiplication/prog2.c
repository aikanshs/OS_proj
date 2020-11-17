//Filename:             prog2.c 
//Team Members:         Aikansh Priyam and Rupesh RajKumar Biradar
//UTD_ID:               2021489135 and 2021463884
//NetID:                axp190019 and rrb180004
//Class:                OS 5348.001
//Project:              Project 2



#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

#define size 10005
#define max_size 200000
#define out_size 100000005

int input[max_size+1];								    	// input array to store the numbers
long int i1,i2,k=0;											// i1 last index of 1st number, i2 last index of second number

int inp_size1[10],inp_size2[10];							// inp_size1 and inp_size2 store the number of digits in both the numbers
int input1[max_size];										// For Storing 1st number
int input2[max_size];										// For storing 2nd number

void read_input(){
	FILE *read;
	int inp1=0,inp2=0;
	read=fopen("a.txt","r");								// Open 1st input file to read number
	int c=fgetc(read);
	while(c!=32){											// reading the number of digits in the 1st number
		inp_size1[inp1++]=c;
		c=fgetc(read);
	}

	c=fgetc(read);
	k=1;
	while(c!=EOF){											// reading the 1st number and storing it in array
		input[k++]=c-'0';
		c=fgetc(read);
	}
	int i=0;
	for( i=k-1;i>=1;i--){
		input1[i1++]=input[i];
	}
	fclose(read);
	
	read=fopen("b.txt","r");								// Open 2nd input file to read number
	c=fgetc(read);
	input[0]=c;
	while(c!=32){									   		// reading the number of digits in the 2nd number
		inp_size1[inp1++]=c-'0';
		c=fgetc(read);
	}
	c=fgetc(read);
	while(c!=EOF){											// reading the 2nd number and storing it in array
		input[k++]=c-'0';
		c=fgetc(read);
	}
	for(i=k-1;i>i1;i--){
		input2[i2++]=input[i];
	}
}

int output[out_size];									    // Array to store computation of each thread
long int p=0;												// total length of result
int num_threads,part=0; 									// num_threads stores number of threads given by user.
int b=0;
pthread_mutex_t lock1;										// mutex lock
int num_per_thread;											// num_per_thread stores the number of digits each thread should execute

void *multiply(void *x){
	
	pthread_mutex_lock(&lock1);								// locking so that only one thread can access it
    
    int thread_part=part++;									// thread_part tells how many threads have accesees the function and further used in multiplication
	pthread_mutex_unlock(&lock1);							// unlocking so other threads can access it
	long int i=0; 
	long int start=thread_part*num_per_thread;
	long int finish=(thread_part+1)*num_per_thread;
	if(thread_part==num_threads-1)
		finish+=(i1%num_threads);
	int sum=0;
	for ( i=0; i<i2; i++) 
    { 
    	int j=0;
    	   
        for ( j=start; j<finish; j++) 
        {												
            sum=input1[j]*input2[i];
            pthread_mutex_lock(&lock1);						// locking so that only one thread can access it
            output[i+j]+= sum % 10; 						// Store result
    		output[i+j+1]+= sum/10; 
    		pthread_mutex_unlock(&lock1);					// unlocking mutex
        }
       
        
    }
    return NULL;
}
void print_answer(){
	long int i=0;
	for(i = 0; i <=max_size;++i){
		output[i + 1] = output[i+1] + (output[i]/10);		// Checking if the output array has element with more than one digit
		output[i] %= 10;
	}

	p=max_size;
    FILE *write;
	write=fopen("c2.txt","w");								// Opening file to write to the output file
	while(output[p]==0)										// Decrementing p if array value is 0
		p--;
	for(i=p;i>=0;i--)
    	fprintf(write, "%d",output[i]);						// Writing to the output file
    fclose(write);											// closing the file
    
}
int main(){
	
	//sem_init( &sem, 0, 1 );
	if (pthread_mutex_init(&lock1, NULL) != 0) 				// Initializing mutex
    { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
	printf("Enter number of threads\n" );
	scanf("%d",&num_threads);								// User input for number of threads
	pthread_t thread[num_threads];
	int err;
	read_input();											// Calling Function to read input
	int i=0;
	num_per_thread=i1/num_threads;
												
	for( i=0;i<num_threads;i++){
		err=pthread_create(&thread[i],NULL,&multiply,NULL);	// Creating threads 
		
		if(err)
			printf("error is:%d",err);
	}
	printf("waiting for thread to end\n");
	for(i=0;i<num_threads;i++)
		pthread_join(thread[i],NULL);
	printf("termination ends\n");
	print_answer();											// Calling function to print answer in the output file
	
	return 0;
}

