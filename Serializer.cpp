/*  GPL v3
*/
#include "StdAfx.h"
#include "Serializer.h"
#ifdef __CYGWIN32__
#include <stdio.h>
#include <stdlib.h>
#else
#ifdef WIN32
#else
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#endif
#endif
Serializer::Serializer(){
	INT_TYPE=0x01;
	LONG_TYPE=0x02;
	STRING_TYPE=0x03;
	DOUBLE_TYPE=0x04;
	size_=0;
	data_=NULL;
}
Serializer::~Serializer(){
	if (data_!=NULL)
		free(data_);
}
void Serializer::addEnd( unsigned char &a){
	unsigned char *mdat=(unsigned char *)malloc(size_+1);
	
	memcpy ( mdat, data_, size_ );
	mdat[size_]=a;
	unsigned char *todel=data_;
	data_=mdat;
	if (todel!=NULL)
	{
		free(todel);	
	}
	size_++;
}
unsigned char Serializer::readBegin(){
	unsigned char *mdat=(unsigned char *)malloc(size_-1);
	unsigned char ret=data_[0];
	size_t i=1;
	for (i=1;i<size_;i++)
	{
		mdat[i-1]=data_[i];
	}
	
	unsigned char *todel=data_;
	data_=mdat;
	free(todel);
	size_--;
	if (size_==0) data_=NULL;
	return ret;
}

unsigned char Serializer::verifyBegin(){
	if (data_==NULL||size_==0) return 0;

	return data_[0];
}

Serializer &Serializer::operator <<(const bool & b) {
	if (b)
	{
		*this<<1;
	}
	else
	{
		*this<<0;
	}
	return *this;
}
Serializer &Serializer::operator <<(const int & b) {
	addEnd(INT_TYPE);
	char str[100]; 
	
#ifdef __CYGWIN32__
	sprintf(str, "%d", b);

	
#else
#ifdef WIN32
	_itoa_s(b, str,100, 10);
#else
	sprintf(str, "%d", b);
#endif
#endif
	

	
	int i=0;
	
	while (str[i]!=0)
	{
		unsigned char tzz=(unsigned char)str[i];
		addEnd( tzz);
		i++;
	}
	unsigned char tzzz=0;
	addEnd( tzzz);
	/*
	int n=0;
	for (n=0;n< sizeof( b ); n++)
	{
		unsigned int r=b>>(n*8);
		unsigned char f =*reinterpret_cast<unsigned char *>(& r);
		//char f=(char)r& 0xff;
		addEnd( f);
	}*/
	return *this;
    
}
Serializer &Serializer::operator <<(const long & b) {
	addEnd(LONG_TYPE);
	char str[200]; 
#ifdef __CYGWIN32__
	sprintf(str, "%ld", b);

	
#else
#ifdef WIN32
	_ltoa_s(b, str,200, 10);
#else
	sprintf(str, "%ld", b);
#endif
#endif
	
	
	int i=0;
	
	while (str[i]!=0)
	{
		unsigned char tzz=(unsigned char)str[i];
		addEnd( tzz);
		i++;
	}
	unsigned char tzzz=0;
	addEnd( tzzz);
	/*
	int n=0;
	for (n=0;n< sizeof( b ); n++)
	{
		unsigned long r=b>>(n*8);
		unsigned char f =*reinterpret_cast<unsigned char *>(& r);
		//char f=(char)r& 0xff;
		addEnd( f);
	}*/
	return *this;
}

Serializer &Serializer::operator <<(const double & b) {
	addEnd(DOUBLE_TYPE);
	char str[200]; 
#ifdef __CYGWIN32__
	sprintf (str,"%30.30e",  b);

	
#else
#ifdef WIN32
	sprintf_s (str, 200,"%30.30e",  b);
#else
	sprintf (str,"%30.30e",  b);
#endif
#endif

	
	
	int i=0;
	
	while (str[i]!=0)
	{
		unsigned char tzz=(unsigned char)str[i];
		addEnd( tzz);
		i++;
	}
	unsigned char tzzz=0;
	addEnd( tzzz);
	return *this;
}

Serializer &Serializer::operator <<(const std::string & b) {
	addEnd(STRING_TYPE);
	unsigned int n=0;
	*this<<(int)b.length();
	for (n=0;n< b.length(); n++)
	{
		char e=b.at(n);
		unsigned char f =(unsigned char)e;
		addEnd( f);
	}
	return *this;
}
	
Serializer &Serializer::operator >>(  bool  &b) {
	int hy=0;
	*this>>hy;
	if (hy!=0)
	{
		b=true;
	}
	else
	{
		b=false;
	}
	return *this;
}



Serializer &Serializer::operator >>(  int  &b) {

	if (verifyBegin()!=INT_TYPE) {
		return *this;
	}
	
    
	std::string number="";
	unsigned char l= readBegin();
	while (l!=0)
	{
		number+=(char)l;
		l= readBegin();
	}
	b = atoi (number.c_str());

	return *this;

}

Serializer &Serializer::operator >>(  long & b) {
	if (verifyBegin()!=LONG_TYPE) {
		return *this;
	}
	
	std::string number="";
	unsigned char l= readBegin();
	while (l!=0)
	{
		number+=(char)l;
		l= readBegin();
	}
	b = atol (number.c_str());
	return *this;
}

Serializer &Serializer::operator >>(  double & b) {
	if (verifyBegin()!=DOUBLE_TYPE) {
		return *this;
	}
	
	
	std::string number="";
	unsigned char l= readBegin();
	while (l!=0)
	{
		number+=(char)l;
		l= readBegin();
	}
	
	b = atof (number.c_str());
	return *this;
}

Serializer &Serializer::operator >>( std::string & b) {
	if (verifyBegin()!=STRING_TYPE) {
		return *this;
	}
	
	int sizeStr=0;
	*this>>sizeStr;
	int n=0;
	for (n=0; n<sizeStr; n++)
	{
		char a=(char)readBegin();
		b+=a;
	}
	
	return *this;
}
	

	
std::istream&  operator>> (std::istream& in, Serializer& per)

{
	
	in >> per.data_;

	return in;

}

std::ostream&  operator<< (std::ostream& in, Serializer& per)

{
	in << per.data_;
	return in;

}

void Serializer::saveFile (std::string filename){
	FILE * pFile;

#ifdef __CYGWIN32__
	pFile=fopen ( filename.c_str(), "wb" );
#else
#ifdef WIN32
	fopen_s ( &pFile,filename.c_str(), "wb" );
#else
	pFile=fopen ( filename.c_str(), "wb" );
#endif
#endif
	
	fwrite (data_ , 1 , size_ , pFile );
	fclose (pFile);


}
void Serializer::readFile (std::string filename){
	FILE * pFile;
	long lSize;
	size_t result;
	
#ifdef __CYGWIN32__
	pFile=fopen ( filename.c_str(), "rb" );
#else
#ifdef WIN32
	fopen_s ( &pFile,filename.c_str(), "rb" );
#else
	pFile=fopen ( filename.c_str(), "rb" );
#endif
#endif
	
	if (pFile==NULL) {fputs ("File error",stderr); return;};
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);

	// allocate memory to contain the whole file:
	if (data_!=NULL)
		free(data_);
	data_ = (unsigned char*) malloc (sizeof(char)*lSize);
	if (data_ == NULL) {fputs ("Memory error",stderr); return;}
	// copy the file into the buffer:
	result = fread (data_,1,lSize,pFile);
	if (result != lSize) {fputs ("Reading error",stderr); return;}
	/* the whole file is now loaded in the memory buffer. */
	// terminate
	fclose (pFile);
	size_=lSize;

}
	

