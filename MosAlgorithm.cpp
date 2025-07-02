#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int arr[N];
int freq[N];        // Frequency of each element
int answers[N];     // Answers to the queries
int distinctCount = 0;

struct Query {
    int l, r, idx;
};

int blockSize;

bool compare(Query a, Query b) {
    int blockA = a.l / blockSize;
    int blockB = b.l / blockSize;
    if (blockA != blockB)
        return blockA < blockB;
    return a.r < b.r;  // Optional optimization: blockA % 2 ? a.r > b.r : a.r < b.r;
}

void add(int index) {
    freq[arr[index]]++;
    if (freq[arr[index]] == 1)
        distinctCount++;
}

void remove(int index) {
    freq[arr[index]]--;
    if (freq[arr[index]] == 0)
        distinctCount--;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    blockSize = sqrt(n);

    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].idx = i;
    }

    sort(queries.begin(), queries.end(), compare);

    int currL = 0, currR = -1;

    for (Query query : queries) {
        int L = query.l;
        int R = query.r;

        while (currL > L) add(--currL);
        while (currR < R) add(++currR);
        while (currL < L) remove(currL++);
        while (currR > R) remove(currR--);

        answers[query.idx] = distinctCount;
    }

    for (int i = 0; i < q; ++i)
        cout << answers[i] << "\n";

    return 0;
}
