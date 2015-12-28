#include<vector>
#include<iostream>
#include<assert.h>

class LinearInterpolant {

	using ip_pair = std::pair<double, double>;
	using ip_data = std::vector<ip_pair>;

public:
	LinearInterpolant(ip_data && data) {

		data_ = data;
		assert(data_.size() > 1 && "Must specify at least two nodes");

		auto Order = [] (const ip_pair & p, const ip_pair & q) -> bool {
			return p.first < q.first;
		};

		std::sort(data_.begin(), data_.end(), Order);
	}

	double operator() (double x) {

		auto Compare = [] (const ip_pair & p, double x) -> bool { return p.first < x; };

		auto it = std::lower_bound(data_.begin(), data_.end(), x, Compare);

		if (it == data_.begin() && it->first == x) { return it->second; }
		if (it == data_.begin() || it == data_.end()) { return 0; }

		double dist_ratio = (x - (it-1)->first) / (it->first - (it-1)->first);
		return (it-1)->second * (1 - dist_ratio) + it->second * dist_ratio;
	}

private:
	ip_data data_;
};

int main() {
	LinearInterpolant I = LinearInterpolant({{1, 2}, {2, 3}, {4, 4}, {-1, -1}});

	std::cout << I(-2) << " " << I(-1) << " " << I(1) << " " << I(2) << " " << I(4) << " " << I(5) << std::endl;
    std::cout << I(0.5) << " " << I(1) << " " << I(1.5) << " " << I(2.1) << " " << I(3) << " " << I(3.1) << " " << I(4) << std::endl;
}