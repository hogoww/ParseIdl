#include "rule.h"

using namespace std;

Rule::Rule():nom(""),regex(""),atome(false){
}

Rule::~Rule(){
}

void Rule::setName(string nom){
  this->nom=nom;
}

void Rule::setRegex(string regex){
  //Rajouter traitement du string...
  this->regex=regex;
}

void Rule::setAtome(){
  if(this->atome)
    {
      cout<<"trying to set an atome to true, even thought it's already one...\nObjet Rule de nom:"<<this->nom<<"."<<endl;
      terminate();
    }
  else
    this->atome=true;
}

bool Rule::isAtome() const{
  return this->atome;
}

vector<string>* Rule::checkIfIsAtome() const{
  string buffer("");
  vector<string> *v=new vector<string>();
  bool quote=false;
  int despecialise=0;
  int size=regex.size();

  for(int i=0;i<size;i++){
    switch(regex[i]){
    case('\''):{
      if(!despecialise){
	quote=!quote;
      }
      buffer="";
      break;
    }
    case('\\'):{
      if(!despecialise)
	despecialise=2;
      break;
    }
    case('\t'):
    case('\n'):
    case('*'):
    case('+'):
    case(')'):
    case('('):
    case('?'):
    case(' '):{
      if(!quote){
	if(!buffer.empty()){
	  v->push_back(buffer);
	  cout<<buffer<<'\n';
	  buffer="";
	}
      }
    }
    case('|'):{
      break;
    }
    default:{
      if(!quote){
	buffer+=regex[i];
      }
    }
      
    }
  }
  if(!buffer.empty()){
    v->push_back(buffer);//pour un dernier buffer qui finirais sur une id..
  }
  cout<<endl;
  return v;
}

void Rule::reset(){
  nom="";
  regex="";
  //Atome n'as pas été touché au moment du reset. Donc pas nécessaire pour l'instant.
}

string Rule::toString() const{
  return this->nom+" : "+this->regex;
}
