#ifndef TEST_OP_IO_H
#define TEST_OP_IO_H

#include "../my_string.h"
#include "test_logger.h"

#include <sstream>

void test_op_io()
{
	logger(info, "IO TESTS");
	std::string test_name;
	// TEST 1
	test_name = "TEST 1 - INPUT LONG STRING";
	MyString s1;
    std::string input_str(4000, 'a');
	std::stringstream stream1(input_str.c_str());
    stream1 >> s1;
	log_assertion(s1.length() == 4000 && strcmp(s1.c_str(), input_str.c_str()) == 0, test_name);
	// TEST 2
	test_name = "TEST 2 - OUTPUT STRING";
	MyString s2("Hello");
	std::stringstream stream2;
    stream2 << s2;
	log_assertion(strcmp(stream2.str().c_str(), "Hello") == 0, test_name);
}

#endif // !TEST_OP_IO_H
