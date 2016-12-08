#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "coord.h"

#define N 40


void affiche(int (*mat)[N],int taille);
void flushMat(int (*mat)[N],int taille);
void setMat(int (*mat)[N],int taille, Coordonnee *alive);

void initAlive(Coordonnee *alive,int taille);
void flushAlive(Coordonnee *alive,int taille);
void setAlive(int (*mat)[N],int taille,Coordonnee *alive);

int cornerTopLeft(int (*mat)[N]);
int cornerTopRight(int (*mat)[N]);
int cornerBottomLeft(int (*mat)[N]);
int cornerBottomRigth(int (*mat)[N]);

int borderTop(int (*mat)[N],int i, int j);
int borderBottom(int (*mat)[N],int i, int j);
int borderLeft(int (*mat)[N],int i, int j);
int borderRight(int (*mat)[N],int i, int j);


int defaultSum(int(*mat)[N],int i,int j);

int main()
{
    int compteur =0;
    int mat[N][N];
    Coordonnee alive[N*N];

    flushMat(mat,N);
    affiche(mat,N);
    flushAlive(alive,N*N);
    initAlive(alive,N*N);
    setMat(mat,N,alive);
    affiche(mat,N);

    while(1){
        printf("Iteration : %d\n",compteur);
        flushAlive(alive,N*N);
        setAlive(mat,N,alive);
        flushMat(mat,N);
        setMat(mat,N,alive);
        affiche(mat,N);
        sleep(1);
        compteur ++;
        system("clear");
        //flushMat(mat,N);
        //scanf("%c",&tmp);


    }




    return 0;
}


//Corner
int cornerTopLeft(int (*mat)[N]){
    int sum =0;
    sum = mat[0][1]+mat[1][0]+mat[1][1];
    return sum;
}

int cornerTopRight(int (*mat)[N]){
    int sum=0;
    sum = mat[0][N-2]+mat[1][N-2]+mat[1][N-1];
    return sum;
}

int cornerBottomLeft(int (*mat)[N]){
    int sum=0;
    sum=mat[N-2][0]+mat[N-2][1]+mat[N-1][1];
    return sum;
}

int cornerBottomRigth(int (*mat)[N]){
    int sum=0;
    sum = mat[N-2][N-2]+mat[N-2][N-1]+mat[N-1][N-2];
    return sum;
}



//Border
int borderTop(int (*mat)[N],int i, int j){
    int sum=0;
    sum = mat[i][j-1]+mat[i][j+1]+mat[i+1][j-1]+mat[i+1][j]+mat[i+1][j+1];
    return sum;
}

int borderBottom(int (*mat)[N],int i, int j){
    int sum=0;
    sum = mat[i][j-1]+mat[i][j+1]+mat[i-1][j-1]+mat[i-1][j]+mat[i-1][j+1];
    return sum;
}

int borderLeft(int (*mat)[N],int i, int j){
    int sum=0;
    sum = mat[i+1][j]+mat[i-1][j]+mat[i-1][j+1]+mat[i][j+1]+mat[i+1][j+1];
    return sum;
}

int borderRight(int (*mat)[N],int i, int j){
    int sum=0;
    sum = mat[i+1][j]+mat[i-1][j]+mat[i-1][j-1]+mat[i][j-1]+mat[i+1][j-1];
    return sum;
}

//default

int defaultSum(int(*mat)[N],int i,int j){

    int sum=0;
    sum = mat[i+1][j-1]+mat[i][j-1]+mat[i-1][j-1];
    sum += mat[i-1][j]+mat[i+1][j];
    sum += mat[i-1][j+1]+mat[i][j+1]+mat[i+1][j+1];
    return sum;

}



void setAlive(int (*mat)[N],int taille,Coordonnee *alive){

    int i,j,sum;
    int k=0;//indice pour parcourir alive


    for(i=0; i<taille; i++){
        for(j=0;j<taille; j++){
            sum =0;
            if(i==0){//Bord haut
                if(j==0){//Coin haut gauche
                    sum=cornerTopLeft(mat);
                }
                else if(j==N-1){// coin haut droite
                    sum=cornerTopRight(mat);
                }
                else{//Juste bord haut
                    sum = borderTop(mat,i,j);
                }
            }


            else if (i==N-1){//Bord bas
                    if(j==0){//Coin bas gauche
                            sum=cornerBottomLeft(mat);
                    }
                    else if(j==49){//Coin bas droite
                        sum=cornerBottomRigth(mat);
                    }
                    else{//Juste bord bas
                        sum = borderBottom(mat,i,j);
                    }
            }


            else if(j==0){//bord gauche
                sum=borderLeft(mat,i,j);
            }


            else if(j==N-1){//bord droit
                sum=borderRight(mat,i,j);
            }

            else{
                sum = defaultSum(mat,i,j);

            }


            if(sum==3){
                alive[k].ord=i;
                alive[k].abs=j;
                k++;
            }

            else if(sum==2 && mat[i][j]==1){
                alive[k].ord=i;
                alive[k].abs=j;
                k++;
            }


        }

    }



}

//Met a jour la matrice
void setMat(int (*mat)[N],int taille, Coordonnee *alive){
    int i=0;

    while(alive[i].abs !=-1){
        mat[alive[i].ord][alive[i].abs]=1;
        i++;

    }


}

//Met toutes les coordonnee de alive  ? (-1;-1)
void flushAlive(Coordonnee *alive,int taille){
    int i;

    for(i=0;i<taille;i++){
      alive[i].abs=-1;
      alive[i].ord=-1;
    }

}

//Permet de donner les coord des cellules vivantes de depart
void initAlive(Coordonnee *alive,int taille){

    int i,nbCell=0;
    int tmp=-1;
    int choix;

    printf("1)Def manuelle\n2)Vaisseau\n3)Oscillateur Grenouille\n4)Pentomino R\n");
    printf("5)Vaisseau+Oscillateur Grenouille\n");
    printf("6)Vaisseau+Oscillateur Grenouille+Pentomino R\n");
    scanf("%d",&choix);

    if(choix == 2){
        alive[0].abs=1;
        alive[0].ord=N-1;
        alive[1].abs=2;
        alive[1].ord=N-2;
        alive[2].abs=0;
        alive[2].ord=N-3;
        alive[3].abs=1;
        alive[3].ord=N-3;
        alive[4].abs=2;
        alive[4].ord=N-3;

    }

    else if(choix==3){
        alive[0].abs=N/2+1;
        alive[0].ord=N/2+1;
        alive[1].abs=N/2+2;
        alive[1].ord=N/2+1;
        alive[2].abs=N/2+3;
        alive[2].ord=N/2+1;
        alive[3].abs=N/2+0;
        alive[3].ord=N/2+2;
        alive[4].abs=N/2+1;
        alive[4].ord=N/2+2;
        alive[5].abs=N/2+2;
        alive[5].ord=N/2+2;
    }

    else if(choix==4){
        alive[0].abs=1;
        alive[0].ord=0;
        alive[1].abs=1;
        alive[1].ord=1;
        alive[2].abs=2;
        alive[2].ord=1;
        alive[3].abs=0;
        alive[3].ord=2;
        alive[4].abs=1;
        alive[4].ord=2;

    }

    else if(choix==5){
        //vaisseau
        alive[0].abs=1;
        alive[0].ord=N-1;
        alive[1].abs=2;
        alive[1].ord=N-2;
        alive[2].abs=0;
        alive[2].ord=N-3;
        alive[3].abs=1;
        alive[3].ord=N-3;
        alive[4].abs=2;
        alive[4].ord=N-3;

        //Oscillateur Grenouille
        alive[5].abs=N/2+1;
        alive[5].ord=N/2+1;
        alive[6].abs=N/2+2;
        alive[6].ord=N/2+1;
        alive[7].abs=N/2+3;
        alive[7].ord=N/2+1;
        alive[8].abs=N/2+0;
        alive[8].ord=N/2+2;
        alive[9].abs=N/2+1;
        alive[9].ord=N/2+2;
        alive[10].abs=N/2+2;
        alive[10].ord=N/2+2;

        //Pentomino R
        alive[11].abs=1;
        alive[11].ord=0;
        alive[12].abs=1;
        alive[12].ord=1;
        alive[13].abs=2;
        alive[13].ord=1;
        alive[14].abs=0;
        alive[14].ord=2;
        alive[15].abs=1;
        alive[15].ord=2;


    }

    else if(choix ==6){

            alive[0].abs=1;
        alive[0].ord=N-1;
        alive[1].abs=2;
        alive[1].ord=N-2;
        alive[2].abs=0;
        alive[2].ord=N-3;
        alive[3].abs=1;
        alive[3].ord=N-3;
        alive[4].abs=2;
        alive[4].ord=N-3;

        //Oscillateur Grenouille
        alive[5].abs=N/2+1;
        alive[5].ord=N/2+1;
        alive[6].abs=N/2+2;
        alive[6].ord=N/2+1;
        alive[7].abs=N/2+3;
        alive[7].ord=N/2+1;
        alive[8].abs=N/2+0;
        alive[8].ord=N/2+2;
        alive[9].abs=N/2+1;
        alive[9].ord=N/2+2;
        alive[10].abs=N/2+2;
        alive[10].ord=N/2+2;



    }

    else if(choix==7){
        alive[0].abs=N/2+4;
        alive[0].ord=N/2+0;
        alive[1].abs=N/2+6;
        alive[1].ord=N/2+0;

        alive[2].abs=N/2+0;
        alive[2].ord=N/2+1;
        alive[3].abs=N/2+2;
        alive[3].ord=N/2+1;
        alive[4].abs=N/2+5;
        alive[4].ord=N/2+1;

        alive[5].abs=N/2+1;
        alive[5].ord=N/2+2;
        alive[6].abs=N/2+5;
        alive[6].ord=N/2+2;

        alive[7].abs=N/2+1;
        alive[7].ord=N/2+3;
        alive[8].abs=N/2+7;
        alive[8].ord=N/2+3;





    }

    else{

    while(nbCell <1 || nbCell > taille*taille){

        printf("Combien de cellules ?\n");
        scanf("%d",&nbCell);

    }

    for(i=0;i<nbCell;i++){
        tmp = -1;

        while(tmp<0 || tmp>taille){

            printf("Abscisse de la cell %d : ",i);
            scanf("%d",&tmp);
        }

        alive[i].abs=tmp;
        tmp=-1;

        while(tmp<0 || tmp>taille){

            printf("Ordonnee de la cell %d : ",i);
            scanf("%d",&tmp);
        }

        alive[i].ord=tmp;
        //alive[i].etat=1;

    }

    }


}

//set toutes les cases de la matrice ? 0
void flushMat(int (*mat)[N],int taille){

    int i,j;

    for(i=0;i<taille;i++){

        for(j=0;j<taille;j++){
            mat[i][j]=0;

        }
    }

}


//affiche la matrice
void affiche(int (*mat)[N],int taille){

    int i,j;

    printf("*****Affichage de la matrice *****\n\n");

    for(i=0;i<taille;i++){

        for(j=0;j<taille;j++){
                if(mat[i][j]==1)
                printf("O");
                else{
                    printf(".");
                }

        }
        printf("\n");
    }

}
