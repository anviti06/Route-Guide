#include <stdio.h>
#include<bits/stdc++.h>
#include<cstring>
#define V 20
#define H 24 ///traffic matrix height ///time starts from 0600
#define ST 6 ///start time
#include <time.h>
#include <windows.h>
#include<fstream>
#define RoadCost 10
#define MetroCost 3
using namespace std;
int seconds = 1000000;
int final[3][3];
string loc[V] = {"Samaypur Badli" , "Azadpur" , "GTB Nagar" , "Model Town" ,
                "Hauz Khas" , "Dilli Hat INA" , "Lajpat Nagar" , "Qutab Minar" ,
                "Rajiv Chowk" , "New Delhi" , "ITO" , "Central Secretriat" , "Kashmere Gate" ,"Vidhan Sabha" , "Mandi House" ,
                 "Netaji Subhash Place" , "Rajouri Garden" ,
                 "Yamuna Bank" , "Vaishali" , "Botanical Garden"};

///*********************************TRAFFIC DECIDING FUNCTIONS**********************************

///Finding a traffic deciding Factor during different time slots and time zones
//Returns "average" observed traffic factor
//for given time(24 HRS Format) in Northern Zone.
float northZone(int time){
    float factor = 1.0;
    if(time <= ST)
        return factor;
    else if(time <= 9)
        return time*factor;                     //Randomly applied equation
    else if(time <= 15)
    {
        return ((float)(54+time))/7;            //Randomly applied equation
    }
    else if(time <= 18)
    {
        int d = time%ST;                        //Randomly applied equation
        if(!d)
            time/=ST;
        else
            time = time%ST;
        return time*time - ST;
    }
    else
        return 1.5*factor;                      //Randomly applied equation
}

//Returns "average" observed traffic factor
//for given time(24 HRS Format) in Southern Zone.
float southZone(int time){
    float factor = 1.0;
    if(time <= ST)
        return factor;
    else if(time <= 9)
        return time*factor*0.75;                //Randomly applied equation
    else if(time <= 15)
    {
        return ((float)(40+time))/8;            //Randomly applied equation
    }
    else if(time <= 18)                         //Randomly applied equation
    {
        int d = time%ST;
        if(!d)
            time/=ST;
        else
            time = time%ST;
        return abs(time*time - 2*ST);           //Randomly applied equation
    }
    else
        return 2.5*factor;
}

//Returns "average" observed traffic factor
//for given time(24 HRS Format) in Central Zone.
float centralZone(int time){
    float factor = 1.0;
    if(time <= ST)
        return factor;
    else if(time <= 11)
        return time*factor;                 //Randomly applied equation
    else if(time <= 15)
    {
        return ((float)(60+time))/7;        //Randomly applied equation
    }
    else if(time <= 20)
    {
        int d = time%ST;                    //Randomly applied equation
        if(!d)
            time/=ST;
        else
            time = time%ST;
        return abs(time*time - ST);
    }
    else
        return 2.0*factor;
}

//Returns "average" observed traffic factor
//for given time(24 HRS Format) in Western Zone.
float westZone(int time){
    float factor = 1.0;
    if(time <= ST)
        return factor;
    else if(time <= 9)
        return time*factor;                 //Randomly applied equation
    else if(time <= 17)
    {
        return ((float)(54+time))/7;        //Randomly applied equation
    }
    else if(time <= 20)
    {
        int d = time%ST;                    //Randomly applied equation
        if(!d)
            time/=ST;
        else
            time = time%ST;
        return time*time - ST;              //Randomly applied equation
    }
    else
        return 1.5*factor;                  //Randomly applied equation
}

//Returns "average" observed traffic factor
//for given time(24 HRS Format) in Eastern Zone.
float eastZone(int time){
    float factor = 1.0;
    if(time <= ST)
        return factor;
    else if(time <= 8)
        return time*factor;
    else if(time <= 14)
    {
        return ((float)(45+time))/7;
    }
    else if(time <= 18)
    {
        int d = time%ST;
        if(!d)
            time/=ST;
        else
            time = time%ST;
        return time*time - ST;
    }
    else
        return 1.2*factor;
}
//The function returns the zone corresponding to
//the input location(node) value.
string zoneClassifier(int location){
    if(location <= 3)
        return "Northern";
    else if(location <= 7)
        return "Southern";
    else if(location > 7 && location < 15)
        return "Central";
    else if(location < 17)
        return "Western";
    else
        return "Eastern";
}

//The function returns the evaluated
//traffic factor for a given location in
//given time bracket in accordance to its Zone.
float trafficFactorRoad(int time,int location){
    string zone = zoneClassifier(location);
    float mulfactor = 1.0;
    if(zone == "Northern"){
        mulfactor = northZone(time);
    }
    else if(zone == "Southern")
    {
        mulfactor = southZone(time);
    }

    else if(zone == "Central")
    {
        mulfactor = centralZone(time);
    }

    else if(zone == "Western")
    {
        mulfactor = westZone(time);
    }
    else
    {
        mulfactor = eastZone(time);
    }

    return mulfactor;
}

void printTraffic(int arr[V][V]){

    for(int i=0 ; i<V ; i++){
        for(int j=0 ; j<V ; j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<endl;
}

///*********************************************************************************************************************


///****************************FINDING SHORTEST PATH FUNCTIONS WITH ROUTE(DIJKSTRA'S)***********************************
//The function to find the nearest node from the current node or
//To find the next min distance node as we do in dijkstra's while solving manually
int minDistance(int dist[],bool visited[]){
	int min = INT_MAX , min_index;
	for (int v = 0; v < V; v++)
		if (visited[v] == false && dist[v] <= min)
                min = dist[v], min_index = v;

	return min_index;
}

//The function prints the path of the source to destination
// along with indicating the mode of transport used
void printPathWithModeOfTransport(int parent[], int j,char path[]){

	if (parent[j] == - 1){
        //cout<<"error";
		return;
	}

	printPathWithModeOfTransport(parent, parent[j],path);

	string temp;
    if(path[j]=='r'){
        temp="Road";
    }
    else{
        temp="Metro";
    }
    cout<<" -> "<<loc[j]<<" via "<<temp<<endl;
	//printf("-> % via %c", j,path[j]);
}


//The function finds the shortest distance taking in consideration both metro and road map
int dijkstra(int road[V][V],int metro[V][V] ,int src,int des, bool flag){
	int dist[V];
	bool visited[V];
	int parent[V];
	char path[V];

	//Initialising the arrays
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX , visited[i] = false , parent[src] = -1;

    //Defining the distance of src-src as zero
	dist[src] = 0;

	//
	for (int count = 0; count < V-1; count++){

        //'u' is the node from which now all distances will be calculated
        //  OR the node used for starting next row in manual solving
        int u = minDistance(dist ,visited);
        visited[u] = true;

        for (int v = 0; v <V; v++)

            if (!visited[v]  && dist[u] != INT_MAX){

                if(metro[u][v] && road[u][v]  &&                           //Checking if a connection exist between current node and current vertex or not
                   dist[u]+min(metro[u][v],road[u][v]) <= dist[v]){           //If exists then is the new considering distance less than the previous distance

                        ///Deciding distance when both pathways exist
                        dist[v] = dist[u] + min(metro[u][v],road[u][v]);


                        ///Naming parent as metro or roadways
                        if(metro[u][v]<=road[u][v]){
                            parent[v]=u;      //For storing the parent of each node
                            path[v]='m';
                        }

                        else{
                            parent[v]=u;
                            path[v]='r';
                        }

                }

            }

	}
if(flag==0){
        if(dist[des]!=INT_MAX)
            return dist[des];
        else
            return -1;
}
//return dist[des];
else if (flag==1){
    if(dist[des]!=INT_MAX){
        cout<<endl<<endl<<"So here is your Final Route !!!"<<endl;
        cout<<endl<<endl<<"Journey: "<<loc[src]<<" -> "<<loc[des]<<endl<<endl;
        cout<<"Route: "<<endl<<loc[src]<<" ";
        printPathWithModeOfTransport(parent, des,path);
        cout<<endl<<endl;
        return dist[des];
    }
    else {
        cout<<"Route does not Exist";
        return 0;
    }
}

}
//The function prints the path from source to destination without specifying the mode of transport
void printPath(int parent[], int j,string x) {
    if (parent[j] == - 1)
        return;

    printPath(parent, parent[j],x);

    cout<<" -> "<<loc[j]<<" via "<<x<<endl;

}

//The function to find the shortest path by taking in consideration only one map -- Either road map or metro map
int dijkstra1(int graph[V][V], int src,int des, bool flag,string x){
    int dist[V];
    bool visited[V];
    int parent[V];
    for (int i = 0; i < V; i++)    {
        parent[src] = -1;
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    dist[src] = 0;
    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, visited);
        visited[u] = true;

        for (int v = 0; v < V; v++)

            if (!visited[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

if(flag==0){
    if(dist[des]!=INT_MAX)
            return dist[des];
        else
            return -1;
}
else if (flag==1){
    if(dist[des]!=INT_MAX){
        ///Printing the Path
        cout<<endl<<endl<<"So here is your Final Route !!!"<<endl;
        cout<<endl<<endl<<"Journey: "<<loc[src]<<" -> "<<loc[des]<<endl<<endl;
        cout<<"Route: "<<endl<<loc[src]<<" ";
        printPath(parent, des,x);
        cout<<endl<<endl;
        return dist[des];
    }
    else {
    cout<<"Route does not Exist";
    return 0;
    }
}


}



// Driver Code
int main(){



//system("color %");




    //Basic Distance Matrix
    int road[V][V] = {//0   1  2  3  4  5  6  7  8  9 10 11  12 13 14 15 16 17 18 19
                      /*0*/{0, 4, 6, 0, 9, 0, 0, 8, 0, 3, 0, 9, 0, 0, 0, 0, 0, 0, 0, 8},
                      /*1*/{4, 0, 8, 0, 3, 0, 0,11, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0},
                      /*2*/{6, 8, 0, 7, 0, 4, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      /*3*/{0, 0, 7, 0, 9,14, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0},
                      /*4*/{9, 3, 0, 9, 0,10, 0,11, 0,12, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0},
                      /*5*/{0, 0, 4,14,10, 0, 2, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0},
                      /*6*/{0, 0, 0, 0, 0, 2, 0, 1, 6, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0},
                      /*7*/{8,11, 0, 0, 11,0, 1, 0, 7, 0, 0, 0, 0, 3, 0,16, 0, 0, 0, 0},
                      /*8*/{0, 0, 2, 0, 0, 0, 6, 7, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      /*9*/{3, 0, 0, 0,12, 0, 0, 0, 2, 0, 5, 0, 8, 4, 0, 0, 0, 0, 0, 0},
                     /*10*/{0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0,11, 0, 0},
                     /*11*/{9, 0, 0, 0, 2, 0, 8, 0, 0, 0, 4, 0, 7, 9, 0, 0, 0, 0, 0, 0},
                     /*12*/{0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 7, 0, 3, 0, 0, 0, 0, 0,14},
                     /*13*/{0, 0, 0, 5, 0, 7, 0, 3, 0, 4, 0, 9, 3, 0, 9, 4, 0, 0, 0, 0},
                     /*14*/{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 1, 0, 0,18, 0},
                     /*15*/{0, 0, 0, 0, 0, 0, 0,16, 0, 0, 0, 0, 0, 4, 1, 0, 8, 0, 0, 0},
                     /*16*/{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 6, 0, 0},
                     /*17*/{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 6, 0, 4, 0},
                     /*18*/{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 7},
                     /*19*/{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,14, 0, 0, 0, 0, 0, 7, 0}
    };

    int metro[V][V]={//  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
                        {0 ,3 ,0 ,0 ,0 ,8 ,0 ,0 ,0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0,14},
                        {3 ,0 ,17,0 ,0 ,0 ,0 ,11,0, 0, 0, 0, 0, 0,12, 0, 0, 0, 0, 0},
                        {0 ,17,0 ,0 ,5 ,0 ,5 ,0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0},
                        {0 ,0 ,0 ,0 ,3 ,0 ,9 ,0 ,4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0 ,0 ,5 ,3 ,0 ,0 ,0 ,0 ,0,12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {8 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0,18, 0, 0, 0, 0},
                        {0 ,0 ,5 ,9 ,0 ,0 ,0 ,10,7, 0, 0, 0, 0, 0,11, 0, 0, 0, 0, 0},
                        {0 ,11,0 ,0 ,0 ,0 ,10,0 ,0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0},
                        {0 ,0 ,0 ,4 ,0 ,0 ,7 ,0 ,0, 2, 0, 6, 0, 0, 0, 6, 0, 0, 0, 0},
                        {0, 0, 0, 0,12, 0, 0, 0, 2, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 7,10, 0, 0},
                        {9, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
                        {0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 0, 4, 0, 0, 0, 0, 0},
                        {0,12, 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 4, 0, 1, 6, 0, 0, 0},
                        {0, 0, 0, 0, 0,18, 0, 0, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 1, 0, 0, 2, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10, 0, 0, 0, 0, 0, 2, 0, 4, 5},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 1},
                        {14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1, 0}



    };

    int tempMetro[V][V]={0},tempRoad[V][V]={0};

    //Initializing with "unit" traffic
    float roadTraffic[V][V];
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++)
        {
            roadTraffic[i][j] = 1.0;
        }
    }


    system("color A0");
    cout<<"\t\t\t\t\t\t"<<"Welcome to TravelGuide"<<endl<<endl;

    cout<<"\t\t    You are on the go ! Lets begin our journey be seamless experience ! Go ahead and enjoy your ride.\n\n";

        //delay(1.5*seconds);
    for(int i=0;i<V;i++){
        cout << i << " --> " <<loc[i]<<endl;
    }
    cout<<"\nEnter Your respective destinations :- In the form of numeric codes designated against the respective locations"<<endl<<endl;

        ///string startLoc , endLoc;

        int startLoc,endLoc;

        cout<<"From : ";
        cin>>startLoc;
        cout<<endl;
        cout<<"To : ";
            cin>>endLoc;

        cout<<endl<<"Enter Your Operational Time (24 HRS Format :: 1 -> 24) : ";

        int time;
        cin>>time;

        cout<<endl;

        system("CLS");
///*******************************************************************************************************************************************************************************
        ///PART 1:
            system("color E1");
        //1. Only Distance:
            final[0][0]=dijkstra1(road , startLoc , endLoc,0,"Road");            //Only Raod
            final[0][1]=dijkstra1(metro , startLoc , endLoc,0,"Metro");           //Only Metro
            final[0][2]=dijkstra(road , metro , startLoc , endLoc,0);     //Both Metro and Road

        //2. Only Cost:
                for(int i=0;i<V;i++){
                    for(int j=0;j<V;j++){
                        tempMetro[i][j]+=metro[i][j]*MetroCost;
                        tempRoad[i][j]+=road[i][j]*RoadCost;
                    }
                }
            final[1][0]=dijkstra1(tempRoad , startLoc , endLoc,0,"Road");            //Only Raod
            final[1][1]=dijkstra1(tempMetro , startLoc , endLoc,0,"Metro");           //Only Metro
            final[1][2]=dijkstra(tempRoad , tempMetro , startLoc , endLoc,0);     //Both Metro and Road
            //cout<<final[1][2];
            //cout<<dijkstra(tempRoad , tempMetro , startLoc , endLoc,1)<<endl;

        //3. Combining Cost and Traffic (i.e Most Efficient Method) :
                for(int i=0;i<V;i++){
                    float p1 = trafficFactorRoad(time,i);
                    for(int j=0;j<V;j++){
                        if(i==j)
                            continue;
                        float p2 = trafficFactorRoad(time,j);
                        roadTraffic[i][j] = (p1+p2)/2;
                        tempRoad[i][j]+=(tempRoad[i][j] * (roadTraffic[i][j]/4));
                    }
                }
            final[2][0]=dijkstra1(tempRoad , startLoc , endLoc,0,"Road");            //Only Raod
            final[2][1]=dijkstra1(tempMetro , startLoc , endLoc,0,"Metro");           //Only Metro
            final[2][2]=dijkstra(tempRoad , tempMetro , startLoc , endLoc,0);     //Both Metro and Road

        //Printing the final matrix:

        cout<<"Mode of transport\t\tOnly Road Travel\tOnly Metro Travel\tUsing both Road and Metro Travel"<<endl<<endl;
        cout<<"Factors Considered"<<endl<<endl;
        cout<<"1) By Distance "<<endl<<endl;
        cout<<"Net Amount :"<<"\t\t\t\t"<<final[0][0]<<"\t\t\t"<<final[0][1]<<"\t\t\t"<<final[0][2]<<endl<<endl<<endl;
        //cout<<"Route Followed :"<<endl<<endl<<endl;

        cout<<"2) By Cost Of Travel"<<endl<<endl;
        cout<<"Net Amount :"<<"\t\t\t\t"<<final[1][0]<<"\t\t\t"<<final[1][1]<<"\t\t\t"<<final[1][2]<<endl<<endl<<endl;
        //cout<<"Route Followed:"<<endl<<endl<<endl;

        cout<<"3) By Cost and "<<endl;
        cout<<"Traffic Included"<<endl<<endl;
        cout<<"Net Amount :"<<"\t\t\t\t"<<final[2][0]<<"\t\t\t"<<final[2][1]<<"\t\t\t"<<final[2][2]<<endl<<endl;
        //cout<<"Route Followed"<<endl<<endl<<endl;




///*******************************************************************************************************************************************************************************

        ///PART 2:



        cout<<endl<<endl<<"Enter the Mode Of Transport and the Factors considered along with your details to begin your ride : "<<endl;
        cout<<"\nChoose your priority of travel : \n";
        cout<<"\n1 -> Distance\n2 -> Cost \n3 -> Cost With Trafiic Included\n\n ";
        cout<<"Enter your priority : ";
        int ch1,ch2;
        cin>>ch1;
        cout<<"\n\nChoose your mode of travel : \n";
        cout<<"\n1 -> Road\n2 -> Metro\n3 -> Road & Metro\n\n";
        cout<<"Enter your travel mode : ";
        cin>>ch2;

        //system("CLS");
        system("color E1");
        cout<<"\nAlright buddy , we got your travel backed up!\n";
        cout<<"\nJust a step away , kindly enter your details\n";
        string name,mob,email;
        cout<<"\nEnter your name :";
        fflush(stdin);
        getline(cin,name);
        cout<<"\nEnter your mobile number : ";
        cin>>mob;
        cout<<"\nEnter your email ID : ";
        cin>>email;


        system("CLS");
        system("color F4");
        cout<<"\nDear "<<name<<" you're all set to go , enjoy your ride!\nThankyou!\n";


         ch1--;ch2--;
        if(ch1==0 && ch2==0)  cout<<endl<<endl<<"The final cost is :"<<dijkstra1(road , startLoc , endLoc,1,"Road")<<endl<<endl;
        if(ch1==0 && ch2==1)  cout<<endl<<endl<<"The final cost is :"<<dijkstra1(metro , startLoc , endLoc,1,"Metro")<<endl<<endl;
        if(ch1==0 && ch2==2)  cout<<endl<<endl<<"The final cost is :"<<dijkstra(road , metro , startLoc , endLoc,1)<<endl<<endl;

        if(ch1==2 && ch2==0)  cout<<endl<<endl<<"The final cost is :"<<dijkstra1(tempRoad , startLoc , endLoc,1,"Road")<<endl<<endl;
        if(ch1==2 && ch2==1)  cout<<endl<<endl<<"The final cost is :"<<dijkstra1(tempMetro , startLoc , endLoc,1,"Metro")<<endl<<endl;
        if(ch1==2 && ch2==2)  cout<<endl<<endl<<"The final cost is :"<<dijkstra(tempRoad , tempMetro , startLoc , endLoc,1)<<endl<<endl;

        //Converting again to cost matrix
        for(int i=0;i<V;i++){
                    for(int j=0;j<V;j++){
                        tempMetro[i][j]+=metro[i][j]*MetroCost;
                        tempRoad[i][j]+=road[i][j]*RoadCost;
                    }
                }

        if(ch1==1 && ch2==0)  cout<<endl<<endl<<"The final cost is :"<< dijkstra1(tempRoad , startLoc , endLoc,1,"Road")<<endl<<endl;
        if(ch1==1 && ch2==1)  cout<<endl<<endl<<"The final cost is :"<<dijkstra1(tempMetro , startLoc , endLoc,1,"Metro")<<endl<<endl;
        if(ch1==1 && ch2==2)  cout<<endl<<endl<<"The final cost is :"<<dijkstra(tempRoad , tempMetro , startLoc , endLoc,1)<<endl<<endl;




}

