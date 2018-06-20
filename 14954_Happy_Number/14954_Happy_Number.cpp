#include <iostream>
#include <string>
#include <vector>

using namespace std;

const vector<int> iterated{ 4, 16, 37, 58, 89, 145, 42, 20 };

int main()
{
	string in;
	cin >> in;

	while (1)
	{
		int squared_sum = 0;
		for (const char& c : in)
			squared_sum += (c - 48) * (c - 48);

		if (squared_sum == 1)
		{
			cout << "HAPPY";
			return 0;
		}
		else
			for (const int& i : iterated)
				if (i == squared_sum)
				{
					cout << "UNHAPPY";
					return 0;
				}

		in = to_string(squared_sum);
	}
}