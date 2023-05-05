int forAll(int *arr, int elementCount, int (*function)(int,int)) {
    int v = arr[0], i;
    for(i = 1; i < elementCount; i++) {
        v = function(v, arr[i])
    }
    return v;
}
