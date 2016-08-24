#pragma once
#include<vector>
#include<cassert>

template<class T>
struct Less
{
	bool operator()(const T& left, const T& right)
	{
		return left < right;
	}
};
template<class T>
struct Greater
{
	bool operator()(const T& left, const T& right)
	{
		return left > right;
	}
};

template<class T,class Compare=Less<T>>
class Heap
{
private:
	vector<T> _array;
public:

	Heap()
	{}

	Heap(const T* a,int size)
	{
		for (int i = 0; i < size; ++i)
		{
			_array.push_back(a[i]);
		}
		for (int i = (_array.size()-1-1)/2; i >= 0; --i)
		{
			AdjustDown(i);
		}

	}

	void AdjustDown(int root)
	{
		Compare com;
		int parent = root;
		int child = parent * 2 + 1;
		while (child < _array.size())
		{
			if (child + 1 < _array.size() && com(_array[child + 1] , _array[child]))
			{
				child++;
			}
			if (com(_array[parent],_array[child]))
			{
				swap(_array[parent], _array[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}

	void Push(const T& x)
	{
		_array.push_back(x);
		int size = _array.size();
		AdjustUp(size-1);
	}

	void AdjustUp(int last)
	{
		Compare com;
		int child = last;
		int parent = (child - 1) / 2;
		while (child > 0)
		{
			if (com(_array[parent],_array[child]))
			{
				swap(_array[parent], _array[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;
		}
	}

	T& Top()
	{
		assert(_array);
		return _array[0];
	}

	void Pop()
	{
		assert(_array.size()>0);
		_array.pop_back();
		AdjustDown(0);
	}

	int Size()
	{
		return _array.size();
	}
	void Print()
	{
		for (int i = 0; i < _array.size(); ++i)
		{
			cout << _array[i] << " ";
		}
		cout << endl;
	}
};


void Test()
{
	int a[8] = { 5, 7, 3, 1, 4, 0, 9, 2 };
	Heap<int> h(a, 8);
	h.Print();
	h.Push(6);
	h.Print();
	h.Pop();
	h.Print();
}

