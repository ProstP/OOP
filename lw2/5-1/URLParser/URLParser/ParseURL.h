#pragma once
#include "Protocol.h"
#include <iostream>

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document);