#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // 1. 创建一个指向整数的指针，并把它设为 NULL
    int *p = NULL;
    
    // 2. 尝试解引用这个 NULL 指针并赋值
    // 这绝对会触发段错误 (Segmentation Fault)
    *p = 10;
    
    // 这行永远不会执行到
    printf("Value: %d\n", *p);
    
    return 0;
}