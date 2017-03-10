#!/usr/bin/env python3

import re
import os
import sys

truc='truc'

##############################Miscalenious
#   Saute une iteration d'affichage, mais récupère bien le truc.

def printLine(l,p=0):
    for i in l:
        if isinstance(i,list):
            printLine(i,p+1)
        else:
            s=""
            for j in range(p):
                s=s+' '
            print(s+i)

def printMatrice(mat):
    for i in mat:
        printLine(i)
        print("--------------------")




def printLineInFile(descFile,l,p=0):
    if(p):
        p1=p-1
    else:
        p1=0
    i=1;

    s=""
    for j in range(p1):
        s=s+' '
    descFile.write(s+l[0]+"\n")

    if(p):
        s=s+' '

    length=len(l)
    while(i<length):
        if isinstance(l[i],list):
            printLineInFile(descFile,l[i],p+1)
        else:
            descFile.write(s+l[i]+"\n")
        i=i+1

def printInFileMatrice(descFile,mat):
    for i in mat:
        printLineInFile(descFile,i)
        descFile.write(";\n")




def clean(string):
    string=re.sub("//.*","",string)#clear comment1
    string=re.sub("/\*.*?\*/","",string,0,re.DOTALL)#clear comment2
    return re.sub("(\n|\t| )+"," ",string)#vire les blancs pour des espaces (plus pour eviter re.S qu'autre chose..)
    #string=string[:len(string)-1]
    #return string



def getFile(File):
    if(os.path.isfile(File)):
        FileDesc=open(File,"r")
        content=FileDesc.read()
        FileDesc.close()
        return content
    else:
        print("\n"+File+" wasn't find in the directory"+os.getcwd()+"\n")
        exit()


def parseItems(ligne):#penser à rajouter les includes#sert à quelque chose si on fait pas de résolution des types?
    if(not re.search("{",ligne)):#ergo pas(plus) d'items IDL à récup
        return []
    pile=[]
    res=[]
    split=re.split("{",ligne,1)
    rest=split[1]
    res.append(split[0])
    pile.append(res)

    while pile and rest:#tant qu'il y a du texte

        search=re.search("^ ?([^{}]*?);(.*)",rest)
        if search:#l'instruction suivante, est atomique
            
            pile[len(pile)-1].append(search.group(1))#on rajoute le bout suivant
            rest=search.group(2)#on passe à la suite

        elif re.search("^ ?};.*",rest):#fin de bloc #vraiment le seul cas..?
            res=pile.pop()
            rest=re.split(";",rest,1)[1]#on enleve la fin du bloc
            rest=rest[1:]

            if pile:#sinon la pile est vide, et on passe on sort de la boucle
                pile[len(pile)-1].append(res)#on rajoute la branche qu'on vient de faire
            
        else:#bloc imbriqué
            split=re.split("{",rest,1)
            t=split[0]
            if(t[0]==" "):#virer l'espace de devant, pour une évaluation propre
                t=t[1:]
            pile.append([])
            pile[len(pile)-1].append(t)
            rest=split[1]

    return [res]+parseItems(rest)
            
def printInFile(fileName,text):
    parsedFile=open(fileName+".letsCompileIt",'w')
    printInFileMatrice(parsedFile,text)
    parsedFile.close()
    

parsing=parseItems(clean(getFile(sys.argv[1])))

printInFile(sys.argv[1],parsing)

