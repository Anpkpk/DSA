import math
import mmh3
from bitarray import bitarray

class BloomFilter:
    def __init__(self, n, p=0.01):
        self.size = int(-(n * math.log(p)) / (math.log(2) ** 2))
        self.hash_count = int((self.size / n) * math.log(2))
        self.bit_array = bitarray(self.size)
        self.bit_array.setall(0)

    def add(self, item):
        for i in range(self.hash_count):
            idx = mmh3.hash(item, i) % self.size
            self.bit_array[idx] = 1

    def contains(self, item):
        for i in range(self.hash_count):
            idx = mmh3.hash(item, i) % self.size
            if self.bit_array[idx] == 0:
                return False
        return True
