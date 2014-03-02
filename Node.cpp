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
std::uniform_int_distribution<int> TerminalNode::termDist(0, 2);
std::uniform_real_distribution<double> TerminalNode::constDist(-10, 10);
std::uniform_int_distribution<int> UnaryOpNode::unaryDist(0, unaryOps.size() - 1);
std::uniform_int_distribution<int> BinaryOpNode::binaryDist(0, binaryOps.size() - 1);

TerminalNode::TerminalNode(int type, double val)
	:Node(0 ,type)
	,val(val)
{}

double TerminalNode::eval(double x, double y) const{
	return type ? val : (type == 1 ? x : y);
}

std::shared_ptr<Node> TerminalNode::randomTerminalNode(){
	return std::make_shared<TerminalNode>(termDist(rng), constDist(rng));
}

UnaryOpNode::UnaryOpNode(int type)
	:Node(1, type)
	,op(unaryOps[type])
{}

double UnaryOpNode::eval(double x, double y) const{
	return op(children[0]->eval(x, y));
}

std::shared_ptr<Node> UnaryOpNode::randomUnaryOpNode(){
	return std::make_shared<UnaryOpNode>(unaryDist(rng));
}

BinaryOpNode::BinaryOpNode(int type)
	:Node(2, type)
	,op(binaryOps[type])
{}

double BinaryOpNode::eval(double x, double y) const{
	return op(children[0]->eval(x, y), children[1]->eval(x, y));
}

std::shared_ptr<Node> BinaryOpNode::randomBinaryOpNode(){
	return std::make_shared<BinaryOpNode>(binaryDist(rng));
}

std::shared_ptr<Node> getRandomTree(){
	switch(nodeDist(rng)){
		case 0: return TerminalNode::randomTerminalNode();
		case 1: {
			auto temp = UnaryOpNode::randomUnaryOpNode();
			std::generate(temp->children.begin(), temp->children.end(), [&](){return getRandomTree();});
			return temp;
		}
		case 2: {
			auto temp = BinaryOpNode::randomBinaryOpNode();
			std::generate(temp->children.begin(), temp->children.end(), [&](){return getRandomTree();});
			return temp;
		}
	}
}

std::string serializeTree(std::shared_ptr<Node> tree){
	if(tree->children.size() == 0){
		auto temp = reinterpret_cast<TerminalNode*>(tree.get());
		return "0 " + std::to_string(temp->type) + " " + std::to_string(temp->val) + " ";
	}
	if(tree->children.size() == 1){
		auto childString = serializeTree(tree->children[0]);
		return "1 " + std::to_string(tree->type) + " " + childString;
	}
	if(tree->children.size() == 2){
		auto leftString = serializeTree(tree->children[0]);
		auto rightString = serializeTree(tree->children[1]);
		return "2 " + std::to_string(tree->type) + " " + leftString + rightString;
	}
}

std::shared_ptr<Node> deserializeTree(std::stringstream &tree){
	int nodeType;
	int type;
	tree >> nodeType >> type;
	if(nodeType == 0){
		double val;
		tree >> val;
		return std::make_shared<TerminalNode>(type, val);
	}
	if(nodeType == 1){
		auto temp = std::make_shared<UnaryOpNode>(type);
		temp->children[0] = deserializeTree(tree);
		return temp;
	}
	if(nodeType == 2){
		auto temp = std::make_shared<BinaryOpNode>(type);
		temp->children[0] = deserializeTree(tree);
		temp->children[1] = deserializeTree(tree);
		return temp;
	}
}

int height(std::shared_ptr<Node> tree){
	if(tree->children.size() == 0){
		return 0;
	}
	int sum = 0;
	for(auto &child : tree->children){
		sum += height(child);
	}
	return sum + 1;
}
