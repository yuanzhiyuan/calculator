#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

class Calculator{
public:
	inline int get_pri(char c){
		switch (c)
		{
		case '+':return 1;
		case '-':return 1;
		case '*':return 2;
		case '/':return 2;
		case '(':return 3;
		case ')':return 3;
		default:
			return 0;
		}
	}
	bool is_sign(string s){
		return s.size() == 1 && (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/' || s[0] == ')' || s[0] == '(');
	}
	string exp2plsh(string& exp){
		string rst;
		auto it = exp.begin();
		stack<char> cs;
		while (it != exp.end()){
			string cur = read_next(it,exp.end());//可能输出数字，加减乘除括号，空
			
			if (is_sign(cur)){
				
				char sign = cur[0];
				if (cs.size() == 0) {
					cs.push(sign);
					continue;
				}
				
				if (sign == ')'){
					while (!cs.empty()&&cs.top() != '('){
						rst = rst + cs.top() + " ";
						cs.pop();
					}
					cs.pop();
				}
				if (sign == '+' || sign == '-' || sign == '*' || sign == '/'){
					while (!cs.empty() && (get_pri(cs.top()) >= get_pri(sign)&&cs.top()!='(')){
						rst = rst + cs.top() + " ";
						cs.pop();
					}
				}
				if (sign != ')')
					cs.push(sign);


			}
			else if (cur == ""){
				return "";
			}
			else{
				rst = rst + cur + " ";
			}

		}
		while (!cs.empty()){
			rst = rst + cs.top() + " ";
			cs.pop();
		}
		return rst;
	}

	string read_next(string::iterator& first,const string::iterator& last){
		string rst;
		if (isdigit(*first)||*first=='.'){
			int point = 0;//小数点出现的数量
			while (first != last && (isdigit(*first)||*first=='.') && point<2){
				rst += *first;
				if (*first == '.')	point++;
				first++;
			}
			if (point == 2){
				//出现了两个小数点，说明输入有误
				first = last;
				rst.pop_back();
				return rst;
			}
			else{
				return rst;
			}
		}
		else if (*first == '+' || *first == '-' || *first == '*' || *first == '/' || *first == '(' || *first == ')'){
			rst = *first;
			first++;
			return rst;
		}
		else{
			first = last;
			return "";
		}
		
		

		
	}
	bool polish_cal(string& exp, double& rst){
		vector<string> ex;
		istringstream iss(exp);
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(ex));
		stack<string> sn;
		for (auto i = ex.begin(); i != ex.end(); i++){
			int jud = judge(*i);
			double a = 0, b = 0;
			switch (jud)
			{
			case 0://数字
				sn.push(*i);
				break;
			case 1://符号
				if (sn.size() < 2)	return false;
				
				a = stod(sn.top(),nullptr);
				sn.pop();
				b = stod(sn.top(), nullptr);
				sn.pop();
				if (i->compare("+") == 0){
					sn.push(to_string(a+b));

				}
				else if (i->compare("-") == 0){
					sn.push(to_string(b - a));
				}
				else if (i->compare("*") == 0){
					sn.push(to_string(a * b));
				}
				else{
					sn.push(to_string(b / a));
				}
				
				break;
			default:
				return false;
			
			}
		

		}
		if (sn.size() == 1){
			rst = stod(sn.top());
			return true;
		}
		else{
			return false;
		}
		
		
	}
	string cal(string& exp){
		string po = exp2plsh(exp);
		if (po.compare("")==0)	return "wrong input";
		double rst = 0;
		if (polish_cal(po, rst))	return to_string(rst);
		else return "wrong input";
	}
	int judge(const string& a){
		if (isdigit(a[0])){
			auto i = find_if(a.begin(), a.end(), [=](char b)->bool{return !(isdigit(b)||b=='.'); });
			if (i == a.end())	return 0;//是数字
			else return 2;//什么都不是

		}
		else if (a.size() > 1 && a[0] == '-'){
			return 0;
			//是负数
		}
		else{
			if (a.size() == 1 && (a[0] == '+' || a[0] == '-' || a[0] == '*' || a[0] == '/')){
				return 1;//是符号
			}
			
			else return 2;//什么都不是
		}
	}
};

int main(){

	Calculator cal;
	//string exp = "5 1 2 + 4 * + 3.5 -";
	//double rst = 0.0;
	//cal.polish_cal(exp, rst);
	//cout << rst << endl;
	string a = "0+1.5*3+(2*3+4)*5";
	cout << cal.cal(a);
	
	system("pause");
	return 0;
}