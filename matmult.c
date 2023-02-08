#include<stdlib.h>
#include<pthread.h>
#include <stdio.h>

#define Item(X, I, J, NCOL)      X[((J) + (I) * (NCOL))]

/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */
void matmult(int* A, int* B, int* C, int l, int m, int n)
{
    for(int i=0; i<l; i++)
        for(int j=0; j<n; j++)
        {
            int sum = 0;
            for(int k=0; k<m; k++)
                sum += Item(A, i, k, m) * Item(B, k, j, n);
            Item(C, i, j, n) = sum;
        }
}

typedef struct{
	int *A;
	int *B;
	int *C;
	int l;
	int m;
	int n;
	int row;
	int col;
	}data;
/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */

void *threadmultE(void *arg){
	data *arr = (data*) arg;
	int i = arr->row;
	int j = arr->col;
	int*A=arr->A;
	int*B=arr->B;
	int*C=arr->C;
	//int l=arr->l;
	int m=arr->m;
	int n=arr->n;
	int sum = 0;
	for(int k=0; k<m; k++){
		sum += Item(A, i, k, m) * Item(B, k, j, n);   
        }
        Item(C, i, j, n) = sum;
}
 /*creating a thread for each element*/
void matmult_v1(int* A, int* B, int* C, int l, int m, int n)
{
	//thread creation
	data node[l][n];
	pthread_t threads[l][n];
	for(int i=0 ; i < l ; i++){
		for(int j=0 ; j< n ; j++){
			node[i][j].A=A;
			node[i][j].B=B;
			node[i][j].C=C;
			node[i][j].l=l;
			node[i][j].m=m;
			node[i][j].n=n;
			node[i][j].row=i;
			node[i][j].col=j;
			pthread_create(&threads[i][j], NULL , threadmultE, (void*)(&node[i][j]));
		}
	}
	//each thread joins and waits the previous thread to complete its job
	for(int i=0 ; i < l ; i++){
		for(int j=0 ; j<n ; j++){
			pthread_join(threads[i][j], NULL );
			
		}
	}
}


/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */
 void *threadmultR(void *arg){
	data *arr = (data*) arg;
	int i = arr->row;
	//int j = arr->col;
	int*A=arr->A;
	int*B=arr->B;
	int*C=arr->C;
	//int l=arr->l;
	int m=arr->m;
	int n=arr->n;
	for(int j=0; j<n; j++)
        {
            int sum = 0;
            for(int k=0; k<m; k++)
                sum += Item(A, i, k, m) * Item(B, k, j, n);
            Item(C, i, j, n) = sum;
        }
}

 /*creating a thread for each row*/
void matmult_v2(int* A, int* B, int* C, int l, int m, int n)
{
	data node[l];
	//thread creation
	pthread_t threads[l];
	for(int i=0 ; i < l ; i++){
		node[i].A=A;
		node[i].B=B;
		node[i].C=C;
		node[i].l=l;
		node[i].m=m;
		node[i].n=n;
		node[i].row=i;
		pthread_create(&threads[i], NULL , threadmultR, (void*)&node[i]);
	}
	//each thread joins and waits the previous thread to complete its job
	for(int i=0 ; i < l ; i++){
		pthread_join(threads[i], NULL );
	}
}
