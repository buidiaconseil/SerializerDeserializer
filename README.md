# SerializerDeserializer

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


