#include<fstream>

class OrderedFile {
    int *array;
    int len;
    int nodeSize;
    int height;

    int *find(int key);
    int findSpace(int key);
    int countGaps(int start, int end);
    void rebalance(int start, int end);
    void insert(int key);
    int *begin();
    int *end();
}

const BLANK_SENTINEL = -1;

OrderedFile::OrderedFile(int size) {
  array = new int[size];
}

int *OrderedFile::find(int key){
    return array + findSpace(key);
}

int OrderedFile::findSpace(int key){
    int first = 0;
    int last = len;
    while(first != last){
        int len = last - first;
        int mid = first + (len >> 1);
        while(mid != last && array[mid] == BLANK_SENTINEL)
            mid++;
        if(mid == last){
            last = first + (len >> 1);
            continue;
        }
        if(array[mid] <= key) first = mid;
        else last = mid;
    }
    return first;
}

void OrderedFile::insert(int key){
    int space = findSpace(key);
    array[space] = key;
}

int *OrderedFile::begin(){
    return array;
}

int *OrderedFile::end(){
    return array+len;
}

int main (int argc, char **argv) {
  if (argc != 2) {
    std::cout << "provide file name only"
  }
  string file_name(argv[1]);
  ifstream fin(file_name);
  string line;
  int ins, size;
  ofm = OrderedFile(size);
  while (getline(fin, line)) {
    fin >> ins;
    ofm.insert(ins);
  }
  return 0;
}
