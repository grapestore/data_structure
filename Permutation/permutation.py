def gen_permutations(arr, n): 
  result = []
  if n == 0:
    return [[]]
  for i, elem in enumerate(arr):
    for P in gen_permutations(arr[:i] + arr[i+1:], n-1):
      result += [[elem]+P]
  
  return result
  
arr = [0, 1, 2, 3, 4, 5]
print(gen_permutations(arr, 3))
