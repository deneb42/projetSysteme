/*  Find					parcour.h					By : deneb */

#ifndef PARCOUR_H
#define PARCOUR_H
	
	// function which launch the recursive parcour also process the root.
	void parcours(char *path, int minDepth, int maxDepth, int tab[], char* param[], int nbParam);
	
	// recursive func which go through all the files, Depth-first mode.
	void parcours_recur(char *path, int depth, int minDepth, int maxDepth, int tab[], char* param[], int nbParam);
	
	// Function called for every file parcour_recur find.
	int process(char *chemin, int tab[], char* param[], int nbParam);

#endif
