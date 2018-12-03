#pragma once
#include<memory>
#include<string>

class bigInt 
{
public:
	friend bigInt operator +(bigInt& a, bigInt& b) ;
	friend bigInt operator -(bigInt& a, bigInt& b) ;

	bigInt() :innerImpl_("") {};
	//bigInt(bigInt &a);
	bigInt(std::string a); 
	//用来封装可能的细节操作
	std::string get() const ;
	bool set(std::string& bigint) ;
	bool set(std::string&& bigint) ;
	std::uint64_t size()const;
	~bigInt();
private:
	std::string innerImpl_;
	bool checkNum(std::string &bigint);
	bool positive_ = true;
};


