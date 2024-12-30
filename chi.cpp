#include<iostream>
using namespace std;

void chi_square(int o[][100], int row, int col){
        int e[100][100];
        int row_sum[100];
        int col_sum[100];
        int grand_total = 0;

// NOTE: This calculates row sum
        int row_s;
        for(int i=0 ; i<row ; i++){
                row_s = 0;
                for(int j=0 ; j<col ; j++){
                        row_s = row_s + o[i][j];
                }
                row_sum[i]= row_s;
        }

// NOTE: This calculates col sum
        int col_s;
        for(int j=0 ; j<col ; j++){
                col_s = 0;
                for(int i=0 ; i<row ; i++){
                        col_s = col_s + o[i][j];
                }
                col_sum[j]= col_s;
        }

/*      for(int i=0 ; i<row ; i++){
                cout<<row_sum[i]<<" ";
        }cout<<endl;

        for(int i=0 ; i<row ; i++){
                cout<<col_sum[i]<<" ";
        }cout<<endl;
*/

        for(int i=0 ; i<row ; i++){
                row_s = row_s + row_sum[i];
        }

        for(int i=0 ; i<col ; i++){
                col_s = col_s + col_sum[i];
        }

        grand_total = row_s + col_s;

        for(int i=0 ; i<row ; i++){
                for(int j=0 ; j<col ; j++){
                        e[i][j] = (row_sum[i] * col_sum[j])/grand_total;
                }
        }

        // Summation
        double summation = 0;
        for(int i=0; i<row ; i++){
                for(int j=0 ; j<col ; j++){
                        summation = summation +( (o[i][j] - e[i][j]) * (o[i][j] - e[i][j]) / (e[i][j]) );
                }
        }

        cout<<"Chi square is : "<<summation<<endl;

}

int main(){
        int o[100][100];

        int row,col;
        int ele;
        cout<<"Enter the total number of rows and columns"<<endl;
        cin>>row;
        cin>>col;

        cout<<"Enter your elements for each cell"<<endl;
        for(int i=0; i<row ; i++){
                for(int j=0 ; j<col ; j++){
                        cout<<"Cell : ("<<i<<","<<j<<")"<<" ";
                        cin>>ele;
                        o[i][j] = ele;
                }
        }

        cout<<"Your observed frequencies are: "<<endl;
        for(int i=0; i<row ; i++){
                for(int j=0 ; j<col ; j++){
                        cout<<o[i][j]<<" ";
                }cout<<endl;
        }cout<<endl;

        chi_square(o,row,col);

        return 0;
}
