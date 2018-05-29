from builtins import range
import autograd.numpy as np
from autograd import grad
import datetime

t1 = datetime.datetime.now()
def sigmoid(x):
    return 1/(1+np.exp(-x))

def logistic_predictions(weights, inputs):
    # Outputs probability of a label being true according to logistic model.
    return sigmoid(np.dot(inputs, weights))

def training_loss(weights):
    # Training loss is the negative log-likelihood of the training labels.
    preds = logistic_predictions(weights, inputs)
    label_probabilities = preds * targets + (1 - preds) * (1 - targets)
    return -np.sum(np.log(label_probabilities))

# Build a toy dataset.
inputs = np.array([[0.52, 1.12,  0.77],
                   [0.88, -1.08, 0.15],
                   [0.52, 0.06, -1.30],
                   [0.74, -2.49, 1.39]])
targets = np.array([1, 1, 0, 1])

# Build a function that returns gradients of training loss using autograd.
training_gradient_fun = grad(training_loss)

# Check the gradients numerically, just to be safe.
weights = np.array([0.0, 0.0, 0.0])

# Optimize weights using gradient descent.
print("Initial loss:", training_loss(weights))
for i in range(100):
    print(weights)
    print("Trained loss:", training_loss(weights))
    weights -= training_gradient_fun(weights) * 0.01
t2 = datetime.datetime.now()
print('time: '+str(t2-t1))