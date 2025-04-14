#include <map>
#include <cmath>
#include <string>
#include <tuple>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Web {

public:



	/* - CONSTS - */
	const int MAXNUMOFCLMNS = 5;
	int MAXNUMOFROWS = 5;



	/* - PUBLIC VARS - */
	bool isThereWeightValues = false;
	int numberOfColumns;
	int(&numberOfNeuronsInColumns)[5];

	double learningRate;
	int numOfEpochs;

	map <tuple<int, int, int>, double> w;
	vector <vector<double>> neurons;

	vector <double> expectedAnswers;



	/* - CONSTRUCTOR - */

	Web(int clmn, int(&neurons)[5]) : numberOfColumns(clmn), numberOfNeuronsInColumns(neurons) {
		srand(time(NULL));
	}
	


	/* - PUBLIC FUNCS - */
	void startTraining() {
		double generalError = neurons[numberOfColumns - 1][0] - expectedAnswers[0];
		double generalWeightsDelta = generalError * neurons[numberOfColumns - 1][0] * (1 - neurons[numberOfColumns - 1][0]);

		for (int i = 0; i < numberOfNeuronsInColumns[numberOfColumns - 2]; i++) {
			w[make_tuple(i, 0, numberOfColumns - 2)] -= generalWeightsDelta * learningRate * neurons[numberOfColumns - 2][i];
			training(w[make_tuple(i, 0, numberOfColumns - 2)] * generalWeightsDelta, numberOfColumns - 2, i);
		}
	}


	void training(double error = 0, int clmn = 0, int row = 0) {
		double weightsDelta = error * neurons[clmn][row] * (1 - neurons[clmn][row]);

		for (int i = 0; i < numberOfNeuronsInColumns[clmn - 1]; i++) {
			w[make_tuple(i, row, clmn - 1)] -= weightsDelta * learningRate * neurons[clmn - 1][i];
			if (clmn >= 2)
				training(w[make_tuple(i, row, clmn - 1)] * weightsDelta, clmn - 1, i);
		}

	}



	void startWeb() {
		if (!isThereWeightValues) fillRandomWeights();
		calculateOutput();
	}

	void inputNeurons(double* input) {
		for (int i = 0; i < numberOfNeuronsInColumns[0]; i++, input++)
			neurons[0][i] = *input;
	}

	vector<double> getWebOutput() {
		return neurons[numberOfColumns - 1];
	}
	double getWeight(int a, int b, int c) {
		return w[make_tuple(a, b, c)];
	}

	void initVecrors() {
		for (int i = 0; i < numberOfColumns; i++) {
			expectedAnswers.push_back(0);
			neurons.push_back(vector<double>{});
			for (int j = 0; j < numberOfNeuronsInColumns[i]; j++) {
				neurons[i].push_back(0);
			}
		}
	}



private:



	/* - ORO Vars - */



	/* - ORO Funcs - */
	int randomNum(int from, int to) {
		return rand() % (to - from) + from;
	}
	void fillRandomWeights() {
		for (int i = 0; i < numberOfColumns - 1; i++)
			for (int j = 0; j < numberOfNeuronsInColumns[i]; j++)
				for (int k = 0; k < numberOfNeuronsInColumns[i + 1]; k++)
					w[make_tuple(j, k, i)] = randomNum(1, 99) / 100.0;
		isThereWeightValues = true;
	}



	/* - FUNCS - */
	
	double sigmoid(double x) {
		return 1 / (1 + exp(-x));//*/ 
	}

	void calculateOutput() {

		for (int i = 1; i < numberOfColumns; i++) {
			for (int k = 0; k < numberOfNeuronsInColumns[i]; k++)
				neurons[i][k] = getSum(i, k);
		}
	}

	double getSum(int x, int y) {
		double sum = 0.0;

		for (int i = 0; i < numberOfNeuronsInColumns[x - 1]; i++) 
			sum += w[make_tuple(i, y, x-1)] * neurons[x-1][i];

		return sigmoid(sum);
		/*
		^
		|
		y
		x ->
		*/
	}



};

/*

void maxNumOfRowsCalculate() {
		for (int i = 0; i < NumberOfColumns; i++) if (NumberOfNeuronsInColumns[i] > MAXNUMOFROWS) MAXNUMOFROWS = NumberOfNeuronsInColumns[i];
	}


*/

/*
weights:

0 -- > in
1 -- > out
2 -- > clmn

in -- > out


*/