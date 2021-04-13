import pandas as pd
import matplotlib.pyplot as plt

df_insertion = pd.read_csv("insertion.dat")
df_bubble = pd.read_csv("bubblesort.dat")
df_merge = pd.read_csv("mergesort.dat")

x = df_insertion["Number of Inputs"]
y = df_insertion["Time"]

plt.title("Insertion Sort")
plt.plot(x,y)
plt.ylabel("Time")
plt.xlabel("Number of words")
plt.show()

x = df_bubble["Number of Inputs"]
y = df_bubble["Time"]

plt.title("Bubblesort")
plt.plot(x,y)
plt.ylabel("Time")
plt.xlabel("Number of words")
plt.show()

x = df_merge["Number of Inputs"]
y = df_merge["Time"]

plt.title("Mergesort")
plt.plot(x,y)
plt.ylabel("Time")
plt.xlabel("Number of words")
plt.show()