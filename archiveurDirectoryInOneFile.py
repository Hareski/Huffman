#!/usr/bin/env python3
import os, sys, re, shutil

def nbrLigne(tree):
    fichier = open(tree, "r", encoding="ISO-8859-1")
    n = 0
    while fichier.readline():
        n += 1
    return n

def compress(input,output="NULL"):
    if output=="NULL":
        output=input+'.huff'
    if os.path.isfile(input):
        out = open(output, "w", encoding="ISO-8859-1")
        out.write(input)
        out.write('\n')
        os.system("./huff -c "+ input +" "+ output+".temp")
        out.write(str(nbrLigne(output+".temp")))
        out.write('\n')
        shutil.copyfileobj(open(output+".temp", 'r', encoding="ISO-8859-1"), out)
        out.close()
        os.remove(output+".temp")
    else:
        if os.path.isdir(input):
            list_original_file = []
            sub_compress(input,list_original_file)
            out = open(output, "w", encoding="ISO-8859-1")
            for file in list_original_file:
                out.write(input+file)
                out.write('\n')
                out.write(str(nbrLigne(input+"_huff"+file)))
                out.write('\n')
                shutil.copyfileobj(open(input+"_huff"+file, 'r', encoding="ISO-8859-1"), out)
                out.write('\n')
            out.close()
            shutil.rmtree(input+"_huff")
        else:
            print("Erreur entrée inaccessible. Fatal.")
    return

def sub_compress(path,list_original_file,input=""):
    if os.path.isfile(path+input):
        os.system("./huff -c "+ path + "/" + input +" "+ path+"_huff/"+input)
        list_original_file.append(input)
    else:
        if os.path.isdir(path+input):
            if not(os.path.isdir(path+"_huff"+input)):
                os.mkdir(path+"_huff"+input);
                for file in os.listdir(path+input):
                    sub_compress(path,list_original_file,input+"/"+file)
            else:
                print("Verifiez que la compression n'est pas déja effectué ou supprimez le dossier _huff. Fatal.")
                return
        else:
            print("Erreur entrée inaccessible. Fatal. "+path+input)
    return

def decompress(input):
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
                temp = open(path+".huff.temp", "w", encoding="ISO-8859-1")
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
                            temp.close()
                            os.system("./huff -x "+path+".huff.temp " + path )
                            os.remove(path+".huff.temp")
                            compress=-1
    else:
        print("Erreur entrée inaccessible. Fatal.")
    return


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
