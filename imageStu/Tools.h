#pragma once
#include<iostream>
#include<fstream>

//哈夫曼树节点结构体
typedef struct {
	int weight;
	int parent;
	int lchild;
	int rchild;
} HTNode, *HuffmanTree;
typedef char ** HuffmanCode;

//从第1到第upbound行，找两个，parent为0的权值最小的序号, 赋给s1, s2
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

//哈夫曼编码
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

	//=======树
	//分配空间

	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	//初始化前n行

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
	//求第n+1到2*n-1行

	//从第1到第i-1行，找两个，parent为0的权值最小的序号, 赋给s1, s2

	//填充第i行

	//修改第s1和s2行的parent


	for (i = n + 1; i <= m; i++)
	{
		SelectTwoMin(i - 1, HT, s1, s2);

		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
		HT[s1].parent = i;
		HT[s2].parent = i;
	}

	//========编码
	//分配空间
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));
	cd = (char *)malloc(n * sizeof(char));
	cd[n - 1] = '\0';

	//从第1到第n个，依次求HC[i]

	//当前节点current从第i行开始，沿二叉树从下往上到二叉树第二层节点（根节点为结束条件）
	//	如果当前节点current是它父节点father的左孩子，则0，否则1，


	//为第i个编码申请空间，并将cd[start]开始的字符串复制进去



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

//膨胀
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

//取交集
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

//计算点数
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

//连通分量-》膨胀TempA
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

//连通分量-》imgA和tempA取交集得tempB
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

//连通分量-》对比tempAB
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

//求连通分量中腐蚀ImgA
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