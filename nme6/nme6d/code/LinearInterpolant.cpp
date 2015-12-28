#include<vector>
#include<iostream>
#include<assert.h>

class LinearInterpolant {

	using pair = std::pair<double, double>;
	using ip_data = std::vector<pair>;

public:
	LinearInterpolant(ip_data && data) {

		interpolation_data = data;
		assert(interpolation_data.size() > 1 && "Must specify at least two nodes");

		auto Order = [] (const pair & p, const pair & q) -> bool {
			return p.first < q.first;
		};

		std::sort(interpolation_data.begin(), interpolation_data.end(), Order);
	}

	double operator() (double x) {

		Compare = [] (const pair & p, double x) -> bool { return p.first < x; };

		auto it = std::lower_bound( interpolation_data.begin(), interpolation_data.end(), x, Compare );
	}

private:
	ip_data interpolation_data;
};

int main() {
	LinearInterpolant I = LinearInterpolant({{1, 2}, {2, 3}, {4, 4}, {-1, -1}});
}