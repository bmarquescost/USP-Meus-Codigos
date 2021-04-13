# Python program to plot graphs N inputs x Time of the two algoritms
# One after the other, it will be ploted Bubblesort graph, then array inverter graph.
import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("bubblesort.dat")
df1 = pd.read_csv("invert.dat")
x = df["Number of Inputs"]
y = df["Time"]

plt.title("Bubblesort - number of inputs x time")
plt.plot(x,y)
plt.ylabel("Time")
plt.xlabel("Number of inputs")
plt.show()

plt.show()

x1 = df1["Number of Inputs"]
y1 = df1["Time"]


plt.title("Invert array - number of inputs x time")

plt.plot(x1,y1)
plt.ylabel("Time")
plt.xlabel("Number of inputs")
plt.show()