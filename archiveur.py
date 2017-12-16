#!/usr/bin/env python3
import os, sys, re;

def compress(input,output="NULL"):
    if output=="NULL":
        output=input
    if os.path.isfile(input):
        file=os.popen("./Huffman -c "+input+" "+output+".huff", "r").read
    else:
        if os.path.isdir(input):
            if not(os.path.isdir(input+"_huff")):
                os.mkdir(output+"_huff");
                for file in os.listdir(input):
                    compress(input+"/"+file,output+"_huff/"+file)
            else:
                print("Verifiez que la compression n'est pas déja effectué ou supprimez le dossier _huff. Fatal.")
                return
        else:
            print("Erreur entrée inaccessible. Fatal.")
    return

def decompress(input,output="NULL"):
    if output=="NULL":
        output=input
    if os.path.isfile(input):
        file=os.popen("./Huffman -x "+input+" "+output+".dec", "r").read;
    else:
        if os.path.isdir(input):
            if not(os.path.isdir(input+"_dec")):
                os.mkdir(output+"_dec");
                for file in os.listdir(input):
                    decompress(input+"/"+file,output+"_dec/"+file)
            else:
                print("Verifiez que la decompression n'est pas déja effectué ou supprimez le dossier _dec. Fatal.")
                return
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
