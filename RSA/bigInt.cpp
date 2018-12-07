#include "pch.h"
#include<exception>
#include<array>
#include<iostream>
#include "bigInt.h"
#include "DebugMode.h"


bigInt::bigInt(const bigInt& a){
	innerImpl_ = std::string(a.innerImpl_);
	positive_ = a.positive_;
}

bigInt::bigInt(std::string a){
	ASSERT(checkNum(a));
	innerImpl_= a;
}

bigInt & bigInt::operator=(const bigInt & a)
{
	if (this == &a)
		return *this;
	this->innerImpl_ = a.innerImpl_;
	this->positive_ = a.positive_;
	return *this;

}

bigInt operator+(const bigInt& a, const bigInt& b){
	std::string  res;
	std::string minOp;
	//设置进位标志
	bigInt ret;
	if (a.positive_^b.positive_ == 0)
		ret.positive_ = a.positive_;
	else {
		if (a.positive_) {
			bigInt tmp{ b };
			tmp.positive_ = true;
			return a - tmp;
		}
		else {
			bigInt tmp{ a };
			tmp.positive_ = true;
			return b - tmp;
		}
	}

	if (a.size() > b.size()) {
		minOp = b.innerImpl_;
		res=a.innerImpl_;
	}else{
		minOp = a.innerImpl_;
		res=b.innerImpl_;
	}
	res.insert(res.cbegin(), '0');
	int LInd = res.size()-1;
	int RInd = minOp.size()-1;
	minOp.insert(minOp.cbegin(), LInd - RInd, '0');
	RInd = minOp.size()-1;
	bool carry = false;
	char midChar = '0';
	for (; LInd >= 0 && RInd >= 0; LInd--, RInd--) {
		char cm = res[LInd];
		int tmp = res[LInd] + minOp[RInd];
		midChar = res[LInd]+minOp[RInd]-48+carry;
		res[LInd] = (midChar >= 58) ? midChar - 10 : midChar;
		carry = midChar >= 58;
		if (res[LInd] >= 58) {
			ASSERT(false);
		}

		ret.set(res);
		tmp = tmp - carry;
		cm = cm - carry;
	}
	int sh = 0;
	sh += 123;
	int hehl = 1;
	ret.set(res);
	ret.positive_ = a.positive_;
	return ret;
}

bigInt operator-(const bigInt& a, const bigInt& b){
	if (a.positive_^b.positive_ == 1) {
		if (a.positive_) {
			bigInt tmp{ b };
			tmp.positive_ = true;
			return a + tmp;
		}
		else {
			//两个都是负数让+来处理  
			bigInt tmp{ b };
			tmp.positive_ = false;
			return a + tmp;
		}
	}

	bigInt L{ a }, R{ b };
	if (L.size() > R.size())
		R.innerImpl_ = std::string(L.size() - R.size(), '0') + R.innerImpl_;
	else
		L.innerImpl_ = std::string(R.size() - L.size(), '0') + L.innerImpl_;
	//保证L值更大
	bigInt ret;
	bool positive = true;
	if (absCompare(L,R)==1) {
		//TODO::需要修改
		positive = a.positive_;
	}else {
		positive = !a.positive_;
		std::swap(L, R);
	}


	int lSize = L.size(), rSize = R.size();
	ASSERT(lSize == rSize);
	std::string res(L.size(), '0');
	auto &lstr = L.innerImpl_;
	auto &rstr = R.innerImpl_;
	for(int i=0;i<lSize;i++){
		if (lstr[i] < rstr[i]) {
			int j = i-1;
			while (j >= 0) {
				if (res[j] == '0') {
					res[j] = '9';
				}
				else {
					res[j] = res[j] - 1;
					break;
				}
				j--;
			}
			ASSERT(j >= 0);
			lstr[i] += 10;
		}
		res[i] = lstr[i] - rstr[i]+48;
	}
	ret.set(res);
	ret.positive_ = positive;
	return ret;
}

bool operator>(const bigInt & a, const bigInt & b){
	if (a.positive_ == true && b.positive_ == false)
		return true;
	else if (a.positive_ == false && b.positive_ == true)
		return false;
	int rela=absCompare(a, b);
	if (a.positive_ == true && rela == 1)
		return true;
	if (a.positive_ == false && rela == -1)
		return true;
	return false;
}

bool operator==(const bigInt & a, const bigInt & b){
	auto aind = a.innerImpl_.find_first_not_of('0');
	auto bind = a.innerImpl_.find_first_not_of('0');
	aind = (aind == -1) ? 0:aind;
	bind = (bind == -1) ? 0:bind;
	if (a.size() - aind != b.size() - bind) {
		return false;
	}
	for (int i = aind; i < a.size(); i++) {
		if (a.innerImpl_[i] != b.innerImpl_[i])
			return false;
	}
	return true;
}

bigInt operator*(const bigInt& a, const bigInt& b){
	//先拿到0-9乘以一个数的值 然后再去计算
	bigInt L{ a };
	bigInt R{ b };
	bigInt res{"0"};
	if (absCompare(L , R)!=1) {
		std::swap(L, R);
	}
	L.positive_ = true;
	R.positive_ = true;
	std::array<std::string, 10> cachedVal;
	bigInt tmp(L);
	bigInt sum("0");
	for (int i = 1; i < 10; i++) {
		sum = sum + tmp;
		cachedVal[i] = sum.get();
	}
	for (int i = R.size()-1; i >=0; i--) {
		if (i == 0xaf) {
			CDebug("hello");
		}
		if (R.innerImpl_[i] == '0')
			continue;
		bigInt mid(cachedVal[R.innerImpl_[i] - 48]+std::string(R.size()-1-i,'0'));
		ASSERT(mid.checkNum(mid.innerImpl_));
		res = res + mid;
		ASSERT(mid.checkNum(res.innerImpl_));
	}
	res.positive_ =!(a.positive_^b.positive_);
	return res;
}

std::tuple<bigInt, bigInt> operator/(const bigInt & a, const bigInt & b)
{
	if (a.innerImpl_ == b.innerImpl_)
		return std::make_tuple ( bigInt{ "1" }, bigInt{ "0" });
	if (a > b != 1) {
		return std::make_tuple ( bigInt{ a }, bigInt{ "0" });
	}
	//指数增长
	return 
}

int absCompare(const bigInt& a, const bigInt& b)
{
	auto aStart = a.innerImpl_.find_first_not_of('0');
	auto bStart = b.innerImpl_.find_first_not_of('0');

	//对于全零情况的处理
	if (aStart == -1 && bStart == -1)
		return 0;
	else if (aStart == -1 && bStart != -1)
		return -1;
	else if (aStart != -1 && bStart == -1)
		return 1;
	if (a.size() - aStart > b.size() - bStart)
		return 1;
	else if (a.size() - aStart < b.size() - bStart)
		return -1;

	ASSERT(a.size() - aStart == b.size() - bStart);
	for (int i = aStart; i < a.size(); i++) {
		if (a.innerImpl_[i] == b.innerImpl_[i])
			continue;
		if (a.innerImpl_[i] > b.innerImpl_[i])
			return 1;
		else
			return -1; 
	}
	return 0;
}

std::string bigInt::get() const{
	return innerImpl_;
}

std::string bigInt::getWithSign() const{
	return (this->positive_==true?"+":"-")+innerImpl_;
}

bool bigInt::set(std::string& bigint){
	if (!checkNum(bigint)) {
		throw std::runtime_error("bigint can't not be constructed by null string");
	}
	else{
		this->innerImpl_ = bigint;
	}
	return true;
}

bool bigInt::set(std::string&& bigint){
	std::string midVal(bigint);
	return set(midVal);
}

std::uint64_t bigInt::size() const{
	return innerImpl_.size();
}

bigInt::~bigInt()
{
}

//验证字符中的数字-首字符可以为+或者-
bool bigInt::checkNum(std::string& bigint)
{
	if (bigint == "")
		ASSERT(false);
		//return false;
	//'+'=43,'-'=45
	if (!(bigint[0] == 43 || bigint[0] == 45 || (bigint[0] < 58 && bigint[0]>47)))
		ASSERT(false);
		//return false;
	if (bigint.size() == 1 && (bigint[0] == '-' || bigint[0] == '+')) {
		ASSERT(false);
		//return false;
	}
	positive_ = (bigint[0] == '-') ? false : true;
	if (bigint[0] == '-' || bigint[0] == '+')
		bigint[0] = '0';
	for (unsigned int i = 0; i < bigint.size(); i++) {
		if (bigint[i] >= 58 || bigint[0] <= 47)
			ASSERT(false);
			//return false;
	}
	return true;
}

