《算法-第四版》符号表：
用二分查找算法实现符号表的有序插入，和查找等操作。
--------------------------------------------
有序数组的二分查找，使用一对平行的数组，一个用来保存键keys[]另一个用来保存值values[]，
该算法可以保证数组中的键有序，然后使用数组的索引高效的实现get()等其他操作。
该算法到的核心是rank()函数，rank（）函数返回小于参数键的元素个数。在一个有序数组中，小于x的元素个数即为把x放入数组中的位置。
对于put（）方法，只要传入键值对，调用rank（）函数查找键该插入的位置，如果该键已经存在数组中，就覆盖掉该键原有的value
值，可以通过values数组索引操作，若该键不存在数组中，就将插入位置后的所有元素向后移动一个位置，--这就是该算法耗时的地方。

具体实现：
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

class BinSerachST
{
public:
	
	BinSerachST(int capacity)
	{
	keys = new string[capacity];
	values = new int[capacity];
	}
	int size()
	{
		return N;
	}
	int rank(string key)
	{
		int lo = 0; int hi = N - 1;
		while (lo <= hi)
		{
			int mid = lo + (hi - lo) / 2;
			int cmp = key.compare(keys[mid]);
			if (cmp < 0)hi = mid - 1;
			else if (cmp>0)lo = mid + 1;
			else return mid;
		}
		return lo;
	}
	int get(string key)
	{
		int i = rank(key);
		if (i < N&&keys[i] == key)
			return values[i];
		else return -1;
	}
	void put(string key, int value)
	{
		int i = rank(key);
		if (i < N&&keys[i].compare(key) == 0)
		{
			values[i] = value;
			return;
		}
		for (int j = N; j > i; j--)
		{
			keys[j] = keys[j - 1];
			values[j] = values[j - 1];
		}
		keys[i] = key;
		values[i] = value;
		N++;
	}
	void showValue()
	{
		for (int i = 0; i < N; ++i)
			cout << setw(5) << values[i];
		cout << endl;
	}
	void showKey()
	{
		for (int i = 0; i < N; ++i)
			cout << setw(5) << keys[i];
		cout << endl;
	}

private:
	int N = 0;
	string* keys=nullptr;
	int* values=nullptr;
};

int main()
{
	BinSerachST st(50);
	string key;
	int val;
	while (true)
	{
		cin >> key;
		if (key == "quit")
		{
			break;
		}
		cin >> val;
		st.put(key, val);
	}
	st.showKey();
	st.showValue();
	cin >> key;
	cout << st.get(key) <<"\n" <<endl;
	cin >> key;
	cout << st.get(key) <<"\n"<< endl;
	return 0;
}
其他操作都是简单的操作没有具体体现。
