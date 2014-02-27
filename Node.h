#ifndef NODE_H
#define NODE_H

#include <memory>
#include <functional>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>

class Node{
	public:
		virtual double eval(double x) const = 0;
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
		enum Type{
			Neg = 0,
			Cos = 1,
			Sin = 2,
			Tan = 3,
			Sqrt = 4,
			Log = 5
		};
		Type type;
		std::shared_ptr<Node> child;
		std::function<double(double)> op;
		UnaryOpNode(Type type);
		virtual double eval(double x) const;
};

class BinaryOpNode : public Node{
	public:
		enum Type{
			Sub = 0,
			Add = 1,
			Mult = 2,
			Div = 3,
			Pow = 4
		};
		Type type;
		std::shared_ptr<Node> leftChild;
		std::shared_ptr<Node> rightChild;
		std::function<double(double, double)> op;
		BinaryOpNode(Type type);
		virtual double eval(double x) const;
};

std::shared_ptr<Node> getRandomTree();

#endif
