#pragma once
#include<string>
#include<memory>
class bigIntBase
{
public:
	bigIntBase();
	virtual ~bigIntBase();
	//五种基本运算类型
	virtual std::shared_ptr<bigIntBase> operator+(bigIntBase &a)=0;
	//TODO:: 基本功能需要实现
	//virtual std::shared_ptr<bigIntBase> operator-(bigIntBase &a)=0;
	//virtual std::shared_ptr<bigIntBase> operator*(bigIntBase &a)=0;
	//virtual std::shared_ptr<bigIntBase> operator/(bigIntBase &a)=0;
	//virtual std::shared_ptr<bigIntBase> operator^(bigIntBase &a)=0;
	//扩展：求gcd，inv
	//virtual std::shared_ptr<bigIntBase> gcd (bigIntBase &a)=0; 
	//virtual std::shared_ptr<bigIntBase> operator^(bigIntBase &a)=0;
//	从bigInt 到string  的转换
	virtual std::string get()const=0;
private:
	//构造时需要添加验证
	virtual bool checkNum(std::string &a)=0;
	bool positive_ = true;
};
