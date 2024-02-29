import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.scale as scale

data = pd.read_csv(r"data2.csv", sep=' ').iloc[:,:-1]
data = data.T
print(data[0].values)
plt.scatter(data[0].values, data[1].values, marker="+", label="average simple pair search")
plt.scatter(data[0].values, data[2].values/1000, marker="+", label="average optimized pair search")
plt.legend()
plt.xscale("log")
plt.yscale("log")
plt.xlabel("Array size")
plt.ylabel("Time, microseconds")
plt.show()
