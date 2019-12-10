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
        int min_zeros = WIDTH*HEIGHT + 1;
        int min_zeros_layer = -1;

        for(int i = 0; i < layers; i++){
                char* l = malloc(WIDTH*HEIGHT*sizeof(char));
                fscanf(f, "%150c", l);
                int zeros = 0;
                for(int c = 0; c < WIDTH*HEIGHT; c++){
                        if(l[c] == '0'){
                                zeros++;
                        }
                }
                if(zeros < min_zeros){
                        min_zeros = zeros;
                        min_zeros_layer = i;
                }
                free(l);
        }

        // Find number of ones and twos from the min zero layer
        rewind(f);
        char* l = malloc(WIDTH*HEIGHT*sizeof(char));
        for(int i = 0; i < min_zeros_layer; i++){
                fscanf(f, "%*150c");
        }
        fscanf(f, "%150c", l);
        fclose(f);

        int ones = 0;
        int twos = 0;
        for(int c = 0; c < WIDTH*HEIGHT; c++){
                if(l[c] == '1'){
                        ones++;
                }else if(l[c] == '2'){
                        twos++;
                }
        }

        int result = ones * twos;
        printf("%d", result);


        return 0;

}
