//
// Created by baadalvm on 17/08/21.
//
int n;
int **m;
int **a;
int **b;
int x;

void matrixorig(){
    //int* ar=(int*) arg;
    //int ara=*ar;
    int i,j,k;
    //double tc=0,r=3.0,l;
    //for (l=0.0;l<r;l++){
    //double start = Time();
    for (i=0;i<n;i++){
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