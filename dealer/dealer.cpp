/**
 * Dealer implementation.
 *
 * Copyright (c) 2020, Sekhar Ravinutala, Jiayue Sun.
 */

#include "dealer/dealer.h"

#include <algorithm>
#include <cmath>

#include "data/data.h"

#define S(a, c)                                  \
  (10 * std::min(c.arrivalTime - a.when(), 0L) + \
   a.info.expertise.at(c.interest) + a.info.rating)

Dealer::Dealer(const std::vector<AgentInfo>& aInfos) {
  for (auto info : aInfos) {
    _agents.push_back(Agent(info));
  }
}

uint32_t Dealer::assign(const CustomerInfo& cInfo) {
  std::vector<int> agentIndices;  // to be sorted by macro S
  for (int i = 0; i < int(_agents.size()); i++) {
    agentIndices.push_back(i);
  }
  std::sort(agentIndices.begin(), agentIndices.end(),
  [&](const int& a, const int& b) {
    return S(_agents[a], cInfo) > S(_agents[b], cInfo);
  });
  return _agents[agentIndices[0]].assign(cInfo);
}

const std::vector<Agent> Dealer::agents() { return _agents; }
