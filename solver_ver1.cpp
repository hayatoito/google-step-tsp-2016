//#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include <bitset>
#include <cmath>
#include <stack>
#include <iomanip>
#include <map>
#include <math.h>
#include <list>
#include <deque>
#include <queue>
using namespace std;
typedef long long ll;

void ft_split(const string &s, char c, int num, vector<ll> &x, vector<ll> &y) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    ll ret;
    int cnt = 0;

    while (getline(ss, item, c)) {
    if (!item.empty()) {
            //cout<<item<<endl;
            int i=0;
            ret = 0;
            while (item[i]!='.')
            {
                ret = ret*10 + (item[i]-'0');
                i++;
            }
            //ここから小数点以下６桁を追加していきます、、、
            int count=0;
            i++;
            while (count<6)
            {
                ret = ret*10 + (item[i]-'0');
                i++;
                count++;
            }
            //cout<<ret<<endl;
            if (cnt == 0) x[num] = ret;
            else y[num] = ret;
            cnt++;
        }
    }
}

//アルゴリズムの本体
vector<int> solve(vector<ll> x, vector<ll> y, int n)
{
    vector<int> ret(n);
    vector< vector<ll> > dis(n, vector<ll>(n));
        
    //N=10^3だしまずはO(N^2)で愚直に書いてみよ、、、、
    for (int i=0; i<n; i++)
    {
        ll distance = 0;
        for (int j=0; j<n; j++)
        {
            distance = 0;
            if (j != i)
            {
                distance += (x[i]-x[j])*(x[i]-x[j]);
                distance += (y[i]-y[j])*(y[i]-y[j]);//ルートとっても大小変わらないので取る必要はない
            }
            dis[i][j]=distance;
        }
    }

    ll min;
    int min_num;
    int count=0;
    ret[count]=0;//0番からスタート
    int now=0;
    vector<bool> seen(n,false);
    seen[0]=true;
    while (count < n)
    {
        min = 9000000000000000000;
        for (int i=0;i<n;i++)
        {
            //min = 9000000000000000000;
            if (i!=now && seen[i]==false)
            {
                if (min > dis[now][i]) 
                {
                    min = dis[now][i];
                    min_num = i;
                }
            } 
        }

        count++;
        ret[count]=min_num;//count番目に訪れるノード
        seen[min_num]=true;
        now = min_num;
    }

    return (ret);
}

int main(int argc, char *argv[])
{  
    vector<ll> x(3000);
    vector<ll> y(3000);

    if (argc == 1 || argc == 2)
    {
        cout<<"Error : No filename."<<endl;
        return (0);
    }

    string input = argv[1];
    string output = argv[2];
    ifstream ifs(input, ios::in);

    //ファイルを開くのに失敗したときの処理
    if (!ifs) {
        cerr << "Error: file not opened." << endl;
        return (0);
    }

    string line;
    int count=0;
    while (getline(ifs, line))
    {
        if (count != 0)
        {
            //コンマでsplitしてintに格納する、doubleで格納する方法わからず
            //doubleだと誤差も怖いしintの小数点6桁まででやっとく
            ft_split(line, ',', count-1, x, y);
            //cout<<x[count-1]<<" "<<y[count-1]<<endl;
            count++;
        }
        count++;
    }

    int n = (count-1)/2;
    vector<int> res;
    res = solve(x,y,n);

    cout<<"index"<<endl;
    for (int i=0;i<n;i++)
        cout<<res[i]<<endl;

    //ファイル書き込み
    ofstream outputfile(output);
    outputfile<<"index"<<endl;
    for (int i=0;i<n;i++)
        outputfile<<res[i]<<endl;
    outputfile.close();

    // ファイルを閉じる
    ifs.close();
}
