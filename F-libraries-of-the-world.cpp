#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

uniform_real_distribution<double> rng_double(0, 1);
uniform_int_distribution<int> rng_int;
uniform_int_distribution<ll> rng_ll;

int B, L, D;

int C[100005];

bool less_(int i, int j){
    return C[i] < C[j];
}

struct Library{
    Library(){}
    int n, t, m, i;
    vector<int> ID;
    Library(int n_, int t_, int m_, int i_, vector<int> &ID_){
        for (int i : ID_) ID.push_back(i);
        n = n_, t = t_, m = m_, i = i_;
    }
};

vector<Library> X, Y;

vector<int> V;

bool lib_less(Library &i, Library &j){
    return i.t < j.t;
}

ll score(vector<Library> &X){
    //compute score
    ll cur_sum = 0, ret = 0;
    vector<bool> chk(B);
    for (int i=0; i<L; i++){
        cur_sum += X[i].t;
        if (cur_sum >= D) break;
        ll left = D - cur_sum;
        for (ll j=0; j<min(left*X[i].m, 1LL*X[i].n); j++){
            int b = X[i].ID[j];
            if (chk[b]) continue;
            chk[b] = 1;
            ret += C[b];
        } 
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    mt19937_64 seed((unsigned int) time(0));
    cin >> B >> L >> D;
    for (int i=0; i<B; i++){
        cin >> C[i];
    }
    X.resize(L);
    for (int i=0; i<L; i++){
        V.clear();
        int n, t, m;
        cin >> n >> t >> m;
        for (int j=0; j<n; j++){
            int t; cin >> t; V.push_back(t);
        }
        if (rng_int(seed) % 2){
            sort(V.begin(), V.end(), less_);
            reverse(V.begin(), V.end());
        }
        else{
            shuffle(V.begin(), V.end(), seed);
        }
        X[i] = Library(n, t, m, i, V);
    }
    sort(X.begin(), X.end(), lib_less); // greedy solution
    
    ll cur_score = score(X);
    uniform_int_distribution<int> uidx(0, L-1);
    
    for (int i=0; i<300000; i++){
        // Randomly search 300,000 near states and update if better
        Y.clear();
        for (Library x : X) Y.push_back(x);
        if (rng_int(seed) % 5){
            for (int j=0; j<40; j++){
                int x = uidx(seed), y = uidx(seed);
                while (x == y) y = uidx(seed);
                swap(Y[x], Y[y]);
            }         
        }
        else{
            int k = uidx(seed);
            uniform_int_distribution<int> uidxx(0, Y[k].n-1);
            for (int j=0; j<13; j++){
                int x = uidxx(seed);
                int y = uidxx(seed);
                swap(Y[k].ID[x],Y[k].ID[y]);
            }
        }
        ll tmp_score = score(Y);
            if (tmp_score > cur_score){
            cur_score = tmp_score;
            for (int j=0; j<L; j++){
                X[j] = Y[j];
            }
        }
    }
    cout << L << '\n';
    for (int i=0; i<L; i++){
        cout << X[i].i << ' ' << X[i].n << '\n';
        for (auto &j : X[i].ID) cout << j << ' ';
        cout << '\n';
    }
    cout << score(X) << endl; // delete last line when submit
}
