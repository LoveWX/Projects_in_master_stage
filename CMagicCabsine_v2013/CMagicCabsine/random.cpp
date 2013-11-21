#include "stdafx.h"

#include <time.h>
#include <math.h>
#include <limits>
#include "random.h"

Random::Random(bool pseudo)
/*Post:The values of seed, add_on, and multiplier are initialized. The seed is initialized randomly only if pseudo==false.*/
{
	if(!pseudo)
		seed=1;
	else
		seed=time(NULL)%INT_MAX;
	multiplier=2743;
	add_on=5923;
	
	abandonSeveralNums();
}

int Random::reseed()
/*Post:The seed is replaced by a psuedorandom successor.*/
{
	seed=seed*multiplier+add_on;
	return seed;
}

double Random::random_real()//实值
/*Post:A random real number between 0 and 1 is returned.*/
{
	double max=INT_MAX+1.0;
	double temp=reseed();
	if(temp<0)
		temp=temp+max;
	return temp/max;
}

int Random::random_integer(int low,int high)//整数值
/*Post:A random integer between low and high(inclusive) is returned.*/
{
	if(low>high)
		return random_integer(high,low);
	else
		return ((int)((high-low+1)*random_real()))+low;
}

double Random::random_double(double low,double high)//有上下界的双精度
/*Post:A random double between low and high(inclusive) is returned.*/
{
	if(low>high)
		return (low-high)*random_real()+high;
	else
		return (high-low)*random_real()+low;
}

int Random::poisson(double mean)//泊松值
/*Post:A random integer, reflecting a Poisson distribution with parameter mean, is returned.*/
{
	double limit=exp(-mean);
	double product=random_real();
	int count=0;
	while (product>limit)
	{
		count++;
		product*=random_real();
	}
	return count;
}

void Random::abandonSeveralNums()
/*Post:Abandon first several numbers to make them more similar to random numbers.*/
{
	int numToAbandon=random_integer(7,29);
	while(numToAbandon--)
	{
		random_real();
	}
}
