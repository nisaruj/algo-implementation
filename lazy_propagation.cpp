//Lazy propagation
//Segment tree + range update
#include <stdio.h>
#define MAXN 1000000

int num[MAXN],st[MAXN],lazy[MAXN];

//Build the tree
int build(int node,int l,int r) {
    if (l == r) st[node] = num[l];
    else {
        int mid = (l+r)/2;
        build(node*2,l,mid);
        build(node*2+1,mid+1,r);
        st[node] = st[node*2] + st[node*2+1];
    }
}

//Update range [a,b]
int update(int node,int l,int r,int a,int b,int val) {
    if (lazy[node] != 0) {
        //Update it
        st[node] += (r-l+1)*lazy[node];
        //Not leaf node them Make child lazy
        if (l != r) {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        //Reset it
        lazy[node] = 0;
    }
    if (l > r || l > b || r < a) return 0; //Out of range
    if (l >= a && r <= b) { //Fully in range
        st[node] += (r-l+1)*val;
        if (l != r) {
            lazy[node*2] += val;
            lazy[node*2+1] += val;
        }
        return 0;
    }
    int mid = (l+r)/2;
    update(node*2,l,mid,a,b,val);
    update(node*2+1,mid+1,r,a,b,val);
    st[node] = st[node*2] + st[node*2+1];
}

//Query range[a,b]
int query(int node,int l,int r,int a,int b) {
    if (l > r || l > b || r < a) return 0;
    if (lazy[node] != 0) {
        st[node] += (r-l+1)*lazy[node];
        if (l != r) {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if (l >= a && r <= b) return st[node];
    int mid = (l+r)/2;
    int p1 = query(node*2,l,mid,a,b);
    int p2 = query(node*2+1,mid+1,r,a,b);
    return p1 + p2;
}

int main() {
    int n,q,a,b,c,val;
    scanf("%d%d",&n,&q);
    for(int i=0;i<n;i++) scanf("%d",&num[i]);
    build(1,0,n-1);
    for(int i=0;i<q;i++) {
        scanf("%d%d%d",&c,&a,&b);
        if (c == 0) {
            scanf("%d",&val);
            update(1,0,n-1,a,b,val);
        } else {
            printf("Sum in range [%d,%d] = %d\n",a,b,query(1,0,n-1,a,b));
        }
    }
}
