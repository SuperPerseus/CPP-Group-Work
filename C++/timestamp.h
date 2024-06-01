#pragma once
#include"include.h"
#include"head.h"


void timestamp() {
	SYSTEMTIME st;
	GetLocalTime(&st);

	std::cout << "print now timestaomp: "
		<< std::setw(4) << std::setfill('0') << st.wYear << "-"
		<< std::setw(2) << std::setfill('0') << st.wMonth << "-"
		<< std::setw(2) << std::setfill('0') << st.wDay << " "
		<< std::setw(2) << std::setfill('0') << st.wHour << ":"
		<< std::setw(2) << std::setfill('0') << st.wMinute << ":"
		<< std::setw(2) << std::setfill('0') << st.wSecond << std::endl;
}
