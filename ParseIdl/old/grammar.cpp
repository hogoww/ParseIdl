#include "grammar.h"

using namespace std;

Grammar::Grammar(){

}

Grammar::~Grammar(){
}


void Grammar::addRule(Rule r){
  this->Rules.push_back(r);			
}

// void Grammar::Depth(){
//   int size=Rules.size();
//   bool* seen=new bool[size];
//   for(int i=0;i<size;i++){
//     seen[i]=false;
//     Rules[i].checkIfIsAtome();
//   }
//   int time=0;
//   DepthRec(seen,&time);

  

//   del []seen;
// }

// void Grammar::DepthRec(bool* seen,int* time,string Recherche){
  
// }

void Grammar::getGrammar(string filename){
  ifstream f(filename.c_str(),ifstream::in);
  if(!f){
    cout<<"file "<<filename<<" didn't open properly."<<endl;
  }
  
  char c;
  string buffer;
  bool quote=false;
  int despecialise=0;
  Rule temp;
  while(f){
    c=(char)f.get();
    switch(c)
      {
      case ':' :
	{
	  if(!quote){
	    temp.setName(buffer);//Maybe clean \n \t & stuff before flushing.
	    buffer="";
	  }
	  else
	    {
	      buffer+=c;
	    }
	  break;
	}
      case '\n' :
      case '\t' :
	{    
	  break;
	}
      case '\'' :
	{
	  if(!despecialise){
	    quote=!quote;
	  }
	  buffer+=c;
	  break;
	}
      case ';' :
	{
	  if(quote)
	    buffer+=c;
	  else//on fini une regle
	    {
	      temp.setRegex(buffer);
	      addRule(temp);
	      buffer="";
	      temp.reset();
	    }
	  break;
	}
      case '\\':
	{
	  if(despecialise){
	    buffer+=c;
	  }
	  else{
	    despecialise=2;//décrémenté immédiatement à 1, puis après le char suivant redeviens nul. pas fou.
	  }
	  break;
	}
      default :
	buffer+=c;
      }
    if(despecialise)
      despecialise--;
  }
  
  // int j=Rules.size();
  // for(int i=0;i<j;i++){
  //   Rules[i].checkIfIsAtome();
  // }
  // cout<<endl;

  f.close();
}

void Grammar::showMeThatGrammar() const{
  int j=Rules.size();
  for(int i=0;i<j;i++){
    cout<<Rules[i].toString()<<"\n\n";
    Rules[i].checkIfIsAtome();
    cout<<"\n\n";
  }
  cout<<endl;
  
  Rules[0].checkIfIsAtome();
}	        
