#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

void print(int* heap);
void insert(int x, int* &heap);
void remove();
void removeAll();

int main() {
  int* heap = new int[101];
  bool running = true;
  while (running) {
    cout << "Enter PRINT, INSERT, REMOVE, REMOVEALL, or QUIT" << endl << "> ";
    char action[10];
    cin.get(action, 11);
    cin.ignore();
    if (strcmp(action, "PRINT") == 0) { //print table
      print(heap);
    } else if (strcmp(action, "INSERT") == 0) { //insert at next open slot
      cout << "Type 'f' to insert by file or 'n' to insert by number" << endl << "> ";
      char fileornumber;
      cin >> fileornumber;
      cin.ignore();
      if (fileornumber == 'f') {
	//grab number file
	ifstream numbers;
	numbers.open("newNums.txt");
	int x;
	while (numbers >> x) {
	  //insert x into heap
	  insert(x, heap);
	}
	numbers.close();
      } else if (fileornumber == 'n') {
	//ask for number
	cout << "Enter a number" << endl << "> ";
	int x;
	cin >> x;
	cin.ignore();
	insert(x, heap);
      } else {
	cout << "Invalid input" << endl;
      }
    } else if (strcmp(action, "REMOVE") == 0) { //remove root and print, then move everything accordingly
      
    } else if (strcmp(action, "REMOVEALL") == 0) { //continuously remove and print
      
    } else if (strcmp(action, "QUIT") == 0) { //quit program
      cout << "Program terminated";
      running = false;
    } else {
      cout << "Invalid input. Check spelling/capitalization" << endl;
    }
  }
  return 0;
}

void print(int* heap) { //visual printing of array
  int index = 1;
  while (heap[index + 1] != 0) {
    index++;
  }
  int levels = ceil(log2(index)) + 1;
  //reset index once # of levels is found
  index = 1;
  while (heap[index] != 0) {
    //find out how to visualize
  }
}

void insert(int x, int* &heap) { //insert index at empty rightmost spot
  //NOTE: right child is index * 2 and left child is index * 2 + 1 so next open slot in array is rightmost position
  int index = 1;
  while (heap[index] != 0) {
    index++; //next available slot in array
  }
  heap[index] = x;
  int parentID = floor(index/2);
  int parent = heap[parentID];
  while (x > parent && index != 1) {
    int temp = index;
    index = parentID; //swap index
    heap[index] = x; //insert x at parent index
    heap[temp] = parent;
    //now reevaluate parent
    parentID = floor(index/2);
    parent = heap[parentID];
  }
}

void remove() { //remove root, print it, then resort table

}

void removeAll() { //call remove until heap is empty

}
