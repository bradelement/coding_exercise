int find(int x)
{
    if (x == pre[x]) return x;
    return pre[x] = find(pre[x]);
}

int kruskal() {
    for (int i=1; i<=M; i++) {
        pre[i] = i;
    }
    sort(hub, hub+N);

    int sum = 0;
    for (int i=0; i<N; i++) {
        int a = find(hub[i].x);
        int b = find(hub[i].y);
        if (a != b) {
            pre[b] = a;
            sum += hub[i].len;
        }
    }

    return sum;
}