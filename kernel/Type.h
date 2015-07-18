//
// Created by R2 on 06.07.2015.
//

#ifndef MATHPROJECT_TYPE_H
#define MATHPROJECT_TYPE_H

#include <string>
#include <boost/format.hpp>

class Type {
public:
    virtual std::string getType() = 0;

    virtual bool equals(Type &type) = 0;

    virtual bool isNonzero() = 0;

    virtual void print(std::ostream &os) {
        os << boost::format("[%1% instance at address %2%]") % getType() % (int)this;
    }

};

static inline std::ostream &operator<<(std::ostream &stream, Type &p) {
    p.print(stream);
    return stream;
}

#endif //MATHPROJECT_TYPE_H
