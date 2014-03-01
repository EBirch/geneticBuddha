#include "Node.h"
#include <iostream>

std::vector<std::function<double(double)>> unaryOps {
	[&](double val){return -val;},
	[&](double val){return cos(val);},
	[&](double val){return sin(val);},
	[&](double val){return tan(val);},
	[&](double val){return sqrt(abs(val));},
	[&](double val){return log(val);}
};

std::vector<std::function<double(double, double)>> binaryOps {
	[&](double left, double right){return left - right;},
	[&](double left, double right){return left + right;},
	[&](double left, double right){return left * right;},
	[&](double left, double right){return left / right;},
	[&](double left, double right){return pow(left, right);}
};

std::mt19937 rng(time(NULL));
std::uniform_int_distribution<int> nodeDist(0, 2);
std::uniform_int_distribution<int> termDist(0, 1);
std::uniform_int_distribution<int> unaryDist(0, unaryOps.size() - 1);
std::uniform_int_distribution<int> binaryDist(0, binaryOps.size() - 1);
std::uniform_real_distribution<double> constDist(-10, 10);

TerminalNode::TerminalNode(int type, double val)
	:Node(0)
	,type(type)
	,val(val)
{}

double TerminalNode::eval(double x) const{
	return type ? x : val;
}

UnaryOpNode::UnaryOpNode(int type)
	:Node(1)
	,type(type)
	,op(unaryOps[type])
{}

double UnaryOpNode::eval(double x) const{
	return op(children[0]->eval(x));
}

BinaryOpNode::BinaryOpNode(int type)
	:Node(2)
	,type(type)
	,op(binaryOps[type])
{}

double BinaryOpNode::eval(double x) const{
	return op(children[0]->eval(x), children[1]->eval(x));
}

std::shared_ptr<Node> getRandomTree(){
	switch(nodeDist(rng)){
		case 0: return std::make_shared<TerminalNode>(termDist(rng), constDist(rng));
		case 1: {
			auto temp = std::make_shared<UnaryOpNode>(unaryDist(rng));
			std::generate(temp->children.begin(), temp->children.end(), [&](){return getRandomTree();});
			return temp;
		}
		case 2: {
			auto temp = std::make_shared<BinaryOpNode>(binaryDist(rng));
			std::generate(temp->children.begin(), temp->children.end(), [&](){return getRandomTree();});
			return temp;
		}
	}
}
