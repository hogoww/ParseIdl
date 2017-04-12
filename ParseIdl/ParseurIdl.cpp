#include "ParseurIdl.h"

const std::regex ParseurIdl::exprLine("(.*)\\n",std::regex::optimize);
const std::regex ParseurIdl::exprSemiColon(";",std::regex::optimize);
const std::regex ParseurIdl::exprGetLine("( *)(.*)\n",std::regex::optimize);

const std::regex ParseurIdl::exprInclude("^#((?:\\w|\\.)+)\n",std::regex::optimize);
const std::regex ParseurIdl::exprParenthesis("\\(",std::regex::optimize);//Function
const std::regex ParseurIdl::exprFunction("( *)(\\w+) (\\w+) ?(\\(.*\\))",std::regex::optimize);//parseFunction
const std::regex ParseurIdl::exprAtom("^( )*(\\w+) (\\w+) (\\w+) ?",std::regex::optimize);//Attrib
const std::regex ParseurIdl::exprC_E_I("^( *)(\\w+) (\\w+) ?");//Component | Exception | Interface 

const std::regex ParseurIdl::exprException("exception",std::regex::icase|std::regex::optimize);
//Similaires dans la structure
const std::regex ParseurIdl::exprInterface("interface",std::regex::icase|std::regex::optimize);
const std::regex ParseurIdl::exprComponent("component",std::regex::icase|std::regex::optimize);
const std::regex ParseurIdl::exprSemiColonAndBackN(".*;.*\\n",std::regex::optimize);
const std::regex ParseurIdl::exprIncludedWithColon(".* (\\w+) ?:.*\\n",std::regex::optimize);
const std::regex ParseurIdl::exprIncludedFunction(".*? (\\w+) ?\\(.*\\n",std::regex::optimize);
const std::regex ParseurIdl::exprIncludedNormal(".* (\\w+) ?\\n",std::regex::optimize);

bool ParseurIdl::isContainerFlag=false;



/******Constructeurs:******/


/* constructeurs public*/
ParseurIdl::ParseurIdl(std::string fileToParse):file(),fileName(fileToParse){
  //std::cout<<fileToParse<<std::endl;

  //Init class
  S=new std::stack<Container*>();
  componentNames=new std::set<std::string>();
  includes=new std::set<std::string>();
  includes->insert(fileName);//To avoid looping once on the file we're parsing.
  std::string fileName(fileToParse);


  std::string content;//will be initialised in getFile
  try{
    getFile(fileName,content); 
  }
  catch(DidNotFoundFileExcep& DNFF){
    std::cerr<<DNFF.what()<<std::endl;
    std::terminate();
  }
  //std::cout<<"Done loading the file"<<std::endl;
  
  std::set<std::string>* newIncludes=getIncludes(content);//already in the class attribute
  fillMe(content);
  launchTreatmentIncludedFiles(newIncludes);
  delete newIncludes;
 
  
  //to add in the destructor when you'll stop doing a hundred thing at the same time
  //delete things it won't use anymore.
  delete S;//empty at the end, so safe to call.
  delete componentNames;//operation will return this later. Memory economy.
  // S=NULL;//Avoid random uses, shouldn't be used after this time.
  // componentNames=NULL;
}

void ParseurIdl::getFile(std::string& filename,std::string& content) throw (DidNotFoundFileExcep){
  std::string command("./parse.py ");
  command+=filename;
  std::system(command.c_str());
  std::string tempName(filename+".letsCompileIt");

  try{
    content=FileToString(tempName);
  }
  catch(DidNotFoundFileExcep& DNFF){
    throw DNFF;
  }
  // std::cout<<content<<std::endl;
  // command="cat -A ";
  // command+=tempName;
  // std::system(command.c_str());
  // std::cout<<"----------\n";

  // command="wc ";
  // command+=tempName;
  // std::system(command.c_str());
  // std::cout<<"----------\n";

  command="rm ";
  command+=tempName;
  std::system(command.c_str());
}

ParseurIdl::~ParseurIdl(){
  delete includes;
  std::vector<Container*>::iterator end=file.end();
  for (std::vector<Container*>::iterator it = file.begin();it!=end;++it){
    delete *it;
  }
  file.clear();
}


std::set<std::string>* ParseurIdl::getIncludes(std::string& ToBeParse){
  std::set<std::string>* newestIncludes=new std::set<std::string>();
  std::smatch res;
  while(std::regex_search(ToBeParse,res,exprInclude)){
    std::string name(res[1].str());
    //std::cout<<name<<std::endl;
    if(includes->insert(name).second){
      newestIncludes->insert(name);
    }
    ToBeParse=res.suffix();
  }
  return newestIncludes;
}

void ParseurIdl::launchTreatmentIncludedFiles(std::set<std::string>* newIncludes){
  std::set<std::string>::iterator end=newIncludes->end();
  for(std::set<std::string>::iterator it=newIncludes->begin();it!=end;++it){
    treatmentIncludedFiles(*it);
  }
}

void ParseurIdl::treatmentIncludedFiles(std::string name){
  std::string content;
  try{
    getFile(name,content);
  }
  catch(DidNotFoundFileExcep& d){
    std::cerr<<d.what()<<"\n"<<std::endl;//No need to interrupt, as long as we don't precisely check types.
  }
  std::set<std::string>* newIncludes=getIncludes(content);
  getNamesInIncludedFiles(content);
  launchTreatmentIncludedFiles(newIncludes);
  delete newIncludes;
}

void ParseurIdl::getNamesInIncludedFiles(std::string& content){
  std::smatch res;
  std::string name;
  while(!content.empty()){
    if(std::regex_search(content,res,exprIncludedWithColon)){}
    else{
      if(std::regex_search(content,res,exprIncludedFunction)){}
      else{
	if(std::regex_search(content,res,exprIncludedNormal)){}
	else{
	  if(std::regex_search(content,res,exprSemiColonAndBackN)){//end of a component, nothing to get
	    return;
	  }
	  else{
	    std::regex_search(content,res,exprLine);
	    //std::cout<<"Weird no match on line :"<<res[1].str()<<"\"\n in getNamesInIncludedFiles"<<std::endl;
	    return;
	  }
	}
      }
    }
    name=res[1].str();
    if(!componentNames->insert(name).second){
      nameAppearedTwice(name);
    }
    //std::cout<<name<<std::endl;
    content=res.suffix();
  }
}

/******Methodes:******/
/* methodes public*/
const std::vector<Container*> ParseurIdl::getFileContent()const{
  return file;
}

std::string ParseurIdl::getFileName()const{
  return fileName;
}

std::string ParseurIdl::FileToString(std::string fileName) throw (DidNotFoundFileExcep){
  std::ifstream stream(fileName);
  if(stream){
    //get length of file:
    stream.seekg(0,stream.end);
    int length=stream.tellg();
    stream.seekg(0,stream.beg);

    char* buffer=new char[length+1];

    stream.read(buffer,length);
    buffer[length]='\0';//So String does know where it ends...

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
    throw DidNotFoundFileExcep(fileName);
  }
}
  

std::string ParseurIdl::fillMeWasHarderThanExpected(std::string& toBeParse,Container*& endOfPile){
  //std::cout<<toBeParse<<std::endl;;
  std::smatch res;
  if(std::regex_search(toBeParse,res,exprLine)){
    std::string line=res.suffix().str();
    //std::cout<<line<<"\n-----------"<<std::endl;
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
	  S->push(static_cast<Container*>(I));
	}
	else{
	 //std::cout<<"not container."<<std::endl;
	  int difference=S->size()-getDepth(res1);

	  if(difference>=0){
	    multiplePop(difference,endOfPile);
	    S->top()->addItem(I);
	    // addItemInStack(I);
	  }
	  else{
	    //std::cout<<S->size()<<" "<<getDepth(res1)<<"\n";
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
  
  //Weird bug that 7 hours didn't allow me to find.... can't let it.
  //std::cout<<S->size()<<" "<<"I didn't found a line."<<std::endl;
  std::string c("");//Empty file.
  // std::cout<<toBeParse<<"\n";
  // std::cerr<<"in FMWHTE, to be investigate";
  // std::terminate();
  return c;
}

void ParseurIdl::fillMe(std::string& toBeParse){  
  while(!toBeParse.empty()){
    Container* endOfPile;
    toBeParse=fillMeWasHarderThanExpected(toBeParse,endOfPile);
    while(!S->empty()){
      toBeParse=fillMeWasHarderThanExpected(toBeParse,endOfPile);
    }
   //std::cout<<"Stack's empty! "<<std::endl;
    //std::cout<<(endOfPile==NULL)<<std::endl;
    file.push_back(endOfPile);
  }  
}
  
void ParseurIdl::nameAppearedTwice(std::string& name){
  std::cout<<"You can't use "<<name<<" twice !"<<std::endl;
  std::terminate();
}


Item* ParseurIdl::createItem(std::string line){//Return in each if, so doesn't matter.
 //std::cout<<S->size()<<" "<<line<<std::endl;

  std::smatch res;
  if(std::regex_search(line,res,exprParenthesis)){//Fonction
    std::smatch parse;
    if(std::regex_search(line,parse,exprFunction)){
     //std::cout<<"It's a Function!"<<std::endl;
      std::string nom=parse[3].str();
      if(!componentNames->insert(nom).second){
	nameAppearedTwice(nom);
      }
      Function* f=new Function(nom,parse[2].str(),parse[4].str());
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
    std::string nom=res[4].str();
    if(!componentNames->insert(nom).second){
      nameAppearedTwice(nom);
    }    
    Atom *a=new Atom(nom,res[3].str(),res[2].str());
    isContainerFlag=false;
    return a;
  }
  //Not an Atom
  
  if(std::regex_search(line,res,exprC_E_I)){
    std::string myType=res[2].str();
    std::smatch bogus;

    if(std::regex_search(myType,bogus,exprException)){//Exception
      //std::cout<<"It's an exception!"<<std::endl
      std::string nom=res[3].str();
      if(!componentNames->insert(nom).second){
	nameAppearedTwice(nom);
      }
      Container* c=new Container(nom,res[2].str());
      isContainerFlag=true;
      return c;
    }
    else{//Component/Interface
     //std::cout<<"It's an Component or interface!"<<std::endl;
      std::string nom=res[3].str();
      if(!componentNames->insert(nom).second){
	nameAppearedTwice(nom);
      }
      ContainerInherit* ci=new ContainerInherit(nom,res[2].str(),res.suffix().str());
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

void ParseurIdl::multiplePop(int& numberOfTime,Container*& endOfPile){  
  for(int i=1;i<numberOfTime;i++){//if 0 times, doesn't matter.
   //std::cout<<"I like to pop things"<<std::endl;
    if(S->size()){
      Container* temp=S->top();
      S->pop();
      S->top()->addItem(temp);
    }
    else{
      endOfPile=S->top();
      S->pop();
    }
  }
}


void ParseurIdl::emptyStack(Container*& endOfPile){  
 //std::cout<<"I like to empty things"<<std::endl;

  Container* C=S->top();
  S->pop();
  while(!S->empty()){
    S->top()->addItem(C);
    C=S->top();
    S->pop();
  }

  endOfPile=C;
}

// std::vector<std::string> getAllIdInFile(){
// }


void ParseurIdl::showMeThatFile()const{
  std::setvbuf(stdout, nullptr, _IOFBF, BUFSIZ);//Switch to fully buffered mode
  std::cout<<std::nounitbuf;
  std::cout<<"\n";
  std::vector<Container*>::const_iterator end=file.cend();
  for(std::vector<Container*>::const_iterator it=file.cbegin();it!=end;++it){
    (*it)->showMeWhatYouGot();
    std::cout<<"\n";
  }
  std::cout<<std::flush;
}

void ParseurIdl::checkForInterfaceInheritance(){//maybe switch to file.doIInheritFromYou, less code duplication
  std::vector<Container*>::iterator end=file.end();
  for(std::vector<Container*>::iterator it=file.begin();it!=end;++it){
    (*it)->doIInheritFromYou();
  }
}
