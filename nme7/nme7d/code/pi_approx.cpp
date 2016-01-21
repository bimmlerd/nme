#include<iostream>
#include<assert.h>
#include<vector>
#include<cmath>

double pi_approx(int k);

int main() {
	for (int i = 1; i < 8; i++) {
		std::cout << i << ": " << pi_approx(i) << std::endl;
	}

	return 0;
}

double pi_approx(int k) {
	assert(k > 0 && k <= 7 && "k is not in the valid range");

	std::vector<double> node = {1.0/2, 1.0/3, 1.0/4, 1.0/5, 1.0/6, 1.0/8, 1.0/10};
	std::vector<double> data = {2,
		(3.0 / 2) * sqrt(3),
		2 * sqrt(2),
		(5.0 / 4) * sqrt(10 - (2 * sqrt(5))),
		3,
		4 * sqrt(2 - sqrt(2)),
		(5.0 / 2) * (sqrt(5) - 1)};

	for (int i = 0; i < k; ++i) {
		for (int j = i - 1; j >= 0; --j) {
			data[j] = data[j + 1] + (data[j + 1] - data[j]) * (0 - node[i]) / (node[i] - node[j]);
		}
	}
	return data[0];
}