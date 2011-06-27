/*  Find					parcour.h					By : deneb */

#ifndef PARCOUR_H
#define PARCOUR_H

	void parcours(char *path, int minDepth, int maxDepth, int tab[], char* param[], int nbParam);
	void parcours_recur(char *path, int depth, int minDepth, int maxDepth, int tab[], char* param[], int nbParam);
	int process(char *chemin, int tab[], char* param[], int nbParam);

#endif
