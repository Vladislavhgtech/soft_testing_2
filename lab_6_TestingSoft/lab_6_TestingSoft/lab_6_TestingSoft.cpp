//#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include "Matrix.h"

using namespace std;

mutex mtx;

int main()
{
	constexpr size_t N = 200, M = 200;
	typedef Matrix<M> M100;
	const Matrix<M> vm[N]{};
	vector<Matrix<M>> resm;

	auto matrix_mult = [&](const M100* mas)
	{
		M100 res(mtype::ones);
		for (auto i = 0u; i < N / 8; i++)
			res = res * mas[i];
		lock_guard<std::mutex> lock(mtx);
		resm.push_back(res);
	};
	vector<thread> threads;
	for (auto i = 0u; i < 7; i++)
	{
		thread thr(matrix_mult, vm + i * N / 8);
		threads.emplace_back(std::move(thr));
	}
	matrix_mult(vm + 7 * N / 8);
	for (auto& i : threads)
		i.join();
	Matrix<M> res(mtype::ones);
	for (const auto& i : resm)
		res = res * i;
	return 0;
}