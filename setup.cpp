#include<fstream>
#include"setup.h"

int dim_imp=4;
int dim_dot=4;
int N;
int n0;//number of step starting discarding states.num_basis[n0]>num_kept
double Beta_bar=0.6;//unit same as Beta!
double U=0.12;// in unit of D
double Ed=-1.0*U/3.0;//in unite of D
double Lambda=2.0;
double alpha=0.3;
bool smear=false;
