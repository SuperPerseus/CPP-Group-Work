#pragma once
#include"include.h"

class Reserve {//预订票
public:
    Reserve();
    ~Reserve();
};

class Viewing {//没有必要，可以合并到reservation
public:
    Viewing();
    ~Viewing();
};

class Reservation {
public:
    Reservation();
    ~Reservation();
};

class Payment {
public:
    Payment();
    ~Payment();
};

class Refund {
public:
    Refund();
    ~Refund();
};