/*

   File: server.c
   Author: Vishal Chopra
   Purpose: This will create a shared memory, data will be receive from client send to processing client, get the result from processing client and send the data to requesting client.
*/

#include "header.h" 


//********************************* Function Prototype****************************************
int create_shm();
int receive_data();
int delete_shm();

//********************************* Global Variable ******************************************
struct shm_data *data[2];
struct shm_data *client_data;

int main()
{
	create_shm();
	receive_data();
	send_data();
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

int receive_data()
{
	client_data = ( struct shm_data *)malloc( sizeof(struct shm_data) );
	client_data -> oper1 = data[0] -> oper1;
	client_data -> oper2 = data[0] -> oper2;
	client_data -> operand = data[0] -> operand;

	printf("%d %d %c\n", client_data -> oper1, client_data -> oper2, client_data -> operand );

	free(client_data);
	client_data = NULL;
	return 0;
}

int delete_shm()
{
	if( shmdt(data[0]) == -1)
		perror("shm_dt");
	//if( shm_dt(data[1]) )
	//	perror("shm_dt");
	
	return 0;
}

send_data()
{
	int *arr, ret;
	char **p, rfd[4], wfd[4];
	pid_t pid;
	arr = ( int * )malloc*( sizeof( int ) * 2);
	*p = "./client_pro";
	if ( pipe(arr))
		perror("pipe");
	pid = fork();

	switch(pid){
	case -1:
		perror("fork");
		break;
	case 0:
		ret = write( arr[1], client_data, sizeof( struct shm_data ) );
		if( ret == 0 )
			perror("write");
		printf("Number of bytes write in the pipe %d\n", ret);
		sprintf(rfd, "%d", arr[0]);
		sprintf(wfd, "%d", arr[1]);
		execl( *p, *p, rfd, wfd, NULL );
	}
	return 0;
}
