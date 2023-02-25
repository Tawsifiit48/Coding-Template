//nth permutation
void solve() {
    string s; cin >> s;
    int n; cin >> n;
    int freak[30] = {0};
    for(auto x : s) {
        freak[x - 'a']++;
    }
    int sz = s.size();
    ll total = fact[sz];
    for(int i = 0; i < 26; i++) {
        total /= (fact[freak[i]]);
    }
    cout << "Case " << ++cs << ": ";
    if(total < n) {
        cout << "Impossible" << N; return;
    } 
    for(int a = sz - 1; a >= 0; a--) {
        ll crt = 0;
        for(int i = 0; i < 26; i++) {
            if(!freak[i]) continue;
            freak[i]--;
            ll temp = fact[a];
            fe(j, 0, 25) {
                temp /= (fact[freak[j]]);
            }
            if(crt + temp >= n) {
                n -= crt;
                char ans = 'a';
                ans += i;
                cout << ans;
                break;
            } else {
                freak[i]++;
                crt += temp;
            }
        }
    }
    cout << N;
}
