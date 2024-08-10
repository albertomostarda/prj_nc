#ifndef ERRORS_H
#define ERRORS_H

int conditionError(int lastPos);
void ifErrorMSG();
void elseErrorMSG();
int elseEndError(int lPos);
void elseEndErrorMSG();
int endIFError(int lPos);
void cicleErrorMSG(int curPos);
int endCicleError(int lPos);
void cOverflowErrMSG();


#endif