/* NOTE ON COORDINATE SYSTEMS: TOP LEFT OF ASTEROID FIELD IS (0,0). x INCREASES
 * AS YOU MOVE RIGHT, AND y INCREASES AS YOU MOVE DOWN. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// GCD
int gcd(int a, int b){
	if(a < 0){a = -a;}
	if(b < 0){b = -b;}
	if(a == 0){return b;}
	if(b == 0){return a;}
	int d;
	if(a < b){
		d = a;
	}else{
		d = b;
	}
	while(d > 1){
		if(a % d == 0 && b % d == 0){
			return d;
		}
		d--;
	}
	return 1;
}

// Returns 0 if the given coordinate is out of bounds, 1 if it is in bounds
int in_bounds(int x, int y){
	if(0 <= x && x < 43 && 0 <= y && y < 43){
		return 1;
	}
	return 0;
}


// Obstruct other asteroids from view by erasing asteroids on the same line
// as the one that connects (mx, my) and (ax, ay)
char** obstruct(int mx, int my, int ax, int ay, char** asteroids){
	int dx = ax-mx;
	int dy = ay-my;
	int d = gcd(dx, dy);
	dx /= d;
	dy /= d;
	// Iterate over possible obstructed asteroid positions within the bounds of
	// the field
	ax += dx;
	ay += dy;
	while(in_bounds(ax, ay)){
		asteroids[ay][ax] = '.';
		ax += dx;
		ay += dy;
	}
	return asteroids;
}


// Detect all possible asteroids from monitoring station at point (mx, my)
int detect_asteroids(int mx, int my, char** asteroids){
	
	// Copy the asteroid field into a new matrix
	char** a = malloc(43*sizeof(char*));
	for(int i = 0; i < 43; i++){
		a[i] = malloc(44*sizeof(char));
		strcpy(a[i], asteroids[i]);
	}

	// Scan for # characters in increasingly large squares around (mx,my)
	int max_dx = mx;
	if(42-mx > max_dx){max_dx = 42-mx;}
	int max_dy = my;
	if(42-my > max_dy){max_dy = 42-my;}
	int max_dn = max_dx;
	if(max_dy > max_dx){max_dn = max_dy;}

	int count = 0;
	for(int dn = 1; dn <= max_dn; dn++){ // dn = max distance from (mx,my) in one direction
		// Move clockwise around the square
		// Top side of square
		for(int dx = -dn; dx < dn; dx++){
			if(!in_bounds(mx+dx, my-dn)){
				continue;
			}
			if(asteroids[my-dn][mx+dx] == '#'){
				count++;
				asteroids = obstruct(mx, my, mx+dx, my-dn, a);
			}
		}
		// Right side
		for(int dy = -dn; dy < dn; dy++){
			if(!in_bounds(mx+dn, my+dy)){
				continue;
			}
			if(asteroids[my+dy][mx+dn] == '#'){
				count++;
				asteroids = obstruct(mx, my, mx+dn, my+dy, a);
			}
		}
		// Bottom side
		for(int dx = dn; dx > -dn; dx--){
			if(!in_bounds(mx+dx, my+dn)){
				continue;
			}
			if(asteroids[my+dn][mx+dx] == '#'){
				count++;
				asteroids = obstruct(mx, my, mx+dx, my+dn, a);
			}
		}
		// Left side
		for(int dy = dn; dy > -dn; dy--){
			if(!in_bounds(mx-dn, my+dy)){
				continue;
			}
			if(asteroids[my+dy][mx-dn] == '#'){
				count++;
				asteroids = obstruct(mx, my, mx-dn, my+dy, a);
			}
		}
	}

	for(int i = 0; i < 43; i++){
		free(a[i]);
	}
	free(a);

	return count;

}


int main(int argc, char** argv){

	// Scan asteroid text from file
	// The file is 43x43 characters
	FILE* f = fopen("day10.txt", "r");
	char** asteroids = malloc(43*sizeof(char*));
	for(int i = 0; i < 43; i++){
		asteroids[i] = malloc(44*sizeof(char));
		fscanf(f, "%s\n", asteroids[i]);
	}
	fclose(f);

	// Detect asteroids from every point with a # character
	int max_asteroids = 0;
	for(int y = 0; y < 43; y++){
		for(int x = 0; x < 43; x++){
			if(asteroids[y][x] == '.'){
				continue;
			}
			int a = detect_asteroids(x, y, asteroids);
			if(max_asteroids < a){
				max_asteroids = a;
			}
		}
	}

	printf("%d", max_asteroids);

	for(int i = 0; i < 43; i++){
		free(asteroids[i]);
	}
	free(asteroids);

	return 0;

}
