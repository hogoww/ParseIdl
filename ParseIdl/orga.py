#!/usr/bin/env python3

import re
import os
import sys

truc='truc'
includes=[]
##############################Miscalenious
#   Saute une iteration d'affichage, mais récupère bien le truc.




def cleanComment(string):
    string=re.sub("//.*","",string)#clear comment1
    return re.sub("/\*.*?\*/","",string,0,re.DOTALL)#clear comment2
    #string=string[:len(string)-1]
    #return string

def everyBlankToSpaces(string):
    return re.sub("(\n|\t| )+"," ",string)#vire les blancs pour des espaces (plus pour eviter re.S qu'autre chose..)


def getFile(File):
    if(os.path.isfile(File)):
        FileDesc=open(File,"r")
        content=FileDesc.readlines()
        FileDesc.close()
        #content=cleanComment(content)
        #content=everyBlankToSpaces(content)
        return content
    else:
        print(File+" wasn't find in the directory"+os.getcwd())
        exit()


def parseItems(File):#penser à rajouter les includes#sert à quelque chose si on fait pas de résolution des types?
    startClass=re.compile("^class ")
    endClass=re.compile("^};")
    public=re.compile("\s*public\s*:\s*\n")
    protected=re.compile("^\s*protected\s*:\s*\n")
    private=re.compile("^\s*private\s*:\s*\n")
    nothing=re.compile("^\s*\n")

    D={}
    m="nothing"#mode
    D["nothing"]=[]
    D["public"]=[]
    D["protected"]=[]
    D["private"]=[]
    D["preClass"]=[]
    D["postClass"]=[]
    seenClass=False

    i=0
    while(i<len(File)):#réorganiser le if.
        if(None!=startClass.match(File[i])):
            D["preClass"].append(File[i])
            seenClass=True
            i=i+1
            while(None==endClass.match(File[i])):
                if(nothing.match(File[i])):
                    i=i+1
                    continue
                if(public.match(File[i])):
                    m="public"
                elif(protected.match(File[i])):
                    m="protected"
                elif(private.match(File[i])):
                    m="private"
                else:
                    D[m].append(File[i])
                i=i+1
            D["postClass"].append(File[i])
            i=i+2
        else:
            if(seenClass):
                D["postClass"].append(File[i])
            else:
                D["preClass"].append(File[i])
            i=i+1
    return D

def printLineInFile(descFile,l):
    for i in l:
        descFile.write(i+"")
        
def printInFile(fileName,D):
    parsedFile=open(fileName,'w')
    printLineInFile(parsedFile,D["preClass"])
    #print(D["nothing"])
    #print(D["public"])
    #print(D["protected"])
    #print(D["private"])
    if(len(D["nothing"])):
        printLineInFile(parsedFile,D["nothing"])
    if(len(D["private"])):
        parsedFile.write("private:\n")
        printLineInFile(parsedFile,D["private"])
        parsedFile.write("\n")
    if(len(D["protected"])):
        parsedFile.write("protected:\n")
        printLineInFile(parsedFile,D["protected"])
        parsedFile.write("\n")
    if(len(D["public"])):
        parsedFile.write("public:\n")
        printLineInFile(parsedFile,D["public"])
        parsedFile.write("\n")
    printLineInFile(parsedFile,D["postClass"])
    parsedFile.close()
    

fileName=sys.argv[1]
parsing=parseItems(getFile(fileName))

printInFile(fileName,parsing)
#printMatrice(parsing)
