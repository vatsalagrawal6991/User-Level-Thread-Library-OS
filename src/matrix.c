//
// Created by baadalvm on 17/08/21.
//

int n,sm;
int **m;
int **a;
int **b;
int x;

void matrix(void* arg){
    int* ar=(int*) arg;
    int ara=*ar;
    int i,j,k;
    int sm=n/x;
    //double tc=0,r=3.0,l;
    //for (l=0.0;l<r;l++){
        //double start = Time();
        for (i=ara*sm;i<n&&i<(ara+1)*sm;i++){
            for (j=0;j<n;j++){
                m[i][j]=0;
                for (k=0;k<n;k++){
                    m[i][j]=(a[i][k]*b[k][j])+m[i][j];
                }
            }
        }

       // double stop = Time();
       // tc =stop-start+tc;

    //}
    //tc=tc/r;
    //printf("%lf     ", tc);
}