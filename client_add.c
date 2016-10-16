/*
   File: client_add.c
   Author: Vishal Chopra
   Purpose: This will create a shared memory, data will be send to server and receive from server
*/

#include "header.h" 


// Function Prototype
int create_shm();
int send_data();
int delete_shm();

// Global Variable
struct shm_data *data[2];


int main()
{
	create_shm();
	send_data();
	create_shm();
	delete_shm();
	return 0;
}

int create_shm()
{
	key_t key;
	int shm_id;
	static int index = 0; 
	void *shm_ptr = 0;	
	key = 1803;	
	shm_id = shmget( key, sizeof( struct shm_data ), IPC_CREAT | 0666 ); // to get a unique ID for the shared memory
	if( shm_id == -1 ){
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	
	shm_ptr = shmat( shm_id, 0, 0 );	// shmat API choose free space and return pointer to the free space  
	if(!shm_ptr){
		perror("shmat");
		exit(EXIT_FAILURE);
	}
	data[index] = (struct shm_data *)shm_ptr;	// 
	index++;
	return 0;
}

int send_data()
{
	data[0] -> oper1 = 3;
	data[0] -> oper2 = 5;
	data[0] -> operand = '+';
	printf("%d %d %c\n", data[0]->oper1, data[0]->oper2, data[0]->operand);
	return 0;
}

int delete_shm()
{
	if( shmdt(data[0]) == -1)
		perror("shm_dt");
	if( shmdt(data[1]) )
		perror("shm_dt");

	
	return 0;
}
