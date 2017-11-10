# -*- coding: utf-8 -*-
"""
Created on Mon Oct 23 12:56:54 2017

@author: cvbrasil
"""

from numpy import genfromtxt
my_data1 = genfromtxt('/home/cvbrasil/Documentos/C++/Trabalhos/Trabalho4/Template oficial/cmake_template-master/build/TabelasTrab4Simul1mat.csv', delimiter=',',dtype=None)


from numpy import genfromtxt
my_data2 = genfromtxt('/home/cvbrasil/Documentos/C++/Trabalhos/Trabalho4/Template oficial/cmake_template-master/build/TabelasTrab4Analit1mat.csv', delimiter=',',dtype=None)

from numpy import genfromtxt
my_data3 = genfromtxt('/home/cvbrasil/Documentos/C++/Trabalhos/Trabalho4/Template oficial/cmake_template-master/build/TabelasTrab4erroMAX1mat.csv', delimiter=',',dtype=None)

from numpy import genfromtxt
my_data4 = genfromtxt('/home/cvbrasil/Documentos/C++/Trabalhos/Trabalho4/Template oficial/cmake_template-master/build/SolucaoAnalitica2Mat.csv', delimiter=',',dtype=None)

from numpy import genfromtxt
my_data5 = genfromtxt('/home/cvbrasil/Documentos/C++/Trabalhos/Trabalho4/Template oficial/cmake_template-master/build/DoisMatQpreConvInterpDesalinhada.csv', delimiter=',',dtype=None)

from numpy import genfromtxt
my_data6 = genfromtxt('/home/cvbrasil/Documentos/C++/Trabalhos/Trabalho4/Template oficial/cmake_template-master/build/DoisMatQpreConvResistDesalinhada.csv', delimiter=',',dtype=None)

Tanalit = []
Tsimul = []
DistOrigem = []
NumDePontos = []
Erro = []
Tanalit2mat = []
Tinterp = []
Tresist = []
X = []

for m in range(0,len(my_data2)):
    Tanalit.append(my_data2[m][0])
    DistOrigem.append(my_data2[m][1])
    
for m in range(0,len(my_data1)):
    Tsimul.append(my_data1[m][0])
    
for m in range(0,len(my_data3)):
    NumDePontos.append(my_data3[m][1])
    
for m in range(0,len(my_data3)):
    Erro.append(my_data3[m][0])
    
for m in range(0,len(my_data4)):
    Tanalit2mat.append(my_data4[m][0])
    
for m in range(0,len(my_data5)):
    Tinterp.append(my_data5[m][0])

for m in range(0,len(my_data6)):
    Tresist.append(my_data6[m][0])
    
for m in range(0,len(my_data4)):
    X.append(my_data4[m][1])


import numpy as np

Tanalit = np.array(Tanalit)
Tsimul = np.array(Tsimul)
DistOrigem = np.array(DistOrigem)
NumDePontos = np.array(NumDePontos)

import matplotlib.pyplot as TsimulGraph
TsimulGraph.plot(DistOrigem,Tsimul,linewidth=1)
TsimulGraph.plot(DistOrigem,Tsimul,'ko')
TsimulGraph.ylabel('Tsimul')
TsimulGraph.xlabel('x')
TsimulGraph.savefig('/home/cvbrasil/Documentos/Latex/Trabalhos/Trabalho4/Tsimul1mat.png')
TsimulGraph.close()

import matplotlib.pyplot as TanalitGraph
TanalitGraph.plot(DistOrigem,Tanalit,linewidth=1)
TanalitGraph.plot(DistOrigem,Tanalit,'ko')
TanalitGraph.ylabel('Tanalit')
TanalitGraph.xlabel('x')
TanalitGraph.savefig('/home/cvbrasil/Documentos/Latex/Trabalhos/Trabalho4/Tanalit1mat.png')
TanalitGraph.close()

import matplotlib.pyplot as ErroGraph
ErroGraph.plot(NumDePontos,Erro,linewidth=1)
ErroGraph.plot(NumDePontos,Erro,'ko')
ErroGraph.ylabel('ErroMax')
ErroGraph.xlabel('NumeroDeVC')
ErroGraph.savefig('/home/cvbrasil/Documentos/Latex/Trabalhos/Trabalho4/Erro1mat.png')
ErroGraph.close()

import matplotlib.pyplot as DoisMat
DoisMat.plot(X,Tanalit2mat,linewidth=1)
DoisMat.plot(X,Tanalit2mat,'g--')
DoisMat.plot(X,Tinterp,linewidth=1)
DoisMat.plot(X,Tinterp,'bs')
DoisMat.plot(X,Tresist,linewidth=1)
DoisMat.plot(X,Tresist,'r^')
DoisMat.ylabel('T')
DoisMat.xlabel('x')
DoisMat.savefig('/home/cvbrasil/Documentos/Latex/Trabalhos/Trabalho4/DoisMat.png')
DoisMat.close()