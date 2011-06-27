/*  Find					param.h					By : deneb */

#ifndef PARAM_H
#define PARAM_H

	#define PRED_NOT 0
	#define PRED_OR 1
	#define PRED_AND 2
	#define PRED_PRINT 3
	#define PRED_LS 4
	#define PRED_PRUNE 5
	#define PRED_EXEC 18
	
	#define END_OP 3
	
	int getParam(int* nbPath, int** tab, char*** param, int* minDepth, int* maxDepth, char* argv[], int argc);
	void freeParam(int tab[], char* param[], int nbParam);

#endif
