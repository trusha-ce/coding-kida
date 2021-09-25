#include<stdio.h>
#include<math.h>

double F(double);

int main()
{
	int N,i;
	double Ni[100],max=0;

    //--------------------ask number packets
	scanf("%d",&N);

    //--------------------ask number of balls in each packet
	for(i=0;i<N;i++)
	{
		scanf("%lf",&Ni[i]);
	}

    //--------------------calculate maximum moves
	for(i=0;i<N;i++)
	{
	    //--------------------F() find max move of ith packet and add to current max moves
		max = max + F(Ni[i]);
	}

	//--------------------print max moves
	printf("%.0lf",max);

	return 0;
}

//--------------------function to find max moves of packet
double F(double x)
{
	double maxi=0,fact[170],maxfact,i,x1;
	int k,j;

	//--------------------if 1 ball in packet max move is 1
	if(x==1)
	{
		maxi = 1;
	}

	//--------------------balls in packet >1
	else
	{
		k=-1;

		//--------------------find possible division option by finding factors
		for(i=2,x1=x;i<x1;i++)
		{
			if(fmod(x,i)==0)
			{
			    x1=x/i;
				fact[++k]=i;
				fact[++k]=x1;
			}
		}

		//--------------------could no find factor then moves are same as no. of balls
		if(k==-1)
		{
			maxi=x+1;
		}

		//--------------------find factors then find division with max moves
		else
		{
			for(j=0;j<=k;j++)
			{
				maxfact=F(fact[j])*fact[k-j];
				if(maxfact>maxi)
				{
					maxi=maxfact;
				}
			}
			maxi = maxi+1;
		}
	}
	return maxi;
}
