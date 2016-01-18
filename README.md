Programming Assignment 5
========================

_Your description here_
For this assignment, I continued to use the geocode that I created in PG4, which is an unordered map from streets to segments. I modified the constructor and also the geocode function so that the segment stored nodes now. This made test1 work, as it pointed to the specific nodes connected by a street.

I created a custom class called graph for this assignment, which has a few custom data structures. First, it has a map from ints to a set of ints, which represent the nodes that are connected. It also has a map which basically maps two ints to a length, symbolizing the length of a street segment. It also has the same thing, but for the street name between two nodes instead of the length. These are useful for finding the length and street name in part 5.

I implemented Dijkstra's Algorithm as one single function inside of graph that accouts for all of the test cases (test3-test5). It was easier this way so I did not have to copy and paste code.

I implemented my graph as a directed graph, but it is directed both ways. If I wanted to, I could check for one-way streets before directing it both ways, so that it could not route people the wrong way on one-way roads. 

On my Mac, test5b runs in 42 seconds, but I will gladly take 1 point off for this, as I tried to improve the running time without success for quite a while.

_Grader comments here_
