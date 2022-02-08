#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

int N, M;
int hole_x, hole_y;
std::vector<std::vector<bool>> wall;
int ans = 11;
std::unordered_map<int, int /*min_cnt*/> hash;

void solve(int cnt, const int r_x, const int r_y, const int b_x, const int b_y)
{
	if (cnt == 10)
	{
		//std::cout << cnt << ", " << r_x << ", " << r_y << ", " << b_x << ", " << b_y << "\n";
		return;
	}

	//std::cout << cnt << ", " << r_x << ", " << r_y << ", " << b_x << ", " << b_y << "\n";
	// up
	do
	{
		int cur_r_y = r_y, cur_b_y = b_y;
		if (r_x == b_x && cur_r_y < cur_b_y)
		{
			bool r_in = false, b_in = false;
			// move red first
			while (cur_r_y > 0)
			{
				if (wall[cur_r_y - 1][r_x])
					break;
				if (hole_y == cur_r_y - 1 && hole_x == r_x)
				{
					--cur_r_y;
					r_in = true;
					break;
				}
				--cur_r_y;
			}
			// move blue next
			while (cur_b_y > 0)
			{
				if (wall[cur_b_y - 1][b_x])
					break;
				if (hole_y == cur_b_y - 1 && hole_x == b_x)
				{
					b_in = true;
					break;
				}
				if (cur_r_y == cur_b_y - 1)
					break;
				--cur_b_y;
			}
			if (b_in)
				break; // do-while
			if (r_in && !b_in)
			{
				ans = std::min(ans, cnt + 1);
				return;
			}
		}
		else
		{
			// move blue first
			bool b_in = false;
			while (cur_b_y > 0)
			{
				if (wall[cur_b_y - 1][b_x])
					break;
				if (hole_y == cur_b_y - 1 && hole_x == b_x)
				{
					b_in = true;
					break;
				}
				--cur_b_y;
			}
			if (b_in)
				break; // do-while
			while (cur_r_y > 0)
			{
				if (wall[cur_r_y - 1][r_x])
					break;
				if (cur_b_y == cur_r_y - 1 && b_x == r_x)
					break;
				if (hole_y == cur_r_y - 1 && hole_x == r_x)
				{
					ans = std::min(ans, cnt + 1);
					return;
				}
				--cur_r_y;
			}
		}

		const auto tup = 1000*r_x + 100*cur_r_y + 10*b_x + cur_b_y;
		const auto iter = hash.find(tup);
		if (iter == hash.end()
			|| iter->second > cnt + 1)
		{
			hash[tup] = cnt + 1;
			//std::cout << " UP\n";
			solve(cnt + 1, r_x, cur_r_y, b_x, cur_b_y);
		}
	} while(false);

	//std::cout << cnt << ", " << r_x << ", " << r_y << ", " << b_x << ", " << b_y << "\n";
	// right
	do
	{
		int cur_r_x = r_x, cur_b_x = b_x;
		if (r_y == b_y && cur_r_x > cur_b_x)
		{
			bool r_in = false, b_in = false;
			// move red first
			while (cur_r_x < M - 1)
			{
				if (wall[r_y][cur_r_x + 1])
					break;
				if (hole_x == cur_r_x + 1 && hole_y == r_y)
				{
					++cur_r_x;
					r_in = true;
					break;
				}
				++cur_r_x;
			}
			// move blue next
			while (cur_b_x < M - 1)
			{
				if (wall[b_y][cur_b_x + 1])
					break;
				if (hole_x == cur_b_x + 1 && hole_y == b_y)
				{
					b_in = true;
					break;
				}
				if (cur_r_x == cur_b_x + 1)
					break;
				++cur_b_x;
			}
			if (b_in)
				break; // do-while
			if (r_in && !b_in)
			{
				ans = std::min(ans, cnt + 1);
				return;
			}
		}
		else
		{
			// move blue first
			bool b_in = false;
			while (cur_b_x < M-1)
			{
				if (wall[b_y][cur_b_x + 1])
					break;
				if (hole_x == cur_b_x + 1 && hole_y == b_y)
				{
					b_in = true;
					break;
				}
				++cur_b_x;
			}
			if (b_in)
				break; // do-while
			while (cur_r_x < M-1)
			{
				if (wall[r_y][cur_r_x + 1])
					break;
				if (cur_b_x == cur_r_x + 1 && b_y == r_y)
					break;
				if (hole_x == cur_r_x + 1 && hole_y == r_y)
				{
					ans = std::min(ans, cnt + 1);
					return;
				}
				++cur_r_x;
			}
		}

		const auto tup = 1000*cur_r_x + 100*r_y + 10*cur_b_x + b_y;
		const auto iter = hash.find(tup);
		if (iter == hash.end()
			|| iter->second > cnt + 1)
		{
			hash[tup] = cnt + 1;
			//std::cout << " RIGHT\n";
			solve(cnt + 1, cur_r_x, r_y, cur_b_x, b_y);
		}
	} while(false);

	//std::cout << cnt << ", " << r_x << ", " << r_y << ", " << b_x << ", " << b_y << "\n";
	// down
	do
	{
		int cur_r_y = r_y, cur_b_y = b_y;
		if (r_x == b_x && cur_r_y > cur_b_y)
		{
			bool r_in = false, b_in = false;
			// move red first
			while (cur_r_y < N-1)
			{
				if (wall[cur_r_y + 1][r_x])
					break;
				if (hole_y == cur_r_y + 1 && hole_x == r_x)
				{
					++cur_r_y;
					r_in = true;
					break;
				}
				++cur_r_y;
			}
			// move blue next
			while (cur_b_y < N-1)
			{
				if (wall[cur_b_y + 1][b_x])
					break;
				if (hole_y == cur_b_y + 1 && hole_x == b_x)
				{
					b_in = true;
					break;
				}
				if (cur_r_y == cur_b_y + 1)
					break;
				++cur_b_y;
			}
			if (b_in)
				break; // do-while
			if (r_in && !b_in)
			{
				ans = std::min(ans, cnt + 1);
				return;
			}
		}
		else
		{
			// move blue first
			bool b_in = false;
			while (cur_b_y < N-1)
			{
				if (wall[cur_b_y + 1][b_x])
					break;
				if (hole_y == cur_b_y + 1 && hole_x == b_x)
				{
					b_in = true;
					break;
				}
				++cur_b_y;
			}
			if (b_in)
				break; // do-while
			while (cur_r_y < N-1)
			{
				if (wall[cur_r_y + 1][r_x])
					break;
				if (cur_b_y == cur_r_y + 1 && b_x == r_x)
					break;
				if (hole_y == cur_r_y + 1 && hole_x == r_x)
				{
					ans = std::min(ans, cnt + 1);
					return;
				}
				++cur_r_y;
			}
		}

		const auto tup = 1000*r_x + 100*cur_r_y + 10*b_x + cur_b_y;
		const auto iter = hash.find(tup);
		if (iter == hash.end()
			|| iter->second > cnt + 1)
		{
			hash[tup] = cnt + 1;
			//std::cout << " DOWN\n";
			solve(cnt + 1, r_x, cur_r_y, b_x, cur_b_y);
		}
	} while(false);

	//std::cout << cnt << ", " << r_x << ", " << r_y << ", " << b_x << ", " << b_y << "\n";
	// left
	do
	{
		int cur_r_x = r_x, cur_b_x = b_x;
		if (r_y == b_y && cur_r_x < cur_b_x)
		{
			bool r_in = false, b_in = false;
			// move red first
			while (cur_r_x > 0)
			{
				if (wall[r_y][cur_r_x - 1])
					break;
				if (hole_x == cur_r_x - 1 && hole_y == r_y)
				{
					--cur_r_x;
					r_in = true;
					break;
				}
				--cur_r_x;
			}
			// move blue next
			while (cur_b_x > 0)
			{
				if (wall[b_y][cur_b_x - 1])
					break;
				if (hole_x == cur_b_x - 1 && hole_y == b_y)
				{
					b_in = true;
					break;
				}
				if (cur_r_x == cur_b_x - 1)
					break;
				--cur_b_x;
			}
			if (b_in)
				break; // do-while
			if (r_in && !b_in)
			{
				ans = std::min(ans, cnt + 1);
				return;
			}
		}
		else
		{
			// move blue first
			bool b_in = false;
			while (cur_b_x > 0)
			{
				if (wall[b_y][cur_b_x - 1])
					break;
				if (hole_x == cur_b_x - 1 && hole_y == b_y)
				{
					b_in = true;
					break;
				}
				--cur_b_x;
			}
			if (b_in)
				break; // do-while
			while (cur_r_x > 0)
			{
				if (wall[r_y][cur_r_x - 1])
					break;
				if (cur_b_x == cur_r_x - 1 && b_y == r_y)
					break;
				if (hole_x == cur_r_x - 1 && hole_y == r_y)
				{
					ans = std::min(ans, cnt + 1);
					return;
				}
				--cur_r_x;
			}
		}

		const auto tup = 1000*cur_r_x + 100*r_y + 10*cur_b_x + b_y;
		const auto iter = hash.find(tup);
		if (iter == hash.end()
			|| iter->second > cnt + 1)
		{
			hash[tup] = cnt + 1;
			//std::cout << " LEFT\n";
			solve(cnt + 1, cur_r_x, r_y, cur_b_x, b_y);
		}
	} while(false);
}

int main()
{
	std::cin >> N >> M;

	wall = std::vector<std::vector<bool>>(N, std::vector<bool>(M, false));

	int r_x = 0, r_y = 0, b_x = 0, b_y = 0;

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
		{
			char c;
			std::cin >> c;

			if (c == '#')
			{
				wall[i][j] = true;
				continue;
			}

			if (c == 'R')
			{
				r_x = j;
				r_y = i;
			}
			else if (c == 'B')
			{
				b_x = j;
				b_y = i;
			}
			else if (c == 'O')
			{
				hole_x = j;
				hole_y = i;
			}
		}

	const auto tup = 1000*r_x + 100*r_y + 10*b_x + b_y;
	hash[tup] = 0;

	solve(0, r_x, r_y, b_x, b_y);

	if (ans == 11)
		std::cout << -1 << "\n";
	else
		std::cout << ans << "\n";
}
