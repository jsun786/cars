/**
 * Unit tests for dealer.
 *
 * Copyright (c) 2020, Sekhar Ravinutala, Jiayue Sun.
 */

#include <gtest/gtest.h>
#include "data/data.h"
#include "dealer/dealer.h"

const AgentInfo AGENTS[] = {
  {
    223432,
    {
      {FERRARI, 3},
      {LAMBORGHINI, 2},
      {MCLAREN, 2},
      {PORSCHE, 4}
    },
    3,
    0.5
  },
  {
    223433,
    {
      {FERRARI, 2},
      {LAMBORGHINI, 1},
      {MCLAREN, 1},
      {PORSCHE, 3}
    },
    1,
    0.5
  },
  {
    223434,
    {
      {FERRARI, 3},
      {LAMBORGHINI, 2},
      {MCLAREN, 2},
      {PORSCHE, 4}
    },
    3,
    0.6
  }
};
const CustomerInfo CUSTOMERS[] = {
  {
    std::time(NULL),
    FERRARI,
    true
  },
  {
    0,
    PORSCHE,
    true
  }
};

TEST(Dealer, dealer) {
  std::vector<AgentInfo> agentInfo(AGENTS,
                                AGENTS + sizeof(AGENTS) / sizeof(AgentInfo));
  Dealer dealer(agentInfo);
  uint32_t wait = dealer.assign(CUSTOMERS[1]);
  EXPECT_EQ(int(wait), 0);  // test the returned wait time

  // Test if the agent of highest expertise and rating is matched
  std::vector<Agent> dealerAgents(dealer.agents());
  EXPECT_TRUE(int(dealerAgents[0].when()) == 0);
  EXPECT_TRUE(int(dealerAgents[1].when()) == 0);
  EXPECT_FALSE(int(dealerAgents[2].when()) == 0);

  // Test if the next available agent is matched
  dealer.assign(CUSTOMERS[1]);
  dealer.assign(CUSTOMERS[1]);
  dealer.assign(CUSTOMERS[1]);
  std::vector<Agent> dealerAgents1(dealer.agents());
  EXPECT_EQ(int(dealerAgents1[0].closes()), 1);
  EXPECT_EQ(int(dealerAgents1[1].closes()), 2);
  EXPECT_EQ(int(dealerAgents1[2].closes()), 1);

}
