
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

/************************************
*  Note that in general using global
*  variables is a bad habit.
*  I use globals here because I don't 
*  want to scare you with "double***"
*************************************/

int m;
int n;
double **v;  // n*(m+1) 2D-array
double **h;  // (n+1)*m 2D-array

// For internal use only. Do not really use them directly
double *real_v;
double *real_h;
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

struct node{
	int x,y;
	long int d;
	node(int _x,int _y){
		x = _x;
		y = _y;
		d = 712271227122;
	}
};
bool operator<(node a,node b){
	return a.d > b.d;
}

void readParameters()
{
    ifstream ifs("input1", ifstream::binary);

    ifs.read((char*)&m, sizeof(int));
    ifs.read((char*)&n, sizeof(int));
	
	
    real_v = new double[n*(m+1)];
    real_h = new double[(n+1)*m];

    ifs.read((char*)real_v, sizeof(double)*n*(m+1));
    ifs.read((char*)real_h, sizeof(double)*(n+1)*m);

    v = new double*[n];
    for (int i=0; i<n; ++i){
        v[i] = &(real_v[i*(m+1)]);
		
	}
    h = new double*[n+1];
    for (int i=0; i<n+1; ++i){
        h[i] = &(real_h[i*m]);
	}

    ifs.close();
	
	
}

void release()
{

    delete []v;
    delete []h;

    delete []real_v;
    delete []real_h;
}

int main()
{
    readParameters();
   	bool **visit;
   	visit = new bool*[n+1];
   	parent[]
   	for(int i = 0;i<n+1;i++){
   		visit[i] = new bool[m+1]();
   	}
    node* first = NULL;
    priority_queue<node>pq;
    cur = new node(0,0);
    cur->d = 0;
    pq.push(cur);
    while(!pq.empty()){
    	node* cur = pq.top();
    	pq.pop();
    	int curx = cur.x;
    	int cury = cur.y;
    	for(int i = 0;i<4;i++){
    		if(curx +dx[i] > 0&& curx+dx[i]< m&&cury+dy[i] > 0 && cury+dy[i]< n){
    			
    		}
    	}
    }



    release();
    return 0;
}

