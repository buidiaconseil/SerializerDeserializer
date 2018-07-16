/*  GPL v3
*/
#pragma once
#include "ApiTest.h"
class SerializerTest : public ApiTest
{
public:
	SerializerTest(void);
	~SerializerTest(void);
	int testInteger();
	int testLong();
	int testDouble();
	int testString();
	int testMixStringLongInt();
	int testAll(){
		return testInteger()+
		testLong()+
		testString()+
		testDouble()+
		testMixStringLongInt();
	}
};
