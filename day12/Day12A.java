package day12;

import java.lang.Math.*;
import java.util.*;
import java.util.regex.*;
import java.io.*;

class Moon{
	
	// 0 = x, 1 = y, 2 = z
	public int[] position;
	public int[] velocity;
	
	public Moon(int x, int y, int z) {
		position = new int[]{x, y, z};
		velocity = new int[]{0, 0, 0};
	}
	
}


public class Day12A {

	public static void main(String[] args) {
		
		// Strip planet positions with regex
		File f = new File("day12.txt");
		Scanner sc;
		try {
			sc = new Scanner(f);
		}catch(FileNotFoundException fnfe) {
			return;
		}
		sc.useDelimiter("\\Z");
		String data = sc.next();
		sc.close();
		
		Pattern p = Pattern.compile("-?[0-9]+");
		Matcher m = p.matcher(data);
		
		ArrayList<Moon> moons = new ArrayList<Moon>();
		while(m.find()) {
			int x = Integer.parseInt(data.substring(m.start(), m.end()));
			m.find();
			int y = Integer.parseInt(data.substring(m.start(), m.end()));
			m.find();
			int z = Integer.parseInt(data.substring(m.start(), m.end()));
			moons.add(new Moon(x, y, z));
		}
		
		// Simulate gravity between moons in pairs
		// Once all pairs for a moon have been exhausted, that moon's position can change
		for(int step = 0; step < 1000; step++) {
			for(int i = 0; i < moons.size(); i++) {
				Moon m1 = moons.get(i);
				for(int j = i+1; j < moons.size(); j++) {
					Moon m2 = moons.get(j);
					for(int k = 0; k < 3; k++) {
						if(m1.position[k] < m2.position[k]) {
							m1.velocity[k]++;
							m2.velocity[k]--;
						}else if(m1.position[k] > m2.position[k]) {
							m1.velocity[k]--;
							m2.velocity[k]++;
						}
					}
				}
				for(int j = 0; j < 3; j++) {
					m1.position[j] += m1.velocity[j];
				}
			}
		}
		
		// Find total potential and kinetic energy
		int energy = 0;
		for(int i = 0; i < moons.size(); i++) {
			Moon m1 = moons.get(i);
			int pe = (Math.abs(m1.position[0]) + Math.abs(m1.position[1]) + Math.abs(m1.position[2]));
			int ke = (Math.abs(m1.velocity[0]) + Math.abs(m1.velocity[1]) + Math.abs(m1.velocity[2]));
			energy += (pe * ke);
		}
		
		System.out.println(energy);
		
	}
	
}
