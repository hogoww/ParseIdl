#include "Function.h"

#define MY_TYPE 2

//avoid multiple exact same thing
const std::regex Function::exprParam("^\\((.*?)\\)",std::regex::optimize);
const std::regex Function::exprParseParam("^ ?(\\w+?) (\\w+?) (\\w+?) ?,?",std::regex::optimize);
const std::regex Function::exprExcep("^ ?\\w+ ?\\((.*?)\\)",std::regex::optimize);
const std::regex Function::exprParseExcept("^ ?(\\w+) ?,?",std::regex::optimize);
/******Constructeurs:******/


/* constructeurs public*/
Function::Function(std::string name,std::string type,std::string ToBeParse):Item(name,type),Param(),Exception(){
  parseEnd(ToBeParse);//remplis Excep&Param
}

Function::~Function(){
  Param.clear();
  Exception.clear();
}

void Function::parseEnd(std::string ToBeParse){
  std::smatch res;

  //recup param
  if(std::regex_search(ToBeParse,res,exprParam)){
    std::string inProgress(res[1].str());
    ToBeParse=res.suffix().str();

    std::smatch parse;
    while(std::regex_search(inProgress,parse,exprParseParam)){
      Parameter New(parse[3].str(),parse[2].str(),parse[1].str());
      this->Param.push_back(New);
      inProgress=parse.suffix().str();
    }
  }
  else{
    std::cout<<"wth, "<<ToBeParse<<" doesn't match with exprParam :("<<std::endl;
    std::terminate();
  }
  
  //recup exceptions
  if(std::regex_search(ToBeParse,res,exprExcep)){
    std::string inProgress(res[1].str());
    //std::cout<<res.suffix().str()<<" left after except recuperation'"<<std::endl;//theoriquement vide ou pas loin
    
    std::smatch parse;
    while(std::regex_search(inProgress,parse,exprParseExcept)){
      this->Exception.push_back(parse[1].str());

      inProgress=parse.suffix().str();
    }
  }
  else{
    return;
    // std::cout<<ToBeParse<<" doesn't raise any exception."<<std::endl;    
  }

}


/******Methodes:******/
/* methodes public*/
const std::vector<Parameter> Function::getParam() const{
  return this->Param;
}

const std::vector<std::string> Function::getException() const{
  return this->Exception;
}


void Function::showMeWhatYouGot(size_t depth)const{
  // Item::showMeWhatYouGot(depth);
  // std::cout<<"(";
  // std::vector<Parameter>::const_iterator end=Param.cend();
  // for(std::vector<Parameter>::const_iterator it=Param.cbegin();it!=end;++it) {
  //   it->showMeThatParameter();
  // }
  // std::cout<<")";
  // if(Exception.size()){//forcement une
  //   std::vector<std::string>::const_iterator end=Exception.cend();
  //   std::cout<<" raises ("<<*Exception.begin();
  //   for(std::vector<std::string>::const_iterator it=++Exception.cbegin();it!=end;++it) {
  //     std::cout<<','<<*it;
  //   }
  //   std::cout<<")";
  // }
  std::cout<<Item::getDepth(depth);
  std::cout<<Declaration();
  std::cout<<"\n";
}



std::string Function::Declaration()const{
  std::string res=Item::Declaration();
  res+="(";
  std::vector<Parameter>::const_iterator end=Param.cend();
  if(Param.size()){
    res+=Param.cbegin()->showMeThatParameter();
    for(std::vector<Parameter>::const_iterator it=++Param.cbegin();it!=end;++it) {
      res+=", "+it->showMeThatParameter();
    }
  }
  res+=")";
  
  if(Exception.size()){//forcement une
    std::vector<std::string>::const_iterator end=Exception.cend();
    res+=" raises ("+*Exception.begin();
    for(std::vector<std::string>::const_iterator it=++Exception.cbegin();it!=end;++it) {
      res+=", "+*it;
    }
    res+=")";
  }
  return res;
}

const int Function::whoAreYou()const{
  return MY_TYPE;
}
