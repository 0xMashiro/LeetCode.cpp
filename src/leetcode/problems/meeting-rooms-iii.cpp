#include "leetcode/problems/meeting-rooms-iii.h"

namespace leetcode {
namespace problem_2402 {

// Strategy 1: Two heaps with wait queue
// 使用两个堆（空闲房间堆、使用中房间堆）和一个等待队列模拟
// 时间复杂度: O(m log n), 空间复杂度: O(n + m)
static int solution1(int n, vector<vector<int>>& meetings) {
  // 按开始时间排序会议
  sort(meetings.begin(), meetings.end());
  
  // 空闲房间堆（最小房间编号优先）
  priority_queue<int, vector<int>, greater<int>> freeRooms;
  for (int i = 0; i < n; ++i) {
    freeRooms.push(i);
  }
  
  // 使用中房间堆（按结束时间排序，如果结束时间相同则按房间编号排序）
  // 使用 pair<long long, int> 存储 (结束时间, 房间编号)
  priority_queue<pair<long long, int>, vector<pair<long long, int>>, 
                 greater<pair<long long, int>>> usedRooms;
  
  // 等待队列（先进先出，存储原始开始时间和持续时间）
  queue<pair<int, int>> waitQueue;
  
  // 每个房间举办会议的次数
  vector<int> count(n, 0);
  
  // 处理所有会议
  for (const auto& m : meetings) {
    int start = m[0];
    int end = m[1];
    int duration = end - start;
    
    // 释放所有在当前会议开始时间之前或同时结束的房间
    while (!usedRooms.empty() && usedRooms.top().first <= start) {
      int room = usedRooms.top().second;
      usedRooms.pop();
      freeRooms.push(room);
    }
    
    // 如果有空闲房间，先分配等待队列中的会议（按原始开始时间顺序）
    while (!waitQueue.empty() && !freeRooms.empty()) {
      auto [wStart, wDuration] = waitQueue.front();
      waitQueue.pop();
      
      int room = freeRooms.top();
      freeRooms.pop();
      ++count[room];
      
      // 等待会议的开始时间就是当前时间 start（因为房间刚释放）
      long long newEnd = start + wDuration;
      usedRooms.push({newEnd, room});
    }
    
    // 处理当前会议
    if (freeRooms.empty()) {
      // 没有空闲房间，加入等待队列
      waitQueue.push({start, duration});
    } else {
      // 分配空闲房间中编号最小的房间
      int room = freeRooms.top();
      freeRooms.pop();
      ++count[room];
      
      long long newEnd = start + duration;
      usedRooms.push({newEnd, room});
    }
  }
  
  // 处理剩余的等待会议
  while (!waitQueue.empty()) {
    // 获取最早结束的房间时间
    long long freeTime = usedRooms.top().first;
    
    // 释放所有在 freeTime 时刻结束的房间
    while (!usedRooms.empty() && usedRooms.top().first <= freeTime) {
      int room = usedRooms.top().second;
      usedRooms.pop();
      freeRooms.push(room);
    }
    
    // 分配等待会议
    while (!waitQueue.empty() && !freeRooms.empty()) {
      auto [wStart, wDuration] = waitQueue.front();
      waitQueue.pop();
      
      int room = freeRooms.top();
      freeRooms.pop();
      ++count[room];
      
      long long newEnd = freeTime + wDuration;
      usedRooms.push({newEnd, room});
    }
  }
  
  // 找出举办会议最多的房间（如果有多个，取编号最小的）
  int maxRoom = 0;
  for (int i = 1; i < n; ++i) {
    if (count[i] > count[maxRoom]) {
      maxRoom = i;
    }
  }
  return maxRoom;
}

// Strategy 2: Priority queue simulation (no explicit wait queue)
// 使用两个堆，并将会议按原始开始时间排序，模拟时间推进
// 时间复杂度: O(m log n), 空间复杂度: O(n + m)
static int solution2(int n, vector<vector<int>>& meetings) {
  // 按开始时间排序会议
  sort(meetings.begin(), meetings.end());
  
  // 空闲房间堆（最小房间编号优先）
  priority_queue<int, vector<int>, greater<int>> freeRooms;
  for (int i = 0; i < n; ++i) {
    freeRooms.push(i);
  }
  
  // 使用中房间堆（按结束时间排序，如果结束时间相同则按房间编号排序）
  // 使用 pair<long long, int> 存储 (结束时间, 房间编号)
  priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                 greater<pair<long long, int>>> usedRooms;
  
  // 每个房间举办会议的次数
  vector<int> count(n, 0);
  
  // 当前时间，从0开始
  long long currentTime = 0;
  
  // 按顺序处理每个会议
  for (const auto& m : meetings) {
    int start = m[0];
    int end = m[1];
    int duration = end - start;
    
    // 更新当前时间到当前会议的开始时间（如果当前时间更小）
    if (currentTime < start) {
      currentTime = start;
    }
    
    // 释放所有在当前时间之前或同时结束的房间
    while (!usedRooms.empty() && usedRooms.top().first <= currentTime) {
      int room = usedRooms.top().second;
      usedRooms.pop();
      freeRooms.push(room);
    }
    
    // 如果仍然没有空闲房间，需要推进时间到最早结束的房间时间
    if (freeRooms.empty()) {
      long long earliestEnd = usedRooms.top().first;
      currentTime = earliestEnd;
      
      // 再次释放所有在当前时间之前结束的房间
      while (!usedRooms.empty() && usedRooms.top().first <= currentTime) {
        int room = usedRooms.top().second;
        usedRooms.pop();
        freeRooms.push(room);
      }
    }
    
    // 此时肯定有空闲房间
    int room = freeRooms.top();
    freeRooms.pop();
    ++count[room];
    
    // 会议的开始时间是 currentTime，结束时间是 currentTime + duration
    long long newEnd = currentTime + duration;
    usedRooms.push({newEnd, room});
  }
  
  // 找出举办会议最多的房间（如果有多个，取编号最小的）
  int maxRoom = 0;
  for (int i = 1; i < n; ++i) {
    if (count[i] > count[maxRoom]) {
      maxRoom = i;
    }
  }
  return maxRoom;
}

MeetingRoomsIiiSolution::MeetingRoomsIiiSolution() {
  setMetaInfo({.id = 2402,
               .title = "Meeting Rooms III",
               .url = "https://leetcode.com/problems/meeting-rooms-iii"});
  registerStrategy("Two Heaps with Wait Queue", solution1);
  registerStrategy("Priority Queue Simulation", solution2);
}

int MeetingRoomsIiiSolution::mostBooked(int n, vector<vector<int>>& meetings) {
  return getSolution()(n, meetings);
}

}  // namespace problem_2402
}  // namespace leetcode