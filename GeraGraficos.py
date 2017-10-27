# -*- coding: utf-8 -*-
"""
Created on Mon Oct 23 12:56:54 2017

@author: cvbrasil
"""

from numpy import genfromtxt
my_data1 = genfromtxt('/home/cvbrasil/Documentos/C++/Trabalhos/Trabalho4/Template oficial/cmake_template-master/build/TabelasTrab4Simul1mat.csv', delimiter=',',dtype=None)


from numpy import genfromtxt
my_data2 = genfromtxt('/home/cvbrasil/Documentos/C++/Trabalhos/Trabalho4/Template oficial/cmake_template-master/build/TabelasTrab4Analit1mat.csv', delimiter=',',dtype=None)

Tanalit = []
Tsimul = []
DistOrigem = []
NumDePontos = []

for m in range(0,len(my_data2)):
    Tanalit.append(my_data2[m][0])
    DistOrigem.append(my_data2[m][1])
    
for m in range(0,len(my_data1)):
    Tsimul.append(my_data1[m][0])
    
for m in range(0,len(Tsimul)):
    NumDePontos.append(m+1)

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