class Node:
  def __init__(self, data):
      self.data = data
      self.next = None

class Stack:
  def __init__(self):
      self.head = None

  def push(self, data):
    new_node = Node(data)
    new_node.next = self.head
    self.head = new_node

  def pop(self):
    data = None
    if self.isEmpty():
      print("stack is empty")
    else:
      data = self.head.data
      self.head = self.head.next
    return data
    
  def isEmpty(self):
    is_empty = False
    if self.head == None:
      is_empty = True
    return is_empty

  def top(self):
    data = None
    if self.isEmpty():
      print("stack is empty")
    else:
      data = self.head.data
    return data


if __name__ == "__main__":
  a = Stack()
  print(a.top())
  a.push(10)
  print(a.top())
  print(a.pop())
  