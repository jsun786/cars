/**
 * Agent implementation.
 *
 * Copyright (c) 2020, Sekhar Ravinutala, Jiayue Sun.
 */

#include "dealer/agent.h"

#include <algorithm>

const uint32_t DEALS_FOR_BONUS = 10;  // deals required for bonus

Agent::Agent(const AgentInfo &aInfo) : info(aInfo) {}

uint32_t Agent::closes() { return _closes; }

double Agent::revenue() { return _revenue; }

uint16_t Agent::bonuses() { return _bonuses; }

std::time_t Agent::when() { return _when; }

uint32_t Agent::assign(const CustomerInfo &cInfo) {
  time_t begin = std::max(_when, cInfo.arrivalTime);
  _when = update(begin, info.serviceTime * 3600);

  if (_sunday == 0) {
    _sunday = update(begin, 0, true);
  }
  if (cInfo.saleClosed) {
    _closes += 1;
    _revenue += PRICES[cInfo.interest];
    _weekCloses += 1;
    if (_weekCloses == DEALS_FOR_BONUS) {
      _bonuses += 1;
    }
  }
  if (_when == _sunday) {
    _weekCloses = 0;
    _sunday = update(_sunday, 0, true);
  }

  return (begin - cInfo.arrivalTime) / 60;
}
