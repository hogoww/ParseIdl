#include "Function.h"


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

void Function::parseEnd(std::string ToBeParse){
  std::smatch res;

  //recup param
  if(std::regex_search(ToBeParse,res,exprParam)){
    std::string inProgress(res[1].str());
    ToBeParse=res.suffix().str();

    std::smatch parse;
    while(std::regex_search(inProgress,parse,exprParseParam)){
      Parameter New(parse[3].str(),parse[2].str(),parse[1].str()=="in");
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
  Item::showMeWhatYouGot(depth);
  std::cout<<"(";
  for(std::vector<Parameter>::const_iterator it=Param.begin();it!=Param.end();++it) {
    it->showMeThatParameter();
  }
  std::cout<<")";
  if(Exception.size()){//forcement une
    std::cout<<" raises ("<<*Exception.begin();
    for(std::vector<std::string>::const_iterator it=++Exception.begin();it!=Exception.end();++it) {
      std::cout<<','<<*it;
    }
    std::cout<<")";
  }
  std::cout<<"\n";
}
