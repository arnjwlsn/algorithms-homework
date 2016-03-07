# Aaron Wilson
# Zach Wilson
# March 3, 2016
# generator.py

# Traveling salesman location generator

import sys
import random
import math
import os

# Take two arguments: (1) range (2) size
if len(sys.argv) is not 3:
  sys.exit('ERROR: invalid number of arguments: (1) range (2) size.')
elif not sys.argv[1].isdigit():
  sys.exit('ERROR: argument 1 is not a digit!')
elif not sys.argv[2].isdigit():
  sys.exit('ERROR: argument 2 is not a digit!')

# Graph will be a list of tuples
graph = []

maxrange = int(sys.argv[1])
size = int(sys.argv[2])

# Creates a tuple of random x and random y coordinates
def get_random_tuple():
  x = random.randint(0, maxrange)
  y = random.randint(0, maxrange)
  return (x, y)

# Load up the list full of randomly generated tuples
counter = 0;
while counter < size:
  tup = get_random_tuple()
  if not tup in graph:
    graph.append(tup)
    counter += 1

# Distance formula
def get_distance(one, two):
  x = (float) (two[0] - one[0])**2
  y = (float) (two[1] - one[1])**2
  return math.sqrt(x + y)

# Define matrix to contain distances
matrix = [[0 for x in range(size)] for x in range(size)] 

# Populate matrix with distances every pair of tuples
for i in xrange(0, size-1):
  for j in xrange(1, size):
    dist = int(round(get_distance(graph[i], graph[j])))
    matrix[i][j] = dist
    matrix[j][i] = dist

# File to write to
filename = 'input.inp'

# If 'input.inp' exists, delete it
try:
  os.remove(filename)
except OSError:
  pass

# Create a new 'input.inp' file and write out the matrix data
with open(filename, 'w+') as f:
  f.write(str(size) + '\n')
  for i in xrange(size):
    for j in xrange(size):
      f.write(str(matrix[i][j]) + ' ')
    f.write('\n')
  f.close()
