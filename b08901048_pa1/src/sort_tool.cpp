// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
// #include <cmath>
// using std::floor;
#include <iostream>
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int> &data)
{
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for (int i = 1; i < data.size(); i++)
    {
        int key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > key)
        {
            data[j + 1] = data[j];
            j = j - 1;
        }
        data[j + 1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int> &data)
{
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int> &data, int low, int high)
{
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if (low < high)
    {
        int middle = Partition(data, low, high);
        QuickSortSubVector(data, low, middle - 1);
        QuickSortSubVector(data, middle + 1, high);
    }
}

int SortTool::Partition(vector<int> &data, int low, int high)
{
    // Function : Partition the vector
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int x = data[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        if (data[j] <= x)
        {
            i++;
            swap(data[i], data[j]);
        }
    }
    swap(data[i + 1], data[high]);
    return i + 1;
}

// Merge sort method
void SortTool::MergeSort(vector<int> &data)
{
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int> &data, int low, int high)
{
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if (high > low)
    {
        int middle1 = (low + high) / 2;
        int middle2 = middle1 + 1;
        MergeSortSubVector(data, low, middle1);
        MergeSortSubVector(data, middle2, high);
        Merge(data, low, middle1, middle2, high);
    }
}

// Merge
void SortTool::Merge(vector<int> &data, int low, int middle1, int middle2, int high)
{
    int n_one = middle1 - low + 1;
    int n_two = high - middle1;
    vector<int> L(n_one + 1);
    vector<int> R(n_two + 1);
    for (int i = 0; i < n_one; i++)
    {
        L[i] = data[low + i];
    }
    for (int j = 0; j < n_two; j++)
    {
        R[j] = data[middle1 + j + 1];
    }
    L[n_one] = 10000000;
    R[n_two] = 10000000;
    int ii = 0;
    int jj = 0;
    for (int k = low; k <= high; k++)
    {
        if (L[ii] <= R[jj])
        {
            data[k] = L[ii];
            ii++;
        }
        else
        {
            data[k] = R[jj];
            jj++;
        }
    }
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
}

// Heap sort method
void SortTool::HeapSort(vector<int> &data)
{
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--)
    {
        swap(data[0], data[i]);
        heapSize--;
        MaxHeapify(data, 0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int> &data, int root)
{
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left = root * 2 + 1;
    int right = root * 2 + 2;
    int largest;
    if (left <= heapSize - 1 && data[left] > data[root])
    {
        largest = left;
    }
    else
    {
        largest = root;
    }
    if (right <= heapSize - 1 && data[right] > data[largest])
    {
        largest = right;
    }
    if (largest != root)
    {
        // int temp = data[root];
        // data[root] = data[largest];
        // data[largest] = temp;
        swap(data[root], data[largest]);
        MaxHeapify(data, largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int> &data)
{
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i = (heapSize / 2) - 1; i >= 0; i--)
    {
        MaxHeapify(data, i);
    }
}
