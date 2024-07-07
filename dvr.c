#include<stdio.h>
struct router{
unsigned from[50];
unsigned cost[50];


}routingtable[50];

int main(){
int costmat[40][40];int routers;
printf("enter the number of routers\n");
scanf("%d",&routers);
printf("enter the cost matrix\n");
for(int i=0;i<routers;i++)
{for(int j=0;j<routers;j++)
{
scanf("%d",&costmat[i][j]);
costmat[i][i]=0;
routingtable[i].cost[j]=costmat[i][j];
routingtable[i].from[j]=j;

}
}

int otherpathexists;
do{
for(int i=0;i<routers;i++)
{ for(int j=0;j<routers;j++)
{ for(int k=0;k<routers;k++)
{   
   otherpathexists=0;
        if(costmat[i][j]>costmat[i][k]+routingtable[k].cost[j])
        {
          costmat[i][j]=routingtable[i].cost[k]+routingtable[k].cost[j];
          routingtable[i].from[j]=k;
          otherpathexists=1;
        
        }
}

}

}



}while(otherpathexists!=0);

for(int i=0;i<routers;i++)
{  
printf("for router %d\n",i+1);
for(int j=0;j<routers;j++)
{printf("the router %d routes from %d by %d\n",j+1,routingtable[i].from[j],routingtable[i].cost[j]);
}
}

}
