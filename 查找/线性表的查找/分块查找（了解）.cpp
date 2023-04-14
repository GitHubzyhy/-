#include<stdio.h>

//索引表
typedef struct
{
	int key;	//最大关键字
	int start;	//块开始下标
	int end;	//块结束下标
}Node;
typedef struct
{
	Node idx[10];//表项
	int len;	//表长
}IdxTable;


//分块查找
IdxTable table;	//索引表
int BlockingSearch(int key,int a[])
{
	//折半查找
	int  low, high, mid;
	low = 1;
	high = table.len;
	while (low <= high)
	{
		mid = (low + high) / 2;			//找到中间位置
		if (key<=table.idx[mid].key)
		{
			//顺序查找
			if (key <= table.idx[mid - 1].key)
			{
				high = mid - 1;//继续二分操作 
			}
			else
			{//i为数组下标 start和end是开始和结束的下标 
						for (int i = table.idx[mid].start; i <= table.idx[mid].end; i++)
						{
							if (key == a[i])
							{
								return (i + 1);	//从1开始算起
							}
						}
						return 0;//最终没有找到 
			}
			
		}
		else
		{
			low = mid + 1;				//如果小于查找的记录则重新定位mid指针
		}
	}//while 
	
	return 0;
}
/*测试数据输入60 结果为13*/


int main()
{
	int i;
	int a[] = {22,12,13,8,9,20,33,42,44,38,24,48,60,58,74,49,86,53 };
	//索引表
	table.idx[1].key = 22; table.idx[1].start = 0; table.idx[1].end = 5;
	table.idx[2].key = 48; table.idx[2].start = 6; table.idx[2].end = 11;
	table.idx[3].key = 86; table.idx[3].start = 12; table.idx[3].end = 17;
	table.len = 3;
	
	//查找结果
	int key;
	printf("请输入要查找的记录：");
	scanf("%d", &key);
	i = BlockingSearch(key, a);
	printf("查找记录在表中的位置是（从1开始，0为未找到）：%d\n", i);
}
