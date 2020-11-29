/**
 * Generate report for an integration test.
 *
 * Copyright (c) 2020, Sekhar Ravinutala, Jiayue Sun.
 */

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <numeric>

#include "data/data.h"
#include "dealer/dealer.h"

#define COMMISSION 10000.0
#define BONUS 100000.0

int main() {
  Dealer dealer(agentInfos(5));
  std::vector<uint32_t> waits;

  for (CustomerInfo& ci : customerInfos(100)) {
    waits.push_back(dealer.assign(ci));
  }
  std::sort(waits.begin(), waits.end());
  int waitsSize = waits.size();
  int waitsMid = waitsSize / 2;
  double mean = std::accumulate(waits.begin(), waits.end(), .0) / waitsSize;
  double median = (waitsSize % 2 == 0)
                      ? (waits[waitsMid - 1] + waits[waitsMid]) / 2.0
                      : waits[waitsMid];
  // difference of x - mean;
  std::vector<double> diff(waitsSize);
  std::transform(waits.begin(), waits.end(), diff.begin(),
                 [mean](double x) { return x - mean; });
  // sum of squares of differences
  double squareSum =
      std::inner_product(diff.begin(), diff.end(), diff.begin(), .0);
  // standard deviation
  double stdDev = std::sqrt(squareSum / waitsSize);
  printf(
      "----------------------------------------------------------------------"
      "\n");
  printf("Mean/mins      Median/mins    Standard Deviation\n");
  printf("\n");
  printf("%-15.0lf%-15.0lf%.2lf\n", mean, median, stdDev);
  printf(
      "----------------------------------------------------------------------"
      "\n");
  std::vector<Agent> agentList(dealer.agents());
  std::vector<int> agentIndices;  // to sort by agent ID
  for (int i = 0; i < int(agentList.size()); i++) {
    agentIndices.push_back(i);
  }
  std::sort(agentIndices.begin(), agentIndices.end(),
            [&agentList](const int& a, const int& b) {
              return agentList[a].info.agentId < agentList[b].info.agentId;
            });
  printf("Agent ID       Deals Closed   Revenue        Commission     Bonus\n");
  printf("\n");
  for (auto i : agentIndices) {
    printf("%-15d%-15u$%-14.2lf$%-14.2lf$%.2lf\n", agentList[i].info.agentId,
           agentList[i].closes(), agentList[i].revenue(),
           agentList[i].closes() * COMMISSION, agentList[i].bonuses() * BONUS);
  }
  printf(
      "----------------------------------------------------------------------"
      "\n");
}
