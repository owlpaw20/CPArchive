#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;
using str = string;
using lng = unsigned long long;

struct Member {
    int index;
    str name;
    Member() {}
    Member(int _t, str _n) : index(_t), name(_n) {}
};

const int N = 1e4 + 10;

int Q, idx;
lng sizes[N], alignment[N];
vector<Member> members[N];
unordered_map<string, int> typeMap;

void defineClass();
void declareVariable();
void locateVariable();
void visitAddress();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 在类型映射表和变量表中初始化四种基本数据类型
    typeMap["byte"] = ++idx;
    sizes[idx] = alignment[idx] = 1;
    typeMap["short"] = ++idx;
    sizes[idx] = alignment[idx] = 2;
    typeMap["int"] = ++idx;
    sizes[idx] = alignment[idx] = 4;
    typeMap["long"] = ++idx;
    sizes[idx] = alignment[idx] = 8;

    cin >> Q;

    while (Q--) {
        int opt;
        cin >> opt;
        switch (opt) {
            case (1):
                defineClass();
                break;
            case (2):
                declareVariable();
                break;
            case (3):
                locateVariable();
                break;
            case (4):
                visitAddress();
                break;
        }
    }
    return 0;
}

void defineClass() {
    str typeName;
    int memberCnt;
    cin >> typeName >> memberCnt;

    // 在类型映射表中创建新类
    typeMap[typeName] = ++idx;
    members[idx].resize(memberCnt);

    // 输入新类中的各个成员
    for (Member &obj : members[idx]) {
        str memberType, memberName;
        cin >> memberType >> memberName;
        obj = Member(typeMap[memberType], memberName);
        alignment[idx] = max(alignment[idx], alignment[obj.index]); // 保存类的对齐量
    }

    // 更新类及内部成员的大小
    for (Member obj : members[idx]) {
        if (sizes[idx] % alignment[obj.index]) // 根据对齐量调整位置
            sizes[idx] = (sizes[idx] / alignment[obj.index] + 1) * alignment[obj.index];
        sizes[idx] += sizes[obj.index]; // 更新整个类的大小
    }

    if (sizes[idx] % alignment[idx])
        sizes[idx] = (sizes[idx] / alignment[idx] + 1) * alignment[idx];
    cout << sizes[idx] << " " << alignment[idx] << endl;
}

void declareVariable() {
    str varType, varName;
    cin >> varType >> varName;

    // 全局声明一个变量
    members[0].emplace_back(typeMap[varType], varName);

    // 计算该变量的地址
    lng address = 0ULL;
    for (int i = 0; i < members[0].size(); i++) {
        Member obj = members[0][i];
        if (address % alignment[obj.index]) // 根据对齐量调整位置
            address = (address / alignment[obj.index] + 1) * alignment[obj.index];
        if (i != members[0].size() - 1)
            address += sizes[obj.index];
    }

    cout << address << endl;
}

void locateVariable() {
    str varPath;
    cin >> varPath;

    // 根据路径对变量进行溯源
    int currentClass = 0;
    lng address = 0ULL;
    for (int i = 0; i < varPath.length() && varPath[i] != '.';) {
        str varName;
        while (i < varPath.length() && varPath[i] != '.')
            varName += varPath[i], i++; // 查找下级成员的名称
        i++;
        for (Member obj : members[currentClass]) {
            if (address % alignment[obj.index]) // 根据对齐量调整位置
                address = (address / alignment[obj.index] + 1) * alignment[obj.index];
            if (obj.name == varName) { // 如果找到了下级成员
                currentClass = obj.index; // 则指针跳转至下级成员的位置
                break;
            }
            address += sizes[obj.index]; // 如果没有找到则加上当前成员所占用的空间
        }
    }

    cout << address << endl;
}

void visitAddress() {
    lng target = 0ULL;
    cin >> target;
    if (members[0].empty())
        return (void)(cout << "ERR" << endl);

    // 不断向下探查直到到达基础类型元素
    str path;
    int currentClass = 0;
    lng address = 0ULL, lastAddress = 0ULL;
    while (!members[currentClass].empty()) {
        if (!path.empty())
            path += "."; // 每轮循环确定一个下级成员所以需要加一个点
        bool OK = false;

        // 对当前层级的所有成员进行遍历
        for (int i = 0; i < members[currentClass].size(); i++) {
            Member obj = members[currentClass][i];
            if (address % alignment[obj.index]) // 根据对齐量调整位置
                address = (address / alignment[obj.index] + 1) * alignment[obj.index];
            if (address > target) { // 如果当前成员遍历完后已经超过目标地址
                address = lastAddress; // 则找到上一个成员的下标
                path += members[currentClass][i - 1].name; // 确定上一个成员为目标所在处
                currentClass = members[currentClass][i - 1].index; // 指针跳转到该成员的下标
                OK = true; // 记录已经找到所在成员的对齐量
                break;
            }
            lastAddress = address;
            address += sizes[obj.index]; // 加上当前成员所占用的空间
        }

        // 特判访问到最后一个成员的情况
        if (address > target) {
            address = lastAddress;
            path += members[currentClass].back().name;
            currentClass = members[currentClass].back().index;
            OK = true;
        }

        // 判断当前位置是否为空
        if (members[currentClass].empty() && address + sizes[currentClass] <= target)
            OK = false;
        if (!OK)
            return (void)(cout << "ERR" << endl);
    }

    cout << path << endl;
}
