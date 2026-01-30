# run program. vary numOfPages- 1-5000
import subprocess, math
import matplotlib.pyplot as plt

PAGE_SHIFT = 12

with open("rawtrace.txt") as f:
  for line in f:
    if line[0] in ("I", "L", "S"):
      token = line.split()[1]         # '0401f540,3'
      addr_hex = token.split(',')[0]  # '0401f540'
      addr = int(addr_hex, 16)
      page = addr >> PAGE_SHIFT
      print(page)