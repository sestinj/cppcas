#include <iostream>

class Operator {
    private:
        int id;
    public:
        double raw_comp(double args[10]){ // TODO: What's it called? Vector?
            return 0;
        }
};

class Addition: Operator {
    public:
        double raw_comp(double args[10]) override {
            return 5;
        }
};
class Expr {
    private:


    public:

};

struct LazyVal {
    double val;
    bool lazy;
};

struct Expression {
    int id;
    LazyVal val;
    Operator *op;
    Expression args[10]; // TODO: again, vector...play around to find out what issues this might cause like in Rust.
};

int main() {
  std::cout << "Hello World!\n";
};


/*
Options:
- Expression is a class, which all operators are subclasses of. The functions for computing are all class methods
- Expression is a class with a pointer to the proper Operator class. Compute functions are done by calling the operator specific class method from the pointer. THis seems like unecessary indirection though...
- Expression is a struct (what are the benefits here? I believe size is the exact same as class. It's possible that there are different rules for passing around classes vs. structs), and an operation is a class. Expr has the pointer to the operation class, of which there should only be a single instance...but if that's true, why does it have to be a subclass and why can't it just be an object instantiated with all the info needed? I think the answer is for intuitive development of new operators. But this might trade off with being able to dynamically create new operators. So I assume you could always do the latter if you have the former, just allow both options.
- Just a single struct and all of the functions are shared, except might have to lookup operator specific information in some top-leve hash table...don't like this, it's what you started to do with the Rust environment concept, and it leads to a very non-portable and...lost train of thought...

I say go with plan #3 probably, at least until you better understand what the differences between structs and classes are.
*/

/*
Questions:
- What does it look like to create a new object? Can I just use the function notation I want without a new keyword or anything?
- Macros?
- Are there traits? How does one make something printable, etc....?

*/