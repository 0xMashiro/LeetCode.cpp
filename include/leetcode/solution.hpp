#ifndef LEETCODE_SOLUTION_H__
#define LEETCODE_SOLUTION_H__

#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

template <typename Func>
class SolutionBase {
 private:
  struct MetaInfo {
    int id;
    std::string title;
    std::string url;
  } info;

 public:
  struct StrategyMetadata {
    std::string name;
    std::string expected = "Accepted";
    std::string time_complexity;
    std::string space_complexity;
    std::vector<std::string> tags;
    std::string notes;
  };

 private:
  struct StrategyEntry {
    StrategyMetadata metadata;
    Func func;
  };

  std::vector<StrategyEntry> strategies;
  std::unordered_map<std::string, size_t> strategyIndex;
  Func solutionFunc = {nullptr};

 public:
  [[deprecated("Use setMetaInfo(const MetaInfo& metaInfo) instead.")]]
  void setMetaInfo(int id, const std::string& title, const std::string& url) {
    info = {id, title, url};
  }

  void setMetaInfo(const MetaInfo& metaInfo) { info = metaInfo; }

  const MetaInfo& getMetaInfo() const { return info; }

  void registerStrategy(const std::string& name, Func func) {
    registerStrategy(StrategyMetadata{.name = name}, std::move(func));
  }

  void registerStrategy(const StrategyMetadata& metadata, Func func) {
    if (metadata.name.empty()) {
      throw std::invalid_argument("Strategy name cannot be empty");
    }
    if (strategyIndex.find(metadata.name) != strategyIndex.end()) {
      std::ostringstream oss;
      oss << "Strategy name {" << metadata.name
          << "} has already been registered.\n"
          << "Meta Information: \n"
          << "  id: " << info.id << "\n"
          << "  title: " << info.title << "\n"
          << "  url: " << info.url << "\n";
      throw std::invalid_argument(oss.str());
    }
    strategyIndex[metadata.name] = strategies.size();
    strategies.push_back({metadata, std::move(func)});
  }

  std::vector<std::string> getStrategyNames() const {
    std::vector<std::string> keys;
    keys.reserve(strategies.size());
    for (const auto& entry : strategies) {
      keys.push_back(entry.metadata.name);
    }
    return keys;
  }

  std::vector<StrategyMetadata> getStrategyMetadata() const {
    std::vector<StrategyMetadata> metadata;
    metadata.reserve(strategies.size());
    for (const auto& entry : strategies) {
      metadata.push_back(entry.metadata);
    }
    return metadata;
  }

  void setStrategy(const std::string& name) {
    auto it = strategyIndex.find(name);
    if (it != strategyIndex.end()) {
      solutionFunc = strategies[it->second].func;
    } else {
      std::ostringstream oss;
      oss << "Invalid strategy name: " << name << "\n"
          << "Problem: [" << info.id << "] " << info.title << "\n"
          << "Available strategies: ";
      bool first = true;
      for (const auto& entry : strategies) {
        if (!first) oss << ", ";
        oss << entry.metadata.name;
        first = false;
      }
      throw std::invalid_argument(oss.str());
    }
  }

  void setDefaultStrategy() {
    if (!strategies.empty()) {
      solutionFunc = strategies.back().func;
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
