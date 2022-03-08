#pragma once
//-----------------------------------------------------------------------------
// Heap.h
// Creates the data structure Heap to any T data
//-----------------------------------------------------------------------------

template<class T>
struct HeapItem
{
	int index;
	T* data;
	bool operator<(HeapItem &b)
	{
		return *(this->data) < *(b.data);
	}
	bool operator>(HeapItem& b)
	{
		return *(this->data) > *(b.data);
	}
};

template<class T>
struct Heap{

	Heap(int maxHeapSize);
	void Add(HeapItem<T> item);
	void SortUp(HeapItem<T> item);
	void UpdateItem(HeapItem<T> item);

	void Swap(HeapItem<T> itemA, HeapItem<T> itemB);
	HeapItem<T> RemoveFirst();

	void SortDown(HeapItem<T> item);
	int getItemsCount() { return currentItemCount; }
private:
	HeapItem<T> items[];
	int currentItemCount;
};


