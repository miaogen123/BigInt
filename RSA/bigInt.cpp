#include "pch.h"
#include "bigInt.h"
#include "DebugMode.h"


//bigInt::bigInt(bigInt& a){
//	innerImpl_ = a.innerImpl_;
//	positive_ = a.positive_;
//}

bigInt::bigInt(std::string a){
	ASSERT(checkNum(a));
	innerImpl_= a;
}

bigInt operator+(bigInt& a, bigInt& b){
	std::string  res;
	std::string minOp;
	//设置进位标志
	bigInt ret;
	if (a.positive_^b.positive_ == 0)
		ret.positive_ = a.positive_;
	else {
		if (a.positive_) {
			b.positive_ = true;
			return a - b;
		}
		else {
			a.positive_ = true;
			return b - a;
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
		midChar = res[LInd]+minOp[RInd]-48+carry;
		res[LInd] = (midChar >= 58) ? midChar - 10 : midChar;
		carry = midChar >= 58;
	}
	ret.set(res);
	if (a.positive_^b.positive_ == 0)
		ret.positive_ = a.positive_;
	return res;
}

bigInt operator-(bigInt& a, bigInt& b){
	if (a.positive_^b.positive_ == 1) {
		if (a.positive_) {
			b.positive_ = true;
			return a + b;
		}
		else {
			//两个都是负数让+来处理  
			return a + b;
		}
	}
	//比较大小前，除掉前面的0
	bigInt L{ a }, R{ b };
	auto firstNotZeroOfL=L.innerImpl_.find_first_not_of('0');
	L.innerImpl_.erase(L.innerImpl_.begin(), L.innerImpl_.begin()+firstNotZeroOfL);
	auto firstNotZeroOfR=R.innerImpl_.find_first_not_of('0');
	R.innerImpl_.erase(R.innerImpl_.begin(), R.innerImpl_.begin()+firstNotZeroOfR);

	//保证L值更大
	bigInt ret;
	if (a.innerImpl_ > b.innerImpl_) {
		ret.positive_ = a.positive_;
		L.set(a.innerImpl_), R.set(b.innerImpl_);
	}else {
		ret.positive_ = !a.positive_;
		L.set(b.innerImpl_), R.set(a.innerImpl_);
	}

	R.innerImpl_.insert(R.innerImpl_.begin(), L.size() - R.size(), '0');
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
	return ret;
}

std::string bigInt::get() const{
	return innerImpl_;
}

bool bigInt::set(std::string& bigint){
	if (!checkNum(bigint)) {
		return false;
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
		return true;
	//'+'=43,'-'=45
	if (!(bigint[0] == 43 || bigint[0] == 45 || (bigint[0] < 58 && bigint[0]>47)))
		return false;
	if (bigint.size() == 1 && (bigint[0] == '-' || bigint[0] == '+')) {
		return false;
	}
	positive_ = (bigint[0] == '-') ? false : true;
	if (bigint[0] == '-' || bigint[0] == '+')
		bigint[0] = '0';
	for (unsigned int i = 0; i < bigint.size(); i++) {
		if (bigint[i] >= 58 || bigint[0] <= 47)
			return false;
	}
	return true;
}

