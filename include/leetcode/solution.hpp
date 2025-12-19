#ifndef LEETCODE_SOLUTION_H__
#define LEETCODE_SOLUTION_H__

#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

template <typename Func>
class SolutionBase {
 private:
  struct MetaInfo {
    int id;
    std::string title;
    std::string url;
  } info;

  std::unordered_map<std::string, Func> strategies;
  Func solutionFunc = {nullptr};

 public:
  [[deprecated("Use setMetaInfo(const MetaInfo& metaInfo) instead.")]]
  void setMetaInfo(int id, const std::string& title, const std::string& url) {
    info = {id, title, url};
  }

  void setMetaInfo(const MetaInfo& metaInfo) { info = metaInfo; }

  const MetaInfo& getMetaInfo() const { return info; }

  void registerStrategy(const std::string& name, Func func) {
    if (strategies.find(name) == strategies.end()) {
      strategies[name] = func;
    } else {
      std::ostringstream oss;
      oss << "Strategy name {" << name << "} has already been registered.\n"
          << "Meta Information: \n"
          << "  id: " << info.id << "\n"
          << "  title: " << info.title << "\n"
          << "  url: " << info.url << "\n";
      throw std::invalid_argument(oss.str());
    }
  }

  std::vector<std::string> getStrategyNames() const {
    std::vector<std::string> keys;
    keys.reserve(strategies.size());
    for (const auto& [name, _] : strategies) {
      keys.push_back(name);
    }
    return keys;
  }

  void setStrategy(const std::string& name) {
    auto it = strategies.find(name);
    if (it != strategies.end()) {
      solutionFunc = it->second;
    } else {
      std::ostringstream oss;
      oss << "Invalid strategy name: " << name << "\n"
          << "Problem: [" << info.id << "] " << info.title << "\n"
          << "Available strategies: ";
      bool first = true;
      for (const auto& [strategy_name, _] : strategies) {
        if (!first) oss << ", ";
        oss << strategy_name;
        first = false;
      }
      throw std::invalid_argument(oss.str());
    }
  }

  void setDefaultStrategy() {
    if (!strategies.empty()) {
      solutionFunc = strategies.begin()->second;
    } else {
      throw std::runtime_error("No strategies registered");
    }
  }

  Func getSolution() const {
    if (!solutionFunc) {
      std::ostringstream oss;
      oss << "No strategy selected. Call setStrategy() first.\n"
          << "Problem: [" << info.id << "] " << info.title << "\n"
          << "URL: " << info.url;
      throw std::runtime_error(oss.str());
    }
    return solutionFunc;
  }
};

#endif  // LEETCODE_SOLUTION_H__