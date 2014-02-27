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

TerminalNode::TerminalNode(Type type, double val)
	:type(type)
	,val(val)
{}

double TerminalNode::eval(double x){
	return type == TerminalNode::Type::Variable ? x : val;
}

BinaryOpNode::BinaryOpNode(Type type)
	:op(binaryOps[type])
{}

double BinaryOpNode::eval(double x){
	return op(leftChild->eval(x), rightChild->eval(x));
}

UnaryOpNode::UnaryOpNode(Type type)
	:op(unaryOps[type])
{}

double UnaryOpNode::eval(double x){
	return op(child->eval(x));
}
