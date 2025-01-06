struct Node {
    long long sum;        // Total sum of the segment
    long long maxSum;     // Maximum subarray sum in the segment
    long long minSum;     // Minimum subarray sum in the segment
    long long prefixSum;  // Maximum prefix sum in the segment
    long long suffixSum;  // Maximum suffix sum in the segment
};

class SegmentTree {
    vector<Node> tree;
    int size;

    Node merge(const Node& left, const Node& right) {
        Node res;
        res.sum = left.sum + right.sum;
        res.prefixSum = max(left.prefixSum, left.sum + right.prefixSum);
        res.suffixSum = max(right.suffixSum, right.sum + left.suffixSum);
        res.maxSum = max({left.maxSum, right.maxSum, left.suffixSum + right.prefixSum});
        res.minSum = min({left.minSum, right.minSum, left.suffixSum + right.prefixSum});
        return res;
    }

    void build(vector<long long>& arr, int x, int lx, int rx) {
        if (lx == rx) {
            if (lx < (int)arr.size()) {
                long long value = arr[lx];
                tree[x] = {value, value, value, value, value};
            }
            return;
        }
        int mid = (lx + rx) / 2;
        build(arr, 2 * x + 1, lx, mid);
        build(arr, 2 * x + 2, mid + 1, rx);
        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void update(int idx, long long value, int x, int lx, int rx) {
        if (lx == rx) {
            tree[x] = {value, value, value, value, value};
            return;
        }
        int mid = (lx + rx) / 2;
        if (idx <= mid) {
            update(idx, value, 2 * x + 1, lx, mid);
        } else {
            update(idx, value, 2 * x + 2, mid + 1, rx);
        }
        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    Node query(int l, int r, int x, int lx, int rx) {
        if (l > rx || r < lx) return {0, LLONG_MIN, LLONG_MAX, LLONG_MIN, LLONG_MIN}; // Neutral element
        if (l <= lx && rx <= r) return tree[x];
        int mid = (lx + rx) / 2;
        Node left = query(l, r, 2 * x + 1, lx, mid);
        Node right = query(l, r, 2 * x + 2, mid + 1, rx);
        return merge(left, right);
    }

public:
    void init(int n) {
        size = n;
        tree.resize(4 * n);
    }

    void build(vector<long long>& arr) {
        build(arr, 0, 0, size - 1);
    }

    void update(int idx, long long value) {
        update(idx, value, 0, 0, size - 1);
    }

    Node query(int l, int r) {
        return query(l, r, 0, 0, size - 1);
    }
};