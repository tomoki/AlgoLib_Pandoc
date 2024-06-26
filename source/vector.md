# std::vector

ここでは、配列のSTL版である、vectorの使いかたについて書く。
ここに書かれている関数は、string等にも用いることができるものが多い。
ちなみに、vector\<bool\>は使ってはいけない。bitsetや、vector\<char\>をつかうこと。
また、all(vector)は、vector.begin(),vector.end()とdefineしている。

## 基本
~~~~~~{.cpp}
//要素数10で、初期値は-1にする。
vector<int> vec(10,-1);
//vecの最初から3つの要素をコピーする。
vector<int> newvec(vec.begin(),vec.begin()+3);
//vecの最初から3つの要素を削除する。
vec.erase(vec.begin(),vec.begin()+3);
~~~~~~

## 並び換え

### sort

C++のsortは、$O(n \log n)$で、introsort。何も指定しない場合には昇順にソートされる。
注意すべきなのは、C++11では、最悪ケースで$O(n \log n)$となること。C++03では特に何も制限はないが、g++ならば$O(n \log n)$である。

~~~~~~{.cpp}
//昇順 (sort(vec.begin(),vec.end())) (2,1,3) -> (1,2,3)
sort(all(vec));
//降順 (ただ単純にreverseしてもいい) (2,1,3) -> (3,2,1)
sort(all(vec),greater<int>());
~~~~~~

第三引数には関数を渡すことができる。

~~~~~~{.cpp}
bool comp(const int& a ,const int& b){
    return abs(a) < abs(b);
}
int main(){
    vector<int> vec(10);
    //絶対値が小さい順にソート
    sort(all(vec),comp);
    sort(all(vec),[](int l,int r) {return abs(l)<abs(r)});
}
~~~~~~

### stable_sort

sortとちがって、同じ優先順位の要素の順番は保存される。最悪計算量は$O(n \log ^ 2 n)$である。

~~~~~~{.cpp}
stable_sort(all(vec),comp);
~~~~~~

## unique


隣あう同じ要素を一つにまとめる。eraseすることに注意。

~~~~~~{.cpp}
int ints[] = {1,1,2,1,1};
vector<int> vec(ints,ints+5);
vec.erase(unique(all(vec)),vec.end());
// 1 2 1
repeat(i,vec.size()) cout << vec[i] << endl;
~~~~~~

## rotate


rotateは第二引数の場所を先頭にするように回転する。

~~~~~~{.cpp}
int[] ints = {1,2,3,4,5};
vector<int> vec(ints,ints+5);
rotate(vec.begin(),vec.begin()+1),vec.end()); //2,3,4,5,1
rotate(vec.begin(),vec.end()-1,vec.end()); //5,1,2,3,4
~~~~~~

## next_permutation

順列をすべて列挙する。$N!$個なので、それなりの勢いで大きくなる。章末の付録参照。

~~~~~~{.cpp}
vector<int> V = {3,2,1,4};
//ソートすること。
sort(all(V));

do{
   for(int i=0;i<V.size();i++){
       cout << V[i] << " ";
   }
   cout << endl;
}while(next_permutation(all(V)));
~~~~~~

## 座標圧縮

~~~~~~{.cpp include=cpp/zip.cpp}
~~~~~~

## LIS

最長増加部分列

~~~~~{.cpp}
// 長さだけを計算する版
// https://atcoder.jp/contests/abc354/editorial/10027
int lis(const vector<ll>& v) {
    int n = v.size();
    const ll INF = 1ll << 50;

    // dp[i] = 長さ i を実現する場合の最後の要素の大きさ。必ず増加列になる。
    vector<ll> dp(n+1, INF);
    dp[0] = -INF;
    for (int i = 0; i < n; i++) {
        // 最後の要素が v[i] 以上の箇所を更新する
        auto it = lower_bound(all(dp), v[i]);
        *it = min(v[i], *it);
    }

    dump(dp);
    int length = lower_bound(all(dp), INF) - dp.begin() - 1;

    return length;
}

// https://atcoder.jp/contests/abc354/editorial/10027
vector<int> lis_hukugen(const vector<ll>& v) {
    int n = v.size();
    const ll INF = 1ll << 50;

    // 長さの計算と一緒に、その要素がどの長さの場合を更新したかを覚えていく
    vector<int> updated_index(n, INF);
    {
        vector<ll> dp(n+1, INF);
        dp[0] = -INF;
        for (int i = 0; i < n; i++) {
            auto it = lower_bound(all(dp), v[i]);
            *it = min(v[i], *it);
            updated_index[i] = it - dp.begin();
        }
    }
    int length = lower_bound(all(dp), INF) - dp.begin() - 1;
    return updated_index;
}
~~~~~