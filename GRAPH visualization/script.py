import networkx as nx
import matplotlib.pyplot as plt
from operator import itemgetter
import os
import subprocess


# create graph
g=nx.Graph()
"""
subprocess.call("a.exe",shell=True)
subprocess.run("a.exe",shell=True)
"""


"""
# Taking inputs
inputs=input(" no.of nodes &edges").split(' ')
number_nodes=int(inputs[0])
number_edges=int(inputs[1])
"""

# Taking inputs from file

file=open("input.txt","r")
lines=file.readlines()
inputs =lines[0].split(' ')
number_nodes=int(inputs[0])
number_edges=int(inputs[1])


"""
# Taking edges
edges=[]

while len(edges)<number_edges :
    node1=int(input("source:"))
    node2=int(input("destination:"))
    weight=int(input("weight:"))
    #creating edges
    edges.append((node1,node2,{'weight':weight}))
edges    
"""

#Taking edges from file
edges=[]

for i in range(1,len(lines)):

    inputs=lines[i].split(' ')
    inputs
    node1=int(inputs[0])
    node2=int(inputs[1])
    weight=int(inputs[2])
    #creating edges
    edges.append((node1,node2,{'weight':weight}))


#adding edges to graph
g.add_edges_from(edges)


node_centre=list(g.degree(g.nodes))
sorted_node_centre=sorted(node_centre,key=itemgetter(1),reverse=True)
levels=[]
levels.append(sorted_node_centre[0][1])
for i in range(1,len(sorted_node_centre)):
    if(sorted_node_centre[i][1]!= levels[len(levels)-1]):
        levels.append(sorted_node_centre[i][1])

cols=['red','blue','green','yellow']




node_colors=[]
for i in node_centre:
    
    
    if(len(levels)==1):
         node_colors.append(cols[0])
     
    elif(len(levels)==2):
        
        if(i[1]==levels[0]):
            node_colors.append(cols[0])
        else:
             node_colors.append(cols[1])
    
    elif(len(levels)>=3):
        
        if(i[1]==levels[0]):
            node_colors.append(cols[0])
        elif (i[1]==levels[1]):
             node_colors.append(cols[1])
        elif (i[1]==levels[2]):
            node_colors.append(cols[2])   
        else:
             node_colors.append(cols[3])     
        
        """
print(levels)    
print(node_colors)
print(node_centre)
sorted_node_centre
 """

#labels of edges
pos=nx.spring_layout(g)
nx.draw(g,pos,node_color=node_colors,node_size=900,with_labels=True)
labels = nx.get_edge_attributes(g,'weight')
nx.draw_networkx_edge_labels(g,pos,edge_labels=labels)
plt.savefig("degree centrality")
print("///////////DEGREE CENTRALITY////////////")
print(g.degree(g.nodes))
plt.show()#degree centrality


closness=[]
close_colors=[]
for node in node_centre:
    
    closness.append((node[0],nx.closeness_centrality(g,node[0],'weight')))
    
sorted_node_close=sorted(closness,key=itemgetter(1),reverse=True)


levels=[]
levels.append(sorted_node_close[0][1])
for i in range(1,len(sorted_node_close)):
    if(sorted_node_close[i][1]!= levels[len(levels)-1]):
        levels.append(sorted_node_close[i][1])

cols=['red','blue','green','yellow']   


node_colors=[]
for i in closness:
    
    
    if(len(levels)==1):
         node_colors.append(cols[0])
     
    elif(len(levels)==2):
        
        if(i[1]==levels[0]):
            node_colors.append(cols[0])
        else:
             node_colors.append(cols[1])
    
    elif(len(levels)>=3):
        
        if(i[1]==levels[0]):
            node_colors.append(cols[0])
        elif (i[1]==levels[1]):
             node_colors.append(cols[1])
        elif (i[1]==levels[2]):
            node_colors.append(cols[2])   
        else:
             node_colors.append(cols[3])     
                
                
        


#labels of edges
pos=nx.spring_layout(g)
nx.draw(g,pos,node_color=node_colors,node_size=900,with_labels=True)
labels = nx.get_edge_attributes(g,'weight')
nx.draw_networkx_edge_labels(g,pos,edge_labels=labels)
plt.savefig("closeness centrality")
print("//////////CLOSENESS CENTRALITY//////////")
print(closness)
plt.show()# closness centrality

#open pictures
#os.startfile("closeness centrality.png")
#os.startfile("degree centrality.png")


#Run c++ app
#os.startfile("a.exe")

bet=nx.betweenness_centrality(g,None,False,'weight')
bet


levels=[]
for i in range(len(bet)):
    if(~(bet.get(i)in levels)):
        levels.append(bet.get(i))
        

levels=list(set(levels))
levels=sorted(levels)
levels.reverse()


node_colors=[]
cols=['red','blue','green','yellow']   

for i in bet.items():
    
    
    if(len(levels)==1):
         node_colors.append(cols[0])
     
    elif(len(levels)==2):
        
        if(i[1]==levels[0]):
            node_colors.append(cols[0])
        else:
             node_colors.append(cols[1])
    
    elif(len(levels)>=3):
        
        if(i[1]==levels[0]):
            node_colors.append(cols[0])
        elif (i[1]==levels[1]):
             node_colors.append(cols[1])
        elif (i[1]==levels[2]):
            node_colors.append(cols[2])   
        else:
             node_colors.append(cols[3])     
                
                
        



#labels of edges
pos=nx.spring_layout(g)
nx.draw(g,pos,node_color=node_colors,node_size=900,with_labels=True)
labels = nx.get_edge_attributes(g,'weight')
nx.draw_networkx_edge_labels(g,pos,edge_labels=labels)
plt.savefig("betweeness centrality")
print("////////////BETWEENESS CENTRALITY////////////")
print(bet)
plt.show()# betweeness centrality


"""
#open pictures
os.startfile("closeness centrality.png")
os.startfile("degree centrality.png")

"""

#Run c++ app
os.startfile("a.exe")