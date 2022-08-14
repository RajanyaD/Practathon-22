#include<bits/stdc++.h>
using namespace std;

default_random_engine de(time(0)); //seed
normal_distribution<double> nd(0, 100); //mean followed by stdiv

int stringtoint(string x){
    stringstream ss;
    ss<<x;
    int y;
    ss>>y;
    return y;
}

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
    
    vector<vector<int>>vv;
    fstream file;
    string word, t, q, filename;
    filename = "vector_file.txt";
    file.open(filename.c_str());
    int count=0;
    vector<int>v;
    int i=0;
    Node *node=new Node();
    Node *p=node;
    vector<double>time;

    while(file>>word){
        if(count<100)
            v.push_back(stringtoint(word));
        if(count==99){
            count=0;
            if(!i){
                node->a=v;
                node->c=0;
            }
            else{
                Node *temp=new Node();
                p=node;
                temp->a=v;
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
            vv.push_back(v);
            v.clear();
            i++;
        }
        else
            count++;
        cout<<word<<" "<<i<<endl;
    }

    cout<<"Done"<<endl;

    for(int i=1;i<=100;i++)
    {
        priority_queue<Pair>pq;

        vector<int>qq;
        for(int i=0;i<100;i++)
            qq.push_back(nd(de));

        clock_t start=clock();
        searchMin(node,qq,pq,0);
        clock_t end=clock();
        time.push_back((double)(end-start)/CLOCKS_PER_SEC);


        vector<vector<int>>f;
        while(!pq.empty()){
            f.push_back(pq.top().v);
            pq.pop();
        }
        
        for(int i=0;i<f.size();i++)
        {
            for(auto j:f[i])
                cout<<j<<" ";
            cout<<endl;
        }
    }
    sort(time.begin(),time.end());
    cout<<(time[time.size()/2]+time[time.size()/2+1])/2<<endl;

    return 0;
}