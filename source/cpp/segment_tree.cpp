
template<typename T, auto op, auto e>
class SegmentTree {
    static_assert(std::is_convertible_v<decltype(op), std::function<T(T, T)>>,
              "op must work as T(T, T)");
    static_assert(std::is_convertible_v<decltype(e), std::function<T()>>,
              "e should be T()");
public:
    explicit SegmentTree(int _n) : original_n(_n)
    {
        n = 1;
        while (n < _n) n *= 2;
        data = vector<T>(2 * n - 1, e());
    }
    template<class InputIterator>
    explicit SegmentTree(InputIterator first, InputIterator last)
    {
        n = 1;
        original_n = distance(first, last);
        while (n < original_n) n *= 2;
        data = vector<T>(2 * n - 1, e());
        size_t i = 0;
        for (auto it = first; it != last; ++it, i++) {
            update(i, *it);
        }
    }
    void update(int i, T v)
    {
        assert(0 <= i && i < original_n);
        int k = i + n - 1;
        data[k] = v;
        while (k > 0) {
            k = get_parent_index(k);
            auto left = data[get_left_index(k)];
            auto right = data[get_right_index(k)];
            data[k] = op(left, right);
        }
    }

    // [a, b) 半開区間の値を取得する、 a == b なら e() を返す
    [[nodiscard]] T get(int a, int b) const
    {
        assert(0 <= a && a <= b && b <= original_n);
        // ノード 0 の管理区間は [0, n)
        return get(a, b, 0, 0, n);
    }
    [[nodiscard]] size_t size() const { return n; }
private:
    static int get_left_index(int k) { return (k << 1) + 1; }
    static int get_right_index(int k) { return (k << 1) + 2; };
    static int get_parent_index(int k) { return (k - 1) >> 1; }
    // l, r はノード k の管理する区間
    [[nodiscard]] T get(int a, int b, int k, int l, int r) const
    {
        if (r <= a || b <= l) return e();
        if (a <= l && r <= b) return data[k];
        const int left_index = get_left_index(k);
        const int right_index = get_right_index(k);
        const int mid = (l+r) >> 1;
        const auto left = get(a, b, left_index, l, mid);
        const auto right = get(a, b, right_index, mid, r);
        return op(left, right);
    }

    int n = 0;
    int original_n = 0;
    vector<T> data;
};


int main(int argc, char** argv) {
    // RMQ.
    const auto op = [](int a, int b) {return max(a, b); };
    const auto e = []() { return 0; };
    vector<int> a;
    SegmentTree<int, op, e> st(all(a));
}