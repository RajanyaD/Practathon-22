#include<bits/stdc++.h>
#include<random>
using namespace std;
#include<time.h>

default_random_engine de(time(0)); //seed
normal_distribution<double> nd(0, 100); //mean followed by stdiv

struct Node{
    vector<int>a;
    int c=0;
    Node *left=NULL;
    Node *right=NULL;
};

class Pair{
    public:
        int dist=0;
        vector<int>v;
    Pair(int dist,vector<int>v):dist(dist),v(v){}
};

bool operator<(const Pair &p1,const Pair &p2){
    return p1.dist<p2.dist;
}

Node * createTree(vector<vector<int>>&v){
    Node *node=new Node();
    for(int i=0;i<100;i++)
        (node->a).push_back(0);
    for(int i=0;i<100;i++)
        node->a[i]=v[0][i];
    node->c=0;
    for(int i=1;i<v.size();i++){
        Node *p=node;
        Node *temp=new Node();
        for(int i=0;i<100;i++)
            (temp->a).push_back(0);
        for(int j=0;j<100;j++)
            temp->a[j]=v[i][j];
        // temp->c=i%2;
        Node *q=p;
        while(p){
            if(temp->a[p->c]<p->a[p->c]){
                q=p;
                p=p->left;
            }
            else{
                q=p;
                p=p->right;
            }
        }
        if(temp->a[q->c]<q->a[q->c])
            q->left=temp;
        else
            q->right=temp;
        temp->c=(q->c+1)%100;
    }
    return node;
}

void searchMin(Node *node,vector<int>&q,priority_queue<Pair>&pq,int c){
    if(!node)
        return;
    int dist=0;
    for(int i=0;i<q.size();i++)
        dist+=(q[i]-node->a[i])*(q[i]-node->a[i]);
    if(pq.size()<10){
        pq.push(Pair(dist,node->a));
    }
    else if(pq.top().dist>dist){
        pq.pop();
        pq.push(Pair(dist,node->a));
    }
    
    if(q[c]<node->a[c]){
        searchMin(node->left,q,pq,(c+1)%100);
        if((node->a[c]-q[c])*(node->a[c]-q[c])<pq.top().dist)
            searchMin(node->right,q,pq,(c+1)%100);
    }
    
    else{
        searchMin(node->right,q,pq,(c+1)%100);
        if((q[c]-node->a[c])*(node->a[c])<pq.top().dist)
            searchMin(node->left,q,pq,(c+1)%100);        
    }
}

int main(){
    priority_queue<Pair>pq;
    
    vector<vector<int>>v;
    //v={{2,3},{1,5},{4,2},{4,5},{3,3},{4,4},{0,7},{0,0},{-1,7},{1,7},{-1,1}};
    for(int i=0;i<1000000;i++){
        vector<int>t;
        for(int j=0;j<100;j++){
            t.push_back(nd(de));
        }
        v.push_back(t);
    }
    vector<double>timeit;
    //vector<int>q={0,0};
    for(int x=1;x<=1;x++)
    {
        vector<int>q;
        for(int i=0;i<100;i++)
            q.push_back(nd(de));
        
        Node *node = createTree(v);
        clock_t start=clock();
        searchMin(node,q,pq,0);
        clock_t end=clock();
        timeit.push_back((double)(end-start)/CLOCKS_PER_SEC);
        cout<<"Wall clock time "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
        
        vector<vector<int>>f;
        while(!pq.empty()){
            f.push_back(pq.top().v);
            pq.pop();
        }
        
        for(int i=0;i<f.size();i++){
            for(auto j:f[i])
            cout<<j<<" ";
            cout<<endl;
        }
        
        cout<<endl;   
        cout<<"Brute force result..."<<endl;
        vector<vector<int>>brute;
        map<int,vector<int>>mp;    
        for(int i=0;i<v.size();i++){
            int dist=0;
            for(int j=0;j<100;j++)
                dist+=(v[i][j]-q[j])*(v[i][j]-q[j]);
            mp[dist]=v[i];
        }
        int count=0;
        for(auto it=mp.begin();it!=mp.end();it++){
            brute.push_back(it->second);
            count++;
            if(count==10)
                break;
        }
        reverse(brute.begin(),brute.end());
        cout<<"Result and brute force IsEqual? "<<(brute==f)<<endl;
    }

    sort(timeit.begin(),timeit.end());
    cout<<"Median time"<<(timeit[timeit.size()/2]+timeit[timeit.size()/2+1])/2<<endl;
        
    return 0;
}