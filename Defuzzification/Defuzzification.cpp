#include <iostream>
#include <iomanip>
using namespace std;

double get_u1_for_0_4(double x)
{
	return 1;
}
double get_u2_for_4_7(double x)
{
	return 1 / (x - 3);
}
double get_u3_for_7_10(double x)
{
	return 0.25;
}

double get_u1_for_0_4_umn_na_x(double x)
{
	return 1 * x;
}
double get_u2_for_4_7_umn_na_x(double x)
{
	return (1 / (x - 3)) * x;
}
double get_u3_for_7_10_umn_na_x(double x)
{
	return 0.25 * x;
}

double u_res(double x)
{
	if ((x >= 0) && (x <= 4))
	{
		return get_u1_for_0_4(x);
	}
	if ((x > 4) && (x <= 7))
	{
		return get_u2_for_4_7(x);
	}
	if ((x > 7) && (x <= 10))
	{
		return get_u3_for_7_10(x);
	}
}

double u_res_umn_na_x(double x)
{
	if ((x >= 0) && (x <= 4))
	{
		return get_u1_for_0_4_umn_na_x(x);
	}
	if ((x > 4) && (x <= 7))
	{
		return get_u2_for_4_7_umn_na_x(x);
	}
	if ((x > 7) && (x <= 10))
	{
		return get_u3_for_7_10_umn_na_x(x);
	}
}



double trapeze(double (*f)(double x), double x_nach, double x_konech, int n)
{
	double h = (x_konech - x_nach) / n;
	double sum = (f(x_nach) + f(x_konech));
	for (int i = 1; i < n; i++)
		sum = sum + (2 * f(x_nach + i * h));
	sum = 0.5 * h * sum;
	return sum;
}

double centerOfGravity(double x_nach, double x_konech, double n)
{
	double znamenatel = trapeze(u_res, x_nach, x_konech, n);
	double chislitel = trapeze(u_res_umn_na_x, x_nach, x_konech, n);
	return chislitel / znamenatel;
}

double VisotDefazzifikaciya(double x_nach, double x_konech, double n)
{
	double znamenatel = trapeze(u_res, x_nach, x_konech, n);
	double chislitel = trapeze(u_res_umn_na_x, x_nach, x_konech, n);
	return chislitel / znamenatel;
}

double medianMethod(double x_nach, double x_konech, int n, double half_of_S_all_figure)
{
	double step = (x_konech - x_nach) / n;
	double start = x_nach;
	double ploshad = 0.0;
	for (int i = 0; i < n; i++)
	{
		ploshad = ploshad + 0.5 * step * (u_res(start) + u_res(start + i * step));
		start = x_nach + i * step;
		if (ploshad >= half_of_S_all_figure)
			return start - step;
	}
}


int main()
{
	setlocale(LC_ALL, "rus");
	double otvet;
	int n;
	cout.precision(3);
	cout << "20 Вариант. 211-723, Сергеев С. О." << "\n\n       1, если x c [0; 1]\nu(x) = 1/(x-3), если x c (4; 7]       a = 0,3\n       0,25, если x c (7; 10]\n\n";
	cout << "Введите количество дроблений: ";
	cin >> n;
	otvet = centerOfGravity(0, 10, n);
	cout << "Метод центра тяжести: y* = " << otvet << endl;

	double new_b_for_u2 = (double)((10.0 + 3.0 * 3.0) / 3.0);
	otvet = VisotDefazzifikaciya(0, new_b_for_u2, n);
	cout << "Метод высотной дефаззификации: y* = " << otvet << endl;

	double S_of_All_Figure = trapeze(u_res, 0, 10, n);
	otvet = medianMethod(0, 10, n, S_of_All_Figure / (double)2);
	cout << "Медианный метод способ y* = " << otvet << endl;

	return 0;
}