#include <vector>
#include <iostream>
#include <math.h>
using namespace std;

#define DEF_BIN_OP(name, lc_name, op) \
    class name: public Expr { \
        public: \
            name(ExP a, ExP b) { \
                args.push_back(a); \
                args.push_back(b); \
            }; \
            double raw_comp(std::vector<double> args) override { \
                return args[0] op args[1]; \
            }; \
    }; \
    name* lc_name(ExP a, ExP b) { \
        return new name(a, b); \
    };
    // ExP operator op( Expr a, Expr b) { \
    //     return new name(a, b); \
    // };

#define DEF_UN_OP(name, lc_name, func) \
    class name: public Expr { \
        public: \
            name(ExP a) { \
                args.push_back(a); \
            }; \
            double raw_comp(std::vector<double> args) override { \
                return func(args[0]); \
            }; \
    }; \
    name* lc_name(ExP a) { \
        return new name(a); \
    };

class Expr {
    public:
        vector<Expr*> args;
        virtual double raw_comp(vector<double> args) = 0;
};
typedef Expr* ExP;

DEF_BIN_OP(Add, add, +)
DEF_BIN_OP(Sub, sub, -)
DEF_BIN_OP(Mul, mul, *)
DEF_BIN_OP(Div, div, /)

DEF_UN_OP(Sin, sin, sin);
DEF_UN_OP(Cos, cos, cos);
DEF_UN_OP(Tan, tan, tan);
DEF_UN_OP(Exp, exp, exp);
DEF_UN_OP(Log, log, log);
DEF_UN_OP(Sqrt, sqrt, sqrt);
DEF_UN_OP(Abs, abs, abs);
DEF_UN_OP(Floor, floor, floor);
DEF_UN_OP(Ceil, ceil, ceil);
DEF_UN_OP(Round, round, round);
DEF_UN_OP(Sinh, sinh, sinh);
DEF_UN_OP(Cosh, cosh, cosh);
DEF_UN_OP(Tanh, tanh, tanh);
DEF_UN_OP(Asin, asin, asin);
DEF_UN_OP(Acos, acos, acos);
DEF_UN_OP(Atan, atan, atan);
DEF_UN_OP(Asinh, asinh, asinh);
DEF_UN_OP(Acosh, acosh, acosh);
DEF_UN_OP(Atanh, atanh, atanh);
DEF_UN_OP(Erf, erf, erf);
DEF_UN_OP(Erfc, erfc, erfc);
DEF_UN_OP(Gamma, gamma, tgamma);
DEF_UN_OP(Lgamma, lgamma, lgamma);

class Value: public Expr {
    public:
        double val;
        Value(double v) {
            val = v;
        };
        double raw_comp(vector<double> args) override {
            return val;
        }
};

Value* value(double v) {
    return new Value(v);
}

double full_eval(ExP e) {
    vector<double> args_vals;
    for (Expr* e : e->args) {
        args_vals.push_back(full_eval(e));
    };
    return e->raw_comp(args_vals);
};

int main() {
    cout << "Testing..." << endl;

    ExP v = value(3.14);

    cout << "Done." << endl;
    return 0;
};