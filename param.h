#ifndef PARAM_H
#define PARAM_H

	int getParam(int* nbPath, int** tab, char*** param, char* argv[], int argc);
	void freeParam(int tab[], char* param[], int nbParam);

#endif
