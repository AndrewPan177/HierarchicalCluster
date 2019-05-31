
// HierarchicalCluster.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdio.h"
#include "limits.h"
#include "malloc.h"
#include "math.h"

//�����n�������
double Mean(int *a, int n) {
	double sum = 0;
	double mean = 0;
	for (int i = 0; i < 6; i++) {
		sum += a[n*6+i];
	}
	mean = sum / 6;
	return mean;
}

//�ó�����xÿһ������ľ���xx
void GetHeart(int *x, double *xx) {
	for (int i = 0; i < 5; i++) {
		xx[i] = Mean(x, i);
	}
}

//��õ�m�͵�n��Ԫ�ؼ�ľ���
double GetDis(double *H, int m, int n) {
	return fabs(H[m] - H[n]);
}

int n = 5;						//�����Ŀ����������������
int dd = 1;						//������
int ojbk = 5;					//ָ��������

void GetMin(double *H, double *D, int *order) {
	
	//int n = 5;
	int *temp = (int*)malloc((n - 1) * sizeof(int)); //���ڴ����һ��˳������
	double min = 10000;
	int a, b;								   //���ڴ�źϲ���������ĽǱ�

	//�ھ���������ҳ���С��Ԫ��
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i > j) {
				if (D[i * n + j] < min) {
					min = D[i * n + j];
					a = i; b = j;
				}
			}
		}
	}
	printf("min=%.1lf  a=%d  b=%d\n", min, a, b);
	printf("n=%d\n", n);

	//�ϲ�order
	int m = 0;
	for (int i = 0; i < n; i++) {
		if (i != a && i != b) {
			temp[m] = order[i];
			m++;
		}
	}
	if(order[a]>10)
		temp[n - 1 - 1] = order[b] * 100 + order[a];
	else
		temp[n - 1 - 1] = order[b] * 10 + order[a];

	//��ӡtemp
	printf("\nTemp:\n");
	for (int i = 0; i < n-1; i++)
		printf("%d\t", temp[i]);
	printf("\n");

	//�ϲ��������
	double *D2 = (double*)malloc((n - 1)*(n - 1) * sizeof(double));
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (i < n - 1 - 1) {	//����ǰn-1-1�еĹ���
				if (i <= j)
					D2[i*(n - 1) + j] = 0;
				else
					D2[i*(n - 1) + j] = GetDis(H, temp[i] - 1, temp[j] - 1);
			}
			else if (i != j)
				D2[i*(n - 1) + j] = ((GetDis(H, a, temp[j] - 1) < GetDis(H, b, temp[j] - 1)) ? GetDis(H, a, temp[j] - 1) : GetDis(H, b, temp[j] - 1));
			else
				D2[i*(n - 1) + j] = 0;
		}
	}

	//��ӡD2
	printf("\nD%d:\n",dd);
	for (int i = 0; i < (n - 1); i++) {
		for (int j = 0; j < n - 1; j++) {
			printf("%.1lf\t", D2[i*(n - 1) + j]);
		}
		printf("\n");
	}

	dd++;//������
	n--;

	if (dd >= ojbk || n == 2) { 
		printf("\n\nOjbk!\n"); 
	}
	else GetMin(H, D2, temp);
	
	free(temp);
}

void GetMin2(double *H, double *D, int *order) {

	//int n = 5;
	int *temp = (int*)malloc((n - 1) * sizeof(int)); //���ڴ����һ��˳������
	double min = 10000;
	int a, b;								   //���ڴ�źϲ���������ĽǱ�

											   //�ھ���������ҳ���С��Ԫ��
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i > j) {
				if (D[i * n + j] < min) {
					min = D[i * n + j];
					a = i; b = j;
				}
			}
		}
	}
	printf("min=%.1lf  a=%d  b=%d\n", min, a, b);
	printf("n=%d\n", n);

	//�ϲ�order
	int k = 0;
	for (int i = 0; i < n; i++) {
		if (i != a && i != b) {
			temp[k] = order[i];
			k++;
		}
	}
	if (order[a]>10)
		temp[n - 1 - 1] = order[b] * 100 + order[a];
	else
		temp[n - 1 - 1] = order[b] * 10 + order[a];

	//��ӡtemp
	printf("\nTemp:\n");
	for (int i = 0; i < n - 1; i++)
		printf("%d\t", temp[i]);
	printf("\n");

	int p = 0, q = 0;//������order����

	//�ϲ��������
	double *D2 = (double*)malloc((n - 1)*(n - 1) * sizeof(double));
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (i < n - 1 - 1) {	//����ǰn-1-1�еĹ���
				if (i <= j)
					D2[i*(n - 1) + j] = 0;//�����ϰ벿�ֽ��и�0
				else {
					while (p < n) {
						if (order[p] == temp[i])
							break;
						else p++;
					}
					while (q < n) {
						if (order[q] == temp[j])
							break;
						else q++;
					}

					D2[i*(n - 1) + j] = D[p*n + q];
					p = 0; q = 0;
				}
					
			}
			else if (i != j) {
				while (p < n) {
					if (order[p] == temp[j])
						break;
					else p++;
				}

				D2[i*(n - 1) + j] = (D[p*n + a] < D[p*n + b] ? D[p*n + a] : D[p*n + b]);
				p = 0;
				//D2[i*(n - 1) + j] = ((GetDis(H, a, temp[j] - 1) < GetDis(H, b, temp[j] - 1)) ? GetDis(H, a, temp[j] - 1) : GetDis(H, b, temp[j] - 1));
			}
				
			else
				D2[i*(n - 1) + j] = 0;
		}
	}

	//��ӡD2
	printf("\nD%d:\n", dd);
	for (int i = 0; i < (n - 1); i++) {
		for (int j = 0; j < n - 1; j++) {
			printf("%.1lf\t", D2[i*(n - 1) + j]);
		}
		printf("\n");
	}

	dd++;//������
	n--;

	if (dd >= ojbk || n == 2) {
		printf("\n\nOjbk!\n");
	}
	else GetMin(H, D2, temp);

	free(temp);
}


//�����������D���ݹ�
void D(double *H,int *order) {  

	//int n = 5;	//nΪ�����ʱ�ĸ���,Ҳ���Ǿ�������������������	���㲻�������ֶ������ 
	//n = sizeof(H) / sizeof(double); 

	double *D=(double*)malloc(n*n*sizeof(double)); 
	
	//�ó���ʼ�������
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i <= j)
				D[i*n + j] = 0;
			else
				D[i*n + j] = GetDis(H, i, j);
		}
	}

	//��ӡ D
	printf("D0:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("%.1lf \t", D[i * n + j]);
		printf("\n");
	}
	printf("\nn=%d\n\n", n);

	//��ʼ����
	//GetMin(H, D, order);

	GetMin2(H, D, order);

	free(D);
}

int main()
{
	//����
	int x[30] = { 0,1,3,1,3,4,
				  3,3,3,1,2,1,
			   	  1,0,0,0,1,1,
				  2,1,0,2,2,1,
				  0,0,1,0,1,0 };
	int order[5] = { 1,2,3,4,5 };	//˳��

	//�������ľ��� Heart[5]
	double Heart[5];
	GetHeart(x, Heart);
	//��ӡHeart
	printf("Heart:\n");
	for (int i = 0; i < 5; i++) {
		printf("%.1lf\t", Heart[i]);
	}
	printf("\n\n");
	
	D(Heart, order);

	printf("\n");
    return 0;
}
