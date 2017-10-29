//Binary search
//Find the element
#include <stdio.h>
#include <algorithm>
#define MAXN 1000000

int num[MAXN];

int bs(int num[],int l,int r,int key) {
    if (l > r) return -1;
    int mid = (l+r)/2;
    if (num[mid] > key) return bs(num,l,mid-1,key);
    if (num[mid] < key) return bs(num,mid+1,r,key);
    return mid;
}

int main() {
    int n,key;
    scanf("%d%d",&n,&key);
    for(int i=0;i<n;i++) scanf("%d",&num[i]);
    std::sort(num,num+n);
    printf("%d",bs(num,0,n-1,key));
}
