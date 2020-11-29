/**
 * Unit tests for agent.
 *
 * Copyright (c) 2020, Sekhar Ravinutala, Jiayue Sun.
 */

#include <gtest/gtest.h>
#include "data/data.h"
#include "dealer/dealer.h"
#include <cstdlib>

// Workaround to access const agents() returned from dealer.
#define AP(i) (new Agent{dealer.agents()[i]})

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
    FERRARI,
    true
  }
};

TEST(Agent, agent){
  Agent agent(AGENTS[0]);
  agent.assign(CUSTOMERS[1]);
  uint32_t wait = agent.assign(CUSTOMERS[1]);
  EXPECT_EQ(int(wait), 180);  // test returned wait time
  EXPECT_EQ(int(agent.closes()), 2);  // test closes
  EXPECT_EQ(agent.revenue(), 513100.0);  // test revenue
  EXPECT_EQ(int(agent.when()), 21600);  // test when
  for (int i = 0; i < 8; i++) {
    agent.assign(CUSTOMERS[1]);
  }
  EXPECT_EQ(int(agent.bonuses()), 1);  // test bonuses
}

