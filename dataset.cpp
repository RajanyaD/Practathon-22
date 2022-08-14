#include <iostream>
#include <fstream>
#include<random>
#include<bits/stdc++.h> 
using namespace std;

default_random_engine de(time(0)); //seed
normal_distribution<double> nd(0, 100); //mean followed by stdiv
 
int main()
{
    fstream file;
    file.open("vector_file.txt",ios_base::out);

    for(int i=0;i<10000000;i++){
    vector<int> v;
    for(int j=0;j<100;j++){
        v.push_back(nd(de));
    }
 
    for(int i=0;i<v.size();i++)
    {
        file<<v[i]<<" ";
    }
    file<<endl;
    }
    file.close();
    return 0;
}