class OrderedFile {
    int *array;
    int len;
    int nodeSize;
    OrderedFile();
    int *findSpace(int key);
    void rebalance(int *start, int *end);
    void insert(int key);
    int *begin();
    int *end();
}