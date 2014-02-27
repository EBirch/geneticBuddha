#include "Node.h"

#include <limits>

std::vector<std::function<double(double, double)>> binaryOps {
	[&](double left, double right){return left - right;},
	[&](double left, double right){return left + right;},
	[&](double left, double right){return left * right;},
	[&](double left, double right){return left / right;},
	[&](double left, double right){return pow(left, right);}
};

std::vector<std::function<double(double)>> unaryOps {
	[&](double val){return -val;},
	[&](double val){return cos(val);},
	[&](double val){return sin(val);},
	[&](double val){return tan(val);},
	[&](double val){return sqrt(val);},
	[&](double val){return log(val);}
};

std::mt19937 rng(time(NULL));
std::uniform_int_distribution<int> nodeDist(0, 2);
std::uniform_int_distribution<int> termDist(0, 1);
std::uniform_int_distribution<int> unaryDist(0, 5);
std::uniform_int_distribution<int> binaryDist(0, 4);
std::uniform_real_distribution<double> constDist(std::numeric_limits<double>::min(), std::numeric_limits<double>::max());

TerminalNode::TerminalNode(Type type, double val)
	:type(type)
	,val(val)
{}

double TerminalNode::eval(double x) const{
	return type == TerminalNode::Type::Variable ? x : val;
}

UnaryOpNode::UnaryOpNode(int type)
	:op(unaryOps[type])
{}

double UnaryOpNode::eval(double x) const{
	return op(child->eval(x));
}

BinaryOpNode::BinaryOpNode(int type)
	:op(binaryOps[type])
{}

double BinaryOpNode::eval(double x) const{
	return op(leftChild->eval(x), rightChild->eval(x));
}

std::shared_ptr<Node> getRandomTree(){
	switch(nodeDist(rng)){
		case 0: return std::make_shared<TerminalNode>((TerminalNode::Type)termDist(rng), constDist(rng));
		case 1: {
			auto temp = std::make_shared<UnaryOpNode>(unaryDist(rng));
			temp->child = getRandomTree();
			return temp;
		}
		case 2: {
			auto temp = std::make_shared<BinaryOpNode>(binaryDist(rng));
			temp->leftChild = getRandomTree();
			temp->rightChild = getRandomTree();
			return temp;
		}
	}
}
