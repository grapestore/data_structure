class Node:
  def __init__(self, data):
      self.data = data
      self.next = None

class Queue:
  def __init__(self):
      self.head = None
      self.tail = None

  def enqueue(self, data):
    new_node = Node(data)
    if self.isEmpty():
      self.tail = new_node
      self.head = new_node
    else:
      self.tail.next = new_node
      self.tail = new_node

  def dequeue(self):
    data = None
    if self.isEmpty():
      print("queue is empty")
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
      data = self.tail.data
    return data

  def search(self):
    cur = self.head
    temp = '['
    while cur != None:
      temp += str(cur.data) + ','
      cur = cur.next
    return temp[:-1]+']'

if __name__ == "__main__":
  a = Queue()
  print(a.top())
  a.enqueue(10)
  print(a.top())
  a.enqueue(20)
  print(a.top())
  a.enqueue(30)
  print(a.top())
  print(a.search())
  print(a.dequeue())
  print(a.dequeue())
  print(a.dequeue())
  print(a.dequeue())
  