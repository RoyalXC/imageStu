#pragma once
#include<iostream>
#include<fstream>

//���������ڵ�ṹ��
typedef struct {
	int weight;
	int parent;
	int lchild;
	int rchild;
} HTNode, *HuffmanTree;
typedef char ** HuffmanCode;

//�ӵ�1����upbound�У���������parentΪ0��Ȩֵ��С�����, ����s1, s2
void SelectTwoMin(int upbound, HuffmanTree HT, int &s1, int &s2)
{
	int i, smin1, smin2;

	smin1 = 2147483647;
	smin2 = 2147483647;

	for (i = 1; i <= upbound; i++)
	{
		if (HT[i].weight < smin1  && HT[i].parent == 0)
		{
			s1 = i;
			smin1 = HT[i].weight;

		}

	}

	for (i = 1; i <= upbound; i++)
	{

		if (HT[i].weight < smin2 && HT[i].parent == 0 && HT[i].weight != smin1)
		{

			s2 = i;
			smin2 = HT[i].weight;

		}
	}
}

//����������
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{
	int m, i, start, current, father;
	int s1, s2;
	char *cd;

	HuffmanTree p;

	m = 2 * n - 1;

	if (n <= 1)
	{
		return;
	}

	//=======��
	//����ռ�

	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	//��ʼ��ǰn��

	for (i = 1; i <= n; i++)
	{
		HT[i].weight = w[i - 1];
		HT[i].lchild = 0;
		HT[i].parent = 0;
		HT[i].rchild = 0;

	}




	for (; i <= m; i++)
	{

		HT[i].weight = 0;
		HT[i].lchild = 0;
		HT[i].parent = 0;
		HT[i].rchild = 0;
	}
	//���n+1��2*n-1��

	//�ӵ�1����i-1�У���������parentΪ0��Ȩֵ��С�����, ����s1, s2

	//����i��

	//�޸ĵ�s1��s2�е�parent


	for (i = n + 1; i <= m; i++)
	{
		SelectTwoMin(i - 1, HT, s1, s2);

		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
		HT[s1].parent = i;
		HT[s2].parent = i;
	}

	//========����
	//����ռ�
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));
	cd = (char *)malloc(n * sizeof(char));
	cd[n - 1] = '\0';

	//�ӵ�1����n����������HC[i]

	//��ǰ�ڵ�current�ӵ�i�п�ʼ���ض������������ϵ��������ڶ���ڵ㣨���ڵ�Ϊ����������
	//	�����ǰ�ڵ�current�������ڵ�father�����ӣ���0������1��


	//Ϊ��i����������ռ䣬����cd[start]��ʼ���ַ������ƽ�ȥ



	for (i = 1; i <= n; i++)
	{
		start = n - 1;

		for (current = i, father = HT[i].parent; father != 0; current = father, father = HT[father].parent)
		{
			if (HT[father].lchild == current)
			{
				cd[--start] = '0';
			}

			else
			{
				cd[--start] = '1';
			}
		}
		HC[i] = (char *)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);
	}
	free(cd);
}

//����
int* Expland(int width, int height, int* imgX)
{

	int size = width * height;

	int step = 1;
	int color = 0;
	int* temp = new int[size];
	for (int i = 0; i < size; i++)
	{
		temp[i] = imgX[i];
	}

	for (int x = step; x < width - step; x++)
	{
		for (int y = step; y < height - step; y++)
		{
			int index = y * width + x;
			if (temp[index] == color
				|| temp[index - 1] == color
				|| temp[index + 1] == color
				|| temp[index - width] == color
				|| temp[index + width] == color)
			{
				imgX[index] = 0;
			}
			else
				imgX[index] = 1;
		}
	}
	delete[] temp;
	return imgX;
}

//ȡ����
int* Mixed(int size, int* imgX, int* imgB)
{
	for (int i = 0; i < size; i++)
	{
		if (imgX[i] == 0 && imgB[i] == 0)
		{
			imgX[i] = 0;
		}
		else
			imgX[i] = 1;
	}
	return imgX;
}

//�������
int CountX(int size, int* imgX)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (imgX[i] == 1)
		{
			count++;
		}
	}
	return count;
}

//��ͨ����-������TempA
void ExplandTempA(int width, int height, int* tempA)
{

	int size = width * height;

	int step = 1;
	int color = 1;
	int* temp = new int[size];
	for (int i = 0; i < size; i++)
	{
		temp[i] = tempA[i];
	}

	for (int x = step; x < width - step; x++)
	{
		for (int y = step; y < height - step; y++)
		{
			int index = y * width + x;
			if (temp[index] == color
				|| temp[index - 1] == color
				|| temp[index + 1] == color
				|| temp[index - width] == color
				|| temp[index + width] == color
				|| temp[index - width - 1] == color
				|| temp[index - width + 1] == color
				|| temp[index + width - 1] == color
				|| temp[index + width + 1] == color)
			{
				tempA[index] = 1;
			}
			else
				tempA[index] = 0;
		}
	}
	delete[] temp;
}

//��ͨ����-��imgA��tempAȡ������tempB
void MixTempA(int size, int* imgA, int* tempA, int* tempB)
{
	for (int i = 0; i < size; i++)
	{
		if (imgA[i] == 1 && tempA[i] == 1)
		{
			tempB[i] = 1;
		}
		else
			tempB[i] = 0;
	}
}

//��ͨ����-���Ա�tempAB
bool CompareAB(int size, int * tempA, int * tempB)
{
	for (int i = 0; i < size; i++)
	{
		if (!(tempA[i] == tempB[i]))
		{
			return false;
		}

	}
	return true;
}

//����ͨ�����и�ʴImgA
void CorrImgA(int width, int height, int* imgA) {
	int size = width * height;

	int step = 3;
	int color = 1;
	int count = 0;
	int* temp = new int[size];
	for (int i = 0; i < size; i++)
	{
		temp[i] = imgA[i];
	}

	for (int x = step; x < width - step; x++)
	{
		for (int y = step; y < height - step; y++)
		{
			count = 0;

			for (int k = x - step; k < x + step; k++)
			{
				for (int j = y - step; j < y + step; j++)
				{
					int index = j * width + k;
					if (temp[index] == color)
					{
						count++;
					}
				}
			}
			if (count >= 25)
			{
				imgA[y*width + x] = 1;
			}
			else
				imgA[y*width + x] = 0;
		}
	}
	delete[] temp;
} 