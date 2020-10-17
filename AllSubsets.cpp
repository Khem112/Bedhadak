#include<bits/stdc++.h>
using namespace std;

    vector<vector<string> > all_subsets(vector<string> a){
        int n = pow(2,a.size());
        vector<string> v;
        vector<vector<string>> khem;
        for(int i=1;i<n-1;i++){
            v.clear();
            int j=1;
            int cnt=0;
            while(j<n){
                if(i&j){
                    v.push_back(a[cnt]);
                }
                cnt++;
                j *= 2;
            }
            if(v.size()){
                khem.push_back(v);
            }
        }
        return khem;
    }

int main(){
    vector<string> v;
    v.push_back("0");
    v.push_back("1");
    v.push_back("2");
    v.push_back("3");
    vector<vector<string> > ans = all_subsets(v);
    for(int i=0;i<ans.size();i++){
        for(int j=0;j<ans[i].size();j++){
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }
}
