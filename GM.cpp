#include<iostream>
#include<cmath>
using namespace std;

void hm(int arr[], int size){
        double hm;

        // Calculating 1/xi summation
        double sum = 0;
        for(int i=0 ; i<size ; i++){
                sum = sum + (1.0/arr[i]);
        }

        hm = size/sum;

        cout<<"HM is : "<<hm<<endl;
}

void gm(int arr[], int size){
        double gm;

        // Calculating summation logx
        double logx = 0;
        for(int i=0 ; i<size ; i++){
                logx = logx + log10(arr[i]);
        }

        gm = pow(10, (logx/size));

        cout<<"GM is : "<<gm<<endl;
}

int main(){
        int arr[100];

        int size;
        cout<<"Enter the size of the array"<<endl;
        cin>>size;

        cout<<"Enter the elements"<<endl;
        for(int i=0 ; i<size ; i++){
                cin>>arr[i];
        }
        cout<<"Your input is:"<<endl;
        for(int i=0; i<size ; i++){
                cout<<arr[i]<<" ";
        }cout<<endl;

        gm(arr,size);
        hm(arr,size);

        return 0;
}
