/* file header.h 
   Author: Vishal Chopra
   Purpose: Include all the header file
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>


struct shm_data{
	int oper1, oper2;
	char operand;
};
