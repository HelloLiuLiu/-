#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100
//定义三元组
typedef struct
{
	int i;//横坐标
	int j;//纵坐标
	int v;//非零元素的值
}Triple;
//定义稀疏矩阵
typedef struct
{
	Triple data[MAXSIZE];//保存三元组的数组
	int rpos[MAXSIZE];//非零元素行的起始位置
	int rnum[MAXSIZE];//各行非零元素的个数
	int mu, nu, tu;//原始矩阵的行列数和非零元素的个数
}SparMatrix;
void Creat(SparMatrix *matrix)
{//创建一个稀疏矩阵
	int i, x, y, e;
	printf("Please input the spare matrix's row and cow:\n");//提示输入行列数
	scanf("%d %d", &matrix->mu, &matrix->nu);
	printf("Please input the number of nonzero value:\n");//提示输入非零元素个数
	scanf("%d", &matrix->tu);
	//开始创建三元组
	for (i = 1; i <=matrix->tu; i++)
	{
		scanf("%d %d %d", &x, &y, &e);//输入非零元素的行，列，和非零值。
		matrix->data[i].i=x;
		matrix->data[i].j=y;
		matrix->data[i].v=e;
    }

	memset(matrix->rnum, 0, sizeof(matrix->rnum));
	for (i = 1; i <= matrix->tu; ++i)//计算每列的非零元素的个数
	{
		matrix->rnum[matrix->data[i].i]++;
	}
	for (i = 1; i <= matrix->mu; ++i)
	//计算行非零元素的起始位置
	memset(matrix->rpos, 0, sizeof(matrix->rpos));
	//计算行非零元素的起始位置
	memset(matrix->rpos, 0, sizeof(matrix->rpos));
	i = matrix->data[1].i;
	matrix->rpos[i] = 1;
	for (i =i+1; i <= matrix->mu; ++i)
	{
		/*if (matrix->rnum[i] == 0)
			matrix->rpos[i] = matrix->rpos[i - 1]+matrix->rpos[i - 1];
		else*/
			matrix->rpos[i] = matrix->rnum[i - 1] + matrix->rpos[i - 1];
	}
	matrix->rpos[i] = matrix->tu + 1;
}
void Trans(SparMatrix matrix,SparMatrix* tran_res)
{//稀疏矩阵的转置，一个M*N的稀疏矩阵，转置为N*M的矩阵
	int cnum[MAXSIZE];
	int cpot[MAXSIZE];
	memset(cnum, 0, sizeof(cnum));
	memset(cpot, 0, sizeof(cpot));
	int i,p;
	tran_res->mu = matrix.nu;//转置后的行数等于原来的列数
	tran_res->nu = matrix.mu;//转置后的列数等于原来的行数
	tran_res->tu = matrix.tu;
	for (i = 1; i <= matrix.tu; i++)//计算每列的非零元素的个数
	{
		cnum[matrix.data[i].j]++;
	}
	for (i = 1; i <= matrix.nu; ++i) {//找到第一个有非零元素的列
		if (cnum[i] != 0) {
			cpot[i] = 1;
			break;
		}
	}
	for (i=2; i <= matrix.nu; ++i)
	{//计算每列的非零元素的起始位置
		cpot[i] = cpot[i - 1] + cnum[i - 1];
	}
	//转置运算
	for (i = 1; i <= matrix.tu;++i)
	{
		p = cpot[matrix.data[i].j]++;//p为转置后该列在矩阵中的位置
		tran_res->data[p].i=matrix.data[i].j;//行列互换
		 tran_res->data[p].j=matrix.data[i].i;
		 tran_res->data[p].v=matrix.data[i].v;
    }
}
/*
1 3 1
2 1 3
2 4 1
2 2 2
3 3 1
3 4 3
*/
void recover(SparMatrix matrix)
{//将稀疏矩阵恢复原样输出
	int i,j;
	int arr[MAXSIZE][MAXSIZE];
	memset(arr, 0,sizeof(arr));
	for (i = 1; i <= matrix.tu; ++i) {
		arr[matrix.data[i].i][matrix.data[i].j] = matrix.data[i].v;
	}
	printf("The spare matrix is:\n");
	for (i = 1; i <= matrix.mu; ++i)
	{
		for (j = 1; j <=matrix.nu; ++j)
			printf("%d ", arr[i][j]);
		printf("\n");
	}
}
void multip(SparMatrix A, SparMatrix B, SparMatrix *C)
{//矩阵的乘法
	int arow,brow, p, q,tp,t,ccol;
	int cres[MAXSIZE];
	memset(cres, 0, sizeof(cres));
	//A矩阵的列是否与B矩阵的行相等
	if (A.nu != B.mu) {//不满足乘法条件
		printf("Error\n");
		return;
	}
	else//满足
	{
		C->mu = A.mu;
		C->nu = B.nu;
		C->tu = 0;
		for (arow = 1; arow <= A.mu;++arow)//处理A中的每一行
		{
			if (A.rnum[arow] == 0)
				continue;
			memset(cres, 0, sizeof(cres));
			C->rpos[arow] = C->tu + 1;//
			tp = A.rpos[arow + 1];//相邻非零行的起始位置 相邻行的起始位置-当前行的起始位置=该行非零元素的个数
			for (p =A.rpos[arow]; p < tp; ++p)//对当前行中的每一个非零元素
			{
				brow = A.data[p].j;//B矩阵中的行等于当前行的列
				t = B.rpos[brow + 1];//B矩阵中相邻行的起始位置
				for (q = B.rpos[brow]; q < t; ++q) {//处理B矩阵中每一行的元素
					ccol = B.data[q].j;//结果所处的列号
					cres[ccol] += A.data[p].v*B.data[q].v;//累加
				}
			}
			//处理完一行
			for (ccol = 1; ccol <= C->nu; ++ccol)//查找结果中该行的非零元素
			{
				if (cres[ccol]) {//如果累加结果不为0
					//结果矩阵的非零元素个数增加
					if (++C->tu > MAXSIZE)//非零元素个数大于最大个数
						exit(0);
					else
						{//将非零元素的位置和值的信息压入C
						    C->data[C->tu].i=arow;
						    C->data[C->tu].j=ccol;
						    C->data[C->tu].v=cres[ccol];
						}
				}
			}
		}
	}
}
int main()
{
	SparMatrix M, N,Q,P;
	int i;
	Creat(&M);
	//recover(M);
	//Trans(M, &N);
	Creat(&N);
	multip(M, N, &Q);
	printf("The result is:\n");
	for (i = 1; i <= Q.tu; ++i)
		printf("%d %d %d\n",Q.data[i].i,Q.data[i].j,Q.data[i].v);
    printf("\n");
    recover(Q);
    Trans(Q,&P);
    recover(P);
	return 0;
}
