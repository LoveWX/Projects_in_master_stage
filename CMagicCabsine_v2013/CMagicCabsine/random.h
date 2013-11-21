#ifndef random
#define random

class Random
{
public:
	Random(bool pseudo=true);  //Declare random-number generation methods here.
	double random_real();
	int random_integer(int low,int high);
	int poisson(double mean);

	double random_double(double low,double high);
private:
	int reseed();              //Re-randomize the seed.
	int seed,multiplier,add_on;//constants for use in arithmetic operations.

	void abandonSeveralNums();//Abandon first several numbers to make them more similar to random numbers
};

#endif
