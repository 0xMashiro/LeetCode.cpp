#include "leetcode/problems/process-tasks-using-servers.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1882 {

class ProcessTasksUsingServersTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ProcessTasksUsingServersSolution solution;
};

TEST_P(ProcessTasksUsingServersTest, Example1) {
  vector<int> servers = {3, 3, 2};
  vector<int> tasks = {1, 2, 3, 2, 1, 2};
  vector<int> expected = {2, 2, 0, 2, 1, 2};
  EXPECT_EQ(expected, solution.assignTasks(servers, tasks));
}

TEST_P(ProcessTasksUsingServersTest, Example2) {
  vector<int> servers = {5, 1, 4, 3, 2};
  vector<int> tasks = {2, 1, 2, 4, 5, 2, 1};
  vector<int> expected = {1, 4, 1, 4, 1, 3, 2};
  EXPECT_EQ(expected, solution.assignTasks(servers, tasks));
}

TEST_P(ProcessTasksUsingServersTest, SingleServer) {
  // 只有一个服务器
  vector<int> servers = {10};
  vector<int> tasks = {1, 2, 3, 4};
  vector<int> expected = {0, 0, 0, 0};
  EXPECT_EQ(expected, solution.assignTasks(servers, tasks));
}

TEST_P(ProcessTasksUsingServersTest, SingleTask) {
  // 只有一个任务
  vector<int> servers = {5, 3, 1};
  vector<int> tasks = {10};
  vector<int> expected = {2};  // weight 最小的服务器索引是 2
  EXPECT_EQ(expected, solution.assignTasks(servers, tasks));
}

TEST_P(ProcessTasksUsingServersTest, MoreServersThanTasks) {
  // 服务器比任务多
  vector<int> servers = {1, 2, 3, 4, 5};
  vector<int> tasks = {1, 2};
  vector<int> expected = {0, 0};  // weight 最小的服务器是 0
  EXPECT_EQ(expected, solution.assignTasks(servers, tasks));
}

TEST_P(ProcessTasksUsingServersTest, SameWeight) {
  // 相同权重的服务器，选择索引小的，然后循环使用
  vector<int> servers = {5, 5, 5};
  vector<int> tasks = {1, 1, 1, 1};
  // 任务0时间0分配服务器0，时间1释放
  // 任务1时间1分配服务器0（已释放）或服务器1，按题目应该优先使用空闲的weight最小的
  // 由于都在时间1空闲，weight相同，选index小的，所以是0
  // 但期望是 {0, 1, 2, 0}，说明我理解有误
  // 重新理解：时间1时服务器0刚释放，任务1加入，应该在所有空闲服务器中选
  // 实际上服务器0、1、2都在空闲状态，选weight最小(都是5)，然后选index最小(0)
  // 但期望是1，说明我理解错了...
  // 哦，仔细看题目例子2：时间2服务器1和4都释放，任务2分配给了服务器1
  // 这说明当多个服务器同时空闲时，是按照index顺序分配的吗？
  // 不对，再看例子1：时间5三个服务器都空闲，任务5分配给了服务器2（weight最小）
  // 例子2：时间2服务器1(weight1)和4(weight2)都空闲，任务2分配给了服务器1（weight最小）
  // 所以策略是对的，但为什么SameWeight期望是{0,1,2,0}？
  // 等等，让我重新模拟：
  // 时间0: 任务0分配给服务器0，服务器0在时间1释放
  // 时间1: 任务1加入，服务器0在时间1释放，此时检查：服务器0即将释放，服务器1、2空闲
  // 但代码逻辑是在分配前释放，所以服务器0会被放入available，然后三个都可选
  // 选weight最小(5)，然后index最小(0) -> 应该是0
  // 但期望是1... 让我再看看题目
  
  // 实际上题目描述的SameWeight情况下的期望输出就是{0,1,2,0}
  // 这是因为当服务器0在时间1释放后，任务1加入，此时所有服务器都可用
  // 但服务器0刚刚被使用过，应该轮到服务器1？不对，题目说选weight最小...
  // 实际上我理解错了，让我仔细重读题目
  
  // "the task in the front of the queue will be assigned to a free server with the smallest weight"
  // 所以确实是选weight最小的，weight相同选index最小的
  // 那为什么期望是{0,1,2,0}呢？
  
  // 哦！我找到了问题。题目说的是"free server"，而服务器0在时间1才释放
  // 如果任务1在时间1加入，服务器0是在时间1释放，那它是在任务加入前释放还是后释放？
  // "At second j, the jth task is inserted into the queue"
  // "A server that is assigned task j at second t will be free again at second t + tasks[j]"
  // 服务器0在时间0分配任务，时间1释放。任务1在时间1加入。
  // 问题是在时间1加入任务1之前还是之后检查服务器释放？
  
  // 根据题目描述，应该是任务先加入队列，然后分配。所以：
  // 时间1：任务1加入队列，然后检查哪些服务器空闲
  // 服务器0在时间1释放，所以它现在空闲了
  // 三个服务器都空闲(weight都是5)，选index最小的0
  // 结果应该是{0,0,0,0}，但期望是{0,1,2,0}
  
  // 这说明我理解还是有误。也许测试用例期望不对？或者我理解错题目了？
  // 让我看看LeetCode原题的输出...
  // 实际上原题没有SameWeight这个测试用例，这是我自己加的
  // 按照题目逻辑，{0,0,0,0}应该是正确的输出
  // 但让我再仔细看看... 也许是我代码的问题
  
  // 重新思考：例子2中
  // 时间0任务0分配给服务器1(weight1)
  // 时间1任务1分配给服务器4(weight2) 
  // 时间2任务2加入，此时服务器1和4都在时间2释放
  // 分配给了服务器1(weight1最小)
  // 
  // 所以策略是对的：选weight最小，相同选index最小
  // 那SameWeight的情况下，三个服务器weight都是5
  // 每次都选index最小的0，结果应该是{0,0,0,0}
  
  // 但等等，让我再仔细看例子1：
  // 服务器[3,3,2]，任务[1,2,3,2,1,2]
  // 输出[2,2,0,2,1,2]
  // 时间0: 任务0分配给服务器2(weight2最小) -> 2 ✓
  // 时间1: 任务1加入，服务器2在时间1释放(0+1=1)，分配给它 -> 2 ✓
  // 时间2: 任务2加入，服务器2忙到时间3，服务器0、1空闲，weight都是3，选index0 -> 0 ✓
  // 时间3: 任务3加入，服务器2释放，服务器0忙到时间5，服务器1空闲(weight3)，服务器2空闲(weight2)
  //        weight最小是2，分配给服务器2 -> 2 ✓
  // 时间4: 任务4加入，服务器1空闲，分配给它 -> 1 ✓
  // 时间5: 任务5加入，三个服务器都释放，weight最小是2(服务器2)，分配给它 -> 2 ✓
  // 
  // 所以我的理解是正确的！
  // SameWeight测试用例期望{0,1,2,0}可能是错误的，或者我理解错了什么
  // 让我修改测试用例为正确期望值{0,0,0,0}
  vector<int> expected = {0, 0, 0, 0};
  EXPECT_EQ(expected, solution.assignTasks(servers, tasks));
}

TEST_P(ProcessTasksUsingServersTest, LongTasks) {
  // 任务很长，需要等待
  vector<int> servers = {1, 2};
  vector<int> tasks = {100000, 100000, 100000};
  vector<int> expected = {0, 1, 0};  // 第三个任务需要等待服务器 0
  EXPECT_EQ(expected, solution.assignTasks(servers, tasks));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ProcessTasksUsingServersTest,
    ::testing::ValuesIn(ProcessTasksUsingServersSolution().getStrategyNames()));

}  // namespace problem_1882
}  // namespace leetcode
