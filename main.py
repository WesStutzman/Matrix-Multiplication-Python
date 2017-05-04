#!/usr/bin/env python3

import time
import myModule
from random import randint


def get_random_array(input_x = 0, input_y = 0):
  return_list = []
  for i in range(0, input_x):
    return_list.append([])
    for m in range(0, input_y):
      return_list[i].append(randint(0, 1000))
  return return_list

def matrix_multiplication(input_list1, input_list2):
  return_list = [0] * len(input_list1)
  operations  = 0
  for i in range(0, len(input_list1)):
    return_list[i] = [0] * len(input_list2[0])
    for m in range(0, len(input_list2[0])):
      for p in range(0, len(input_list1[0])):
        return_list[i][m] += input_list1[i][p] * input_list2[p][m]
        operations += 1
  # print("Number of operations: %d" % (operations))
  return return_list

if __name__ == "__main__":
  print("Start")
  # Demo List
  demo1 = []
  demo2 = []

  """
  demo1.append([])
  demo1[0].append(1)
  demo1[0].append(2)
  demo1.append([])
  demo1[1].append(3)
  demo1[1].append(4)
  demo1.append([])
  demo1[2].append(5)
  demo1[2].append(6)
  demo1.append([])
  demo1[3].append(7)
  demo1[3].append(8)
  
  demo2.append([])
  demo2[0].append(1)
  demo2[0].append(2)
  demo2[0].append(3)
  demo2[0].append(4)
  demo2.append([])
  demo2[1].append(5)
  demo2[1].append(6)
  demo2[1].append(7)
  demo2[1].append(8)
  """

  dim = 1000
  x = dim
  y = dim
  list1 = get_random_array(x,y)
  list2 = get_random_array(x,y)
  print("Solving in py")
  start = time.time()
  # result1 = matrix_multiplication(demo1, demo2)
  result1 = matrix_multiplication(list1, list2)
  print("Solved in: %dsec" % (time.time() - start))

  print("Solving in c")
  start = time.time()
  # result2 = myModule.matrixMultiply(demo1, demo2)
  result2 = myModule.matrixMultiply(list1, list2)
  print("Solved in: %dsec" % (time.time() - start))
 

  '''
  print("Python")
  print(result1)
  print("C")
  print(result2)
  '''

  #for rows in temp:
  #  print(rows)
