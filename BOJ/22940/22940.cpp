#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Fraction {
    long long a;
    long long b;

    Fraction(long long numerator = 0, long long denominator = 1)
        : a(numerator), b(denominator) {
        normalize();
    }

    void normalize()
    {
        auto gcd = [](long long u, long long v) {
            while (v != 0) {
                long long r = u % v;
                u = v;
                v = r;
            }
            return u;
        };

        if (b < 0) {
            a = -a;
            b = -b;           
        }

        auto _gcd = gcd(abs(a), abs(b));
        a /= _gcd;
        b /= _gcd;
    }

    double get()
    {
        return (double)a / (double)b;
    }

    Fraction operator+(Fraction& other)
    {
        Fraction result;
        result.a = this->a * other.b + this->b * other.a;
        result.b = this->b * other.b;
        result.normalize();

        return result;
    }
    Fraction operator-(Fraction other)
    {
        Fraction result;
        result.a = this->a * other.b - this->b * other.a;
        result.b = this->b * other.b;
        result.normalize();

        return result;
    }
    Fraction operator*(Fraction other)
    {
        Fraction result;
        result.a = this->a * other.a;
        result.b = this->b * other.b;
        result.normalize();

        return result;
    }
    Fraction operator*(int other)
    {
        Fraction result;
        result.a = this->a * other;
        result.b = this->b;

        result.normalize();

        return result;
    }
    Fraction operator/(Fraction other)
    {
        Fraction result;
        result.a = this->a * other.b;
        result.b = this->b * other.a;
        result.normalize();

        return result;
    }
};

int main()
{
    int n;
    cin >> n;

    vector<vector<Fraction>>
        matrix(n, vector<Fraction>(n, Fraction(0, 1)));
    vector<vector<Fraction>>
        addMatrix(n, vector<Fraction>(n, Fraction(0, 1)));

    vector<int> v(n);
    vector<Fraction> result(n, { 0,1 });

    for (int i = 0;i < n;++i)
    {
        for (int j = 0;j < n;++j)
        {
            cin >> matrix[i][j].a;
        }
        cin >> v[i];
        addMatrix[i][i].a = 1;
    }

    for (int o = 0;o < n;++o)
    {
        if (matrix[o][o].a == 0)
        {
            int targetRow = o;

            for (int i = o + 1; i < n; ++i)
            {
                if (matrix[i][o].a != 0)
                {
                    targetRow = i;
                    break;
                }
            }

            auto tmpVector = matrix[o];
            auto tmpAddVector = addMatrix[o];

            matrix[o] = matrix[targetRow];
            matrix[targetRow] = tmpVector;

            addMatrix[o] = addMatrix[targetRow];
            addMatrix[targetRow] = tmpAddVector;
        }

        // divide by first element
        for (int i = o;i < n;++i)
        {
            auto div = matrix[i][o];
            if (div.a == 0) continue;
            for (int j = 0;j < n;++j)
            {
                matrix[i][j] = matrix[i][j] / div;
                addMatrix[i][j] = addMatrix[i][j] / div;
            }
        }

        for (int i = o + 1;i < n;++i)
        {
            // a/b - c/d = ad/bd - cb/bd = ad-cb/bd
            if (matrix[i][o].a == 0) continue;
            for (int j = 0;j < n;++j)
            {
                matrix[i][j] = matrix[i][j] - matrix[o][j];
                addMatrix[i][j] = addMatrix[i][j] - addMatrix[o][j];
            }
        }
    }

    for (int i = n - 1;i >= 1;--i)
    {
        for (int j = 0;j < i;++j)
        {
            for (int k = 0; k < n; ++k)
            {
                addMatrix[j][k] = addMatrix[j][k] -
                    (matrix[j][i] * addMatrix[i][k]);
            }
            matrix[j][i] = Fraction(0, 1);
        } 
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            auto addValue = addMatrix[i][j] * v[j];
            result[i] = result[i] + addValue;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << (int)(result[i].get()) << " ";
    }
    cout << endl;

}