#include <iostream>
#include <fstream>
#include "NeuralWebClass.cpp"
#include <string>
#include <tuple>
#include <vector>

//#include <map>
//#include <cmath>

using namespace std;

int randomNum(int from, int to);

int main() {
    srand(time(NULL));

    // Input test
    ifstream inputFile("input.txt");
    string str;
    getline(inputFile, str);
    //cout << str << endl;
    
    // Input Count of neurons
    int x, y[5];

    inputFile >> x;
    for (int i = 0; i < x; i++) inputFile >> y[i];
     
    Web web1(x, y);
    web1.initVecrors();

    //cout << web1.NumberOfColumns << " - num of columns\n";
    //for (int i = 0; i < x; i++) cout << web1.NumberOfNeuronsInColumns[i] << " in the " << i << "place\n";

    // Input Weights
    /*for (int i = 0; i < web1.numberOfColumns - 1; i++)
        for (int j = 0; j < web1.numberOfNeuronsInColumns[i]; j++)
            for (int k = 0; k < web1.numberOfNeuronsInColumns[i + 1]; k++)
                inputFile >> web1.w[make_tuple(j, k, i)];
    web1.isThereWeightValues = true;//*/

    inputFile >> web1.expectedAnswers[0];
    inputFile >> web1.numOfEpochs;
    inputFile >> web1.learningRate;

    double inputNeurons[8][3] = {
        {0, 0, 0},
        {0, 0, 1},
        {0, 1, 0},
        {0, 1, 1},
        {1, 0, 0},
        {1, 0, 1},
        {1, 1, 0},
        {1, 1, 1}
    };
    double expectedOutputs[8] = { 0, 1, 0, 1, 1, 1, 0, 0 };

    web1.startWeb();
    do {
        int randNum = randomNum(0, 8);
        web1.inputNeurons(inputNeurons[randNum]);
        web1.expectedAnswers[0] = expectedOutputs[randNum];
        web1.startWeb();
        web1.startTraining();
        web1.numOfEpochs--;
        if (web1.numOfEpochs % 100 == 0) {
            cout << endl << "Result ";
            double sum = 0;
            for (int i = 0; i < 8; i++) {
                web1.inputNeurons(inputNeurons[i]);
                web1.expectedAnswers[0] = expectedOutputs[i];
                web1.startWeb();
                sum += abs(web1.expectedAnswers[0] - web1.getWebOutput()[0]);
            }
            sum /= 8;
            cout << "error = " << sum;
        }
        //cout << web1.getWebOutput()[0] << " vs " << web1.expectedAnswers[0] << endl;
    } while (web1.numOfEpochs >= 0);

    cout << endl << "Trained Network:\n";
    double sum = 0;
    for (int i = 0; i < 8; i++) {
        web1.inputNeurons(inputNeurons[i]);
        web1.expectedAnswers[0] = expectedOutputs[i];
        web1.startWeb();
        cout << web1.getWebOutput()[0] << " vs " << web1.expectedAnswers[0] << endl;
        sum += abs(web1.expectedAnswers[0] - web1.getWebOutput()[0]);
    }
    sum /= 8;
    cout << "\nTotal error = " << sum;
    //system("pause");
    return 0;
}

int randomNum(int from, int to) {
    return rand() % (to - from) + from;
}



/*
weights:

0 -- > in
1 -- > out
2 -- > clmn

in -- > out

*/

/*
for (int i = 0; i < web1.numberOfColumns - 1; i++) {
    for (int j = 0; j < web1.numberOfNeuronsInColumns[i]; j++) {
        for (int k = 0; k < web1.numberOfNeuronsInColumns[i + 1]; k++)
            cout << web1.w[make_tuple(j, k, i)] << " ";
        cout << " ";
}
cout << endl;
}//*/


/*
0 0 0  0
0 0 1  1
0 1 0  0
0 1 1  1
1 0 0  1
1 0 1  1
1 1 0  0
1 1 1  0
*/