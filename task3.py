import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.scale as scale

data = pd.read_csv(r"data3.csv", sep=' ')
print(data["0"])
plt.scatter(data["0"].values, data["1"].values/1e6, marker="+", label="default search")
plt.scatter(data["0"].values, data["2"].values/1e6, marker="+", label="alg. A")
plt.scatter(data["0"].values, data["3"].values/1e6, marker="+", label="alg. B")
plt.scatter(data["0"].values, data["4"].values/1e6, marker="+", label="alg. C")
plt.legend()
plt.xscale("linear")
plt.yscale("linear")
plt.xlabel("Array size")
plt.ylabel("Time, microseconds")
plt.show()

