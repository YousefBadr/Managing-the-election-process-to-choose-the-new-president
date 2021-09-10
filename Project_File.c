#include <stdio.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"

int Arr[100];

void shuffle(int *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}
void makeRandomArray(int *array ,int NumOfCandidates )
{
    int x, p;
    int count;
    int i=0;
    srand(time(NULL));

    for(count=0;count<NumOfCandidates;count++)
    {
        array[count]=rand()%NumOfCandidates+1;
    }
    while(i<NumOfCandidates){
        int r=rand()%NumOfCandidates+1;

        for (x = 0; x < i; x++)
        {
            if(array[x]==r){
                break;
            }
        }
        if(x==i){
            array[i++]=r;
        }
    }
}
void printRandoms( int *array ,int NumOfCandidates, int NumOfVoters )
{
   FILE * fp;
   int i,j,c;
   fp = fopen ("Data.txt","w+");

   //array[NumOfCandidates];
    array=malloc(NumOfCandidates*sizeof(int));
    makeRandomArray(array , NumOfCandidates);

     int n;
     fprintf (fp, "%d ",NumOfCandidates);
     fprintf (fp, "%d\n",NumOfVoters);

for(j=0 ; j<NumOfVoters ; j++)
   {
      for ( c = 0; c <NumOfCandidates; c++)
        {
             n = array[c];
             fprintf (fp, "%d ",n);
        }
        shuffle(array , NumOfCandidates);
           fprintf (fp,"\n");
   }
     fclose (fp);
}

int main(int argc , char * argv[])
{
    int temp=-1;
    int my_rank;
    int p,i,j,k,mi=0,mj=0;
    int portionSize,rem;
    int P_Array;
    int stage=1;
    int Candidates,Voters;
    int *subFirst_Round,*First_Round;
    int Highest_1=0,Highest_2=0;
    int qual1=-1,qual2=-1;
    int flag=0;
    int flageeeeeem=0;
    char*str= malloc (280*sizeof(char));
    int choice=0;
    FILE *fptr;
    MPI_Status status;
    MPI_Init( &argc , &argv );
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if(my_rank==0)
    {
        printf("1-Generate a data file and calculate results.\n2-Calculate Results on data already generated.\n>>");
        scanf("%d",&choice);
        if(choice==1)
           printRandoms(Arr , 5 , 50000);
    }




    fptr=fopen("Data.txt","r");
    if(fptr == NULL)
         {
           printf("Error!");
           exit(1);
          }

    if (my_rank == 0 )
    {
          fscanf(fptr,"%d", &Candidates);
          fscanf(fptr,"%d", &Voters);
          if(p>Voters)
            p=Voters;
          portionSize=Voters/p;
          rem=Voters%p;
     }

   MPI_Bcast (&Candidates , 1, MPI_INT,0,MPI_COMM_WORLD);
   MPI_Bcast (&Voters , 1, MPI_INT,0,MPI_COMM_WORLD);
   MPI_Bcast (&portionSize , 1, MPI_INT,0,MPI_COMM_WORLD);

   subFirst_Round = malloc (Candidates*sizeof(int));
   First_Round = malloc (Candidates*sizeof(int));
while(1)
{
    fseek(fptr,0,SEEK_SET);
    for(i=0;i<Candidates;i++)
    {
        subFirst_Round[i]=0;
        First_Round[i]=0;
    }
    //goto desired line
    for(i=0;i<portionSize*my_rank+1;i++)
         fgets(str,280,fptr);
        //printf("my Rank= %d\n",my_rank);
    for(i=0;i<portionSize;i++)
         {
         flageeeeeem=0;
         fgets(str,280,fptr);
         int counter=1;
         int sum=0;

          for(j=0;j<280;j++)
          {
              if(str[j]=='1' || str[j]=='2'|| str[j]=='3'|| str[j]=='4'|| str[j]=='5'|| str[j]=='6'|| str[j]=='7'|| str[j]=='8'|| str[j]=='9'|| str[j]=='0')
              {
                  int num=str[j]-'0';
                  sum*=10;
                  sum+=num;
              }
              else if(sum!=0)
              {

                  if(counter==1)
                  {
                if(stage==1 )
                  {
                      subFirst_Round[sum-1]+=1;
                  }
                  else
                  {
                      if(sum-1==Highest_1 || sum-1==Highest_2)
                      {
                      if(flageeeeeem==0)
                                   {
                                   flageeeeeem=1;
                                   subFirst_Round[sum-1]+=1;
                                   }
                      }
                  }
                    counter++;
                  }
                  else if(counter!=1 )
                  {
                      if(stage!=1)
                      {
                           if(sum-1==Highest_1 || sum-1==Highest_2)
                               {
                                   if(flageeeeeem==0)
                                   {
                                   flageeeeeem=1;
                                   subFirst_Round[sum-1]+=1;
                                   }
                               }
                      }
                       counter++;
                  }
//                   if(sum==2)
//                      {
//                          printf("--after >>rank=%d sum=%d counter=%d stage=%d subFirst_Round[1]=%d\n",my_rank,sum,counter,stage,subFirst_Round[1]);
//                      }
                  sum=0;
              }
          }

         }





if (my_rank == 0 && rem!=0)
    {
    //  printf("rem=%d Voters-rem+1=%d\n",rem,Voters-rem+1);
      fseek(fptr,0,SEEK_SET);
      for(i=0;i<Voters-rem+1;i++)
         fgets(str,280,fptr);

    //printf("my Rank= %d\n",my_rank);
    for(i=0;i<rem;i++)
         {
         flageeeeeem=0;
         fgets(str,280,fptr);
         int counter=1;
         int sum=0;
           for(j=0;j<280;j++)
          {
              if(str[j]=='1' || str[j]=='2'|| str[j]=='3'|| str[j]=='4'|| str[j]=='5'|| str[j]=='6'|| str[j]=='7'|| str[j]=='8'|| str[j]=='9'|| str[j]=='0')
              {
                  int num=str[j]-'0';
                  sum*=10;
                  sum+=num;
              }
              else if(sum!=0)
              {

                  if(counter==1)
                  {
                if(stage==1 )
                  {
                      subFirst_Round[sum-1]+=1;
                  }
                  else
                  {
                      if(sum-1==Highest_1 || sum-1==Highest_2)
                      {
                      if(flageeeeeem==0)
                                   {
                                   flageeeeeem=1;
                                   subFirst_Round[sum-1]+=1;
                                   }
                      }
                  }
                    counter++;
                  }
                  else if(counter!=1 )
                  {
                      if(stage!=1)
                      {
                           if(sum-1==Highest_1 || sum-1==Highest_2)
                               {
                                   if(flageeeeeem==0)
                                   {
                                   flageeeeeem=1;
                                   subFirst_Round[sum-1]+=1;
                                   }
                               }
                      }
                       counter++;
                  }
                  sum=0;
              }
          }
         }
    }



      MPI_Reduce (subFirst_Round ,First_Round,Candidates,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    //  printf("aftereeeeeeee>>>>rank=%d  First_Round[2]=%d\n",my_rank,subFirst_Round[2]);

if(my_rank==0)
   {
    printf("Stage=%d\n",stage);
    for(i=0;i<Candidates;i++)
    {
        //printf("First_Round[%d]= %d \n",i,First_Round[i]);
         printf("Candidate %d got %d/%d which is %.2f%%\n", i + 1, First_Round[i], Voters, (First_Round[i]*1.0/Voters) * 100);
    }

float fVoters=Voters;


  for(i=0;i<Candidates;i++)
    {
        temp=First_Round[i];
        if(temp/fVoters>0.5)
        {
            printf("Candidate %d won in stage %d with %d votes.\n",i+1,stage,First_Round[i]);
            flag=1;
            break;
        }
        if(First_Round[i]>=First_Round[Highest_1])
           Highest_1=i;
    }
    if(flag==0)
    {
    stage+=1;
    First_Round[Highest_1]=0;
    for(i=0;i<Candidates;i++)
    {
       if(First_Round[i]>=First_Round[Highest_2])
           Highest_2=i;
    }

    }
    if(stage==3)
    {
        printf("it's a draw between %d and %d.\n",Highest_1+1,Highest_2+1);
        flag=1;
    }

   }
   MPI_Bcast (&flag , 1, MPI_INT,0,MPI_COMM_WORLD);
   MPI_Bcast (&stage , 1, MPI_INT,0,MPI_COMM_WORLD);
   MPI_Bcast (&Highest_1 , 1, MPI_INT,0,MPI_COMM_WORLD);
   MPI_Bcast (&Highest_2 , 1, MPI_INT,0,MPI_COMM_WORLD);

if(flag==1)
    break;
}
    if(my_rank==0)
      fclose(fptr);

    MPI_Finalize();
    return 0;
}



