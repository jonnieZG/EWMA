#include "Ewma.h"

Ewma::Ewma(double alpha) {
	this->alpha = alpha;
}

Ewma::Ewma(double alpha, double initialOutput) {
	this->alpha = alpha;
	this->output = initialOutput;
	this->hasInitial = true;
}

void Ewma::reset() {
	this->hasInitial = false;
}

double Ewma::filter(double input) {
	if (hasInitial) {
		output = alpha * (input - output) + output;
	} else {
		output = input;
		hasInitial = true;
	}
	return output;
}
