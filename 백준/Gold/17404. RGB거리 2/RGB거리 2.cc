#include <iostream>
int dp[3][1001][3];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	int N;
	std::cin >> N;

	for (int i = 0; i < N; ++i) {
		int a, b, c;
		std::cin >> a >> b >> c;
		dp[0][i][0] = dp[1][i][0] = dp[2][i][0] = a;
		dp[0][i][1] = dp[1][i][1] = dp[2][i][1] = b;
		dp[0][i][2] = dp[1][i][2] = dp[2][i][2] = c;
	}

	// 0 ~ 2행 까지는 정해질 수 밖에 없는 규칙
	// 3행 부터는 기존 DP 방식(BOJ 1149)을 사용한다.

	//[0][0]에서 시작하는 것은 dp[0][][] 저장
	dp[0][1][1] += dp[0][0][0];
	dp[0][1][2] += dp[0][0][0];
	dp[0][2][0] += std::min(dp[0][1][1], dp[0][1][2]);
	dp[0][2][1] += dp[0][1][2];
	dp[0][2][2] += dp[0][1][1];

	//[0][1]에서 시작하는 것은 dp[1][][] 저장
	dp[1][1][0] += dp[1][0][1];
	dp[1][1][2] += dp[1][0][1];
	dp[1][2][0] += dp[1][1][2];
	dp[1][2][1] += std::min(dp[1][1][0], dp[1][1][2]);
	dp[1][2][2] += dp[1][1][0];

	//[0][2]에서 시작하는 것은 dp[2][][] 저장
	dp[2][1][0] += dp[2][0][2];
	dp[2][1][1] += dp[2][0][2];
	dp[2][2][0] += dp[2][1][1];
	dp[2][2][1] += dp[2][1][0];
	dp[2][2][2] += std::min(dp[2][1][0], dp[2][1][1]);

	for (int i = 3; i < N; ++i) {
		for (int j = 0; j < 3; ++j) {
			dp[j][i][0] += std::min(dp[j][i - 1][1], dp[j][i - 1][2]);
			dp[j][i][1] += std::min(dp[j][i - 1][0], dp[j][i - 1][2]);
			dp[j][i][2] += std::min(dp[j][i - 1][0], dp[j][i - 1][1]);
		}
	}

	// 3개의 2차원 DP 테이블 중 최소값을 출력
	// [0] 테이블은 [0] 열의 최소값을 출력하지 않도록 함(시작과 끝의 색은 달라야 하기 때문)
	std::cout << std::min(std::min(std::min(dp[0][N - 1][1], dp[0][N - 1][2]), std::min(dp[1][N - 1][0], dp[1][N - 1][2])), std::min(dp[2][N - 1][0], dp[2][N - 1][1]));
	return 0;
}