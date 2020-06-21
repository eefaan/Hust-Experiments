/* problem: optimal binary search tree */

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cfloat>
#include <climits>

using namespace std;

int check_sum(int n, double p[], double q[]){
    double sum=0;
    //calculate sum
    for(int i=0;i<=n;i++){
        if(i==0){
            sum+=q[i];
        }
        else{
            sum+=q[i];
            sum+=p[i];
        }
        // cout<<sum<<'\n';
    }
    //check the result
    if(abs(sum-1)<0.0000001)return 1;
    return 0;
}

void CONSTRUCT_OPTIMAL_BST(int root[][10000], int i, int j, int last){
    if(i>j){
        if(j<last)
            cout<<'d'<<j<<" is the left child of k"<<last<<'\n';
        else
            cout<<'d'<<j<<" is the right child of k"<<last<<'\n';
        // cout<<i<<' '<<j<<' '<<last<<'\n';
        return;
    }
    if(last==0)
        cout<<'k'<<root[i][j]<<" is the root.\n";
    else if(j<last)
        cout<<'k'<<root[i][j]<<" is the left child of k"<<last<<'\n';
    else
        cout<<'k'<<root[i][j]<<" is the right child of k"<<last<<'\n';

    CONSTRUCT_OPTIMAL_BST(root,i,root[i][j]-1,root[i][j]);
    CONSTRUCT_OPTIMAL_BST(root,root[i][j]+1,j,root[i][j]);
}

int main(void){
    while(1){
        int n;

        cout<<"number of key:";
        cin>>n;

        //input
        double p[n+1],q[n+1];
        //result
        double e[n+1][n],w[n+1][n];
        int root[n+1][10000];

        cout<<"p("<<n<<"): ";
        for(int i=1;i<=n;i++){
            cin>>p[i];
        }
        cout<<"q("<<n+1<<"): ";
        for(int i=0;i<=n;i++){
            cin>>q[i];
        }

        //p+q=1?
        if(check_sum(n,p,q)==0){
            cout<<"check your input plz.\n";
        }

        else{
            //initial
            for(int i=1;i<=n+1;i++){
                e[i][i-1]=q[i-1];
                w[i][i-1]=q[i-1];
            }
            //main
            for(int l=1;l<=n;l++){
                for(int i=1;i<=n-l+1;i++){
                    int j=i+l-1;
                    e[i][j]=DBL_MAX;
                    w[i][j]=w[i][j-1]+p[j]+q[j];
                    for(int r=i;r<=j;r++){
                        double t=e[i][r-1]+e[r+1][j]+w[i][j];
                        if(t<e[i][j]){
                            e[i][j]=t;
                            root[i][j]=r;
                        }
                    }
                }
            }

            // for(int i=1;i<=n;i++){
            //     for(int j=i;j<=n;j++){
            //         cout<<root[i][j]<<' ';
            //     }
            //     cout<<'\n';
            // }

            CONSTRUCT_OPTIMAL_BST(root,1,n,0);
        }
        cout<<endl;
    }
    return 0;
}
