
// (C) 2023 e6nlaq

#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <vector>
#include <set>
#include <unordered_set>
#include <queue>
#include <algocpp/all.hpp>
using namespace std;

void split(string s, vector<double> &num, vector<char> &op)
{
	num.clear();
	op.clear();

	string sum = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (isdigit(s[i]) || s[i] == '.')
			sum += s[i];
		else
		{
			num.push_back(stod(sum));
			op.push_back(s[i]);
			sum = "";
		}
	}

	num.push_back(stod(sum));
}

double calc(string s, bool out = false)
{
	string tmp = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '(')
		{
			string cop = "";
			int inc = 1;
			for (int j = i + 1; j < s.size() && inc > 0; j++)
			{
				if (s[j] == '(')
					inc++;
				else if (s[j] == ')')
					inc--;

				if (inc != 0)
					cop += s[j];

				i = j;
			}

			tmp += to_string(calc(cop));
		}
		else
			tmp += s[i];
	}

	s = tmp;

	if (out)
		cout << "= " << s << endl;

	vector<double> num;
	vector<char> op;
	split(s, num, op);

	if (num.size() != op.size() + 1 || op.size() == 0)
	{
		throw invalid_argument("operror");
	}

	string check1 = s;
	string check = s;

	do
	{
		split(s, num, op);
		queue<char> ope;
		queue<double> nm;
		for (int i = 0; i < op.size(); i++)
		{
			ope.push(op[i]);
		}

		for (int i = 0; i < num.size(); i++)
		{
			nm.push(num[i]);
		}

		check = s;
		tmp = "";
		while (!nm.empty())
		{
			if (ope.front() == '*')
			{
				double a = nm.front();
				nm.pop();
				tmp += to_string(a * nm.front());
				ope.pop();
				if (!ope.empty())
				{
					tmp += ope.front();
				}
			}
			else if (ope.front() == '/')
			{
				double a = nm.front();
				nm.pop();
				tmp += to_string(a / nm.front());
				ope.pop();
				if (!ope.empty())
				{
					tmp += ope.front();
				}
			}
			else
			{
				tmp += to_string(nm.front());
				if (!ope.empty())
				{
					tmp += ope.front();
				}
			}

			if (ope.empty())
				break;

			ope.pop();
			nm.pop();
		}

		check = tmp;
	} while (check != tmp);

	s = check;

	if (out && s != check1)
	{
		cout << "= " << s << endl;
	}

	split(s, num, op);
	queue<char> ope;
	queue<double> nm;
	for (int i = 0; i < op.size(); i++)
	{
		ope.push(op[i]);
	}

	for (int i = 0; i < num.size(); i++)
	{
		nm.push(num[i]);
	}

	double now = nm.front();
	nm.pop();
	while (!ope.empty())
	{
		if (ope.front() == '+')
		{
			now += nm.front();
		}
		else
		{
			now -= nm.front();
		}

		ope.pop();
		nm.pop();
	}

	if (out)
		cout << "= " << now << endl;

	return now;
}

int main()
{
	cout << "\n"
		 << "CONSOLE JAMAICA GAME"
		 << "\n"
		 << "(C) 2023 e6nlaq"
		 << "\n\n"
		 << "Press Enter to start." << endl;

	string inp;
	getline(cin, inp);
	srand(time(NULL));

	while (true)
	{
		system("cls");

		vector<int> number(5);
		int ans = -1;
		for (int i = 0; i < 5; i++)
		{
			number[i] = rand() % 6 + 1;
		}
		sort(number.begin(), number.end());

		for (int i = 0; i < 5; i++)
			cout << number[i] << (i != 4 ? ", " : "\n");
		ans = ((rand() % 6 + 1) * 10) + (rand() % 6 + 1);
		cout << "= " << ans << endl
			 << endl;

		while (true)
		{
			cout << ">>> ";
			getline(cin, inp);
			inp = algocpp::string::replace(inp, " ", "");

			try
			{
				calc(inp, true);
			}
			catch (const std::exception &e)
			{
				cout << "FE(Format Error)" << endl
					 << endl;
			}
		}
	}

	return 0;
}
