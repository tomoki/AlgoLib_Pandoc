# データ構造

## Union-Find

~~~~~~{.cpp}
struct UnionFind{
    const int is_root = -1;
    vector<int> data;
    UnionFind(int n){
        data = vector<int>(n,-1);
    }
    // 親を探す
    int root(int x){
        if(data[x] < 0){
            return x;
        }else{
            return data[x] = root(data[x]);
        }
    }
    // x,yの含まれる集合を併合
    bool unite(int x,int y){
        x = root(x);
        y = root(y);
        if(x != y){
            // 大きいほうに追加する。
            if(data[y] < data[x]) swap(x,y);
            data[x] += data[y];
            data[y] = x;
            return true;
        }else{
            return false;
        }
    }
    // 同じ集合にいるかどうか
    bool same(int x,int y){
        return root(x) == root(y);
    }
    int size(int x){
        return -data[root(x)];
    }
};
~~~~~~

## ヒープ

~~~~~~{.cpp}
#include <queue>
#include <iostream>

using namespace std;

typedef pair<int,int> pii;

struct Comp{
    bool operator()(pii left,pii right){
        if(left.second < right.second) return true;
        else if(left.second == right.second and left.first > right.first) return true;
        else return false;
    };
};

struct Robot{
    int y,x,dir,step;
    Robot(int y,int x,int dir,int step) : y(y),x(x),dir(dir),step(step) {};
};

// <,>を定義すればless<Robot>みたいに扱える。
bool operator<(const Robot& lhs,const Robot& rhs){
    return lhs.step < rhs.step;
}
bool operator>(const Robot& lhs,const Robot& rhs){
    return lhs.step > rhs.step;
}

int main(){
    // 何も書かないと降順。(おっきい方からでてくる。)
    // これは昇順(ちいさいほうから出てくる)にしたもの。
    priority_queue<int,vector<int>,greater<int> > Qi;
    //関数オブジェクトを使っていい感じにもできる。
    priority_queue<pii,vector<pii>,Comp> Q;
    // 自作クラスの場合はこんな感じ
    priority_queue<Robot,vector<Robot>,greater<Robot> > que;

    Q.push(make_pair(1,2));
    Q.push(make_pair(2,2));
    Q.push(make_pair(3,2));
    while(not Q.empty()){
        cout << Q.top().first << " " << Q.top().second << endl;
        Q.pop();
    }
}
~~~~~~

## bitset
限られた大きさのvector\<bool\>を使いたいときに、bitsetを使うことができる。

~~~~~~{.cpp}
#include <iostream>
#include <bitset>

using namespace std;
const int N = 10;

struct bit_cmp{
    bool operator() (const bitset<N> &left,const bitset<N> &right) {
        for(int i=N-1;i>=0;i--){
            if(left[i] < right[i]) return true;
            if(left[i] > right[i]) return false;
        }
        return false;
    }
};


int main(){
    //定数じゃないとダメ。最初は全部false
    bitset<N> bits;
    // すべての要素をtrue -> 1111111111
    bits.set();
    if(bits.all()) cout << "all" << endl;
    // 立っているbitの数 -> 10
    cout << bits.count() << endl;
    // すべての要素をfalse -> 0000000000
    bits.reset();
    if(bits.none()) cout << "none" << endl;

    //1番目の要素をtrue -> 0100000000
    bits.set(1);
    if(bits.any()) cout << "any" << endl;

    // 0110000000
    bits.set(2);
    //1番目の要素をfalse -> 0010000000
    bits.reset(1);

    if(bits[2]) cout << 2 << endl;
    cout << bits << endl;

    bitset<N> newbits;
    // 和を取る
    bits |= newbits;
    // 積を取る
    bits &= newbits;

    // 関数オブジェクトを作る必要アリ
    map<bitset<N>,int,bit_cmp> M;
}
~~~~~~

## 分数
テストちゅう.

~~~~~~{.cpp}
typedef long long ll;
ll gcd(ll a,ll b){
    return b==0 ? a : gcd(b,a%b);
}

ll lcm(ll a,ll b){
    if(a < 0) a *= -1;
    if(b < 0) b *= -1;
    return a*b / gcd(a,b);
}

struct Fraction{
    ll n,d;
    Fraction(ll _n,ll _d){
        ll c = lcm(_n,_d);
        n = c / _d;
        d = c / _n;
        if(d < 0){
            n *= -1;
            d *= -1;
        }
    }

    Fraction(ll _n){
        Fraction(_n,1);
    }

    bool operator<(const Fraction& r) const{
        ll c_d = lcm(d,r.d);
        return n*(c_d/d)< r.n*(c_d/r.d);
    }
    bool operator>(const Fraction& r) const{
        return not ((*this) < r or (*this) == r);
    }
    bool operator<=(const Fraction& r) const{
        return (*this) < r or (*this) == r;
    }
    bool operator>=(const Fraction& r) const{
        return (*this) > r or (*this) == r;
    }
    bool operator==(const Fraction& r) const{
        return n == r.n and d == r.d;
    }
    Fraction operator+(const Fraction& r) const{
        ll c_d = lcm(d,r.d);
        return Fraction(n*(c_d/d)+r.n*(c_d/r.d),c_d);
    }
    Fraction operator-(const Fraction& r) const{
        return (*this) + (-r);
    }
    Fraction operator*(const Fraction& r) const{
        return Fraction(n*r.n,d*r.d);
    }
    Fraction operator/(const Fraction& r) const{
        return (*this) * Fraction(r.d,r.n);
    }
    Fraction operator+() const{
        return Fraction(n,d);
    }
    Fraction operator-() const{
        return (*this) * -1;
    }
    Fraction operator*(const ll& a) const{
        return Fraction(a*n,d) ;
    }
};

ostream& operator<<(ostream &os,const Fraction& f){
    os << f.n << "/" << f.d;
    return os;
}
~~~~~~

## セグメント木

### 普通の
RMQ (POJ 3264)

~~~~~~{include="cpp/segment_tree.cpp" .cpp}
~~~~~~

### Lazy
テスト中 参考: http://d.hatena.ne.jp/kyuridenamida/20121114/1352835261

~~~~~~{.cpp}
// T = 各要素および区間取得の結果の型
// op = T(T, T), 区間取得を行う関数 (例えば RMQ なら min)
// e = T(), op における単位元
// F = "Lazy" 遅延している操作の型
// mapping = T(F, T) 遅延している操作 F を区間取得の結果 T に対し行う関数
// composition = F(F f, F g)、遅延している操作 g に対し、追加で f を行った時に生成する遅延操作を生成する
//   f(g(x)) となるので g がさきに行われる処理
// id = F(), composition の恒等写像 (遅延している操作の単位元)
// F(op(x, y)) = op(F(x), F(y)) を満たす必要がある
template<typename T, auto op, auto e, typename F, auto mapping, auto composition, auto id>
class LazySegmentTree {
    static_assert(std::is_convertible_v<decltype(op), std::function<T(T, T)>>, "op should be T(T, T)");
    static_assert(std::is_convertible_v<decltype(e), std::function<T()>>, "e should be T()");
    static_assert(std::is_convertible_v<decltype(mapping), std::function<T(F, T)>>, "mapping should be T(F, T)");
    static_assert(std::is_convertible_v<decltype(composition), std::function<F(F, F)>>, "composition should be F(F, F)");
    static_assert(std::is_convertible_v<decltype(id), std::function<F()>>, "id should be F()");

public:
    explicit LazySegmentTree(int _n)
    {
        n = 1;
        while (n < _n) n *= 2;
        data = vector<T>(2 * n - 1, e());
        lazy = vector<F>(2 * n - 1, id());

    }
    template<class InputIterator>
    explicit LazySegmentTree(InputIterator first, InputIterator last) : LazySegmentTree(distance(first, last))
    {
        size_t i = 0;
        for (auto it = first; it != last; ++it, i++) {
            update(i, *it);
        }
    }
    void update(int i, T v)
    {
        int k = i + n - 1;
        data[k] = v;
        while (k > 0) {
            k = get_parent_index(k);
            auto left = data[get_left_index(k)];
            auto righ = data[get_right_index(k)];
            data[k] = op(left, righ);
        }
    }
    // [a, b) に操作 f を行う
    void apply(int a, int b, F f)
    {
        assert(0 <= a && a <= b && b <= n);
        return apply(a, b, f, 0, 0, n);
    }

    // [a, b) 半開区間の値を取得する
    [[nodiscard]] T get(int a, int b)
    {
        assert(0 <= a && a < b && b <= n); // FIXME: should check the original n?
        // ノード 0 の管理区間は [0, n)
        return get(a, b, 0, 0, n);
    }
    [[nodiscard]] size_t size() const { return n; }
private:
    static int get_left_index(int k) { return 2 * k + 1; }
    static int get_right_index(int k) { return 2 * k + 2; };
    static int get_parent_index(int k) { return (k - 1) / 2; }
    // k 番目のノードの遅延操作を反映する
    void apply_lazy(int k, int l, int r)
    {
        if (lazy[k] == id()) return;
        data[k] = mapping(lazy[k], data[k]);
        // 子供に遅延評価を伝搬する
        if (r - l > 1) {
            const int left_index = get_left_index(k);
            const int right_index = get_right_index(k);
            lazy[left_index] = composition(lazy[k], lazy[left_index]);
            lazy[right_index] = composition(lazy[k], lazy[right_index]);
        }
        lazy[k] = id();
    }

    // l, r はノード k の管理する区間
    [[nodiscard]] T get(int a, int b, int k, int l, int r)
    {
        if (r <= a || b <= l) return e();
        apply_lazy(k, l, r);
        if (a <= l && r <= b) return data[k];
        const int left_index = get_left_index(k);
        const int right_index = get_right_index(k);
        const auto left = get(a, b, left_index, l, (l+r)/2);
        const auto right = get(a, b, right_index, (l+r)/2, r);
        return op(left, right);
    }
    void apply(int a, int b, F f, int k, int l, int r)
    {
        apply_lazy(k, l, r);
        if (r <= a || b <= l) return;
        if (a <= l && r <= b) {
            lazy[k] = composition(f, lazy[k]);
            apply_lazy(k, l, r);
        } else {
            apply(a, b, f, get_left_index(k), l, (l+r)/2);
            apply(a, b, f, get_right_index(k), (l+r)/2, r);
            data[k] = op(data[get_left_index(k)], data[get_right_index(k)]);
        }
    }

    int n = 0;
    vector<T> data;
    vector<F> lazy;
};

~~~~~~

## 定数個のみを保持するpriority_queue
ビームサーチとかに使える？

~~~~~~{.cpp include="cpp/lens_queue.cpp"}
~~~~~~

## Set で区間を管理するテクニック

~~~~~~
// 「区間を set で管理するテクニック」
// 半開区間 [a, b) を pair(a, b) として set にいれる。
// ただし set の中の区間は重複を持たないよう管理する
// https://codeforces.com/contest/915/problem/E
struct RangeSet {
    using T = int64_t;
    RangeSet()
    {
        // 番兵
        segs.emplace(std::numeric_limits<T>::min(), std::numeric_limits<T>::min());
        segs.emplace(std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
    }
    // [l, r) を完全に含む区間が存在するならその区間を返す
    std::optional<std::pair<T, T>> containedBy(T l, T r)
    {
        // assert(l <= r);
        // [l, r) が含まれているとしたら一つ前のもの
        auto it = std::upper_bound(segs.begin(), segs.end(), make_pair(l, r));
        --it;
        if (it->first <= l && r <= it->second) return *it;
        return std::nullopt;
    }
    // 区間の数を返す
    size_t size()
    {
        return segs.size() - 2; // 番兵のぶんをひく
    }
    // 区間 [l, r) を追加する。区間のうち、新規に追加された要素を返す
    T insert(T l, T r)
    {
        // assert(l <= r);
        auto it = segs.upper_bound(make_pair(l, r));
        --it;
        // カバーされているので 0
        if (it->first <= l && r <= it->second) return 0;
        // 以下では l, r を書き換えていくが、この時既存の要素でカバーされていたものを "erased" とする
        // そして最後に追加された要素を (l-r) - erased で計算。
        T erased = 0;
        // 左の区間と一部被っている場合は合体する
        if (it->first <= l && l <= it->second) {
            erased += it->second - it->first;
            l = it->first;
            it = segs.erase(it);
        } else {
            ++it; // 左の区間とは被っていないので次へ
        }
        // 右の区間と共通部分があれば合体していく (it = upper_bound 相当)
        while (it->first <= r) {
            if (it->second <= r) {
                // 新しくできた要素で完全にカバーされている
                erased += it->second - it->first;
                it = segs.erase(it);
            } else {
                // l <= it->first <= r < it->second
                erased += it->second - it->first;
                r = it->second;
                segs.erase(it);
                // 既存の要素の方が r が長いのであればそれ以上に長い要素は存在しない
                break;
            }
        }
        segs.emplace(l, r);
        return (r - l) - erased;
    }
    // 区間 [l, r) を削除する。区間のうち、削除された要素を返す
    T erase(T l, T r)
    {
        auto it = segs.upper_bound(make_pair(l, r));
        --it;
        // 完全にカバーされている場合はその区間を分割する
        if (it->first <= l && r <= it->second) {
            if (it->first != l)
                segs.emplace(it->first, l);
            if (r != it->second)
                segs.emplace(r, it->second);
            segs.erase(it);
            return r - l;
        }
        T erased = 0;
        // 左の区間と一部被っている場合は左の区間の削除を行う
        if (it->first <= l && l < it->second) {
            erased += it->second - l;
            if (it->first != l) {
                segs.emplace(it->first, l);
            }
            it = segs.erase(it);
        } else {
            ++it;
        }
        // 右の区間と共通部分があれば削除していく (it = upper_bound 相当)
        while (it->first < r) {
            if (it->second <= r) {
                // 完全に削除される
                erased += it->second - it->first;
                it = segs.erase(it);
            } else {
                // l <= it->first <= r < it->second
                erased += r - it->first;
                segs.emplace(r, it->second);
                segs.erase(it);
                break;
            }
        }
        return erased;
    }
    // x 以上のカバーされていない最小の値を返す
    T mex(T x)
    {
        auto it = segs.lower_bound(make_pair(x, x+1));
        if (it->first <= x && x <= it->second) return it->second;
        return x;
    }
private:
    std::set<std::pair<T, T>> segs;
    friend ostream& operator<<(ostream&, const RangeSet&);
};
~~~~~~