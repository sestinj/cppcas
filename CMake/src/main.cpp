#include <arrayfire.h>
#include <af/util.h>
#include <af/gfor.h>
#include <vector>
#include <iostream>
#include <math.h>
using namespace std;
using namespace af;

#define DEF_INFIX_BIN_OP(name, lc_name, op) \
    class name: public Expr { \
        public: \
            name(ExP a, ExP b) { \
                args.push_back(a); \
                args.push_back(b); \
            }; \
            af::array raw_comp(std::vector<af::array> args) override { \
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
            af::array raw_comp(std::vector<af::array> args) override { \
                return func(args[0]); \
            }; \
    }; \
    name* lc_name(ExP a) { \
        return new name(a); \
    };

#define DEF_BIN_OP(name, lc_name, func) \
    class name: public Expr { \
        public: \
            name(ExP a, ExP b) { \
                args.push_back(a); \
                args.push_back(b); \
            }; \
            af::array raw_comp(std::vector<af::array> args) override { \
                return func(args[0], args[1]); \
            }; \
    }; \
    name* lc_name(ExP a, ExP b) { \
        return new name(a, b); \
    };

class Expr {
    public:
        vector<Expr*> args;
        virtual af::array raw_comp(vector<af::array> args) = 0;
};
typedef Expr* ExP;

DEF_INFIX_BIN_OP(Add, add, +);
DEF_INFIX_BIN_OP(Sub, sub, -);
DEF_INFIX_BIN_OP(Mul, mul, *);
DEF_INFIX_BIN_OP(Div, div, /);

DEF_BIN_OP(MatMul, matmul, af::matmul);

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
        af::array val;
        Value(af::array v) {
            val = v;
        };
        af::array raw_comp(vector<af::array> args) override {
            return val;
        }
};

Value* value(af::array v) {
    return new Value(v);
}

af::array full_eval(ExP e) {
    vector<af::array> args_vals;
    for (Expr* e : e->args) {
        args_vals.push_back(full_eval(e));
    };
    return e->raw_comp(args_vals);
};

void print_val(af::array v) {
    std::stringstream ss(af::toString("", v));
    std::string to;
    int i = 0;
    while(std::getline(ss,to,'\n')){
        if (i < 2) {
            i++;
            continue;
        }
        cout << to << endl;
    }
};

int main() {
    cout << "Testing..." << endl;

    ExP v = value(af::constant(3.14, 2, 2));

    ExP a = value(af::constant(1, 2, 2));
    ExP b = mul(a, v);
    ExP c = matmul(a, v);
    
    print_val(full_eval(b));
    print_val(full_eval(c));

    cout << "Done." << endl;
    return 0;
};