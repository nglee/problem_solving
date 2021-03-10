#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

using LineData = map<int, vector<pair<int, int>>>;

pair<pair<int, int>, int> get_input(int n, LineData& v, LineData& h);
void print_lines(const LineData& l);
void solve(pair<pair<int, int>, int> start, int t, const LineData& v, const LineData& h);

int main()
{
	int n, t;
	LineData v; // vertical line
	LineData h; // horizontal line

	cin >> n >> t;

	try {
		const auto start = get_input(n, v, h);
		//{
		//	// debug
		//	cout << "vertical lines:\n";
		//	print_lines(v);
		//	cout << "horizontal lines:\n";
		//	print_lines(h);
		//	cout << "starting point: (" << start.first.first << ", " << start.first.second << ")\n";
		//	cout << "starting direction: " << start.second << "\n"; // 0 : UP 1 : RIGHT 2 : DOWN 3 : LEFT
		//}
		solve(start, t, v, h);
	}
	catch (exception & e)
	{
		cout << e.what();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void solve(const pair<pair<int, int>, int> start, int t, const LineData& v, const LineData& h)
{
	constexpr pair<int, int> no_segment{ 0, 0 };
	auto find_segment = [no_segment](const LineData& l, int key, int target)
	{
		pair<int, int> ret = no_segment;

		const auto& segments = l.find(key);
		if (segments == l.end())
			throw runtime_error("key " + std::to_string(key) + " does not exist in LineData");

		auto iter = find_if((*segments).second.begin(), (*segments).second.end(), [target](const pair<int, int>& s) { return s.first <= target && target <= s.second; });
		if (iter != (*segments).second.end())
			ret = *iter;

		return ret;
	};

	int cur_x = start.first.first;
	int cur_y = start.first.second;
	int direction = start.second; // 0 : UP 1 : RIGHT 2 : DOWN 3 : LEFT

	int covered_distance = 0;

	while (true)
	{
		//cout << "cur_pos: (" << std::to_string(cur_x) << ", " << std::to_string(cur_y) << ") direction: " << std::to_string(direction) << " covered_distance: " << std::to_string(covered_distance) << "\n";
		// get distance to the next cross-section or the endpoint
		int dist = 0;
		int next_direction;
		if (direction == 0) // UP
		{
			const auto cur_segment = find_segment(v, cur_x, cur_y);
			auto iter = h.upper_bound(cur_y);

			while (true)
			{
				if (iter == h.end())
				{
					dist = cur_segment.second - cur_y;
					next_direction = 2; // down
					break;
				}

				const int next_y = (*iter).first;
				if (cur_segment.second < next_y)
				{
					dist = cur_segment.second - cur_y;
					next_direction = 2; // down
					break;
				}
				else
				{
					const auto hori_segment = find_segment(h, next_y, cur_x);
					if (hori_segment == no_segment)
					{
						iter = h.upper_bound(next_y);
						continue;
					}
					else
					{
						dist = next_y - cur_y;
						next_direction = 3; // left
						break;
					}
				}
			}
		}
		else if (direction == 1) // RIGHT
		{
			const auto cur_segment = find_segment(h, cur_y, cur_x);
			auto iter = v.upper_bound(cur_x);

			while (true)
			{
				if (iter == v.end())
				{
					dist = cur_segment.second - cur_x;
					next_direction = 3; // left
					break;
				}

				const int next_x = (*iter).first;
				if (cur_segment.second < next_x)
				{
					dist = cur_segment.second - cur_x;
					next_direction = 3; // left
					break;
				}
				else
				{
					const auto verti_segment = find_segment(v, next_x, cur_y);
					if (verti_segment == no_segment)
					{
						iter = v.upper_bound(next_x);
						continue;
					}
					else
					{
						dist = next_x - cur_x;
						next_direction = 0; // up
						break;
					}
				}
			}
		}
		else if (direction == 2) // DOWN
		{
			const auto cur_segment = find_segment(v, cur_x, cur_y);
			auto iter = h.lower_bound(cur_y);

			while (true)
			{
				if (iter == h.begin())
				{
					dist = cur_y - cur_segment.first;
					next_direction = 0; // up
					break;
				}

				--iter;

				const int next_y = (*iter).first;
				if (cur_segment.first > next_y)
				{
					dist = cur_y - cur_segment.first;
					next_direction = 0; // up
					break;
				}
				else
				{
					const auto hori_segment = find_segment(h, next_y, cur_x);
					if (hori_segment == no_segment)
					{
						iter = h.lower_bound(next_y);
						continue;
					}
					else
					{
						dist = cur_y - next_y;
						next_direction = 1; // right
						break;
					}
				}
			}
		}
		else if (direction == 3) // LEFT
		{
			const auto cur_segment = find_segment(h, cur_y, cur_x);
			auto iter = v.lower_bound(cur_x);

			while (true)
			{
				if (iter == v.begin())
				{
					dist = cur_x - cur_segment.first;
					next_direction = 1; // right
					break;
				}

				--iter;

				const int next_x = (*iter).first;
				if (cur_segment.first > next_x)
				{
					dist = cur_x - cur_segment.first;
					next_direction = 1; // right
					break;
				}
				else
				{
					const auto verti_segment = find_segment(v, next_x, cur_y);
					if (verti_segment == no_segment)
					{
						iter = v.lower_bound(next_x);
						continue;
					}
					else
					{
						dist = cur_x - next_x;
						next_direction = 2; // down
						break;
					}
				}
			}
		}

		if (dist == 0)
			throw runtime_error("distance 0 error: cur_pos (" + std::to_string(cur_x) + ", " + std::to_string(cur_y) + "), direction " + std::to_string(direction));

		if (covered_distance + dist >= t)
		{
			int delta = t - covered_distance;

			if (direction == 0) // up
				cout << cur_x << " " << cur_y + delta;
			else if (direction == 1) // right
				cout << cur_x + delta << " " << cur_y;
			else if (direction == 2) // down
				cout << cur_x << " " << cur_y - delta;
			else if (direction == 3) // left
				cout << cur_x - delta << " " << cur_y;

			return;
		}

		covered_distance += dist;

		if (direction == 0) // up
			cur_y += dist;
		else if (direction == 1) // right
			cur_x += dist;
		else if (direction == 2) // down
			cur_y -= dist;
		else if (direction == 3) // left
			cur_x -= dist;

		direction = next_direction;

		// factor t
		if (cur_x == start.first.first && cur_y == start.first.second)
		{
			t %= covered_distance;
			covered_distance = 0;
		}
	}
}

void print_lines(const LineData& l)
{
	for (const auto& kv : l)
	{
		cout << kv.first << "";
		for (const auto& lines : kv.second)
		{
			cout << " ("
				<< lines.first
				<< ", "
				<< lines.second
				<< ")";
		}
		cout << "\n";
	}
}

pair<pair<int, int>, int> get_input(const int n, LineData& v, LineData& h)
{
	pair<int, int> init;
	int direction = 0;

	int _n = n;

	while (_n--)
	{
		int bx, by, ex, ey;

		cin >> bx >> by >> ex >> ey;

		if (bx == ex) // vertical line
		{
			if (by == ey)
				throw runtime_error(to_string(n - _n) + ": " + to_string(bx) + " " + to_string(by) + " " + to_string(ex) + " " + to_string(ey));

			v[bx].emplace_back(min(by, ey), max(by, ey));
		}
		else if (by == ey) // horizontal line
		{
			if (bx == ex)
				throw runtime_error(to_string(n - _n) + ": " + to_string(bx) + " " + to_string(by) + " " + to_string(ex) + " " + to_string(ey));

			h[by].emplace_back(min(bx, ex), max(bx, ex));
		}
		else
		{
			throw runtime_error("line neither vertical nor horizontal");
		}

		if (n - _n == 1)
		{
			init = { bx, by };
			if (bx == ex)
			{
				if (by < ey)
					direction = 0; // UP
				else
					direction = 2; // DOWN
			}
			else
			{
				if (bx < ex)
					direction = 1; // RIGHT
				else
					direction = 3; // LEFT
			}
		}
	}

	return { init, direction };
}