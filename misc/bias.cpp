#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>       /* pow */

using namespace std;


int main(){

    srand((unsigned)time(NULL));
    
    const int runs = 100;
    
    const int minH = 25;
    const int maxH = 75;
    const int diff = 5;
    
    float total = 0.0f;
    int totalH = 0;
    for(int i=0; i<runs; i++){
        int randInt = rand() % 100000; // 0 to 99999
        float randf = randInt / 100000.0; // 0 to .99999
        
        float bias = pow(randf, 1.5);
        float val = 0.f;
        
        int selector = rand() % 2; // 0 or 1
        if(selector == 0)
            val = 1 - bias;
        else
            val = 1 + bias;
        val = val / 2;
        
        total = total + val;
        
        // do actual height calculations
        const int range = maxH - minH;
        int numHeights = range/diff + 1;
        
        int selIndex = (int)(val * numHeights);
        int height = minH + diff * selIndex;
        totalH = totalH + height;
    }
    
    float average = total / runs;
    float averageH = totalH / (float)runs;
    float idealH = (minH + maxH) / 2.0;
    cout << "RUNS: " << runs << endl;
    cout << "   Avverage Bias:  " << average << endl;
    cout << "   Average Height: " << averageH << endl;
    cout << "   Ideal Height:   " << idealH << endl;
    
    return 0;
}
