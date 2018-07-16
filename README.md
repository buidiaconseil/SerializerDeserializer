# SerializerDeserializer

A simple tool developed to serializeand deserialize type to a file.
Support long, int, double and string. Association of different type permit to create a more complex object.


# can be serialized on istream/ostream and files

        void saveFile (std::string);
	void readFile (std::string);
	friend std::istream& operator>> (std::istream& out, Serializer& per);
	friend std::ostream& operator<< (std::ostream& out, Serializer& per);

## Sample Code

### test int 

```java
#include "Serializer.h"

void tests(){
  Serializer aa;
	int pp=45544;
	
	aa<<pp;
	int returne;
	aa>>returne;
	
	if (pp!=returne)
	{
		std::cout <<"Error testInteger: << "<<pp<<" != >>"<<returne<<std::endl;
	}
	else
	{
		std::cout <<"Ok testInteger "<<std::endl;
		
  }
 }
```

### test long

```java
#include "Serializer.h"

void tests(){
  Serializer aa;
  long pp=(unsigned long)455445455l;
	
	aa<<pp;
	long returne;
	aa>>returne;
	
	if (pp!=returne)
	{
		std::cout <<"Error testLong: << "<<pp<<" != >>"<<returne<<std::endl;
	}
	else
	{
		std::cout <<"Ok testLong "<<std::endl;
  }
}
```
### Test double

```java
#include "Serializer.h"

void tests(){
	Serializer aa;
	double pp=45.4515454545115454;
	
	aa<<pp;
	double returne;
	aa>>returne;
	
	if (pp!=returne)
	{
		std::cout.precision(15);
		std::cout <<"Error testDouble: << "<<pp<<" != >>"<<returne<<std::endl;
	}
	else
	{
		std::cout <<"Ok testDouble "<<std::endl;
	}
}
```

### Test string
```java
#include "Serializer.h"

void tests(){
	Serializer aa;
	std::string ee="Un test pokkklke3334éezazeza";
	
	aa<<ee;
	std::string returne;
	aa>>returne;
	
	if (ee!=returne)
	{
		std::cout <<"Error testString: << "<<ee<<" != >>"<<returne<<std::endl;
	}
	else
	{
		std::cout <<"Ok testString "<<std::endl;
	}
}
```

### Test mix of different formats
```java
#include "Serializer.h"

void tests(){
	Serializer aa;
	long a1=(unsigned long)499465645l; 
	std::string a2="Un test pokkklke3334éezazeza";
	int a3=(unsigned int)60654; 
	aa<<a1;
	aa<<a3;
	aa<<a2;
	long r1; 
	std::string r2;
	int r3; 
	aa>>r1;
	aa>>r3;
	aa>>r2;
	if (a1!=r1&&a2!=r2&&a3!=r3)
	{
		std::cout <<"Error testMixStringLongInt: << "<<a1<<":"<<a2<<":"<<a3<<" != >>"<<r1<<":"<<r2<<":"<<r3<<std::endl;
	}
	else
	{
		std::cout <<"Ok testMixStringLongInt "<<std::endl;
	}
}
