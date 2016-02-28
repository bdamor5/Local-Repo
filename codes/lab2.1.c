#include <stdio.h> 
#include <string.h> 
int main(int argc, char *argv[])
{ 
	int value = 5; 
	char buffer1[8], buffer2[8]; 
	strcpy(buffer1, "one"); // copy "one" in the first buffer 
	strcpy(buffer2, "two"); // copy "two" in the second buffer 
	// show location and content of buffers and of variable 'value' 
	printf("[BEFORE] buffer2 is at location %p and contains %s\n",buffer2, buffer2); 
	printf("[BEFORE] buffer1 is at location %p and contains %s\n",buffer1, buffer1); 
	printf("[BEFORE] value is at location %p and contains %d 0x%08x\n",&value, value, value); 
	strcpy(buffer1, argv[1]); // copy first argument into buffer1 (no check on length!!) 
	// show again location and content to see what has happened 
	printf("[AFTER] buffer2 is at location %p and contains %s\n",buffer2, buffer2); 
	printf("[AFTER] buffer1 is at location %p and contains %s\n",buffer1, buffer1); 
	printf("[AFTER] value is at location %p and contains %d 0x%08x\n",&value, value,value);
	return 0; 
} 
