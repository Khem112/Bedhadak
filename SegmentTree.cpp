#include<bits/stdc++.h>
using namespace std;

struct club{
	int gcd;
	int data;
	int max;
	int min;
};

int gcd(int a,int b)
{
	if(a>=b)
	{
		for(int i=b;i>=1;i--)
		{
			if(a%i==0&&b%i==0)
			return i;
		}
	}
	else
	{
		for(int i=a;i>=1;i--)
		{
			if(a%i==0&&b%i==0)
			return i;
		}
	}
}

int getid(int a[],int n,int key)
{
	for(int i=0;i<n;i++)
	{
		if(a[i]==key)
		return i;
		if(a[i]>key && a[i-1]<key)
		return i;
	}
	return -1;
}

int g_query(club *st_arr,int start,int end,int r_start,int r_end,int pos=1)
{
	int mid  = (start+end)/2;
	if(r_start<=start && r_end>=end)	return st_arr[pos].gcd;
	
	if(r_start>=start && r_end<=end )
	{
		if(r_start >= mid+1)	return g_query(st_arr,mid+1,end,r_start,r_end,pos*2+1);
		if(r_end <= mid)	return g_query(st_arr,start,mid,r_start,r_end,pos*2);
		return gcd(g_query(st_arr,start,mid,r_start,r_end,pos*2),g_query(st_arr,mid+1,end,r_start,r_end,pos*2+1));
	}
	
	else if(r_end<=end)	return g_query(st_arr,start,mid,r_start,r_end,pos*2);
	else g_query(st_arr,mid+1,end,r_start,r_end,pos*2+1);
}

club create(club *st_arr,int *arr,int start,int end,int &i,int pos=1)
{
	int mid = (start+end)/2;
	if(start == end)
	{ 
		cout << "\nPOS " << pos << " assigned " << arr[i];
		st_arr[pos].gcd = arr[i++];
	}
	else
	{
		st_arr[pos].gcd = gcd(create(st_arr,arr,mid+1,end,i,pos*2+1).gcd,create(st_arr,arr,start,mid,i,pos*2).gcd);
	}
	return st_arr[pos];
}
 
int main()
{
	int n;
	cin >> n;
	club st_arr[2*n+1] ;
	int arr[n]={0};
	for(int j=0;j<n;j++)
	cin >> arr[j];
	sort(arr,arr+n);
	int i =0;
	create(st_arr,arr,1,n,i,1);
	for(int j=1;j<2*n+1;j++)
	cout << " "<<st_arr[j].gcd << " ";
	int q,a,b;
	cout << "\nEnter the number of tests \n";
	cin >> q;
	for(int z=0;z<q;z++)
	{
	cout << "\nEnter the limits(smaller followed by bigger)\n";
	cin >> a >> b;
	a = getid(arr,n,a)+1;
	b = getid(arr,n,b)+1;
	cout << g_query(st_arr,1,n,a,b,1) << endl;
	}
	return 0;
}
