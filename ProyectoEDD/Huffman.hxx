#ifndef HUFFMAN_HXX
#define HUFFMAN_HXX
#include "Dato.hxx"
std::vector<Dato> HuffmanCodes(int data[], int freq[], int size);

void printCodes(struct MinHeapNode* root, int arr[], int top, std::vector<Dato> &codigos);

struct MinHeapNode* buildHuffmanTree(int data[], int freq[], int size);

struct MinHeap* createAndBuildMinHeap(int data[], int freq[], int size);

int isLeaf(struct MinHeapNode* root);

void printArr(int arr[], int n);

void buildMinHeap(struct MinHeap* minHeap);

void insertMinHeap(struct MinHeap* minHeap,
				struct MinHeapNode* minHeapNode);


struct MinHeapNode* extractMin(struct MinHeap* minHeap);


int isSizeOne(struct MinHeap* minHeap);

void minHeapify(struct MinHeap* minHeap, int idx);

void swapMinHeapNode(struct MinHeapNode** a,
					struct MinHeapNode** b);

struct MinHeap* createMinHeap(unsigned capacity);

struct MinHeapNode* newNode(int data, unsigned freq);

#endif