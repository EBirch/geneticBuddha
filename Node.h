#ifndef NODE_H
#define NODE_H

#include <memory>
#include <functional>

class Node{
	public:
		virtual double eval(double x) const = 0;
};

class TerminalNode : public Node{
	public:
		enum Type{
			Variable,
			Constant
		};
		Type type;
		double val;
		virtual double eval(double x);
};

class BinaryOpNode : public Node{
	public:
		std::shared_ptr<Node> leftChild;
		std::shared_ptr<Node> rightChild;
		std::function<double(double, double)> op;
		virtual double eval(double x);
};

class UnaryOpNode : public Node{
	public:
		std::shared_ptr<Node> child;
		std::function<double(double)> op;
		virtual double eval(double x);
};

#endif
