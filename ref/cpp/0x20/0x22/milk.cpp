#include <bits/stdc++.h>

using namespace std;

// ==================== 1. 容器与状态定义 ====================
const int CAPACITIES[3] = {8, 5, 3}; // 三个容器的容量：8L, 5L, 3L

struct State {
    int amount[3]; // 三个容器中当前的液体量
    // 构造函数，初始状态 (8, 0, 0)
    State(int a = 8, int b = 0, int c = 0) {
        amount[0] = a;
        amount[1] = b;
        amount[2] = c;
    }
    // 为便于存入unordered_set，重载==和哈希
    bool operator==(const State &other) const {
        return amount[0] == other.amount[0] && amount[1] == other.amount[1] && amount[2] == other.amount[2];
    }
};
// 自定义哈希函数
struct StateHash {
    size_t operator()(const State &s) const {
        return (size_t)s.amount[0] * 100 + s.amount[1] * 10 + s.amount[2];
    }
};

// ==================== 2. 状态集合与路径记录 ====================
unordered_set<State, StateHash> visited; // 已访问状态，防止重复
vector<string> steps;                    // 存储从初始到目标的每一步操作描述
State start_state(8, 0, 0);              // 初始状态
State target_state(4, 4, 0);             // 目标状态：分成4L+4L

// ==================== 3. 裴蜀(贝祖)定理判断存在性 ====================
// 裴蜀定理指出：对于整数a,b，方程 ax+by 能表示的所有整数都是 gcd(a,b) 的倍数。
// 推广到多个容器：所有可量出的体积都是所有容器容量最大公约数的倍数。
// 这里求三个容量 8, 5, 3 的最大公约数，判断目标体积4是否可被整除。
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int gcd_three(int a, int b, int c) {
    return gcd(gcd(a, b), c);
}

// ==================== 4. 递归搜索函数 ====================
bool dfs(State current) {
    // 到达目标状态，返回成功
    if (current == target_state) {
        return true;
    }

    // 标记当前状态已访问
    visited.insert(current);

    // 尝试所有可能的倒水操作：从 i 倒入 j (i != j, 共6种可能)
    for (int i = 0; i < 3; ++i) {
        if (current.amount[i] == 0) continue; // 源容器为空，无法倒出
        for (int j = 0; j < 3; ++j) {
            if (i == j) continue;
            if (current.amount[j] == CAPACITIES[j]) continue; // 目标容器已满，无法倒入

            // 计算可倒出的液体量：源容器当前量 与 目标容器剩余空间 的较小值
            int pour = min(current.amount[i], CAPACITIES[j] - current.amount[j]);

            // 生成新状态
            State next = current;
            next.amount[i] -= pour;
            next.amount[j] += pour;

            // 若新状态未访问过，则递归尝试
            if (visited.find(next) == visited.end()) {
                // 记录操作描述（在递归前压入步骤，若失败则弹出）
                string desc = "将 " + to_string(pour) + "L 从 " + to_string(CAPACITIES[i]) +
                    "L 容器倒入 " + to_string(CAPACITIES[j]) + "L 容器，"
                                                               "状态变为 (" +
                    to_string(next.amount[0]) + ", " + to_string(next.amount[1]) + ", " + to_string(next.amount[2]) + ")";
                steps.push_back(desc);

                if (dfs(next)) {
                    return true; // 找到解
                }

                steps.pop_back(); // 回溯：此路不通，移除该操作记录
            }
        }
    }

    // 若所有可能操作均无法到达目标，可选择性取消visited标记以允许其他路径访问
    // 但由于状态空间很小且是树或DAG，这里不取消也没关系，或可以取消：
    // visited.erase(current); // 若想找出所有路径可加上，但这里只需要一个解
    return false;
}

// ==================== 5. 主程序 ====================
int main() {
    // ---- 裴蜀定理存在性判断 ----
    int g = gcd_three(CAPACITIES[0], CAPACITIES[1], CAPACITIES[2]);
    // 总液量8L必须守恒，同时目标体积4L必须能被最大公约数整除
    // 但更严谨的判定是：目标状态每个容器内的体积都必须是g的倍数
    bool bezout_possible = (target_state.amount[0] % g == 0) &&
        (target_state.amount[1] % g == 0) &&
        (target_state.amount[2] % g == 0);
    cout << "裴蜀定理判断：三个容器的容量最大公约数为 " << g << endl;
    cout << "目标状态各容器体积是否均为公约数倍数： "
         << (bezout_possible ? "是" : "否") << endl;

    if (!bezout_possible) {
        cout << "根据裴蜀定理，此目标不可达！" << endl;
        return 0;
    }

    // ---- 递归搜索具体步骤 ----
    cout << "\n开始搜索解决方案...\n"
         << endl;
    if (dfs(start_state)) {
        cout << "找到解决方案！共 " << steps.size() << " 步：" << endl;
        for (size_t i = 0; i < steps.size(); ++i) {
            cout << "步骤 " << i + 1 << ": " << steps[i] << endl;
        }
    } else {
        cout << "虽然裴蜀定理表明理论上可能，但通过有限操作未找到解（程序错误或存在约束）。" << endl;
    }
}