//Sliding window maximum : Deque sol
//Find min/max in range with size k
#include <stdio.h>
#include <deque>
#define MAXN 1000000
using namespace std;

int num[MAXN];

int main() {
    int n,k;
    deque <int> dq;
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++) scanf("%d",&num[i]);
    for(int i=0;i<k;i++) {
        while (!dq.empty() && num[dq.back()] <= num[i]) dq.pop_back();
        dq.push_back(i);
    }
    for(int i=k;i<n;i++) {
        printf("%d ",num[dq.front()]);
        while (!dq.empty() && dq.front() <= i-k) dq.pop_front();
        while (!dq.empty() && num[dq.back()] <= num[i]) dq.pop_back();
        dq.push_back(i);
    }
    printf("%d",num[dq.front()]);
}
