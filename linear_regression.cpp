#include <iostream>
#include <math.h>
#include <numeric>

using namespace std;

float sigmoid(float[] x){
	float[sizeof(x)/sizeof(float)] sig;
	for (int i = 0; i < sizeof(x)/sizeof(float); ++i)
	{
		sig[i] = 1/(1+exp(-x[i]));
	}
	return sig;
}

float[] logistic_predictions(float weights[], float inputs[][] inputs){
    # Outputs probability of a label being true according to logistic model.
    return sigmoid(inner_product(begin(inputs), end(inputs), std::begin(weights), 0.0));
}

float training_loss(float weights[], float inputs[][] inputs){
    # Training loss is the negative log-likelihood of the training labels.
    preds = logistic_predictions(weights, inputs);
    float label_probabilities[sizeof(preds)/sizeof(float)];
    for (int i = 0; i < sizeof(preds)/sizeof(float); ++i)
    {
    	label_probabilities[i] = preds[i]*targets[i] + (1 - preds[i]) * (1 - targets[i]);
    }
    float sum = 0.0;

    for (int i = 0; i < sizeof(preds)/sizeof(float); ++i)
    {
    	sum += log(label_probabilities[i]);
    }
    return -sum;
}

int main() {
    float inputs[4][3] = {  
		{0.52, 1.12,  0.77},
        {0.88, -1.08, 0.15},
        {0.52, 0.06, -1.30},
        {0.74, -2.49, 1.39}   /*  initializers for row indexed by 2 */
	};

	bool targets[4] = {1, 1, 0, 1};

	//training_gradient_fun = take gradient

	float weights[3] = {0.0, 0.0, 0.0};
    return 0;
}
