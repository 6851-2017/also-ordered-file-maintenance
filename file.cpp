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

constexpr double lowerDensityBound(int depth, int height){
    return 0.5 - depth/(4. * height);
}

constexpr double upperDensityBound(int depth, int height){
    return 0.75 + depth/(4. * height);
}

OrderedFile::OrderedFile() {

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

int OrderedFile::countGaps(int start, int end){
    int num = 0;
    while(int i = start; i < end; i++) if(array[i] == BLANK_SENTINEL) num++;
    return num;
}

void OrderedFile::rebalance(int start, int end){
    int len = end - start;
    int filled = 0;
    int *buffer = new int[len];
    for(int i = start; i < end; i++){
        if(array[i] == BLANK_SENTINEL) continue;
        buffer[filled] = array[i];
        filled++;
    }
    int pos = 0;
    for(int i = 0; i < len; i++){
        //if it's greater than the wanted density, 
        if(pos/(i+1.) > filled/(double)len){
            array[start + i] = BLANK_SENTINEL;
            continue;
        }
        array[start+i] = buffer[pos];
        pos++;
    }
}

void OrderedFile::insert(int key){
    int space = findSpace(key);
    array[space] = key;
    int rangeSize = nodeSize;
    int depth = height;
    int rangeIndex = (space / nodeSize);
    while(true){
        int gaps = countGaps(rangeIndex * rangeSize, (rangeIndex + 1) * rangeSize);
        if(gaps > lowerDensityBound(depth, height)*rangeSize &&
            gaps < upperDensityBound(depth, height)*rangeSize) break;
        //if the density bound is not met
        depth--;
        rangeSize *= 2;
        rangeIndex = rangeIndex/2;
    }
    rebalance(rangeIndex*rangeSize, (rangeIndex+1)*rangeSize);
}

int *OrderedFile::begin(){
    return array;
}

int *OrderedFile::end(){
    return array+len;
}