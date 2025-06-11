#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <climits>

int evalRPN(const std::vector<std::string>& tokens) {
    std::vector<int> stack;
    for (const std::string& s : tokens) {
        if (s == "+") {
            int a = stack.back(); stack.pop_back();
            int b = stack.back(); stack.pop_back();
            stack.push_back(a + b);
        } else if (s == "-") {
            int a = stack.back(); stack.pop_back();
            int b = stack.back(); stack.pop_back();
            stack.push_back(b - a);
        } else if (s == "*") {
            int a = stack.back(); stack.pop_back();
            int b = stack.back(); stack.pop_back();
            stack.push_back(a * b);
        } else if (s == "/") {
            int a = stack.back(); stack.pop_back();
            int b = stack.back(); stack.pop_back();
            if (a == 0) return INT_MIN;
            stack.push_back(b / a);
        } else {
            int x = std::stoi(s);
            stack.push_back(x);
        }
    }
    return stack.front();
}

void dfs(
    const std::vector<std::string>& a,
    const std::vector<std::string>& ops,
    std::vector<std::string>& st,
    std::set<std::string>& formula,
    const std::vector<int>& idx,
    int N, int K, int depth, int op_sum
) {
    if (depth == K && op_sum == K - 1) {
        std::string tmp;
        for (size_t i = 0; i < st.size(); ++i) {
            tmp += st[i];
            if (i + 1 != st.size()) tmp += " ";
        }
        if (evalRPN(st) == N) {
            formula.insert(tmp);
        }
        return;
    }
    if (depth < K) {
        st.push_back(a[idx[depth]]);
    }
    if (op_sum < K && depth > 0) {
        for (int i = 0; i < 4; ++i) {
            st.push_back(ops[i]);
            dfs(a, ops, st, formula, idx, N, K, depth + (depth < K), op_sum + 1);
            st.pop_back();
        }
    }
    if (depth < K) {
        dfs(a, ops, st, formula, idx, N, K, depth + 1, op_sum);
        st.pop_back();
    }
}

int main() {
    int N, K;
    std::cin >> N >> K;
    std::vector<std::string> a(K);
    for (int i = 0; i < K; ++i) {
        std::cin >> a[i];
    }
    std::vector<std::string> ops = {"+", "-", "*", "/"};
    std::vector<int> idx(K);
    for (int i = 0; i < K; ++i) idx[i] = i;
    std::set<std::string> formula;
    std::vector<std::string> st;
    do {
        dfs(a, ops, st, formula, idx, N, K, 0, 0);
    } while (std::next_permutation(idx.begin(), idx.end()));
    if (formula.empty()) {
        std::cout << "No" << std::endl;
        return 0;
    }
    std::cout << "Yes" << std::endl;
    std::cout << formula.size() << std::endl;
    for (const std::string& s : formula) {
        std::cout << s << std::endl;
    }
    return 0;
}
