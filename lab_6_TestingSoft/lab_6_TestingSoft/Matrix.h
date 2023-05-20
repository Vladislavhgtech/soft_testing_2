#pragma once
#ifndef __MATRIX
#include <random>
#include <memory>

static std::default_random_engine generator;
static std::uniform_real_distribution<double> distribution(-1, 1);

enum class mtype { zeros, ones, normal };
class MatrixException final {};
template<size_t M>
class Matrix final
{
	std::shared_ptr<double[]> mas;
	const size_t m;
public:
	Matrix(mtype T = mtype::normal) : mas(new double[M * M]), m(M)
	{
		for (auto i = 0u; i < M * M; i++)
			switch (T)
			{
			case mtype::normal:
				mas[i] = distribution(generator);
				break;
			case mtype::ones:
				mas[i] = 1;
				break;
			case mtype::zeros:
				mas[i] = 0;
				break;
			}
	}
	const size_t size() const { return m; }
	const Matrix operator*(const Matrix& b) const
	{
		if (b.size() != size())
			throw MatrixException();
		Matrix<M> c(mtype::zeros);
		for (auto i = 0u; i < M; i++)
			for (auto j = 0u; j < M; j++)
				for (auto k = 0u; k < M; k++)
					c.mas[i * M + j] += mas[i * M + k] * b.mas[k * M + j];
		return c;
	}
	Matrix operator=(const Matrix& b)
	{
		this->mas = b.mas;
		return *this;
	}
};
#endif // __MATRIX