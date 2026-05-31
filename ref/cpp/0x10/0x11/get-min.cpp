#include <bits/stdc++.h>

using namespace std;

class MinStack {
    stack<int> s;
    stack<int> m;

  public:
    MinStack() {
    }

    void push(int x) {
        this->s.push(x);
        if (this->m.empty()) {
            this->m.push(x);
        } else {
            this->m.push(min(x, m.top()));
        }
    }

    void pop() {
        this->s.pop();
        this->m.pop();
    }

    int top() {
        return this->s.top();
    }

    int getMin() {
        return this->m.top();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}