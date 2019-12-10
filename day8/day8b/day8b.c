#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char** argv){

	// Image size
	int WIDTH = 25;
	int HEIGHT = 6;
	int FILE_SIZE = 15000;
	int layers = FILE_SIZE / (WIDTH*HEIGHT);
	
	// Read image from file one layer at a time
	FILE* f = fopen("day8.txt", "r");
	char** image = malloc(layers*sizeof(char*));
	for(int i = 0; i < layers; i++){
		image[i] = malloc(WIDTH*HEIGHT*sizeof(char));
		fscanf(f, "%150c", image[i]);
	}
	fclose(f);

	// Find topmost non-transparent pixel for each position
	char* message = malloc(WIDTH*HEIGHT*sizeof(char));
	for(int i = 0; i < WIDTH*HEIGHT; i++){
		int depth = 0;
		while(image[depth][i] == '2'){
			depth++;
		}
		message[i] = image[depth][i];
	}

	// Print message
	for(int h = 0; h < HEIGHT; h++){
		for(int w = 0; w < WIDTH; w++){
			if(message[WIDTH*h + w] == '0'){
				printf("X");
			}else{
				printf(" ");
			}
		}
		printf("\n");
	}

	free(message);
	for(int i = 0; i < layers; i++){
		free(image[i]);
	}
	free(image);
	
	return 0;

}
