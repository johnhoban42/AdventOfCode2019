package day6;

import java.util.*;
import java.io.*;


/* Orbital Transfer Satellites includes only a parent field so the tree can be traversed upward. */

class OTSatellite{
	String name;
	OTSatellite parent;
	
	public OTSatellite(String name) {
		this.name = name;
	}
	
}

public class Day6B {
	
	// Finds common parent of two satellites and adds together the distances from the parent
	private static int satelliteDistance(OTSatellite s1, OTSatellite s2) {
		ArrayList<OTSatellite> trace = new ArrayList<OTSatellite>();
		for(OTSatellite ptr = s1; ptr != null; ptr = ptr.parent) {
			trace.add(ptr);
		}
		OTSatellite commonParent = s2;
		int distance = 0;
		while(!trace.contains(commonParent)) {
			commonParent = commonParent.parent;
			distance++;
		}
		return trace.indexOf(commonParent) + distance;
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
		HashMap<String, OTSatellite> satellites = new HashMap<String, OTSatellite>();
		
		// Build satellites tree
		while(sc.hasNextLine()) {
			
			String s = sc.nextLine();
			String pName = s.substring(0,3);
			String cName = s.substring(4,7);
			
			OTSatellite parent = satellites.get(pName);
			if(parent == null) {
				parent = new OTSatellite(pName);
				satellites.put(pName, parent);
			}
			OTSatellite child = satellites.get(cName);
			if(child == null) {
				child = new OTSatellite(cName);
				satellites.put(cName, child);
			}
			child.parent = parent;
			
		}
		
		sc.close();
		
		// The minimum distance between satellites is the sum of their distances from their common parent
		OTSatellite you = satellites.get("YOU").parent;
		OTSatellite san = satellites.get("SAN").parent;
		int distance = satelliteDistance(you, san);
		System.out.println(distance);
		
	}
	
}
