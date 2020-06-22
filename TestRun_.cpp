#include <stdio.h>
#include<bits/stdc++.h>
#define V 9
#include <time.h>
#include <windows.h>
#define m 10
#define r 20
using namespace std;
int seconds = 1000000;

///Combo
int minDistance(int dist[],bool sptSet[]){
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false &&
				dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

void printPath(int parent[], int j,char path[]){
	if (parent[j] == - 1)
		return;

	printPath(parent, parent[j],path);

	printf("-> %d via %c", j,path[j]);
}

int dijkstra(int graph[V][V],int metro[V][V] ,int src,int des){
	int dist[V];
	bool sptSet[V];
	int parent[V];
	char path[V];
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false,parent[0] = -1;;

	dist[src] = 0;

	for (int count = 0; count < V-1; count++){
	int u = minDistance(dist ,sptSet);

	sptSet[u] = true;
	for (int v = 0; v <V; v++)
	if (!sptSet[v]  && dist[u] != INT_MAX){

        if(metro[u][v] && graph[u][v]  && dist[u]+min(metro[u][v],graph[u][v]) < dist[v] ){
            ///Deciding distance when both pathways exist
            dist[v] = dist[u] + min(metro[u][v],graph[u][v]);
            ///Naming parent as metro or roadways
            if(metro[u][v]<=graph[u][v]){
                parent[v]=u;
                path[v]='m';
            }
            else{
                parent[v]=u;
                path[v]='r';
            }

        }
        else  if(graph[u][v] && dist[u]+graph[u][v] < dist[v]){
                parent[v] = u;
                path[v]='r';
                dist[v] = dist[u] + graph[u][v];
        }
	}

	}
///Printing the Path
cout<<"Journey: "<<src<<" -> "<<des;
cout<<endl<<"Cost: "<<dist[des]<<endl;
cout<<"Route: "<<src<<" ";
printPath(parent, des,path);
}

void delay(int a){

    clock_t start;
    start = clock();

    while(clock() - start < a){}

}


///Only Metro or Only Road
int minDistance1(int dist[],bool sptSet[]) {

    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false &&
                   dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printPath1(int parent[], int j) {

    // Base Case : If j is source
    if (parent[j] == - 1)
        return;

    printPath1(parent, parent[j]);

    printf("-> %d ", j);
}

void dijkstra1(int graph[V][V], int src,int des){


    int dist[V];


    bool sptSet[V];


    int parent[V];


    for (int i = 0; i < V; i++)
    {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }


    dist[src] = 0;


    for (int count = 0; count < V - 1; count++)
    {

        int u = minDistance(dist, sptSet);


        sptSet[u] = true;


        for (int v = 0; v < V; v++)


            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    ///Printing the Path
    cout<<"Journey: "<<src<<" -> "<<des;
    cout<<endl<<"Cost: "<<dist[des]<<endl;
    cout<<"Route: "<<src<<" ";
    printPath1(parent, des);
    cout<<endl<<endl;
}

// Driver Code
int main()
{
	int graph[V][V] = {
                        {0, 4, 0, 0, 0, 0, 0, 8, 0},
                        {4, 0, 8, 0, 0, 0, 0, 11, 0},
						{0, 8, 0, 7, 0, 4, 0, 0, 2},
						{0, 0, 7, 0, 9, 14, 0, 0, 0},
						{0, 0, 0, 9, 0, 10, 0, 0, 0},
						{0, 0, 4, 0, 10, 0, 2, 0, 0},
						{0, 0, 0, 14, 0, 2, 0, 1, 6},
						{8,11, 0, 0, 0, 0, 1, 0, 7},
						{0, 0, 2, 0, 0, 0, 6, 7, 0}
                                                        };

    int metro[V][V]={
                        {0 ,3 ,0 ,0 ,0 ,8 ,0 ,0 ,0},
                        {3 ,0 ,17 ,0 ,0 ,0 ,0 ,11,0},
                        {0 ,17 ,0 ,0 ,5 ,0 ,5 ,0 ,0},
                        {0 ,0 ,0 ,0 ,3 ,0 ,9 ,0 ,4},
                        {0 ,0 ,5 ,3 ,0 ,0 ,0 ,0 ,0},
                        {8 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0},
                        {0 ,0 ,5 ,0 ,0 ,0 ,0 ,10,7},
                        {0 ,11,0 ,0 ,0 ,0 ,10,0 ,0},
                        {0 ,0 ,0 ,4 ,0 ,0 ,7 ,0 ,0}
                                                        };

    for(int i=0 ; i<V ; i++){
        for(int j=0 ; j<V ; j++){
            metro[i][j] *= m;
            graph[i][j] *= r;
        }
    }


    bool userType;

    cout<<"\t\t\t"<<"Welcome to TravelGuide"<<endl<<endl<<endl;

    //delay(0.5*seconds);

    cout<<"Please Enter your user type from the following: "<<endl;
    cout<<"0. Customer"<<endl;
    cout<<"1. Administration"<<endl<<endl;

    cin>>userType;

    if(!userType){ ///Customer Mode
        //system("clear");

        cout<<"\t\t\t"<<"Welcome to TravelGuide"<<endl<<endl<<endl;

        ///delay(1.5*seconds);

        cout<<"Enter Your respective destinations: "<<endl<<endl;

        ///string startLoc , endLoc;

        int startLoc,endLoc;

        cout<<"FROM: ";
        cin>>startLoc;

        cout<<"TO: ";
        cin>>endLoc;

        cout<<endl<<endl;
        cout<<"1:\tCombining both metro and road"<<endl<<endl;
        dijkstra(graph , metro , startLoc , endLoc);
        cout<<""<<endl;

        cout<<endl<<"2:\tOnly road"<<endl<<endl;
        dijkstra1(graph , startLoc , endLoc);
        cout<<""<<endl;

        cout<<endl<<"3:\tOnly metro"<<endl<<endl;
        dijkstra1(metro , startLoc , endLoc);
        cout<<""<<endl;

        cout<<endl<<endl<<endl;

    }
    else{   ///Admin mode

        cout<<"\t\t\t"<<"Welcome to TravelGuide"<<endl<<endl<<endl;

    }


	return 0;
}
