#include "Node.h"

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

double TerminalNode::eval(double x){
	return type == TerminalNode::Type::Variable ? x : val;
}

double BinaryOpNode::eval(double x){
	return op(leftChild->eval(x), rightChild->eval(x));
}

double UnaryOpNode::eval(double x){
	return op(child->eval(x));
}
