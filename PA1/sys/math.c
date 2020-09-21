#include<stdio.h>
#include<kernel.h>
//#include<math.h>
#include<math.h>

#define RAND_MAX 32000

double log(double x);
double pow(double x, double y);
double expdev(double lambda);


double pow(double base, double exp){
	double pow_val = 1;
	int i;
	
	while (i <exp){

	pow_val = pow_val * base;
	i++;
	}
	return pow_val;

	
	}
	

double log(double x){
	if(x<0)
		return -1;
	int n = 20;
	//double sum = 0;
	double result = 0;
	//double power_val;
	int i=1;
	while (i <= n){
	 //power_val = pow(x,i);
	 result = result + pow(x,i)/i;
	 i++;

	}
	return -result;
}

double expdev(double lambda) {
    double dummy;
    //kprintf("in expdev function");
    do
        dummy= (double) rand() / RAND_MAX;
    while (dummy == 0.0);
    //kprintf("\ndummy value = %d\n", dummy);
    return -log(dummy) / lambda;
}






