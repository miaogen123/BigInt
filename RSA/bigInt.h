#pragma once
#include<tuple>
#include<memory>
#include<string>


//TODO:: 有时间还是做一个2^32进制的吧，have a try
//ATTENTION:
class bigInt 
{
public:
	friend bigInt operator +(const bigInt& a, const bigInt& b) ;
	friend bigInt operator -(const bigInt& a, const bigInt& b) ;
	friend bigInt operator*(const bigInt& a, const bigInt& b);
	//整数算法：pre-require:a>b | 返回商与余数
	friend std::tuple<bigInt, bigInt> operator/(const bigInt& a, const bigInt& b);
	//返回值1:a>b, 0:a=b, -1:a<b
	friend bool operator>(const bigInt& a, const bigInt& b);
	friend bool operator==(const bigInt& a, const bigInt& b);
	friend int absCompare(const bigInt& a, const bigInt& b);

	bigInt() :innerImpl_("") {};
	bigInt(const bigInt &);
	bigInt(std::string a); 
	bigInt& operator = (const bigInt &a);
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


