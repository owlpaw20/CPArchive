#include <cstdio>
#include <string>
#include <unordered_map>

#define endl '\n'

using f64 = double;
using str = std::string;
using MAP_SI = std::unordered_map<str, int>;
using MAP_II = std::unordered_map<int, int>;

// 固定的加成数值
const f64 LOC_BOOST[6] = {1.25, 1.00, 0.75, 0.00, 0.75, 1.00};
const f64 TYPE_BOOST[3][3] = {{1.0, 0.9, 1.1}, {1.1, 1.0, 0.9}, {0.9, 1.1, 1.0}};
const int PLACE[6] = {5, 3, 1, 2, 4, 6};

const f64 ACT_SKL_MUL[3][6] = {
    {0.00, 0.10, 0.12, 0.15, 0.17, 0.20},
    {0.00, 0.06, 0.07, 0.08, 0.09, 0.10},
    {1.00, 2.10, 2.17, 2.24, 2.32, 2.40}
};

const f64 PSV_SKL_MUL[3][6] = {
    {0.00, 0.013, 0.016, 0.019, 0.022, 0.025},
    {0.00, 0.01, 0.02, 0.03, 0.04, 0.05},
    {0.00, 0.01, 0.02, 0.03, 0.04, 0.05}
};

f64 atk_boost[2] = {1, 1};
f64 def_boost[2] = {1, 1};
MAP_SI WEAPON_TYPE = {{"B", 0}, {"G", 1}, {"M", 2}};
MAP_SI PLAYER_TYPE = {{"Weak", 0}, {"Average", 1}, {"Strong", 2}};
MAP_II INIT_INDEX = {{1, 2}, {2, 3}, {3, 1}, {4, 4}, {5, 0}, {6, 5}};

int member_cnt[2];
int member_type_cnt[2][3];
int round_cnt;
int attacker[2];

struct PLAYER {
    int team_fr; // 归属队伍
    int team_id; // 归属队伍内编号

    int type; // 类型：0 = weak, 1 = average, 2 = strong
    int lvl; // 等级：1 ~ 100
    f64 atk; // 基础攻击力
    f64 def; // 基础防御力
    int max_hp; // 体力上限
    int act_skl; // 主动技能等级：0 ~ 5
    int psv_skl; // 被动技能等级：0 ~ 5

    int weapon_type; // 武器类型：0 = B, 1 = G, 2 = M
    f64 weapon_atk; // 武器攻击力

    int hp; // 当前体力
    bool status; // 状态：0 = dead, 1 = alive
    f64 skl_boost; // 技能加成

    int dot_dmg; // 持续伤害大小
    int dot_rounds; // 持续伤害层数

    void input() {
        char player_type[10], weapon_type_t[4];
        scanf("%s Lv=%d maxhp=%d atk=%lf def=%lf skillLv=%d passivesklLv=%d %s weaponatk=%lf\n",
            player_type, &lvl, &max_hp, &atk, &def, &act_skl, &psv_skl, weapon_type_t, &weapon_atk);

        hp = max_hp; // 初始生命值为上限
        status = true; // 初始角色未倒下
        skl_boost = 1; // 初始技能加成为 1
        type = PLAYER_TYPE[str(player_type)]; // 根据输入获取角色类型对应数字
        weapon_type = WEAPON_TYPE[str(weapon_type_t)]; // 根据输入获取武器类型对应数字
        dot_rounds = 0; // 初始持续伤害剩余层数为 0
        dot_dmg = 0; // 初始持续伤害大小为 0
    }

    void deal_damage(int, int, f64);
    void DOT();
} team[2][7];

/// @brief 在每回合开始时及有角色倒下后重新计算被动伤害
/// @param t 默认为 -1，有角色倒下；如果输入为 0 或 1，则代表 Weak 类型的被动技能生效的团队
void reapply_passive_skills(int t = -1) {
    if (t != -1) { // 如果是开局，则需要使 Weak 类型的被动效果生效
        f64 weak = 0; // 统计 Weak 被动叠加效果层数
        for (int i = 1; i <= member_cnt[t]; ++i)
            if (team[t][i].status && team[t][i].type == 0) // 对于当前队伍中所有还活着的 Weak 类型角色
                weak += PSV_SKL_MUL[0][team[t][i].psv_skl]; // 根据其等级叠加效果加成

        weak = std::min(weak, 0.05); // 考虑效果加成上限

        for (int i = 1; i <= member_cnt[t]; ++i) {
            if (!team[t][i].status) continue; // 已经倒下的角色就不用考虑了

            int tmp = team[t][i].hp;
            int heal = weak * team[t][i].max_hp; // 计算回复量
            team[t][i].hp += heal; // 回复
            if (team[t][i].hp > team[t][i].max_hp) // 如果回复后超过生命上限
                team[t][i].hp = team[t][i].max_hp; // 则将生命值更改为上限

            if (tmp != team[t][i].hp) // 如果生命值有所变动，就需要输出
                printf("%s %d recovered +%d hp -> %d/%d\n",
                    (t ? "North" : "South"), i, heal, team[t][i].hp, team[t][i].max_hp);
        }
    }

    // 对于其他两种类型，只需要在角色倒下后考虑被动技能分配情况即可
    for (int t = 0; t < 2; ++t) {
        f64 average = 0, strong = 0; // 统计被动效果叠加层数
        for (int i = 1; i <= member_cnt[t]; ++i)
            if (team[t][i].status) // 对于当前队伍中所有还活着的对应类型队员
                if (team[t][i].type == 1) // 统计 Average 被动叠加层数
                    average += PSV_SKL_MUL[1][team[t][i].psv_skl];
                else if (team[t][i].type == 2) // 统计 Strong 被动叠加层数
                    strong += PSV_SKL_MUL[2][team[t][i].psv_skl];

        // 根据上限进行相应调整
        average = std::min(average, 0.1);
        strong = std::min(strong, 0.1);

        // 增加对应的防御加成、攻击加成的值
        def_boost[t] = average + 1;
        atk_boost[t] = strong + 1;
    }
}

/// @brief 根据攻击强度对当前角色进行扣血
/// @param t_a 攻击方队伍的编号
/// @param act 攻击者在攻击方队伍内的编号
/// @param eff 攻击强度
void PLAYER::deal_damage(int t_a, int act, f64 eff) {
    if (!status) return; // 保险措施，如果已经倒下就不用考虑了

    int dmg = eff / (def * def_boost[team_fr]); // 计算攻击产生扣血的有效值
    hp -= dmg; // 扣血

    // 如果扣血后角色生命值不高于 0，则该角色倒下
    if (hp <= 0) {
        hp = 0;
        status = false; // 设定角色状态为倒下
        reapply_passive_skills(); // 重新考虑被动技能
    }

    printf("%s %d took %d damage from %s %d -> %d/%d\n",
        (team_fr ? "North" : "South"), team_id, dmg, (t_a ? "North" : "South"), act, hp, max_hp);
}

/// @brief DoT，即 Damage over Time，处理当前角色受到的 Average 类型的持续伤害
void PLAYER::DOT() {
    if (!status) return; // 保险措施，如果已经倒下就不用考虑了

    if (dot_rounds) { // 如果持续伤害层数不为 0
        --dot_rounds, hp -= dot_dmg; // 则触发一次持续伤害并减一层层数

        // 同上
        if (hp <= 0) {
            hp = 0;
            status = false;
            reapply_passive_skills();
        }

        printf("%s %d took %d damage from skill -> %d/%d\n",
            (team_fr ? "North" : "South"), team_id, dot_dmg, hp, max_hp);
    }
}

/// @brief 计算每一回合攻击方队伍的攻击者
/// @param t 攻击方队伍的编号
void get_attacker(int t) {
    do {
        ++attacker[t];
        if (attacker[t] > member_cnt[t]) attacker[t] = 1;
    } while (!team[t][attacker[t]].status); // 如果找到未倒下的角色就跳出循环
    // 由于题目保证所有操作合法，所以不用担心死循环
}

/// @brief 触发主动技能
/// @param act 释放技能者在释放技能方队伍内的编号
/// @param trg 被释放技能者在被释放技能方队伍内的编号
/// @param t_a 释放技能方队伍的编号
/// @param t_b 被释放技能队伍的编号
void activate_active_skill(int act, int trg, int t_a, int t_b) {
    // 获取技能类型名以便输出
    str skl_type;

    if (team[t_a][act].type == 0) skl_type = "Weak";
    else if (team[t_a][act].type == 1) skl_type = "Average";
    else if (team[t_a][act].type == 2) skl_type = "Strong";

    printf("%s %d applied %s skill to %s %d\n",
        (t_a ? "North" : "South"), act, skl_type.c_str(), (t_b ? "North" : "South"), trg);

    // 对于 Weak 类型的主动技能
    if (team[t_a][act].type == 0) {
        int tmp = team[t_b][trg].hp;
        int heal = ACT_SKL_MUL[0][team[t_a][act].act_skl] * team[t_b][trg].max_hp; // 计算回复量
        team[t_b][trg].hp += heal; // 回复
        if (team[t_b][trg].hp > team[t_b][trg].max_hp) // 如果回复后超过生命上限
            team[t_b][trg].hp = team[t_b][trg].max_hp; // 则将生命值改为上限

        if (tmp != team[t_b][trg].hp) // 如果生命值有所变动，就需要输出
            printf("%s %d recovered +%d hp -> %d/%d\n",
                (t_b ? "North" : "South"), trg, heal, team[t_b][trg].hp, team[t_b][trg].max_hp);
    }

    // 对于 Average 类型的主动技能
    else if (team[t_a][act].type == 1) {
        team[t_b][trg].dot_rounds = 3; // 设持续伤害持续 3 层
        team[t_b][trg].dot_dmg = ACT_SKL_MUL[1][team[t_a][act].act_skl] * team[t_b][trg].max_hp; // 计算持续伤害大小
    }

    // 对于 Strong 类型的主动技能
    else if (team[t_a][act].type == 2)
        team[t_b][trg].skl_boost = ACT_SKL_MUL[2][team[t_a][act].act_skl]; // 更改角色的技能加成
}

/// @brief 实施普通攻击和特殊攻击
/// @param atk_p 攻击位置
/// @param ddg_p 躲闪位置
/// @param act 攻击者在攻击方队伍内的编号
/// @param trg 防御者在防御方队伍内的编号
/// @param t_a 攻击方队伍编号
/// @param t_b 防御方队伍编号
/// @param type 攻击类型，-1 为普通攻击，0~2 为对应的特殊攻击
void perform_attack(int atk_p, int ddg_p, int act, int trg, int t_a, int t_b, int type = -1) {
    // 由于 G 和 M 类型的种族加成对不同目标有不同的取值，所以预处理时不包含种族加成
    f64 eff = team[t_a][act].atk *
        team[t_a][act].weapon_atk *
        team[t_a][act].skl_boost *
        atk_boost[t_a] *
        LOC_BOOST[(atk_p - ddg_p + 6) % 6];

    // 普通攻击
    if (type == -1)
        return team[t_b][trg].deal_damage(t_a, act, eff * TYPE_BOOST[team[t_a][act].type][team[t_b][trg].type]);

    // B 型特殊攻击
    if (type == 0)
        return team[t_b][trg].deal_damage(t_a, act, 1.25 * eff * TYPE_BOOST[team[t_a][act].type][team[t_b][trg].type]);

    // 预处理 G 和 M 类型特殊 AoE 攻击的范围
    int trg_l = -1, trg_r = -1;

    // 西边第一个未倒下的角色
    for (int i = INIT_INDEX[trg] - 1; i >= 0; --i)
        if (team[t_b][PLACE[i]].status) {
            trg_l = PLACE[i];
            break;
        }

    // 东边第一个未倒下的角色
    for (int i = INIT_INDEX[trg] + 1; i < 6; ++i)
        if (team[t_b][PLACE[i]].status) {
            trg_r = PLACE[i];
            break;
        }

    // G 型特殊攻击
    if (type == 1) {
        int cand_cnt = (trg_l != -1) + (trg_r != -1) + 1;
        f64 mul = 1.35 / cand_cnt;

        team[t_b][trg].deal_damage(t_a, act, mul * eff * TYPE_BOOST[team[t_a][act].type][team[t_b][trg].type]);
        if (trg_l != -1) team[t_b][trg_l].deal_damage(t_a, act,
                mul * eff * TYPE_BOOST[team[t_a][act].type][team[t_b][trg_l].type]);
        if (trg_r != -1) team[t_b][trg_r].deal_damage(t_a, act,
                mul * eff * TYPE_BOOST[team[t_a][act].type][team[t_b][trg_r].type]);
    }

    // M 型特殊攻击
    else if (type == 2) {
        team[t_b][trg].deal_damage(t_a, act, 1.15 * eff * TYPE_BOOST[team[t_a][act].type][team[t_b][trg].type]);
        if (trg_l != -1) team[t_b][trg_l].deal_damage(t_a, act,
                0.23 * eff * TYPE_BOOST[team[t_a][act].type][team[t_b][trg_l].type]);
        if (trg_r != -1) team[t_b][trg_r].deal_damage(t_a, act,
                0.23 * eff * TYPE_BOOST[team[t_a][act].type][team[t_b][trg_r].type]);
    }
}

int main() {
    scanf("%d %d\n", &member_cnt[0], &member_cnt[1]);

    // 输入南队队员
    for (int i = 1; i <= member_cnt[0]; ++i) {
        team[0][i].input();
        team[0][i].team_fr = 0;
        team[0][i].team_id = i;
    }

    // 输入北队队员
    for (int i = 1; i <= member_cnt[1]; ++i) {
        team[1][i].input();
        team[1][i].team_fr = 1;
        team[1][i].team_id = i;
    }

    scanf("%d\n", &round_cnt);

    for (int RND = 1; RND <= round_cnt; ++RND) {
        int t_a = (RND % 2) ^ 1; // 计算攻击方队伍
        int t_b = (RND % 2); // 计算防御方队伍

        // 对攻击方队伍施放 Weak 类型被动技能
        reapply_passive_skills(t_a);

        // 获取攻击方队伍的当前攻击者
        get_attacker(t_a);
        int active = attacker[t_a];

        char action_type[20];
        int trg;

        scanf("%s target=%d ", action_type, &trg);

        // 施放普通攻击
        if (str(action_type) == "Basicattack") {
            int atk_p, ddg_p;
            scanf("atkpos=%d ddgpos=%d \n", &atk_p, &ddg_p);
            perform_attack(atk_p, ddg_p, active, trg, t_a, t_b);
            team[t_a][active].skl_boost = 1; // 施放攻击之后重置技能加成
        }

        // 施放特殊攻击
        else if (str(action_type) == "Specialattack") {
            int atk_p, ddg_p;
            scanf("atkpos=%d ddgpos=%d \n", &atk_p, &ddg_p);
            perform_attack(atk_p, ddg_p, active, trg, t_a, t_b, team[t_a][active].weapon_type);
            team[t_a][active].skl_boost = 1; // 施放攻击之后重置技能加成
        }

        // 施放主动技能
        else if (str(action_type) == "Skill") // 只有 Average 类型的主动技能是对敌方的
            activate_active_skill(active, trg, t_a, (team[t_a][active].type == 1 ? t_b : t_a));

        // 对防守方队伍中所有收到持续伤害的队员结算持续伤害（同队施放的持续伤害只在同队为攻击方的回合内生效）
        for (int i = 1; i <= member_cnt[t_b]; ++i)
            team[t_b][i].DOT();

        // 先输出北队，再输出南队
        for (int t = 1; ~t; --t) {
            printf("%s: ", t ? "North" : "South");
            for (int i = 0; i < 6; i++)
                if (PLACE[i] <= member_cnt[t]) // 如果队伍不足 6 人就不输出对应位置的生命值
                    printf("%d/%d ", team[t][PLACE[i]].hp, team[t][PLACE[i]].max_hp);
            putchar('\n');
        }

        putchar('\n');
    }

    // 统计是否有队伍获胜
    int alive_cnt[2] = {0, 0};

    for (int t = 0; t < 2; ++t)
        for (int i = 1; i <= member_cnt[t]; ++i)
            if (team[t][i].status || team[t][i].hp)
                ++alive_cnt[t];

    if (!alive_cnt[0])
        puts("Team North won.");
    else if (!alive_cnt[1])
        puts("Team South won.");

    return fflush(stdout), 0;
}
