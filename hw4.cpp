
#include <iostream>
#include <fstream>
#include <queue>
#include <utility>
using namespace std;
typedef pair<int,int> pii;
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
bool operator<(node* a,node* b){
	return a->d > b->d;
}

void readParameters()
{
    ifstream ifs("input/problem1/input1", ifstream::binary);

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
   	bool **visited;
    pii **parent;
    parent = new pii*[n+1];
   	visited = new bool*[n+1];
   	for(int i = 0;i<n+1;i++){
   		visited[i] = new bool[m+1]();
        parent[i] = new pii[m+1];
   	}
    node* first = NULL;
    priority_queue<node*>pq;
    first = new node(0,0);
    first->d = 0;
    visited[0][0] = true;
    pq.push(first);
    //cout << n << " " << m << endl;
    while(!pq.empty()){
    	node* cur = pq.top();
        cout << cur->x << " "<< cur->y << endl;   
    	int curx = cur->x;
    	int cury = cur->y;
        pq.pop();
    	for(int i = 0;i<4;i++){
    		if(curx +dx[i] >= 0 && curx+dx[i]<= m && cury+dy[i] >= 0 && cury+dy[i]<= n){
    			if(!visited[cury+dy[i]][curx+dx[i]]){
                    node* next;
                    next = new node(curx+dx[i],cury+dy[i]);
                    visited[cury+dy[i]][curx+dx[i]] = true;
                    if(dx[i] == 0){
                        if(dy[i] == -1){
                            next->d =  cur->d+v[cury-1][curx];
                        }
                        else if(dy[i] == 1){
                            next->d = cur->d+v[cury][curx];
                        }
                    }
                    if(dy[i] == 0){
                        if(dx[i] == -1){
                            next->d = cur->d+h[cury][curx-1];
                        }
                        else if(dx[i] == 1){
                             next->d = cur->d+h[cury][curx];
                        }
                    }
                    parent[next->y][next->x] = make_pair(cury,curx);
                    cout << "pushed" << next->x << " " << next->y << endl;
                    if(next->y == n && next->x == m){
                        cout << next->d << endl; 
                        break;
                    }
                    pq.push(next);
                }
    		}
    	}
    }
    release();
    return 0;
}

