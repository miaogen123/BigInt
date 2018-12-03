#pragma once
#include<memory>
#include<string>

//TODO:: 有时间还是做一个2^32进制的吧，have a try
class bigInt 
{
public:
	friend bigInt operator +(bigInt& a, bigInt& b) ;
	friend bigInt operator -(bigInt& a, bigInt& b) ;
	friend bool operator>(bigInt& a, bigInt& b);
	friend bigInt operator*(bigInt& a, bigInt& b);
	//返回值1:a>b, 0:a=b, -1:a<b
	friend int absCompare(bigInt& a, bigInt& b);

	bigInt() :innerImpl_("") {};
	bigInt(const bigInt &);
	bigInt(std::string a); 
	//用来封装可能的细节操作
	std::string get() const ;
	std::string getWithSign() const;
	bool set(std::string& bigint) ;
	bool set(std::string&& bigint) ;
	std::uint64_t size()const;
	~bigInt();
private:
	std::string innerImpl_;
	bool checkNum(std::string &bigint);
	bool positive_ = true;
};


