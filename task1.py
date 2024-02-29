import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.scale as scale

data = pd.read_csv(r"data1.csv", sep=' ').iloc[:,:-1]
data = data.T
print(data[0].values)
plt.scatter(data[0].values, data[1].values/1000, marker="+", color="r", label="average case simple search")
plt.scatter(data[0].values, data[2].values/1000, marker="+", label="worst case simple search")
plt.legend()
plt.xscale("linear")
plt.yscale("linear")
plt.xlabel("Array size")
plt.ylabel("Time, microseconds")
plt.show()
plt.scatter(data[0].values, data[3].values/1e6, marker="+", color="r", label="worst case binary search")
plt.scatter(data[0].values, data[4].values/1e6, marker="+", label="average case binary search")
plt.xlabel("Array size")
plt.ylabel("Time, microseconds")
plt.xscale("log")
plt.yscale("linear")
plt.show()
