#include <iostream>
#include <vector>
#include <cstdlib>
 
using namespace std;
 
int getRand(int a, int b){
   return a + random() % b;
}
 
int main(){
   srandom(time(NULL));
   int t = getRand(1, 1000);
   cout << t << endl << endl;
   for(int k=0 ; k<t ; k++){
      int n = getRand(1, 20);
      cout << n << endl;
      for(int i=0 ; i<n ; i++)
         cout << (char)('A'+i) << endl;
      int b = getRand(1, 1000);
      for(int i=0 ; i<b ; i++){
         vector<bool> v(1001, false);
         for(int j=0 ; j<n ; j++){
            int x = getRand(1, n);
            while(v[x])
               x = getRand(1, n);
            v[x] = true;
            cout << x << " ";
         }
         cout << endl;
      }
      cout << endl;
   }
   return 0;
}