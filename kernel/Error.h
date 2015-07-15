//
// Created by R2 on 15.07.2015.
//


#ifndef MATHPROJECT_ERROR_H
#define MATHPROJECT_ERROR_H

#include <string>


class Error {
    std::string text;

public:
    Error(std::string text){
        //TODO: text processing of mistakes
        this->text = text;
    }

  std::string  getText(){
      return text;
  }
};


#endif //MATHPROJECT_ERROR_H
