#include <tr1/memory>

template <typename T>
struct Node {
  T value;
  tr1::shared_ptr<Node<T> > pointer;
};

template <class T>
struct node_ptr_less {
  bool operator()(const tr1::shared_ptr<Node<T> > &node1,
		  const tr1::shared_ptr<Node<T> > &node2) const {
    return node1->value < node2->value;
  }
};

template <typename T>
vector<T> lis(const vector<T> &n) {
  typedef tr1::shared_ptr<Node<T> > NodePtr;
  vector<NodePtr> pileTops;
  for (typename vector<T>::const_iterator it = n.begin(); it != n.end(); it++) {
    NodePtr node(new Node<T>());
    node->value = *it;
    typename vector<NodePtr>::iterator j =
      lower_bound(pileTops.begin(), pileTops.end(), node, node_ptr_less<T>());
    if (j != pileTops.begin())
      node->pointer = *(j-1);
    if (j != pileTops.end())
      *j = node;
    else
      pileTops.push_back(node);
  }
  vector<T> result;
  for (NodePtr node = pileTops.back(); node != NULL; node = node->pointer)
    result.push_back(node->value);
  reverse(result.begin(), result.end());
  return result;
}
