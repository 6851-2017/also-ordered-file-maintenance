class OrderedFile {
    int *array;
    int len;
    int nodeSize;
    int *findSpace(int key);
    void rebalance(int *start, int *end);
    void insert(int key);
    int *begin();
    int *end();
}

const BLANK_SENTINEL = -1;

OrderedFile::OrderedFile() {

}

OrderedFile::findSpace(int key){
    int* first = begin();
    int* last = end();
    while(first != last){
        int len = last - first;
        int *mid = first + (len >> 1);
        while(mid != last && *mid == BLANK_SENTINEL)
            mid++;
        if(mid == last){
            last = first + (len >> 1);
            continue;
        }
        if(*mid <= key) first = mid;
        else last = mid;
    }
    return first;
}

OrderedFile::rebalance()