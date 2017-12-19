#!/usr/bin/env python3
import os, sys, re, shutil

def nbrLigne(tree):
    fichier = open(tree, "r", encoding="ISO-8859-1")
    n = 0
    while fichier.readline():
        n += 1
    return n

def cat(path,input,output):
    if os.path.isfile(path+input):
        output.write(path+input)
        output.write('\n')
        output.write(str(nbrLigne(path+input)))
        output.write('\n')
        shutil.copyfileobj(open(path+input, 'r', encoding="ISO-8859-1"), output)
    else:
        if os.path.isdir(input):
                for file in os.listdir(input):
                    cat(path,input+"/"+file,output)
        else:
            print("Erreur entrée inaccessible. Fatal. "+path+input)
        return

def decat(input):
    if os.path.isfile(input):
        inFile = open(input, "r", encoding="ISO-8859-1")
        fichier = inFile.readlines()
        inFile.close()
        compress = -1;
        for ligne in fichier:
            if compress==-1:
                path = ligne.strip('\n')
                try:
                    os.makedirs(os.path.dirname(path))
                except:
                    pass
                temp = open(path, "w", encoding="ISO-8859-1")
                compress=-2
            else:
                if compress==-2:
                    compress=int(ligne);
                else:
                    if compress>=0:
                        if compress>0:
                            temp.write(ligne)
                            compress=compress-1
                        if compress==0:
                            compress=-1
    else:
        print("Erreur entrée inaccessible. Fatal.")
    return

def compress(input,output="NULL"):
    path, fileName = os.path.split(input)
    if path!="":
        path = path+"/"
    if output=="NULL":
        output=fileName+".huff"
    File = open(path+"~"+output, "w", encoding="ISO-8859-1")
    print(path+ "   et   "+fileName)
    cat(path,fileName,File)
    File.close()
    os.system("./huff -c "+path+"~"+output +" "+ path+output)
    os.remove(path+"~"+output)
    return

def decompress(input):
    path, fileName = os.path.split(input)
    if path!="":
        path = path+"/"
    os.system("./huff -x "+path+fileName +" "+path+"~"+fileName)
    decat(path+"~"+fileName)
    os.remove(path+"~"+fileName)

if (len(sys.argv)!=3):
    print("No enough/Too many argument.");
else:
    if re.search("^-[c]?[x]?$",sys.argv[1]):
        if re.search("c",sys.argv[1]):
            compress(sys.argv[2])
        if re.search("x",sys.argv[1]):
            decompress(sys.argv[2])
    else:
        print(sys.argv[1], " is not a correct argument.");
exit();
