
#include <iostream>
#include <fstream>
#include <math.h>
#include <queue>
#include <string>
using namespace std;
#define INF 712271227122;
typedef stringstream ss;
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
	double d;
    bool visited;
	node(){
		d = INF;
        visited = false;
	}
    char parent;
};
bool operator<(node a,node b){
	return a.d > b.d;
}

void readParameters()
{
    ifstream ifs("input", ifstream::binary);

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
    priority_queue<node>pq;
    node **map;
    map = new node*[n+1];
    for(int i = 0;i<=n;i++){
        map[i] = new node[m+1];
        for(int j = 0;j<=m;j++){
            map[i][j].x = j;
            map[i][j].y = i;
        }
    }
    map[0][0].d = 0;
    pq.push(map[0][0]);
    while(!pq.empty()){
        int curx = -1;
        int cury = -1;       
        while(!pq.empty() && map[cury = pq.top().y][curx = pq.top().x].visited)
            pq.pop();
        if(curx == -1 || cury == -1) break;
        if(curx == m && cury == n) break;
        map[cury][curx].visited = true;
        for(int i = 0;i<4;i++){
            if(curx +dx[i] >= 0 && curx+dx[i]<= m && cury+dy[i] >= 0 && cury+dy[i]<= n){
                if(!map[cury+dy[i]][curx+dx[i]].visited){
                    if(dx[i] == 0){
                        if(dy[i] == -1){
                            if(map[cury][curx].d+v[cury-1][curx]<map[cury+dy[i]][curx+dx[i]].d){
                                map[cury+dy[i]][curx+dx[i]].parent = 'u';
                                map[cury+dy[i]][curx+dx[i]].d = map[cury][curx].d+v[cury-1][curx];
                                pq.push(map[cury+dy[i]][curx+dx[i]]);
                            }
                        }
                        else if(dy[i] == 1){
                            if(map[cury][curx].d+v[cury][curx]<map[cury+dy[i]][curx+dx[i]].d){
                                map[cury+dy[i]][curx+dx[i]].parent = 'd';
                                map[cury+dy[i]][curx+dx[i]].d = map[cury][curx].d+v[cury][curx];
                                pq.push(map[cury+dy[i]][curx+dx[i]]);
                            }
                        }
                    }
                    if(dy[i] == 0){
                        if(dx[i] == -1){
                            if(map[cury][curx].d+h[cury][curx-1]<map[cury+dy[i]][curx+dx[i]].d){
                                map[cury+dy[i]][curx+dx[i]].parent = 'l';
                                map[cury+dy[i]][curx+dx[i]].d = map[cury][curx].d+h[cury][curx-1];
                                pq.push(map[cury+dy[i]][curx+dx[i]]);
                            }
                        }
                        else if(dx[i] == 1){
                             if(map[cury][curx].d+h[cury][curx]<map[cury+dy[i]][curx+dx[i]].d){
                                map[cury+dy[i]][curx+dx[i]].parent = 'r';
                                map[cury+dy[i]][curx+dx[i]].d = map[cury][curx].d+h[cury][curx];
                                pq.push(map[cury+dy[i]][curx+dx[i]]);
                             }
                        }
                    }
                    
                }
            }
        }
    }
    ofstream ofs("result.txt", ofstream::binary);
    ofs << pq.top().d << endl;
    int px = pq.top().x;
    int py = pq.top().y;
    string path = "";
    while(px !=0  || py!=0){
        path+=map[py][px].parent;
        if(map[py][px].parent == 'u'){
            py++;
        }
        else if(map[py][px].parent == 'd'){
            py--;
        }
        else if(map[py][px].parent == 'l'){
            px++;
        }
        else if(map[py][px].parent == 'r'){
            px--;
        }
    }
    for(int i = path.length()-1;i>=0;i--){
        ofs  << path[i];
    }
    ofs.close();
    release();
    return 0;
}

