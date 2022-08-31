#include <iostream>
#include <vector>

struct LazyVal {
    double val;
    bool lazy;
    bool has_val;
    LazyVal(double v, bool l, bool h) : val(v), lazy(l), has_val(h) {}
};

int NEXT_EXPRESSION_ID = 0;
int getNextExpressionId() {
    return NEXT_EXPRESSION_ID++;
}

class Expression {
    public:
        int id;
        LazyVal val;
        std::vector<Expr> args;

        Expression(): val(0, false, false), args(), id(getNextExpressionId()) {};

        virtual double raw_comp(std::vector<double> args) {
            throw std::logic_error("raw_compute not implemented");
        };
        // TODO: Pass in the map of arguments       
        double full_eval() {
            if (val.has_val) {
                return val.val;
            }
            std::vector<double> args_vals;
            for (Expr e : args) {
                args_vals.push_back(e->full_eval());
            }
            std::cout << raw_comp(args_vals) << std::endl;
            return this->raw_comp(args_vals);
        }
};

typedef Expression* Expr;

class sum: public Expression {
    public:
        double raw_comp(std::vector<double> args) override {
            return args[0] + args[1];
        }
        sum(Expr a, Expr b) {
            args.push_back(a);
            args.push_back(b);
        };
};

class sub: public Expression {
    public:
        double raw_comp(std::vector<double> args) override {
            return args[0] - args[1];
        }
        sub(Expr a, Expr b) {
            args.push_back(a);
            args.push_back(b);
        };
};

class mul: public Expression {
    public:
        double raw_comp(std::vector<double> args) override {
            return  args[0] * args[1];
        }
        mul(Expr a, Expr b) {
            args.push_back(a);
            args.push_back(b);
        };
};

class divide: public Expression {
    public:
        double raw_comp(std::vector<double> args) override {
            return args[0] / args[1];
        }
        divide(Expr a, Expr b) {
            args.push_back(a);
            args.push_back(b);
        };
};

Expr operator+( const Expr& a, const Expr& b) {
    return new sum(a, b);
}
Expr operator-( const Expr& a, const Expr& b) {
    return new sub(a, b);
}
Expr operator*( const Expr& a, const Expr& b) {
    return new mul(a, b);
}
Expr operator/( const Expr& a, const Expr& b) {
    return new divide(a, b);
}

class Value: public Expression {
    public:
        Value(double v) {
            val = LazyVal(v, false, true);
        }
        double raw_comp(std::vector<double> args) {
            return val.val;
        }
};

int main() {
  std::cout << "Hello World!\n";
  Expression* c = new Value(3);
  Expr d = new Value(4);
  Expr a = c + d;
  std::cout << a->full_eval() << c->full_eval() << d->full_eval() << std::endl;
};
