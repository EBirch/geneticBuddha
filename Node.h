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
		virtual double eval(double x, double y) const = 0;
		Node(int numChildren):children(numChildren){};
};

class TerminalNode : public Node{
	public:
		int type;
		double val;
		static std::uniform_int_distribution<int> termDist;
		static std::uniform_real_distribution<double> constDist;
		static std::shared_ptr<Node> randomTerminalNode();
		TerminalNode(int type, double val = 0.0);
		virtual double eval(double x, double y) const;
};

class UnaryOpNode : public Node{
	public:
		int type;
		std::function<double(double)> op;
		static std::uniform_int_distribution<int> unaryDist;
		static std::shared_ptr<Node> randomUnaryOpNode();
		UnaryOpNode(int type);
		virtual double eval(double x, double y) const;
};

class BinaryOpNode : public Node{
	public:
		int type;
		std::function<double(double, double)> op;
		static std::uniform_int_distribution<int> binaryDist;
		static std::shared_ptr<Node> randomBinaryOpNode();
		BinaryOpNode(int type);
		virtual double eval(double x, double y) const;
};

std::shared_ptr<Node> getRandomTree();

#endif
