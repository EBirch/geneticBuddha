#ifndef NODE_H
#define NODE_H

#include <memory>
#include <functional>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <limits>
#include <algorithm>

class Node{
	public:
		std::vector<std::shared_ptr<Node>> children;
		virtual double eval(double x) const = 0;
		Node(int numChildren):children(numChildren){};
};

class TerminalNode : public Node{
	public:
		enum Type{
			Variable = 0,
			Constant = 1
		};
		Type type;
		double val;
		TerminalNode(Type type, double val = 0.0);
		virtual double eval(double x) const;
};

class UnaryOpNode : public Node{
	public:
		std::function<double(double)> op;
		UnaryOpNode(int type);
		virtual double eval(double x) const;
};

class BinaryOpNode : public Node{
	public:
		std::function<double(double, double)> op;
		BinaryOpNode(int type);
		virtual double eval(double x) const;
};

std::shared_ptr<Node> getRandomTree();

#endif
