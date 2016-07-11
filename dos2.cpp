#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdlib>
#include<math.h>
#include<omp.h>
#include"setup.h"
using namespace std;
bool test_sum_rule=true;
double *** rho_red_temp;
double (*pf)(double,double);

void density_of_state(void)
{
    double dos1_up(double);
    double dos1_down(double);
    double dos2_up(double);
    double dos2_down(double);
    double dos3_up(double);
    double dos3_down(double);
	void   rho_red(int);
	double P_LG(double,double);
	double P_G(double,double);

	cout << "density_of_state: "; date_time();
    rho_red_temp=new double ** [N_max+2];
    for (int n=0;n<N_max+2;n++){
    	rho_red_temp[n]=new double * [num_kept];
        for (int i=0;i<num_kept;i++){
			rho_red_temp[n][i]=new double [num_kept];
			for (int j=0;j<num_kept;j++){
				rho_red_temp[n][i][j]=0;
			}
        }
    }
	for (int n1=n0;n1<N_max+1;n1++){
		rho_red(n1);
	}
	cout << "Time finished all reduced density matrice:    ";date_time();cout << endl;
    double freqency;
	ifstream f_freqency("freqency");
	ofstream f_dos_unsmeared("freq_dos_unsmeared.dat");
	ofstream f_dos_smeared("freq_dos_smeared.dat");
	cout << scientific << left << "            ";
	cout << setw(14) << "freqency"<< setw(14) << "dos1_up"<< setw(14) << "dos2_up";
	cout << setw(14) << "dos3_up";
	cout << setw(14) << "dos1_down"<< setw(14) << "dos2_down";
	cout << setw(14) << "dos3_down";
	cout << endl;
	double DOS1_UP,DOS2_UP,DOS3_UP,DOS1_DOWN,DOS2_DOWN,DOS3_DOWN;
	//test sum rule
	freqency=1.0;
	pf=P_LG;
	DOS1_UP=dos1_up(freqency);
	DOS2_UP=dos2_up(freqency);
	DOS3_UP=dos3_up(freqency);
	DOS1_DOWN=dos1_down(freqency);
	DOS2_DOWN=dos2_down(freqency);
	DOS3_DOWN=dos3_down(freqency);
	cout << "  sum_rule ";
	cout << setw(14) << setprecision(5) << freqency;
	cout << setw(14) << setprecision(5) << DOS1_UP;
	cout << setw(14) << setprecision(5) << DOS2_UP;
	cout << setw(14) << setprecision(5) << DOS3_UP;
	cout << setw(14) << setprecision(5) << DOS1_DOWN;
	cout << setw(14) << setprecision(5) << DOS2_DOWN;
	cout << setw(14) << setprecision(5) << DOS3_DOWN;
	cout << "  sum_up= ";
	cout << setw(10) << setprecision(5) << DOS1_UP+DOS2_UP+DOS3_UP;
	cout << "  sum_down= ";
	cout << setw(10) << setprecision(5) << DOS1_DOWN+DOS2_DOWN+DOS3_DOWN;
	cout << endl;
    test_sum_rule=false;
	while (!f_freqency.eof()){//???????????
		f_freqency >> freqency;
		if (fabs(freqency) > fabs(omega0)){
			pf=P_LG;
	        DOS1_UP=dos1_up(freqency);
	        DOS2_UP=dos2_up(freqency);
	        DOS3_UP=dos3_up(freqency);
	        DOS1_DOWN=dos1_down(freqency);
	        DOS2_DOWN=dos2_down(freqency);
	        DOS3_DOWN=dos3_down(freqency);
		    cout << "  unsmeared ";
		    cout << setw(14) << setprecision(5) << freqency;
		    cout << setw(14) << setprecision(5) << DOS1_UP;
		    cout << setw(14) << setprecision(5) << DOS2_UP;
		    cout << setw(14) << setprecision(5) << DOS3_UP;
		    cout << setw(14) << setprecision(5) << DOS1_DOWN;
		    cout << setw(14) << setprecision(5) << DOS2_DOWN;
		    cout << setw(14) << setprecision(5) << DOS3_DOWN;
		    cout << endl;
			f_dos_unsmeared << left;
		    f_dos_unsmeared << setw(20) << setprecision(14) << freqency;
		    f_dos_unsmeared << setw(20) << setprecision(14) << DOS1_UP+DOS2_UP+DOS3_UP;
		    f_dos_unsmeared << setw(20) << setprecision(14) << DOS1_DOWN+DOS2_DOWN+DOS3_DOWN;
		    f_dos_unsmeared << endl;
			f_dos_smeared << left;
		    f_dos_smeared << setw(20) << setprecision(4) << freqency;
		    f_dos_smeared << setw(20) << setprecision(14) << DOS1_UP+DOS2_UP+DOS3_UP;
		    f_dos_smeared << setw(11) << setprecision(14) << DOS1_DOWN+DOS2_DOWN+DOS3_DOWN;
		    f_dos_smeared << endl;
		}else{
			pf=P_G;
	        DOS1_UP=dos1_up(freqency);
	        DOS2_UP=dos2_up(freqency);
	        DOS3_UP=dos3_up(freqency);
	        DOS1_DOWN=dos1_down(freqency);
	        DOS2_DOWN=dos2_down(freqency);
	        DOS3_DOWN=dos3_down(freqency);
		    cout << "  smeared ";
		    cout << setw(14) << setprecision(5) << freqency;
		    cout << setw(14) << setprecision(5) << DOS1_UP;
		    cout << setw(14) << setprecision(5) << DOS2_UP;
		    cout << setw(14) << setprecision(5) << DOS3_UP;
		    cout << setw(14) << setprecision(5) << DOS1_DOWN;
		    cout << setw(14) << setprecision(5) << DOS2_DOWN;
		    cout << setw(14) << setprecision(5) << DOS3_DOWN;
		    cout << endl;
		    f_dos_smeared << setw(20) << setprecision(14) << freqency;
		    f_dos_smeared << setw(20) << setprecision(14) << DOS1_UP+DOS2_UP+DOS3_UP;
		    f_dos_smeared << setw(20) << setprecision(14) << DOS1_DOWN+DOS2_DOWN+DOS3_DOWN;
		    f_dos_smeared << endl;
		}
	}
	cout << "Time leaved:    ";date_time();cout << endl;
}

void rho_red(int n1)// n1 ~ [n0,N_max]. n ~ {0,1,...,N_max+1}
{
	double **** eigen_sigma=new double *** [N_max+2];
	for (int n=0;n<1;n++){//eigen_sigma[0][sigma][k][j] shouldn't be used!
		eigen_sigma[n]=new double ** [1];
		for (int sigma=0;sigma<1;sigma++){
			eigen_sigma[n][sigma]=new double * [1];
			for (int k=0;k<1;k++){
				eigen_sigma[n][sigma][k]=new double [1];
				for (int j=0;j<1;j++){
				    eigen_sigma[n][sigma][k][j]=0;
				}
			}
		}
	}
	for (int n=1;n<N_max+2;n++){
		eigen_sigma[n]=new double ** [dim_dot];
		for (int sigma=0;sigma<dim_dot;sigma++){
			eigen_sigma[n][sigma]=new double * [num_eigen_kept[n-1]];
			for (int k=0;k<num_eigen_kept[n-1];k++){
				eigen_sigma[n][sigma][k]=new double [num_basis[n]];
				for (int j=0;j<num_basis[n];j++){
				    eigen_sigma[n][sigma][k][j]=0;
				}
			}
		}
	}
#pragma omp parallel for 
	for (int n=1;n<N_max+2;n++){//initialization of eigen_sigma[n][sigma][j][k].
		for (int sigma=0;sigma<dim_dot;sigma++){
			for (int k=0;k<num_eigen_kept[n-1];k++){
				for (int j=0;j<num_basis[n];j++){
					//transformation matrix after sorting.
					eigen_sigma[n][sigma][k][j]=eigen[n][j].eigen_vect[basis_kj[n][k][sigma].sort];
					//eigen_sigma[n][sigma][k][j]=vect[n][j][basis_kj[n][k][sigma].sort];
				}
			}
		}
	}
	double *** temp=new double ** [dim_dot];//declaration of temp
	double *** temp2=new double ** [dim_dot];//declaration of temp2
	for (int sigma=0;sigma<dim_dot;sigma++){
		temp[sigma]=new double * [num_kept];
		temp2[sigma]=new double * [num_kept];
		for (int i=0;i<num_kept;i++){
		    temp[sigma][i]=new double [num_kept];
		    temp2[sigma][i]=new double [num_kept];
		}
	}
	double ** sum_temp=new double * [num_kept];//declaration of sum_temp
	double ** ans=new double * [num_kept];//declaration of ans
	for (int i=0;i<num_kept;i++){
		sum_temp[i]=new double [num_kept];
		ans[i]=new double [num_kept];
	    for (int j=0;j<num_kept;j++){
			ans[i][j]=0;//initialization of ans 
		}
	}
	int k_start,k_finish;
	for (int n2=N_max+1;n2>n1;n2--){//N_max>=n2>n1>=n0
		if (n2==N_max+1){
	    	k_start=0;
	    	k_finish=num_basis[n2];
		}else{
	    	k_start=num_kept;
	    	k_finish=num_basis[n2];
		}
#pragma omp parallel for 
	    for (int sigma=0;sigma<dim_dot;sigma++){
	    	for (int i=0;i<num_kept;i++){
		        for (int j=0;j<num_kept;j++){
			    	temp[sigma][i][j]=0;//initialization of temp
			    	temp2[sigma][i][j]=0;//initialization of temp2
			    }
			}
		}
#pragma omp parallel for 
	    for (int i=0;i<num_kept;i++){
	        for (int j=0;j<num_kept;j++){
	    		sum_temp[i][j]=0;//initialization of sum_temp
	    	}
	    }
	    for (int sigma=0;sigma<dim_dot;sigma++){//n=n2
#pragma omp parallel for 
	        for (int i=0;i<num_kept;i++){
	        	for (int j=0;j<num_kept;j++){
	    			for (int k=k_start;k<k_finish;k++){
	        		    temp[sigma][i][j]=temp[sigma][i][j]+eigen_sigma[n2][sigma][i][k]*eigen_sigma[n2][sigma][j][k]*exp(-1.0*Beta*pow(Lambda,-(n2-1-1)/2.0)*eigen[n2][k].eig_val);
	    			}
	        	}
	        }
#pragma omp parallel for 
	    	for (int i=0;i<num_kept;i++){
	    		for (int j=0;j<num_kept;j++){
	    	        sum_temp[i][j]=sum_temp[i][j]+temp[sigma][i][j];
	    		}
	    	}
	    }
	    for (int n=n2-1;n>n1;n--){//n=n2-1 ~ n1+1
#pragma omp parallel for 
	        for (int sigma=0;sigma<dim_dot;sigma++){
		    	for (int i=0;i<num_kept;i++){
		    		for (int j=0;j<num_kept;j++){
		    			temp[sigma][i][j]=0;
		    			temp2[sigma][i][j]=0;
		    		}
		    	}
		    }
	    	for (int sigma=0;sigma<dim_dot;sigma++){
#pragma omp parallel for 
	    		for (int i=0;i<num_kept;i++){//temp=A_{kk}*sum_temp
	    		    for (int j=0;j<num_kept;j++){
	    				for (int k=0;k<num_kept;k++){
	    				    temp[sigma][i][j]=temp[sigma][i][j]+eigen_sigma[n][sigma][i][k]*sum_temp[k][j];
	    				}
	    		    }
	    		}
#pragma omp parallel for 
	    		for (int i=0;i<num_kept;i++){//temp2=temp*A^{\dag}_{kk}
	    		    for (int j=0;j<num_kept;j++){
	    				for (int k=0;k<num_kept;k++){
	    				    temp2[sigma][i][j]=temp2[sigma][i][j]+temp[sigma][i][k]*eigen_sigma[n][sigma][j][k];
	    				}
	    		    }
	    		}
	    	}
#pragma omp parallel for 
	    	for (int i=0;i<num_kept;i++){//set sum_temp to 0
	    	    for (int j=0;j<num_kept;j++){
					sum_temp[i][j]=0;
				}
			}
	    	for (int sigma=0;sigma<dim_dot;sigma++){//summation of sigma
#pragma omp parallel for 
	    	    for (int i=0;i<num_kept;i++){
	    	    	for (int j=0;j<num_kept;j++){
	    	            sum_temp[i][j]=sum_temp[i][j]+temp2[sigma][i][j];
	    	    	}
	    	    }
	    	}
	    }
#pragma omp parallel for 
	    for (int i=0;i<num_kept;i++){
	    	for (int j=0;j<num_kept;j++){
	            ans[i][j]=ans[i][j]+sum_temp[i][j]*pow(dim_dot,N_max+1-n2);
	    	}
	    }
	}
#pragma omp parallel for 
	for (int i=0;i<num_kept;i++){
		for (int j=0;j<num_kept;j++){
			rho_red_temp[n1][i][j]=ans[i][j]/Z;
		}
	}
	for (int n=0;n<1;n++){
		for (int sigma=0;sigma<1;sigma++){
			for (int k=0;k<1;k++){
				delete [] eigen_sigma[n][sigma][k];
			}
			delete [] eigen_sigma[n][sigma];
		}
		delete [] eigen_sigma[n];
	}
	for (int n=1;n<N_max+2;n++){
		for (int sigma=0;sigma<dim_dot;sigma++){
			for (int k=0;k<num_eigen_kept[n-1];k++){
				delete [] eigen_sigma[n][sigma][k];
			}
			delete [] eigen_sigma[n][sigma];
		}
		delete [] eigen_sigma[n];
	}
	delete [] eigen_sigma;
	for (int sigma=0;sigma<dim_dot;sigma++){
		for (int i=0;i<num_kept;i++){
		    delete [] temp[sigma][i];
		    delete [] temp2[sigma][i];
		}
		delete [] temp[sigma];
		delete [] temp2[sigma];
	}
	delete [] temp;
	delete [] temp2;
	for (int i=0;i<num_kept;i++){
		delete [] sum_temp[i];
		delete [] ans[i];
	}
	delete [] sum_temp;
	delete [] ans;
}
double dos1_up(double freqency)
{
	double sum=0,omegan=0;
	for (int n=n0;n<N_max+1;n++){
		double sum_n=0;
#pragma omp parallel for reduction(+:sum_n)
		for (int i=num_kept;i<num_basis[n];i++){
		    for (int j=num_kept;j<num_basis[n];j++){
				omegan=pow(Lambda,-1.0*(n-1-1)/2.0)*(eigen[n][i].eig_val-eigen[n][j].eig_val);
				sum_n=sum_n+c_dag_up_eigen[n][i][j]*c_up_eigen[n][j][i]*(exp(-1.0*Beta*pow(Lambda,-1.0*(n-1-1)/2.0)*eigen[n][i].eig_val)+exp(-1.0*Beta*pow(Lambda,-1.0*(n-1-1)/2.0)*eigen[n][j].eig_val))*(*pf)(freqency,-1.0*omegan);
				//cout << "n= " << n << " f= " << freqency << "  wn= " << omegan <<  "  P_K= " << P_K(freqency,-1.0*omegan) << endl;
			}
		}
		sum=sum+pow(4,N_max+1-n)*sum_n;
	}
	for (int n=N_max+1;n<N_max+2;n++){
		double sum_n=0;
#pragma omp parallel for reduction(+:sum_n)
		for (int i=0;i<num_basis[n];i++){
		    for (int j=0;j<num_basis[n];j++){
				omegan=pow(Lambda,-1.0*(n-1-1)/2.0)*eigen[n][i].eig_val-pow(Lambda,-1.0*(n-1-1)/2.0)*eigen[n][j].eig_val;
				sum_n=sum_n+c_dag_up_eigen[n][i][j]*c_up_eigen[n][j][i]*(exp(-1.0*Beta*pow(Lambda,-1.0*(n-1-1)/2.0)*eigen[n][i].eig_val)+exp(-1.0*Beta*pow(Lambda,-1.0*(n-1-1)/2.0)*eigen[n][j].eig_val))*(*pf)(freqency,-1.0*omegan);
			}
		}
		sum=sum+pow(4,N_max+1-n)*sum_n;
	}
	return sum/Z;
}
double dos1_down(double freqency)
{
	double sum=0,omegan=0;
	double P_K(double,double);
	for (int n=n0;n<N_max+1;n++){
		double sum_n=0;
#pragma omp parallel for reduction(+:sum_n)
		for (int i=num_kept;i<num_basis[n];i++){
		    for (int j=num_kept;j<num_basis[n];j++){
				omegan=pow(Lambda,-1.0*(n-1-1)/2.0)*eigen[n][i].eig_val-pow(Lambda,-1.0*(n-1-1)/2.0)*eigen[n][j].eig_val;
				sum_n=sum_n+c_dag_down_eigen[n][i][j]*c_down_eigen[n][j][i]*(exp(-1.0*Beta*pow(Lambda,-1.0*(n-1-1)/2.0)*eigen[n][i].eig_val)+exp(-1.0*Beta*pow(Lambda,-1.0*(n-1-1)/2.0)*eigen[n][j].eig_val))*(*pf)(freqency,-1.0*omegan);
			}
		}
		sum=sum+pow(4,N_max+1-n)*sum_n;
	}
	for (int n=N_max+1;n<N_max+2;n++){
		double sum_n=0;
#pragma omp parallel for reduction(+:sum_n)
		for (int i=0;i<num_basis[n];i++){
		    for (int j=0;j<num_basis[n];j++){
				omegan=pow(Lambda,-1.0*(n-1-1)/2.0)*eigen[n][i].eig_val-pow(Lambda,-1.0*(n-1-1)/2.0)*eigen[n][j].eig_val;
				sum_n=sum_n+c_dag_down_eigen[n][i][j]*c_down_eigen[n][j][i]*(exp(-1.0*Beta*pow(Lambda,-1.0*(n-1-1)/2.0)*eigen[n][i].eig_val)+exp(-1.0*Beta*pow(Lambda,-1.0*(n-1-1)/2.0)*eigen[n][j].eig_val))*(*pf)(freqency,-1.0*omegan);
			}
		}
		sum=sum+pow(4,N_max+1-n)*sum_n;
	}
	return sum/Z;
}
double dos2_up(double freqency)
{
	double omegan=0,sum=0;
	double P_K(double,double);
	for (int n=n0;n<N_max+1;n++){
		double sum_n=0;
#pragma omp parallel for reduction(+:sum_n)
		for (int i=num_kept;i<num_basis[n];i++){
			for (int j=0;j<num_kept;j++){
				omegan=eigen[n][i].eig_val*pow(Lambda,-1.0*(n-1-1)/2.0)-eigen[n][j].eig_val*pow(Lambda,-1.0*(n-1-1)/2.0);
				sum_n=sum_n+c_dag_up_eigen[n][i][j]*c_up_eigen[n][j][i]*exp(-1.0*Beta*eigen[n][i].eig_val*pow(Lambda,-1.0*(n-1-1)/2.0))*(*pf)(freqency,-1.0*omegan)+c_up_eigen[n][i][j]*c_dag_up_eigen[n][j][i]*exp(-1.0*Beta*eigen[n][i].eig_val*pow(Lambda,-1.0*(n-1-1)/2.0))*(*pf)(freqency,omegan);
			}
		}
		sum=sum+sum_n*pow(4,N_max+1-n);
	}
	return sum/Z;
}
double dos2_down(double freqency)
{
	double omegan=0,sum=0;
	double P_K(double,double);
	for (int n=n0;n<N_max+1;n++){
		double sum_n=0;
#pragma omp parallel for reduction(+:sum_n)
		for (int i=num_kept;i<num_basis[n];i++){
			for (int j=0;j<num_kept;j++){
				omegan=eigen[n][i].eig_val*pow(Lambda,-1.0*(n-1-1)/2.0)-eigen[n][j].eig_val*pow(Lambda,-1.0*(n-1-1)/2.0);
				sum_n=sum_n+c_dag_down_eigen[n][i][j]*c_down_eigen[n][j][i]*exp(-1.0*Beta*eigen[n][i].eig_val*pow(Lambda,-1.0*(n-1-1)/2.0))*(*pf)(freqency,-1.0*omegan)+c_down_eigen[n][i][j]*c_dag_down_eigen[n][j][i]*exp(-1.0*Beta*eigen[n][i].eig_val*pow(Lambda,-1.0*(n-1-1)/2.0))*(*pf)(freqency,omegan);
				}
		}
		sum=sum+sum_n*pow(4,N_max+1-n);
	}
	return sum/Z;
}
double dos3_up(double freqency)
{
	double omegan=0,sum=0;
	double P_K(double,double);
	for (int n=n0;n<N_max+1;n++){
		double sum_n=0;
#pragma omp parallel for reduction(+:sum_n)
		for (int i=0;i<num_kept;i++){
			for (int j=num_kept;j<num_basis[n];j++){
				omegan=eigen[n][i].eig_val*pow(Lambda,-1.0*(n-1-1)/2.0)-eigen[n][j].eig_val*pow(Lambda,-1.0*(n-1-1)/2.0);
				for (int k=0;k<num_kept;k++){
					sum_n=sum_n+c_dag_up_eigen[n][i][j]*c_up_eigen[n][j][k]*rho_red_temp[n][k][i]*(*pf)(freqency,-1.0*omegan)+c_up_eigen[n][i][j]*c_dag_up_eigen[n][j][k]*rho_red_temp[n][k][i]*(*pf)(freqency,omegan);
				}
			}
		}
		sum=sum+sum_n;
	}
	return sum;
}
double dos3_down(double freqency)
{
	double omegan=0,sum=0;
	double P_K(double,double);
	for (int n=n0;n<N_max+1;n++){
		double sum_n=0;
#pragma omp parallel for reduction(+:sum_n)
		for (int i=0;i<num_kept;i++){
			for (int j=num_kept;j<num_basis[n];j++){
				omegan=eigen[n][i].eig_val*pow(Lambda,-1.0*(n-1-1)/2.0)-eigen[n][j].eig_val*pow(Lambda,-1.0*(n-1-1)/2.0);
				for (int k=0;k<num_kept;k++){
					sum_n=sum_n+c_dag_down_eigen[n][i][j]*c_down_eigen[n][j][k]*rho_red_temp[n][k][i]*(*pf)(freqency,-1.0*omegan)+c_down_eigen[n][i][j]*c_dag_down_eigen[n][j][k]*rho_red_temp[n][k][i]*(*pf)(freqency,omegan);
				}
			}
		}
		sum=sum+sum_n;
	}
	return sum;
}
double P_LG(double freqency,double omegan)//---> omega + omega_n !!!!!!!!!!!!
{
	double Pi=3.14159265357L;
	if (test_sum_rule) {
		return 1.0;
	}else{
		if (fabs(omegan)<pow(10,-20)){
			//cout << "xxx =0  " << sqrt(omegan*omegan);
			return 0;
		}else{
		    return exp(-1.0*alpha*alpha/4.0)/(alpha*fabs(omegan)*sqrt(Pi))*exp(-1.0*pow(log(fabs(freqency))-log(fabs(omegan)),2)/alpha/alpha);
		}
	}
}

double P_G(double freqency,double omegan)// ---> omega - omega_n !!!!!!!!!!!!
{
	double Pi=3.14159265357L;
	if (test_sum_rule) {
		return 1.0;
	}else{
		return 1.0/(omega0*sqrt(Pi))*exp(-pow((freqency-omegan)/omega0,2));
	}
}

/*
 *double P_K(double freqency, double omegan)//centered at omegan! not -1.0*omegan.
 *{
 *    double P_L(double,double);
 *    double P_G(double,double);
 *    double ans=0;
 *    if (test_sum_rule){
 *        ans=1.0;
 *    }else{
 *        ans=P_L(freqency,omegan)*(*pf)(omegan)+P_G(freqency,omegan)*(1-(*pf)(omegan));
 *        //ans=P_L(freqency,omegan)*(*pf)(freqency)+P_G(freqency,omegan)*(1-(*pf)(freqency));
 *    }
 *    return ans;
 *}
 *double P_L(double freqency,double omegan)
 *{
 *    double theta(double);
 *    double Pi=3.14159265357L,gamma=alpha/4.0;
 *    double ans;
 *    ans=1.0/(sqrt(Pi)*alpha*fabs(omegan))*exp(-pow(log(fabs(omegan/freqency))/alpha+gamma-alpha/2.0,2))*exp(-alpha*(gamma-alpha/4.0));
 *    //ans=theta(freqency*omegan)/(sqrt(Pi)*alpha*fabs(omegan))*exp(-pow(log(fabs(omegan/freqency))/alpha+gamma-alpha/2.0,2))*exp(-alpha*(gamma-alpha/4.0));
 *}
 *double P_G(double freqency,double omegan)
 *{
 *    double Pi=3.14159265357L,ans;
 *    ans=1.0/(omega0*sqrt(Pi))*exp(-pow((freqency-omegan)/omega0,2));
 *    return ans;
 *}
 *double theta(double freqency)
 *{
 *    double ans;
 *    if (freqency > 1e-20 ){
 *        ans=1.0;
 *    }else if (freqency > 0 && freqency < 1e-20){
 *        ans=1.0/2.0;
 *    }else {
 *        ans=0.0;
 *    }
 *    return ans;
 *}
 *double P_h_unsmeared(double freqency)
 *{
 *    double ans;
 *    ans=1.0;
 *    return ans;
 *}
 *double P_h_smeared(double freqency)
 *{
 *    double ans;
 *    ans=exp(-pow(log(fabs(freqency/omega0))/alpha,2));
 *    return ans;
 *}
 */