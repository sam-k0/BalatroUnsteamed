# Credits to the man who showed me how Balatro compresses its files, problemsalved
# Also worth noting you NEED python 3.11, otherwise zlib.compress() will be fucked.
# Also thanks to Microsoft updating python is pain in the *ace* so please save your braincells and just use linux.

import os
import zlib 
def GetCurrentDirectory():
    return os.getcwd()

def ReadBinary(path):
    with open(path, "rb") as f:
        data = f.read()
        return data

def ReadText(path):
    with open(path, "r") as f:
        data = f.read()
        return data

def Decompress(bindata):
    return zlib.decompress(bindata, wbits=-zlib.MAX_WBITS)

def Compress(save_file_data):
        return zlib.compress(save_file_data, level=1)


def dump():
    fpath = GetCurrentDirectory()+"\\py\\profileNEW.jkr"
    text = str(Decompress(ReadBinary(fpath)), encoding='ascii')
    # save this to a file
    with open("profile.txt", "w") as f:
        f.write(text)

def recompress(): # reads a dumped file and recompresses it
    text = ReadText(GetCurrentDirectory()+"\\profileDumpedOrig.txt")
    savdata = Compress(bytes(text, encoding='ascii'))
    savepath = GetCurrentDirectory()+"\\py\\profileNEW.jkr"
    with open(savepath, "wb") as f:
        f.write(savdata)

recompress()
