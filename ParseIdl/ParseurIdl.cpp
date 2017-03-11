#include "ParseurIdl.h"

const std::regex ParseurIdl::exprLine("(.*)\\n",std::regex::optimize);
const std::regex ParseurIdl::exprSemiColon(";",std::regex::optimize);
const std::regex ParseurIdl::exprGetLine("( *)(.*)\n",std::regex::optimize);

const std::regex ParseurIdl::exprParenthesis("\\(",std::regex::optimize);//Function
const std::regex ParseurIdl::exprFunction("( *)(\\w+) (\\w+) ?(\\(.*\\))",std::regex::optimize);//parseFunction
const std::regex ParseurIdl::exprAtom("^( )*(\\w+) (\\w+) (\\w+) ?",std::regex::optimize);//Attrib
const std::regex ParseurIdl::exprC_E_I("^( *)(\\w+) (\\w+) ?");//Component | Exception | Interface 

const std::regex ParseurIdl::exprException("exception",std::regex::icase|std::regex::optimize);
//Similaires dans la structure
const std::regex ParseurIdl::exprInterface("interface",std::regex::icase|std::regex::optimize);
const std::regex ParseurIdl::exprComponent("component",std::regex::icase|std::regex::optimize);

bool ParseurIdl::isContainerFlag=false;



/******Constructeurs:******/


/* constructeurs public*/
ParseurIdl::ParseurIdl(std::string fileToParse):file(){
  //std::cout<<fileToParse<<std::endl;
  std::string command("./parse.py ");
  command+=fileToParse;
  std::system(command.c_str());

  std::string name(fileToParse);
  name+=".letsCompileIt";
  std::string content=FileToString(name);
  
  command="rm ";
  command+=name;
  std::system(command.c_str());
  //std::cout<<"Done loading the file"<<std::endl;
  fillMe(content);
}


/******Methodes:******/
/* methodes public*/
const std::vector<Container*> ParseurIdl::getFile()const{
  return file;
}

std::string ParseurIdl::FileToString(std::string fileName){
  std::ifstream stream(fileName);
  if (stream) {
    // get length of file:
    stream.seekg(0,stream.end);
    int length=stream.tellg();
    stream.seekg(0,stream.beg);

    char* buffer=new char[length];

    stream.read (buffer,length);

    if(stream){
      //std::cout<<"all characters read successfully.";
    }
    else
      std::cerr<<"error: only "<<stream.gcount()<<" character could be read";
    std::string Buffer(buffer);
    delete[] buffer;
    stream.close();
    return Buffer;
  }
  else{
    std::cerr<<"Error while trying to open "<<fileName<<"."<<std::endl;
    std::terminate();
  }
}
  

std::string ParseurIdl::fillMeWasHarderThanExpected(std::string& toBeParse,Container*& endOfPile){
  std::smatch res;
  if(std::regex_search(toBeParse,res,exprLine)){
    std::string line=res.suffix().str();
    std::smatch bogus;
    // //std::cout<<"I did find a line! "<<std::endl;
    if(std::regex_search(res[1].str(),bogus,exprSemiColon)){
     //std::cout<<"It was a semi Colon!"<<std::endl;
      emptyStack(endOfPile);
    }
    else{
      std::smatch res1;
      if(std::regex_search(toBeParse,res1,exprGetLine)){
	Item *I=createItem(res1[2]);
	//std::cout<<"I created an item ";
	if(isContainerFlag){
	 //std::cout<<"container."<<std::endl;
	  S.push(static_cast<Container*>(I));
	}
	else{
	 //std::cout<<"not container."<<std::endl;
	  int difference=S.size()-getDepth(res1);

	  if(difference>=0){
	    multiplePop(difference,endOfPile);
	    S.top()->addItem(I);
	    // addItemInStack(I);
	  }
	  else{
	    //std::cout<<S.size()<<" "<<getDepth(res1)<<"\n";
	    std::cerr<<"Parse error, an object must be in a container! ("<<res1[0].str()<<")"<<std::endl;
	    std::terminate();
	  }
	}
      }
      else{
	std::cerr<<"Parse error, abnormal form for line ("<<res[1].str()<<")."<<std::endl;
      }
    }
    return line;
  }
  
 //std::cout<<S.size()<<" "<<"I didn't found a line."<<std::endl;
  std::string c("");//Empty file.
  std::terminate();
  return c;
}

void ParseurIdl::fillMe(std::string toBeParse){  
  while(!toBeParse.empty()){
    Container* endOfPile;
    toBeParse=fillMeWasHarderThanExpected(toBeParse,endOfPile);
    while(!S.empty()){
      toBeParse=fillMeWasHarderThanExpected(toBeParse,endOfPile);
    }
   //std::cout<<"Stack's empty! "<<std::endl;
    //std::cout<<(endOfPile==NULL)<<std::endl;
    file.push_back(endOfPile);
  }  
}
  

Item* ParseurIdl::createItem(std::string line){//Return in each if, so doesn't matter.
 //std::cout<<S.size()<<" "<<line<<std::endl;

  std::smatch res;
  if(std::regex_search(line,res,exprParenthesis)){//Fonction
    std::smatch parse;
    if(std::regex_search(line,parse,exprFunction)){
     //std::cout<<"It's a Function!"<<std::endl;
      Function* f=new Function(parse[3].str(),parse[2].str(),parse[4].str());
      isContainerFlag=false;
      return f;
    }
    else{
      std::cerr<<line<<" doesn't match a function, to be investigate (ParseurIdl::createItem())."<<std::endl;
      std::terminate();
    }
  }


  if(std::regex_search(line,res,exprAtom)){//Atom
   //std::cout<<"It's an atom!"<<std::endl;
    Atom *a=new Atom(res[4].str(),res[3].str(),res[2].str());
    isContainerFlag=false;
    return a;
  }
  //Not an Atom
  
  if(std::regex_search(line,res,exprC_E_I)){
    std::string myType=res[2].str();
    std::smatch bogus;

    if(std::regex_search(myType,bogus,exprException)){//Exception
     //std::cout<<"It's an exception!"<<std::endl;
      Container* c=new Container(res[3].str(),res[2].str());
      isContainerFlag=true;
      return c;
    }
    else{//Component/Interface
     //std::cout<<"It's an Component or interface!"<<std::endl;
      ContainerInherit* ci=new ContainerInherit(res[3].str(),res[2].str(),res.suffix().str());
      isContainerFlag=true;
      return ci;
    }
  }
  else{
    std::cerr<<"\""<<line<<"\" wasn't understood, syntax error, or maybe i don't know how to treat them yet :)"<<std::endl;
    isContainerFlag=false;
    Item* I=new Item("Unknown","Unknown");
    return I;
  }
}

int ParseurIdl::getDepth(std::smatch& res)const{
  return (int)res[1].str().length();//never under 0, so cast is fine
}

void ParseurIdl::multiplePop(int numberOfTime,Container*& endOfPile){  
  for(int i=1;i<numberOfTime;i++){//if 0 times, doesn't matter.
   //std::cout<<"I like to pop things"<<std::endl;
    if(S.size()){
      Container* temp=S.top();
      S.pop();
      S.top()->addItem(temp);
    }
    else{
      endOfPile=S.top();
      S.pop();
    }
  }
}


void ParseurIdl::emptyStack(Container*& endOfPile){  
 //std::cout<<"I like to empty things"<<std::endl;

  Container* C=S.top();
  S.pop();
  while(!S.empty()){
    S.top()->addItem(C);
    C=S.top();
    S.pop();
  }

  endOfPile=C;
}


void ParseurIdl::showMeThatFile()const{
  std::cout<<"\n";
  std::vector<Container*>::const_iterator end=file.end();
  for(std::vector<Container*>::const_iterator it=file.begin();it!=end;++it){
    (*it)->showMeWhatYouGot();
    std::cout<<"\n\n";
  }
  std::cout<<std::flush;
}
