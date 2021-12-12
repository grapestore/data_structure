import sys
sys.stdin = open('./inputs.text')

def gen_combinations(arr, n):
  result =[]
  if n == 0:
    return [[]]
  for i,elem in enumerate(arr):
    for C in gen_combinations(arr[i + 1:], n-1):
      result += [[elem]+C]
  return result


arr = [1,2,3,4,5]
print(gen_combinations(arr,2))
