import copy
import random
import sys
import time

moves = ['R', 'U', 'F']
turns = [1, 2, 3]
	
class TwoCube():
	'''
	A 2x2x2 Rubik's Cube. AKA mini-cube. AKA 2-by-2.

	We are free to orient the cube any way we want. So we can
	leave the DBL corner where it is and solve using only {R, U, F}
	turns. You can still do {L, D, B} turns with this class, but
	L is equivalent to R, D to U, and B to F.
	
	The cube state is a list of the 7 moveable corners followed
	by their orientation.
	'''
	corners = ['UFL', 'UFR', 'UBR', 'UBL', 'DFL', 'DFR', 'DBR', 'DBL']
	
	# I developed the class with 'xyz' as the rotation representation
	# for simplicity, then mapped the 6 different orientations to 0-5
	# at the end, for efficiency.
	#
	#solvedState = ([0, 1, 2, 3, 4, 5, 6], ['xyz', 'xyz', 'xyz', 'xyz', 'xyz', 'xyz', 'xyz'])
	#
	#x_table = { 'xyz':'xzy', 'xzy':'xyz', 'yxz':'yzx', 'yzx':'yxz', 'zxy':'zyx', 'zyx':'zxy' }
	#y_table = { 'xyz':'zyx', 'xzy':'yzx', 'yxz':'zxy', 'yzx':'xzy', 'zxy':'yxz', 'zyx':'xyz' }
	#z_table = { 'xyz':'yxz', 'xzy':'zxy', 'yxz':'xyz', 'yzx':'zyx', 'zxy':'xzy', 'zyx':'yzx' }
	
	solvedState = bytearray([0, 1, 2, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0, 0])
	
	x_table = [1, 0, 3, 2, 5, 4]
	y_table = [5, 3, 4, 1, 2, 0]
	z_table = [2, 4, 0, 5, 1, 3]
	
	def __init__(self, other=None):
		'''
		Start in the solved state, or in a copy of another cube's state.
		'''
		if other == None:
			self.state = copy.copy(TwoCube.solvedState)
		else:
			self.state = copy.copy(other.state)
	
	def solved(self):
		return (self.state == TwoCube.solvedState)
	
	def state_key(self):
		return str(self.state)

	def piece_correct(self, n):
		return (self.state[n] == n and self.state[n + 7] == 0)
		
	def twist(self, face, turns):
		if face == 'U' or face == 'D':
			if turns == 1:
				self.cycle_and_rotate_y(0, 3, 2, 1)
			elif turns == 2:
				self.swap(0, 2)
				self.swap(1, 3)
			elif turns == 3:
				self.cycle_and_rotate_y(0, 1, 2, 3)
				
		elif face == 'F' or face == 'B':
			if turns == 1:
				self.cycle_and_rotate_z(0, 1, 5, 4)
			elif turns == 2:
				self.swap(0, 5)
				self.swap(1, 4)
			elif turns == 3:
				self.cycle_and_rotate_z(0, 4, 5, 1)
				
		elif face == 'L' or face == 'R':
			if turns == 1:
				self.cycle_and_rotate_x(1, 2, 6, 5)
			elif turns == 2:
				self.swap(1, 6)
				self.swap(2, 5)
			elif turns == 3:
				self.cycle_and_rotate_x(1, 5, 6, 2)

	def cycle(self, a, b, c, d):
		'''
		a -> b -> c -> d -> a
		'''
		tmp0 = self.state[d]
		tmp1 = self.state[d + 7]
		
		self.state[d] = self.state[c]
		self.state[d + 7] = self.state[c + 7]
		
		self.state[c] = self.state[b]
		self.state[c + 7] = self.state[b + 7]
		
		self.state[b] = self.state[a]
		self.state[b + 7] = self.state[a + 7]
		
		self.state[a] = tmp0
		self.state[a + 7] = tmp1
	
	def cycle_and_rotate_x(self, a, b, c, d):
		'''
		a -> b -> c -> d -> a
		'''
		self.cycle(a, b, c, d)
		self.rotate_x(a)
		self.rotate_x(b)
		self.rotate_x(c)
		self.rotate_x(d)
	
	def cycle_and_rotate_y(self, a, b, c, d):
		'''
		a -> b -> c -> d -> a
		'''
		self.cycle(a, b, c, d)
		self.rotate_y(a)
		self.rotate_y(b)
		self.rotate_y(c)
		self.rotate_y(d)
		
	def cycle_and_rotate_z(self, a, b, c, d):
		'''
		a -> b -> c -> d -> a
		'''
		self.cycle(a, b, c, d)
		self.rotate_z(a)
		self.rotate_z(b)
		self.rotate_z(c)
		self.rotate_z(d)
	
	def rotate_x(self, a):
		'''
		Rotation about the x-axis
		'''
		orient = self.state[a + 7]
		self.state[a + 7] = TwoCube.x_table[orient]

	def rotate_y(self, a):
		'''
		Rotation about the y-axis
		'''
		orient = self.state[a + 7]
		self.state[a + 7] = TwoCube.y_table[orient]
		
	def rotate_z(self, a):
		'''
		Rotation about the z-axis
		'''
		orient = self.state[a + 7]
		self.state[a + 7] = TwoCube.z_table[orient]

	def swap(self, a, b):
		tmp = self.state[a]
		self.state[a] = self.state[b]
		self.state[b] = tmp
		
		tmp = self.state[a + 7]
		self.state[a + 7] = self.state[b + 7]
		self.state[b + 7] = tmp

class Scramble():
	def __init__(self, faces=None, length=0):
		'''
		Generate a scramble of the requested length using the set of face moves provided.
		
		Do not move the same face twice in a row.
		'''
		self.moves = []
		last = ''
		while len(self.moves) < length:
			face = random.choice(faces)
			if face != last:
				self.extend(face, random.choice(turns))
				last = face

	@classmethod
	def from_string(cls, scramble_string):
		scramble = cls()
		for move in scramble_string.split():
			if len(move) < 2:
				scramble.extend(move, 1)
			else:
				if move[1] == '2':
					scramble.extend(move[0], 2)
				else:
					scramble.extend(move[0], 3)
		return scramble

	def __str__(self):
		result = []
		for s in self.moves:
			if s[1] == 1:
				result.append(s[0])
			elif s[1] == 2:
				result.append(s[0] + "2")
			elif s[1] == 3:
				result.append(s[0] + "'")
		return " ".join(result)

	def extend(self, face, turns):
		self.moves.append( (face, turns) )

	def inverse(self):
		inv = Scramble()
		for s in reversed(self.moves):
			inv.extend(s[0], 4 - s[1])
		return inv

def apply_scramble(cube, scramble):
	for s in scramble.moves:
		cube.twist(s[0], s[1])
	
def depth_first(cube, unscramble, move, turn, max_depth, cache, cache_depth):
	
	# to avoid copying cube and unscramble, we must undo any moves
	# we add before returning from this function call.
	
	solutions = 0
	
	# doing the move
	cube.twist(move, turn)
	unscramble.extend(move, turn)
	
	remaining = max_depth - len(unscramble.moves)
	
	if remaining == 0:
		if cube.solved():
			print "solution:", str(unscramble)
			solutions = 1
	elif remaining == cache_depth:
		state = cube.state_key()
		if state in cache:
			for finish in cache[state]:
				print "solution:", str(unscramble), str(finish)
				solutions += 1
	else:
		for m in moves:
			# do not turn the same face twice in a row
			if m != move:
				for t in turns:
					solutions += depth_first(cube, unscramble, m, t, max_depth, cache, cache_depth)
	
	# undoing the move
	cube.twist(move, 4 - turn)
	unscramble.moves.pop()

	return solutions
	
def descend(cube, depth, cache, cache_depth):
	unscramble = Scramble()
	solutions = 0
	
	# start with each possible move and turn combination
	for m in moves:
		for t in turns:
			solutions += depth_first(cube, unscramble, m, t, depth, cache, cache_depth)
	
	return solutions

def calc_depth_first(cache, cube, seq, move, turn, max_depth):
	
	# to avoid copying cube and seq, we must undo any moves
	# we add before returning from this function call.
	
	solutions = 0
	
	# doing the move
	cube.twist(move, turn)
	seq.extend(move, turn)
	
	remaining = max_depth - len(seq.moves)
	
	if remaining == 0:
		state = cube.state_key()
		inverse = str(seq.inverse())
		
		if state in cache:
			cache[state].append(inverse)
		else:
			cache[state] = [inverse]
	else:
		for m in moves:
			# do not turn the same face twice in a row
			if m != move:
				for t in turns:
					calc_depth_first(cache, cube, seq, m, t, max_depth)
	
	# undoing the move
	cube.twist(move, 4 - turn)
	seq.moves.pop()
	
def pre_calculate(depth):
	cache = {}
	cube = TwoCube()
	seq = Scramble()
	
	# start with each possible move and turn combination
	for m in moves:
		for t in turns:
			calc_depth_first(cache, cube, seq, m, t, depth)
	
	return cache

def find_solutions(cube):
	'''
	Find all optimal solutions to the given cube.
	
	The maximum number of moves required is known to be 11.
	'''
	solutions = 0
	n = 0
	now = time.time()
	
	cache_depth = 5
	cache = pre_calculate(cache_depth)
	print "cache at depth", cache_depth, "has", len(cache.keys()), "positions."
	
	while solutions < 1 and n < 11:
		n += 1
		print "depth", n
		solutions = descend(cube, n, cache, cache_depth)

	end = time.time()
	
	if solutions == 1:
		solstring = 'solution'
	else:
		solstring = 'solutions'

	print "found", solutions, solstring, "with", n, "turns in", (end-now), "seconds"
	return n

def test_two_cube():
	cube = TwoCube()
	# 6 cycles of R U R' U' gets us back to solved
	for s in range(6):
		cube.twist('R', 1)
		print cube.state_key(), cube.solved()
		cube.twist('U', 1)
		print cube.state_key(), cube.solved()
		cube.twist('R', 3)
		print cube.state_key(), cube.solved()
		cube.twist('U', 3)
		print cube.state_key(), cube.solved()
		
def solve_scramble(scramble_string):
	print "Python 2x2x2 cube solver."

	cube = TwoCube()

	scramble = Scramble.from_string(scramble_string)
	print "scramble:", str(scramble)

	apply_scramble(cube, scramble)

	return find_solutions(cube)

def solve_random_scramble():
	print "Python 2x2x2 cube solver."

	cube = TwoCube()

	scramble = Scramble(['R', 'U', 'F'], 20)
	print "scramble:", str(scramble)

	apply_scramble(cube, scramble)

	return find_solutions(cube)

def random_scramble_distribution():
    # see how long it takes to solve a worst-case position.
    # there are 2644 positions that require 11 moves, out of
    # a total 3674160 positions. So about a 1 in 1400 chance
    # of picking one at random.
    counts = [0 for _ in range(11)]

    while counts[3] < 1 or counts[10] < 1:
        n = solve_random_scramble()
        counts[n - 1] += 1
        print "distribution:", str(counts)
    
# main

#test_two_cube()
solve_random_scramble()
#random_scramble_distribution()

