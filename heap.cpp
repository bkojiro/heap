#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

int size(int* heap);
void print(int* heap, int pos, int depth, int size);
void insert(int* &heap, int x, int index);
void resort(int* &heap, int index);
void removeAll(int* &heap, int size);

int main() {
  int* heap = new int[101];
  bool running = true;
  while (running) {
    cout << "Enter PRINT, INSERT, REMOVE, REMOVEALL, or QUIT" << endl << "> ";
    char action[10];
    cin.get(action, 11);
    cin.ignore();
    if (strcmp(action, "PRINT") == 0) { //print table
      print(heap, 1, 0, size(heap));
    } else if (strcmp(action, "INSERT") == 0) { //insert at next open slot
      cout << "Type 'f' to insert by file or 'n' to insert by number" << endl << "> ";
      char fileornumber;
      cin >> fileornumber;
      cin.ignore();
      if (fileornumber == 'f') {
	//grab number file
	ifstream numbers;
	numbers.open("numbers.txt");
	int x;
	while (numbers >> x) {
	  //insert x into heap
	  int index = size(heap);
	  heap[index] = x;
	  insert(heap, x, index);
	}
	numbers.close();
      } else if (fileornumber == 'n') {
	//ask for number
	cout << "Enter a number" << endl << "> ";
	int x;
	cin >> x;
	cin.ignore();
	int index = size(heap);
	heap[index] = x;
	insert(heap, x, index);
      } else {
	cout << "Invalid input" << endl;
      }
    } else if (strcmp(action, "REMOVE") == 0) { //remove root and print, then move everything accordingly
      cout << "Root: " << heap[1] << endl;
      heap[1] = heap[size(heap) - 1];
      heap[size(heap) - 1] = 0;
      resort(heap, 1);
    } else if (strcmp(action, "REMOVEALL") == 0) { //continuously remove and print
      removeAll(heap, size(heap));
    } else if (strcmp(action, "QUIT") == 0) { //quit program
      cout << "Program terminated";
      running = false;
    } else {
      cout << "Invalid input. Check spelling/capitalization" << endl;
    }
  }
  return 0;
}

int size(int* heap) {
  int index = 1;
  while(heap[index] != 0) {
    index++;
  }
  return index;
}

void print(int* heap, int pos, int depth, int size) { //visual printing of array
  if (pos * 2 + 1 < size) { //check left NOT null
    print(heap, pos * 2 + 1, depth + 1, size);
  }
  for (int a = 0; a < depth; a++) {
    cout << '\t';
  }
  cout << heap[pos] << endl;
  if (pos * 2 < size) {
    print(heap, pos * 2, depth + 1, size);
  }
}

void insert(int* &heap, int x, int index) {
  int parentID = floor(index/2);
  int parent = heap[parentID];
  if (x > parent && index != 1) {
    int temp = index;
    index = parentID;
    heap[index] = x;
    heap[temp] = parent;
    insert(heap, x, index);
  }
}

void resort(int* &heap, int index) { //recursively go through heap and make children smaller than parent
  int rightID = index * 2;
  int leftID = rightID + 1;
  if (heap[index] < heap[leftID]) { //parent is smaller than left child
    int temp = heap[index];
    heap[index] = heap[leftID];
    heap[leftID] = temp;
    
    resort(heap, leftID);
  }
  if (heap[index] < heap[rightID]) {
    int temp = heap[index];
    heap[index] = heap[rightID];
    heap[rightID] = temp;
    
    resort(heap, rightID);
  }
}

void removeAll(int* &heap, int size) { //call remove until heap is empty
  cout << "Removing values: ";
  for (int a = 1; a < size; a++) {
    cout << heap[1] << "  ";
    heap[1] = heap[size - a];
    heap[size - a] = 0;
    resort(heap, 1);
  }
}
