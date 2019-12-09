package day6;

import java.util.*;
import java.io.*;


/* Satellites have a tree-like structure; each has a parent that they orbit and a child that orbits
 * them. If a satellite has more than one child, then the 2nd, 3rd, etc. children are not identified
 * as the satellite's children, but rather the "siblings" of the 1st child. Siblings have a linked-list
 * structure. */

class Satellite{
	String name;
	Satellite child;
	Satellite sibling;
	
	public Satellite(String name) {
		this.name = name;
	}
	
}

public class Day6A {
	
	// Recursive algorithm for total orbits
	private static int totalOrbits(Satellite com, int height) {
		int orbits = 0;
		if(com.child != null) {
			orbits += totalOrbits(com.child, height+1);
		}
		if(com.sibling != null) {
			orbits += totalOrbits(com.sibling, height);
		}
		return orbits + height;
	}

	public static void main(String[] args) {
		
		// Open file
		File f = new File("day6.txt");
		Scanner sc;
		try {	
			sc = new Scanner(f);
		}catch(FileNotFoundException fnfe) {
			System.out.println(fnfe.getMessage());
			return;
		}
		
		// Stores all satellites for quick retrieval
		HashMap<String, Satellite> satellites = new HashMap<String, Satellite>();
		
		// Build satellites tree
		while(sc.hasNextLine()) {
			
			String s = sc.nextLine();
			String pName = s.substring(0,3);
			String cName = s.substring(4,7);
			
			Satellite parent = satellites.get(pName);
			if(parent == null) {
				parent = new Satellite(pName);
				satellites.put(pName, parent);
			}
			Satellite child = satellites.get(cName);
			if(child == null) {
				child = new Satellite(cName);
				satellites.put(cName, child);
			}
			if(parent.child == null) {
				parent.child = child;
			}else {
				child.sibling = parent.child;
				parent.child = child;
			}
			
		}
		
		sc.close();
		
		// The total orbits in the tree is the sum of the heights of all satellites, with height(COM) = 0
		Satellite com = satellites.get("COM");
		int orbits = totalOrbits(com, 0);
		System.out.println(orbits);
		
	}
	
}
