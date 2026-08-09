#include<iostream>
using namespace std;
int sum, num, n;
int c[30];

void print(int m)
{
	if (sum > n)return;
	if (sum == n)
	{
		for (int i = 1; i <= num; i++)
		{
			if (i != 1)cout << "+";
			cout << c[i];
		}
		cout << endl;
		return;
	}
	for(int i=m;i>=1;i--)
	{
		sum += i;
		c[++num] = i;
		print(i);
		sum -= i;
		num--;
	}
}

int main()
{
	cin >> n;
	print(n);
	return 0;
}