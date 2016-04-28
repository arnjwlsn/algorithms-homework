import sys
import re
from random import randint
import math

output_filename = 'input.inp'

# Distance formula
def get_distance(one, two):
  x = (float) (two[0] - one[0])**2
  y = (float) (two[1] - one[1])**2
  return math.sqrt(x + y)

if len(sys.argv) != 2:
	sys.exit('ERROR: invalid number of arguments: (1) input.txt')

input_file = open(sys.argv[1], 'r')

content = input_file.readlines()

# Get rid of header information
for i in xrange(7):
	content.pop(0)

locations = []

# Find all x and y city coordinates and add tuples into locations array
for line in content:
	group_match = re.match(r'([0-9]+) ([0-9]+\.[0-9]+) ([0-9]+\.[0-9]+)', line)

	if group_match:
		loc = (float(group_match.group(2)), float(group_match.group(3)))
		locations.append(loc)

size = len(locations)

distances = [[0 for x in range(size)] for x in range(size)]

# Generate random edges for random vertices
for i in xrange(0, size-1):
	nr = randint(0, size-1)
	for j in xrange(1, nr):
		r = randint(0, size-1)

		if r != i or distances[i][j] != 0:
			new_dist = int(round(get_distance(locations[i], locations[r])))
			distances[i][r] = new_dist
			distances[r][i] = new_dist

# Create a new 'input.inp' file and write out the matrix data
with open(output_filename, 'w+') as f:
  f.write(str(size) + '\n')
  for i in xrange(0, size-1):
    for j in xrange(0, size-1):
      f.write(str(distances[i][j]) + ' ')
    f.write('\n')
  f.close()
