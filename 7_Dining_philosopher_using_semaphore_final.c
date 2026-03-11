#include<stdio.h>
int p[5];
int ch[5];

void signal(int z){
int j=(z+1)%5;
p[z]=0;// philosopher is done eating
ch[z]=0;// releasing the chopsticks
ch[j]=0;// releasing the chopsticks
}

void wait(int y){

int r=(y+1)%5;

if((ch[y]==0)&&(ch[r])==0){
    p[y]=1;// philosopher is eating
    ch[y]=1;// acquiring the chopsticks
    ch[r]=1; // acquiring the chopsticks
}

else if(p[y]==1){
    int w;
    printf("do you want philosopher %d to stop eating ",y);
    scanf("%d",&w);
    if(w==1)
        signal(y);
}

else{
    printf("chopstick %d %d are busy\n",y,r);
    printf("philosoper %d  has to wait\n",y);
}
}

int main(){
    int i,u;
    for(i=0;i<5;i++){
        p[i]=0;
        ch[i]=0;
    }

    do{
    for(i=0;i<5;i++){

            if(p[i]==0){
        printf("philosopher %d is thinking\n",i);
        printf("\n");
        }

        else{
            printf("philosopher %d is eating \n",i);
            printf("\n");
        }
    }
    int s;
    printf("Which philosopher wants to eat:\n");
    scanf("%d",&s);
    wait(s);
    printf("do you want to continue press 1\n");
    scanf("%d",&u);
    }while(u==1);
return 0;
}