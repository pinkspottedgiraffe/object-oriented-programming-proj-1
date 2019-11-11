#include <iostream>
#include <cstdlib>
#include <time.h>
#include "train.h"

using namespace std;


int main(int argc,char *argv[]){
	int N=atoi(argv[1]);
	
	srand(time(NULL));
	
	train a(N);
	a.operate();
}
