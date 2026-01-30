# run program. vary numOfPages- 1-5000
import subprocess, math
import matplotlib.pyplot as plt

pages, times = [], []
pagesList = [2 ** i for i in range (0, 15)]
trials = 10000

for numOfPages in pagesList:
  result = subprocess.run(
    ["./19-2-tlb", str(numOfPages), str(trials)],
    capture_output=True, text=True
  )
  out = result.stdout.strip().split()
  pages.append(int(out[1]))
  times.append(float(out[3]))
  print(out)

plt.figure(figsize=(8, 5))
plt.plot(pages, times, marker='o', linewidth=2)
plt.xscale('log', base=2)
plt.xlabel('Number of pages')
plt.ylabel('Avg access time (ns/page)')
plt.title('TLB Size and Miss Cost')
plt.grid(True)
plt.tight_layout()
plt.savefig('tlb_plot.png', dpi=300)