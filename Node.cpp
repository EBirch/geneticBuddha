#include "Node.h"

double TerminalNode::eval(double x){
	return type == TerminalNode::Type::Variable ? x : val;
}
