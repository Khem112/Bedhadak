#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
typedef struct bnode* bptr;
#define d 2

struct bnode {
	int flag = 0;
	int cnt = 0;
	int key[2 * d+1];
	bptr child[2 * d + 2];
	bptr parent;
};

void inorder(bptr t)
{
		if(t == NULL)	return;
		for(int i=0;i<t->cnt;i++)
		{
		//if(t->flag)
		inorder(t->child[i]);
		if(t->key[i] == -1)	break;
		cout << t->key[i] << "(" << t->flag << ") ";
		}
	inorder(t->child[t->cnt]);
}

int find_id(int a[],int n,int key)
{
	for(int i=0;i<n;i++)
	{
		if(a[i]==key)
		return i;
	}
	return -1;
}

void printlevel(queue<bptr> &q){
  if(q.size() == 1) return;
  bptr t = q.front();q.pop();
  if(t == NULL){
    cout << endl;
    q.push(NULL);
    printlevel(q);
  }

  else{
    int i=0;
    cout << "{" ;
    while(i<t->cnt){
      if(t->child[i]) q.push(t->child[i]);
      cout << t->key[i] << " , ";
      i++;
    }
    cout << "}\t" ;
    if(t->child[i]) q.push(t->child[i]);
  }
  printlevel(q);
}

void tempGen(int data, bptr ance,bptr &node)
{
	bptr temp = NULL;
	temp = new(bnode);
	for (int i = 0; i <= 2 * d; i++)
		temp->child[i] = NULL;
	for (int i = 0; i < 2 * d; i++)
		temp->key[i] = -1;
	temp->flag = 0;
	temp->key[0] = data;
	temp->cnt = 1;
	temp->parent = ance;
	node = temp;
}

void modify_parent(bptr &par,int median,bptr head,bptr fresh,bptr &root)
{
	if(par == NULL)
	{
		cout << "root is being modified";
		bptr one ;
		tempGen(median,NULL,one);
		one->child[0] = head;
		one->child[1] = fresh;
		one->flag = 1;
		one->child[0]->parent = one;
		one->child[1]->parent = one;
		root = one;
		par  = one;
		inorder(one);
	}
	else{
		par->flag = 1;
		par->key[par->cnt] = median;
		par->cnt++;
		sort(par->key, par->key + par->cnt);
		int id = find_id(par->key,par->cnt,median);
		if(par->cnt > id+1)
		{
			for(int i=par->cnt;i>=id+2;i--)
			{
				par->child[i] = par->child[i-1];
				par->child[i]->parent = par->child[0]->parent;
			}
		}
		par->child[id+1] = fresh;
		par->child[id+1]->parent = par->child[0]->parent;
		if(par->cnt == 2*d+1)
		{
			par->cnt--;
			int medi = par->key[d];
			par->key[d] = -1;
			par->cnt--;
			bptr fre = NULL;
			tempGen(par->key[d + 1], NULL,fre);
			fre->flag = par->flag;
			par->key[d+1] = -1;
			for (int i = 1; i < d; i++)
			{
				//cout << "\n moved " << par->key[d+i+1] << " ";
				fre-> key[i] = par->key[d + i + 1];
				par->key[d + i + 1] = -1;
				fre->cnt++;
				par->cnt--;
			}
			//cout << "fre->key[0] " <<fre->key[1];
			for(int i=0;i<=d;i++)
			{
				//cout << endl;
				//inorder(par->child[d+i+1]);
				//par->child[d+i+1]->parent = fre;
				fre->child[i] = par->child[d+i+1];
				fre->child[i]->parent = fre;
				//par->child[d+i+1] = NULL;
			}
			// cout << endl << "Head ";
			// inorder(par);
			// cout << endl << "Fresh ";
			// inorder(fre);
			modify_parent(par->parent,medi,par,fre,root);
			return;
		}
	}
}

void create(bptr &head, int data, bptr par,bptr &root)
{
	if (head == NULL) {
		 tempGen(data,par,head);
		 //cout << "Parent is " << head->parent->key[0];
		 root = head;
		return;
	}
	if(head->flag == 0){
			head->key[head->cnt++] = data;
			sort(head->key, head->key + head->cnt);
		if (head->cnt == 2 * d+1)
		{
			head->cnt--;
			int median = head->key[d];
			head->key[d] = -1;
			head->cnt--;
			bptr fresh;
			tempGen(head->key[d + 1], par,fresh);
			fresh->flag = head->flag;
			for (int i = 1; i < d; i++)
			{
				fresh->key[i] = head->key[d + i + 1];
				head->key[d + i + 1] = -1;
				fresh->cnt++;
				head->cnt--;
			}
			//cout << fresh->cnt << " " << head->cnt << " ";
			modify_parent(par,median,head,fresh,root);
			head->parent = par;
			return;
		}
			//cout << " " << head->cnt << endl;
	}
	else{
		int c=0;
		for(int i=0;i<head->cnt;i++)
		{
			if(data < head->key[i])
			{
				create(head->child[i],data,head,root);
				return;
			}
		}
		 create(head->child[head->cnt],data,head,root);
	}
}
int main()
{
	int n,key;
	cout << "Enter the number of entries ";
	cin >> n;
	bptr head = NULL, parent = NULL,root = NULL;
	for (int i = 1; i <= n; i++)
	{
		int m;
		cin >> m;
		create(head, m, parent,root);
		//cout << endl;
		//inorder(head);
		head = root;
	}
	  queue<bptr> q;
	  q.push(root);q.push(NULL);
	  cout << "\n\tLevel :  ";
    printlevel(q);
    return 0;
 }

