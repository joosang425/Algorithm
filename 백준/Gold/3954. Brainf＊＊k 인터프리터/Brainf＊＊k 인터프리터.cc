#include <bits/stdc++.h>
using namespace std;

int t, sm, sc, si, cnt, title_idx, char_idx, mem_idx, min_idx, max_idx;
int mem[100000], left_[4096], right_[4096];
char pro_char[4096], pro_title[4096];

bool loop_check() {
	// 명령어 배열 인덱스가 끝에 도착 시 무한루프에 빠지지 않았다는 뜻
	while (char_idx < sc) {
		// 5천만번까지 돌았다는 뜻은 무한루프 속에 들어가있다는 뜻
		if (cnt == 50000000) {
			min_idx = char_idx;
			max_idx = char_idx;
		}
		// 1억번까지 왔을 시 종료
		if (cnt >= 100000000)
			return false;

		if (pro_char[char_idx] == '+') {
			mem[mem_idx]++;

			if (mem[mem_idx] > 255)
				mem[mem_idx] = 0;

			char_idx++;
		}
		else if (pro_char[char_idx] == '-') {
			mem[mem_idx]--;

			if (mem[mem_idx] < 0)
				mem[mem_idx] = 255;

			char_idx++;
		}
		else if (pro_char[char_idx] == '<') {
			mem_idx--;

			if (mem_idx < 0)
				mem_idx = sm - 1;

			char_idx++;
		}
		else if (pro_char[char_idx] == '>') {
			mem_idx++;

			if (mem_idx == sm)
				mem_idx = 0;

			char_idx++;
		}
		else if (pro_char[char_idx] == '[') {
			if (mem[mem_idx] == 0) 
				char_idx = left_[char_idx];

			char_idx++;
		}
		else if (pro_char[char_idx] == ']') {
			if (mem[mem_idx] != 0)
				char_idx = right_[char_idx];

			char_idx++;
		}
		else if (pro_char[char_idx] == '.') {
			char_idx++;
		}
		else {
			if (title_idx < si)
				mem[mem_idx] = pro_title[title_idx++];
			else if (title_idx == si)	// 입력의 마지막인 경우
				mem[mem_idx] = 255;

			char_idx++;
		}

		cnt++;
		// 그러므로 5천만번에서 1억번까지 돌리면서 포인터가 움직였던 범위 기록
		if (cnt > 50000000) {
			min_idx = min(min_idx, char_idx);
			max_idx = max(max_idx, char_idx);
		}
	}

	// 반복문이 끝난 경우 프로그램이 종료되었다는 뜻
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	while (t--) {
		cin >> sm >> sc >> si;

		cnt = 0, title_idx = 0, char_idx = 0, mem_idx = 0;
		min_idx = 0, max_idx = 0;

		memset(mem, 0, sizeof(mem));
		memset(left_, 0, sizeof(left_));
		memset(right_, 0, sizeof(right_));
		memset(pro_char, '0', sizeof(pro_char));
		memset(pro_title, '0', sizeof(pro_title));

		for (int i = 0; i < sc; i++)
			cin >> pro_char[i];

		for (int i = 0; i < si; i++)
			cin >> pro_title[i];

		stack<int> s;

		// 괄호 짝 저장
		for (int i = 0; i < sc; i++) {
			if (pro_char[i] == '[')
				s.push(i);
			else if (pro_char[i] == ']') {
				left_[s.top()] = i;
				right_[i] = s.top();
				s.pop();
			}
		}

		if (loop_check())
			cout << "Terminates\n";
		else // 현재 무한루프에서 ]를 만날 시 [ 인덱스에서 +1를 해주기 때문에 min_idx - 1
			cout << "Loops " << min_idx - 1 << ' ' << max_idx << '\n';
	}

	return 0;
}