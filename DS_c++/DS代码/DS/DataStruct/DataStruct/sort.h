#ifndef _SORT_H_
#define _SORT_H_

#include"Common.h"

void PrintArray(int ar[], int left, int right)
{
	for(int i=left; i<right; ++i)
		printf("%d ", ar[i]);
	printf("\n");
}

//直接插入排序
void InsertSort(int *ar, int left, int right)
{
	for(int i=left+1; i<right; ++i)
	{
		int end = i;
		while(end>left && ar[end]<ar[end-1])
		{
			Swap(&ar[end], &ar[end-1]);
			end--;
		}
	}
}

void InsertSort_1(int *ar, int left, int right)
{
	for(int i=left+1; i<right; ++i)
	{
		int tmp = ar[i];
		int end = i;
		while(end>left && tmp<ar[end-1])
		{
			ar[end] = ar[end-1];
			end--;
		}
		ar[end] = tmp;
	}
}

//哨兵位的直接插入排序
void InsertSort_2(int *ar, int left, int right)
{
	for(int i=left+1; i<right; ++i)
	{
		ar[0] = ar[i]; // 哨兵位
		int end = i;
		while(ar[0] < ar[end-1])
		{
			ar[end] = ar[end-1];
			end--;
		}
		ar[end] = ar[0];
	}
}

//折半插入排序
void BinInsertSort(int *ar, int left, int right)
{
	for (int i = left + 1; i < right; i++)
	{
		int tmp = ar[i];
		int low = left;
		int high = i - 1;
		while (low <= high)
		{
			int m = (low + high) / 2;
			if (tmp < ar[m])
				high = m - 1;
			else
				low = m + 1;
		}
		for (int j = i - 1; j >= high + 1; --j)
			ar[j + 1] = ar[j];
		ar[high + 1] = tmp;
	}
}

//二路插入排序
void TwoWayInsertSort(int *ar, int left, int right)
{
	int n = right - left;
	int *tmp = (int *)malloc(sizeof(int) * n);
	assert(tmp != NULL);
	
	tmp[0] = ar[left];
	int first = 0, finish = 0;

	for(int i=left+1; i<right; ++i)
	{
		if(ar[i] < tmp[first])
		{
			first = (first-1+n) % n;
			tmp[first] = ar[i];
		}
		else if(ar[i] > tmp[finish])
		{
			tmp[++finish] = ar[i];
		}
		else
		{
			int end = finish;
			while(ar[i] < tmp[end])
			{
				tmp[(end+1)%n] = tmp[end];
				end = (end-1+n) % n;
			}
			tmp[(end+1)%n] = ar[i];
			finish++;
		}
	}

	int k = 0;
	for(int i=first; k<n; ++k)
	{
		ar[k] = tmp[i];
		i = (i+1) % n;
	}

	free(tmp);
	tmp = NULL;
}

//Shell排序
/*
void ShellInsert(int *ar, int n, int dk)
{
	for(int i=dk; i<n; ++i)
	{
		if(ar[i] < ar[i-dk])
		{
			int tmp = ar[i];
			int j;
			for(j=i-dk; j>=0 && tmp<ar[j]; j-=dk)
			{
				ar[j+dk] = ar[j];
			}
			ar[j+dk] = tmp;
		}
	}
}
int dlta[] = {5,3,2,1};
void ShellSort(int *ar, int n, int dlta[], int t)
{
	for(int k=0; k<t; ++k)
		ShellInsert(ar, n, dlta[k]);
}


void ShellInsert(int *ar, int left, int right, int dk)
{
	for(int i=left+dk; i<right; ++i)
	{
		if(ar[i] < ar[i-dk])
		{
			int tmp = ar[i];
			int end = i-dk;
			while(end>=left && tmp<ar[end])
			{
				ar[end+dk] = ar[end];
				end -= dk;
			}
			ar[end+dk] = tmp;
		}
	}
}
int dlta[] = {5,3,2,1};  //设计文档
void ShellSort(int *ar, int left, int right)
{
	int t = sizeof(dlta) / sizeof(dlta[0]);
	for(int k=0; k<t; ++k)
		ShellInsert(ar, left, right, dlta[k]);
}
*/

void ShellSort(int *ar, int left, int right) //10
{
	int dk = right - left;
	while(dk > 1)
	{
		dk = dk/3+ 1; //6667  2223  742  248  83  27 10 4 2 1
		for(int i=left+dk; i<right; ++i)
		{
			if(ar[i] < ar[i-dk])
			{
				int tmp = ar[i];
				int end = i-dk;
				while(end>=left && tmp<ar[end])
				{
					ar[end+dk] = ar[end];
					end -= dk;
				}
				ar[end+dk] = tmp;
			}
		}
	}
}

//直接选择排序
int GetMinIndex(int *ar, int left, int right)
{
	int min_val = ar[left];
	int index = left;

	for(int i=left+1; i<right; ++i)
	{
		if(ar[i] < min_val)
		{
			min_val = ar[i];
			index = i;
		}
	}
	return index;
}
void SelectSort(int *ar, int left, int right)
{
	for(int i=left; i<right-1; ++i)
	{
		int index = GetMinIndex(ar, i, right);
		if(index != i)
			Swap(&ar[index], &ar[i]);
	}
}

//堆排序
void _ShiftDown(int *ar, int left, int right, int curpos)
{
	int i = curpos;
	int j = 2*i+1+left;

	int n = right - left;
	while(j < n)
	{
		if(j+1<n && ar[j]<ar[j+1])
			j++;
		if(ar[i] < ar[j])
		{
			Swap(&ar[i], &ar[j]);
			i = j;
			j = 2*i+1;
		}
		else
			break;
	}
}
void HeapSort(int *ar, int left, int right)
{
	//创建大堆
	int n = right - left;
	int cur = n/2 - 1+left;
	while(cur >= 0)
	{
		_ShiftDown(ar, left, right, cur);
		cur--;
	}

	//排序
	int end = right-1;
	while(end > left)
	{
		Swap(&ar[left], &ar[end]);
		end--;
		_ShiftDown(ar, left, end, left);
	}
}

void _ShiftDown_1(int *ar, int left, int right, int curpos)
{
	int i = curpos;
	int j = 2*i+1+left;

	int n = right - left;
	int tmp = ar[i];
	while(j < n)
	{
		if(j+1<n && ar[j]<ar[j+1])
			j++;

		if(tmp < ar[j])
		{
			ar[i] = ar[j];
			i = j;
			j = 2*i+1;
		}
		else
			break;
	}

	ar[i] = tmp;
}
void HeapSort_1(int *ar, int left, int right)
{
	//创建大堆
	int n = right - left;
	int cur = n/2 - 1+left;
	while(cur >= 0)
	{
		_ShiftDown_1(ar, left, right, cur);
		cur--;
	}

	//排序
	int end = right-1;
	while(end > left)
	{
		Swap(&ar[left], &ar[end]);
		end--;
		_ShiftDown_1(ar, left, end, left);
	}
}

//冒泡排序
void BubbleSort(int *ar, int left, int right)
{
	int n = right - left;
	for(int i=left; i<n-1; ++i)
	{
		for(int j=left; j<n-i-1; ++j)
		{
			if(ar[j] > ar[j+1])
			{
				Swap(&ar[j], &ar[j+1]);
			}
		}
	}
}
//冒泡排序的改进方法
void BubbleSort_1(int *ar, int left, int right)
{
	int n = right - left;
	bool is_swap = false; //用于标志此趟排序是否有交换，如果有则说明整体数据未必有序，
						  //若没有则说明数据已经有序，直接退出
	for(int i=left; i<n-1; ++i)
	{
		for(int j=left; j<n-i-1; ++j)
		{
			if(ar[j] > ar[j+1])
			{
				Swap(&ar[j], &ar[j+1]);
				is_swap = true;
			}
		}
		if(!is_swap)
			break;
		else
			is_swap = false;
	}
}

//快速排序 --<快排>

int GetIndexMidVal(int *ar, int left, int right)
{
	int mid = (left + right) / 2;
	if(ar[left]>ar[mid] && ar[left]<ar[right])
		return left;
	if(ar[mid]>ar[left] && ar[mid]<ar[right])
		return mid;
	return right;
}

//hoare版本
int _Partition_1(int *ar, int left, int right)
{
	//三者取中
	int index = GetIndexMidVal(ar, left, right);
	if(index != left)
		Swap(&ar[index], &ar[left]);
	
	int key = ar[left];
	while(left < right)
	{
		while(left<right && ar[right]>=key)
			right--;
		Swap(&ar[left], &ar[right]);
		while(left<right && ar[left]<key)
			left++;
		Swap(&ar[left], &ar[right]);
	}
	return left;
}

//挖坑法
int _Partition_2(int *ar, int left, int right)
{
	//三者取中
	int index = GetIndexMidVal(ar, left, right);
	if(index != left)
		Swap(&ar[index], &ar[left]);

	int key = ar[left];
	while(left < right)
	{
		while(left<right && ar[right] >= key)
			right--;
		ar[left] = ar[right];
		while(left<right && ar[left] < key)
			left++;
		ar[right] = ar[left];
	}
	ar[left] = key;
	return left;
}

//前后指针法
int _Partition_3(int *ar, int left, int right)
{
	//三者取中
	int index = GetIndexMidVal(ar, left, right);
	if(index != left)
		Swap(&ar[index], &ar[left]);

	int key = ar[left];
	int pos = left;
	for(int i=left+1; i<=right; ++i)
	{
		if(ar[i] < key)
		{
			pos++;
			if(pos != i)
				Swap(&ar[pos], &ar[i]);
		}
	}
	Swap(&ar[left], &ar[pos]);
	return pos;
}

#define M 25
void QuickSort(int *ar, int left, int right)
{
	if(left >= right-1)
		return;

	if(right - left <= M)
		InsertSort_1(ar, left, right);
	else
	{
		int pos = _Partition_1(ar, left, right - 1); //用于分割  曲轴位置
		QuickSort(ar, left, pos);
		QuickSort(ar, pos + 1, right);
	}
}

//归并排序
void _MergeSort(int *ar, int left, int right, int *tmp)
{
	//1 先分解
	if(left >= right)
		return;
	int mid = (left + right) / 2;
	_MergeSort(ar, left, mid, tmp);
	_MergeSort(ar, mid+1, right, tmp);

	//2 后归并
	int begin1, end1, begin2, end2, i;
	begin1 = left, end1 = mid;
	begin2 = mid+1, end2 = right;

	i = 0;
	while(begin1<=end1 && begin2<=end2)
	{
		if(ar[begin1] < ar[begin2])
			tmp[i++] = ar[begin1++];
		else
			tmp[i++] = ar[begin2++];
	}
	while(begin1 <= end1)
		tmp[i++] = ar[begin1++];
	while(begin2 <= end2)
		tmp[i++] = ar[begin2++];

	memcpy(ar+left, tmp, sizeof(int)*(right-left+1));
}

void MergeSort(int *ar, int left, int right)
{
	int n = right - left;
	int *tmp = (int *)malloc(sizeof(int) * n);
	assert(tmp != NULL);

	//归并排序的过程
	_MergeSort(ar, left, right-1, tmp);

	free(tmp);
	tmp = NULL;
}

//基数排序
#include"slist.h"
#define RADIX 10
SList list[RADIX];
#define K 2

//278
int GetKey(int value, int k)
{
	int key;
	while(k >= 0)
	{
		key = value % 10;
		value /= 10;
		k--;
	}
	return key;
}

void Distribute(int *ar, int left, int right, int k)
{
	for(int i=left; i<right; ++i)
	{
		int key = GetKey(ar[i], k);
		SListPushBack(&list[key], ar[i]);
	}
}

void Collect(int *ar)
{
	int k = 0;
	for(int i=0; i<RADIX; ++i)
	{
		while(!SListEmpty(&list[i]))
		{
			ar[k++] = SListFront(list[i]);
			SListPopFront(&list[i]);
		}
	}
}

void RadixSort(int *ar, int left, int right)
{
	for(int i=0; i<RADIX; ++i)
		SListInit(&list[i]);

	for(int i=0; i<K; ++i)
	{
		//1 分发
		Distribute(ar, left, right, i);

		//2 回收
		Collect(ar);
	}
}

void TestSort(int *ar, int left, int right)
{
	//InsertSort(ar, left, right);
	//InsertSort_1(ar, left, right);
	//InsertSort_2(ar, left, right);
	//BinInsertSort(ar, left, right);
	//TwoWayInsertSort(ar, left, right);
	//ShellSort(ar, left, right);
	//SelectSort(ar, left, right);
	//HeapSort_1(ar, left, right);
	//BubbleSort(ar, left, right);
	//QuickSort(ar, left, right);
	//MergeSort(ar, left, right);
	RadixSort(ar, left, right);
}

void TestSortEfficiency()
{
	int n = 20000;
	int *a = (int *)malloc(sizeof(int) * n);
	int *a1 = (int *)malloc(sizeof(int) * n);
	int *a2 = (int *)malloc(sizeof(int) * n);
	int *a3 = (int *)malloc(sizeof(int) * n);
	int *a4 = (int *)malloc(sizeof(int) * n);
	int *a5 = (int *)malloc(sizeof(int) * n);
	int *a6 = (int *)malloc(sizeof(int) * n);
	int *a7 = (int *)malloc(sizeof(int) * n);
	int *a8 = (int *)malloc(sizeof(int) * n);
	int *a9 = (int *)malloc(sizeof(int) * n);
	int *a10 = (int *)malloc(sizeof(int) * n);
	int *a11 = (int *)malloc(sizeof(int) * n);

	srand(time(0));
	for(int i=0; i<n; ++i)
	{
		a[i] = rand();
		a1[i] = a[i];
		a2[i] = a[i];
		a3[i] = a[i];
		a4[i] = a[i];
		a5[i] = a[i];
		a6[i] = a[i];
		a7[i] = a[i];
		a8[i] = a[i];
		a9[i] = a[i];
		a10[i] = a[i];
		a11[i] = a[i];
	}

	time_t start = clock();
	InsertSort(a, 0, n);
	time_t end   = clock();
	printf("InsertSort: %u\n", end - start);

	start = clock();
	InsertSort_1(a1, 0, n);
	end   = clock();
	printf("InsertSort_1: %u\n", end - start);

	start = clock();
	BinInsertSort(a2, 0, n);
	end   = clock();
	printf("BinInsertSort: %u\n", end - start);

	start = clock();
	TwoWayInsertSort(a3, 0, n);
	end   = clock();
	printf("TwoWayInsertSort: %u\n", end - start);

	start = clock();
	ShellSort(a4, 0, n);
	end   = clock();
	printf("ShellSort: %u\n", end - start);

	start = clock();
	SelectSort(a5, 0, n);
	end   = clock();
	printf("SelectSort: %u\n", end - start);

	start = clock();
	HeapSort(a6, 0, n);
	end   = clock();
	printf("HeapSort: %u\n", end - start);

	start = clock();
	HeapSort_1(a7, 0, n);
	end   = clock();
	printf("HeapSort_1: %u\n", end - start);

	start = clock();
	BubbleSort(a8, 0, n);
	end   = clock();
	printf("BubbleSort: %u\n", end - start);

	start = clock();
	QuickSort(a9, 0, n);
	end   = clock();
	printf("QuickSort: %u\n", end - start);

	start = clock();
	MergeSort(a10, 0, n);
	end   = clock();
	printf("MergeSort: %u\n", end - start);

	start = clock();
	RadixSort(a11, 0, n);
	end   = clock();
	printf("RadixSort: %u\n", end - start);
}

#endif /* SORT_H_ */