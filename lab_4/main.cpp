#include <iostream>
using namespace std;

template<class T, int N, int M>
class Matrix {
private:
    T data[N][M];

public:
    Matrix() {}

    Matrix(const Matrix& other) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    Matrix& operator=(const Matrix& other) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                data[i][j] = other.data[i][j];
            }
        }
        return *this;
    }

    friend istream& operator>>(istream& in, Matrix& matrix) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                in >> matrix.data[i][j];
            }
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, const Matrix& matrix) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                out << matrix.data[i][j] << ' ';
            }
            out << endl;
        }
        return out;
    }

    Matrix operator+(const Matrix& other) const {
        Matrix res;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                res.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return res;
    }

    Matrix& operator+=(const Matrix& other) {
        *this = *this + other;
        return *this;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix res;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                res.data[i][j] = 0;
                for (int k = 0; k < M; k++) {
                    res.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return res;
    }

    Matrix& operator*=(const Matrix& other) {
        *this = *this * other;
        return *this;
    }

    void operator++() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                data[i][j]++;
            }
        }
    }

    T determinant() const {
        if (N == 2 && M == 2) {
            return (double)data[0][0] * data[1][1] - (double)data[0][1] * data[1][0];
        }
        if (N == 3 && M == 3) {
            return
                ((double)data[0][0] * data[1][1] * data[2][2]) +
                ((double)data[0][1] * data[1][2] * data[2][0]) +
                ((double)data[1][0] * data[2][1] * data[0][2]) -
                ((double)data[0][2] * data[1][1] * data[2][0]) -
                ((double)data[1][2] * data[2][1] * data[0][0]) -
                ((double)data[1][0] * data[0][1] * data[2][2]);
        }

        throw std::exception("Determinant is not defined");
    }

    T& operator()(int i, int j) {
        return data[i][j];
    }

    const T& operator()(int i, int j) const {
        return data[i][j];
    }
};

int main() {
    Matrix<int, 3, 3> a, b;
    cout << "Enter matrix A:" << endl;
    cin >> a;
    cout << "Enter matrix B:" << endl;
    cin >> b;

    cout << "A + B =" << endl;
    cout << a + b;

    cout << "A * B =" << endl;
    cout << a * b;

    a += b;
    cout << "A += B =" << endl;
    cout << a;

    ++a;
    cout << "++A =" << endl;
    cout << a;

    cout << "det(A) = " << a.determinant() << endl;

    a(0, 0)++;
    cout << "A(0, 0) = " << a(0, 0) << endl;
    return 0;
}

