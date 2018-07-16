/*  
GPL v3 
*/
#pragma once
#include <string>
#include <iostream>

class Serializer
{
	public:
	Serializer();
	~Serializer();
	Serializer &operator <<(const bool  &b) ;
	Serializer &operator <<(const int  &b) ;
	Serializer &operator <<(const long  &b) ;
	Serializer &operator <<(const double  &b) ;
	Serializer &operator <<(const std::string & b) ;


	Serializer &operator >>( bool  &b) ;
	Serializer &operator >>( int  &b) ;
	Serializer &operator >>( long  &b) ;
	Serializer &operator >>( double  &b) ;
	Serializer &operator >>( std::string & b) ;

	void saveFile (std::string);
	void readFile (std::string);
	friend std::istream& operator>> (std::istream& out, Serializer& per);
	friend std::ostream& operator<< (std::ostream& out, Serializer& per);
	
private :
	unsigned char INT_TYPE;
	unsigned char LONG_TYPE;
	unsigned char STRING_TYPE;
	unsigned char DOUBLE_TYPE;
	unsigned char *data_;
	size_t size_; 
	void addEnd( unsigned char &);
	unsigned char readBegin();
	unsigned char verifyBegin();
};
