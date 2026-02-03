#include "leetcode/problems/minimum-hours-of-training-to-win-a-competition.h"

namespace leetcode {
namespace problem_2383 {

// 贪心策略：分别计算能量和经验所需的训练时间
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution(int initialEnergy, int initialExperience, 
                    vector<int>& energy, vector<int>& experience) {
  int n = energy.size();
  int total_hours = 0;
  
  // 1. 计算能量所需训练时间
  // 需要总能量 > 所有对手能量之和
  int sum_energy = 0;
  for (int e : energy) {
    sum_energy += e;
  }
  // 需要 initialEnergy > sum_energy，即 initialEnergy >= sum_energy + 1
  if (initialEnergy <= sum_energy) {
    total_hours += (sum_energy + 1 - initialEnergy);
    initialEnergy = sum_energy + 1;  // 更新为训练后的能量
  }
  
  // 2. 计算经验所需训练时间
  // 按顺序击败对手
  int current_exp = initialExperience;
  for (int i = 0; i < n; ++i) {
    // 需要 current_exp > experience[i]，即 current_exp >= experience[i] + 1
    if (current_exp <= experience[i]) {
      int need = experience[i] + 1 - current_exp;
      total_hours += need;
      current_exp += need;  // 训练后的经验
    }
    // 击败对手，获得经验
    current_exp += experience[i];
  }
  
  return total_hours;
}

MinimumHoursOfTrainingToWinACompetitionSolution::MinimumHoursOfTrainingToWinACompetitionSolution() {
  setMetaInfo({.id = 2383,
               .title = "Minimum Hours of Training to Win a Competition",
               .url = "https://leetcode.com/problems/minimum-hours-of-training-to-win-a-competition/"});
  registerStrategy("Greedy", solution);
}

int MinimumHoursOfTrainingToWinACompetitionSolution::minNumberOfHours(
    int initialEnergy, int initialExperience, 
    vector<int>& energy, vector<int>& experience) {
  return getSolution()(initialEnergy, initialExperience, energy, experience);
}

}  // namespace problem_2383
}  // namespace leetcode
