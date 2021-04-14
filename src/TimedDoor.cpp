// Copyright 2021 Ilya Urtyukov
#include<time.h>
#include<string>

#include "TimedDoor.h"

TimedDoor::TimedDoor(int time) {
    iTimeout = time;
    opened = false;
    adapter = new DoorTimerAdapter(*this);
}

bool TimedDoor::isDoorOpened() {
  return opened;
}

void TimedDoor::unlock() {
  this->opened = true;
  adapter->Timeout();
}

void TimedDoor::lock() {
  opened = false;
}

void TimedDoor::DoorTimeOut() const {
  throw std::string("close the door!");
}

void TimedDoor::throwState() {
  if (!opened)
    throw std::string("the door is closed!");
}

int TimedDoor::getTime() const {
  return iTimeout;
}

DoorTimerAdapter::DoorTimerAdapter(TimedDoor& a) {
  door = a;
}

void Timer::sleep(int t) {
  time_t tic = clock();
  while (clock() < tic + t * CLOCKS_PER_SEC) {}
}

void Timer::tregister(int time, TimerClient* timer) {
  sleep(time);
}

void DoorTimerAdapter::Timeout() {
  Timer t;
  t.tregister(door.getTime(), this);
  door.DoorTimeOut();
}


