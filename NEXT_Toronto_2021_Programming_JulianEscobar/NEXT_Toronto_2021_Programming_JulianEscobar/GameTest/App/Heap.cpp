//-----------------------------------------------------------------------------
// Heap.cpp
// Creates the data structure Heap to any T data
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include "Heap.h"

template<class T>
Heap<T>::Heap(int maxHeapSize)
{
	items = new HeapItem<T>[maxHeapSize];
}

template<class T>
void Heap<T>::Add(HeapItem<T> item)
{
	item.index = currentItemCount;
	items[currentItemCount] = item;
	SortUp(item);
	currentItemCount++;
}

template<class T>
void Heap<T>::SortUp(HeapItem<T> item)
{
	int parentIndex = (item.index - 1) / 2;

	while (true)
	{
		HeapItem<T> parentItem = items[parentIndex];
		if (item < parentItem) // item has a lower fCost than parent
		{
			Swap(item, parentItem);
		}
		else
		{
			break;
		}
	}
}

template<class T>
void Heap<T>::UpdateItem(HeapItem<T> item)
{
	SortUp(item);
}

template<class T>
void Heap<T>::Swap(HeapItem<T> itemA, HeapItem<T> itemB)
{
	items[itemA.index] = itemB;
	items[itemB.index] = itemA;
	int itemAIndex = itemA.index;
	itemA.index = itemB.index;
	itemB.index = itemAIndex;
}

template<class T>
HeapItem<T> Heap<T>::RemoveFirst()
{
	HeapItem<T> firstItem = items[0];
	currentItemCount--;
	items[0] = items[currentItemCount];
	items[0].index = 0;
	SortDown(items[0]);
	return firstItem;
}

template<class T>
void Heap<T>::SortDown(HeapItem<T> item)
{
	while (true)
	{
		int childIndexLeft = item.index * 2 + 1;
		int childIndexRight = item.index * 2 + 2;
		int swapIndex = 0;

		if (childIndexLeft < currentItemCount)
		{
			swapIndex = childIndexLeft;
			if (childIndexRight < currentItemCount)
			{
				if (items[childIndexLeft] > items[childIndexRight])
				{
					swapIndex = childIndexRight;
				}
			}

			if (item > items[swapIndex])
			{
				Swap(item, items[swapIndex]);
			}
			else
			{
				return;
			}
		}
		else
		{
			return;
		}
	}
}
