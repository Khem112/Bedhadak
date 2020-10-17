#include<bits/stdc++.h>
#include<string>
using namespace std;

map<vector<string>,int> frequency_of_set;
map<string,vector<string>> items_in_trans;

bool valid_pair(vector<string> a,vector<string> b){
    if(a.size()!=b.size())  return false;
    bool flag =true;
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    int i=0;
    for(i=0;i<a.size()-1;i++){
        if(a[i]!=b[i]){
            return false;
        }
    }
    return (a[i]!=b[i]);
}

vector<string> union_vec(vector<string> a,vector<string> b){
    map<string,int> mp ;
    vector<string> v;
    for(int i=0;i<a.size();i++){
        mp[a[i]]++;
    }
    for(int i=0;i<b.size();i++){
        mp[b[i]]++;
    }
    for(auto it=mp.begin();it!=mp.end();it++){
        v.push_back(it->first);
    }
    return v;
}

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

int find_frequency_of_set(vector<string> setA)
{
    int cnt=0;
    for(auto it=items_in_trans.begin();it!=items_in_trans.end();it++){
        vector<string> T = it->second;
        map<string,int> temp;
        for(int i=0;i<T.size();i++){
            temp[T[i]]++;
        }
        int flag = 1;
        for(int i=0;i<setA.size();i++){
            if(temp[setA[i]]==0){
                flag = 0;
            }
        }
        if(flag){
            cnt++;
        }
    }
    return cnt;
}

int main(){
    string str;
    ifstream in("trans.txt");
        int cur_trans_id = 0 ;
        while(in >> str){
            if(str[0]=='T' && str[1] <= '9' && str[1] >= '0')
            {
                cur_trans_id++;
            }
            else{
                items_in_trans[ "T" + to_string(cur_trans_id)].push_back(str);
            }
        }
    in.close();
    int threshold_support,threshold_confidence;
    cout << "Enter the threshold support value ";
    cin >> threshold_support;
    cout << "Enter the threshold confidence value ";
    cin >> threshold_confidence;
    map<string,int> items;
    cout << "Given transaction set is \n";
    for(int i=1;i<=cur_trans_id;i++){
        string cur_trans = "T"+to_string(i);
        if(items_in_trans[cur_trans].size()!=0){
            cout << cur_trans << " ";
            for(int j=0;j<items_in_trans[cur_trans].size();j++){
                cout << items_in_trans[cur_trans][j] << " ";
                ++items[items_in_trans[cur_trans][j]];
            }
            cout << "\n";
        }
    }
   
 
    vector<vector<string>> Ck,Lk,Ck_1,all_frequent_subsets;
    for(auto it=items.begin();it!=items.end();it++){
        vector<string> v;
        v.push_back(it->first);
        frequency_of_set[v] = it->second;
        Ck.push_back(v);
    }
   
    cout << "First scan \n" ;

    for(int i=0;i<Ck.size();i++){
        for(int j=0;j<Ck[i].size();j++){
            cout << Ck[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n\n";

    while(Ck.size()!=0){
        Ck_1 = Ck;
        Ck.clear();
        if(Ck_1.size()==1){
            Ck = Ck_1;
            break;
        }
        else{
            map<vector<string> , int > already_pushed;
            for(int i=0;i<Ck_1.size()-1;i++){
                for(int j=1;j<Ck_1.size();j++){
                    if(valid_pair(Ck_1[i],Ck_1[j])==true){
                        vector<string> union_i_j = union_vec(Ck_1[i],Ck_1[j]);
                        vector<vector<string>> subsets = all_subsets(union_i_j);
                        bool all_subsets_are_frequent = true;
                        for(int i=0;i<subsets.size();i++){
                            int support_of_set = (find_frequency_of_set(subsets[i])*100)/cur_trans_id;
                            if(support_of_set < threshold_support){
                                all_subsets_are_frequent = false;
                            }
                        }
                        if(all_subsets_are_frequent){
                            if(((find_frequency_of_set(union_i_j)*100)/cur_trans_id)>=threshold_support){
                                if(already_pushed[union_i_j]++==0)
                                    Ck.push_back(union_i_j);
                                    all_frequent_subsets.push_back(union_i_j);
                            }
                        }
                    }
                }
            }
            if(Ck.size()==0){
                Ck = Ck_1;
                break;
            }
            if(Ck.size() == 1)   break;
        }

    }

    /*
    //All frequent sets

    for(int i=0;i<all_frequent_subsets.size();i++){
        for(int j=0;j<all_frequent_subsets[i].size();j++){
            cout << all_frequent_subsets[i][j] << " ";
        }
        cout << "\n";
    }
    */

    for(int i=0;i<Ck.size();i++){
        for(int j=0;j<Ck[i].size();j++){
            cout << Ck[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
