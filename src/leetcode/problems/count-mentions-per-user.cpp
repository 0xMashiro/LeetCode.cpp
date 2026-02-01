#include "leetcode/problems/count-mentions-per-user.h"

namespace leetcode {
namespace problem_3433 {

static vector<int> solution1(int numberOfUsers, vector<vector<string>>& events) {
  // 按时间戳排序，如果时间戳相同，OFFLINE 事件排在 MESSAGE 前面
  sort(events.begin(), events.end(), [](const vector<string>& a, const vector<string>& b) {
    int timeA = stoi(a[1]);
    int timeB = stoi(b[1]);
    if (timeA != timeB) {
      return timeA < timeB;
    }
    // 时间戳相同，OFFLINE 优先于 MESSAGE
    return a[0] == "OFFLINE" && b[0] == "MESSAGE";
  });

  // mentions[i] 表示用户 i 被提及的次数
  vector<int> mentions(numberOfUsers, 0);
  
  // offlineUntil[i] 表示用户 i 恢复在线的时间（当前时间 >= offlineUntil[i] 时在线）
  // 初始为 0，表示所有用户初始在线
  vector<int> offlineUntil(numberOfUsers, 0);

  for (const auto& event : events) {
    const string& type = event[0];
    int timestamp = stoi(event[1]);

    if (type == "OFFLINE") {
      int userId = stoi(event[2]);
      // 用户从 timestamp 开始离线，到 timestamp + 60 恢复
      offlineUntil[userId] = timestamp + 60;
    } else {  // MESSAGE
      const string& mentionsStr = event[2];

      if (mentionsStr == "ALL") {
        // 提及所有用户
        for (int i = 0; i < numberOfUsers; i++) {
          mentions[i]++;
        }
      } else if (mentionsStr == "HERE") {
        // 提及所有在线用户
        for (int i = 0; i < numberOfUsers; i++) {
          if (timestamp >= offlineUntil[i]) {
            mentions[i]++;
          }
        }
      } else {
        // 解析 idX idY ... 格式
        // 使用 stringstream 分割字符串
        stringstream ss(mentionsStr);
        string token;
        while (ss >> token) {
          // token 格式为 "id<number>"
          int userId = stoi(token.substr(2));  // 跳过 "id" 前缀
          mentions[userId]++;
        }
      }
    }
  }

  return mentions;
}

CountMentionsPerUserSolution::CountMentionsPerUserSolution() {
  setMetaInfo({.id = 3433,
               .title = "Count Mentions Per User",
               .url = "https://leetcode.com/problems/count-mentions-per-user/"});
  registerStrategy("Sort and Simulate", solution1);
}

vector<int> CountMentionsPerUserSolution::countMentions(int numberOfUsers, vector<vector<string>>& events) {
  return getSolution()(numberOfUsers, events);
}

}  // namespace problem_3433
}  // namespace leetcode
