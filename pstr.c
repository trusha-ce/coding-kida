#include<stdio.h>
int main()
{
	int T,i,j,sum_odd,sum_even,ab_dif;
	char S[10][10000];

	//----------take number of test case input
	scanf("%d",&T);
	
	for(i=0;i<T;i++)
	{
		//----------take string input
		scanf("%s",S[i]);
	
		//----------initialize both sum
		sum_odd=0;
		sum_even=0;

		//----------process one string till end
		for(j=0;S[i][j]!='\0';j++)
		{
			//----------odd index char add in sum_odd
			if(j%2==0)
			{
				sum_odd += S[i][j];
			}

			//----------even index char add in sum_even
			else
			{
				sum_even += S[i][j];
			}
		}

		//----------find absolute difference
		ab_dif = abs(sum_odd-sum_even);		


		//----------check divisible by prime number <10
		if(ab_dif%3==0 || ab_dif%5==0 || ab_dif%7==0)
		{
			printf("Prime String\n");
		}
		else
		{
			printf("Casual String\n");
		}
	}
}