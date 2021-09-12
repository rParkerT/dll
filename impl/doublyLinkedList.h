#pragma once

#include <iostream>

namespace list {

/**
 * Implementation of the ordered Doubly Linked List class.
 *
 * Doubly Linked List is a linear collection of data elements in which every
 * element points to the next and previous element.
 *
 * @tparam V type of data stored in Doubly Linked List
 */
template <typename V> class DoublyLinkedList {
private:
  /**
   * Implementation of the Node structure.
   *
   * Each Node carries a key and a pointer to next and previous Node.
   *
   * @tparam V data type of key in Node
   */
  struct Node {
    V value;        ///< key value of Node
    Node *next;     ///< pointer to next Node in Linked List
    Node *previous; ///< pointer to previous Node in Linked List

    /**
     * Default Node constructor, with no arguments
     */
    Node() {}

    /**
     * Node constructor.
     * Each Node is constructed using key value and pointer to next and previous
     * Node.
     *
     * @tparam V data type of key in Node
     */
    explicit Node(V &&v)
        : value(std::forward<V>(v)), next(nullptr), previous(nullptr) {}
  };

  /**
   * Adds Node to Doubly Linked List
   *
   * @tparam V data type of key in Node
   *
   * @return Node with set value
   */
  Node *addNode(V &&value) { return new Node(std::forward<V>(value)); }

public:
  /**
   * Constructor of Doubly Linked List
   *
   * Constructor takes no arguments
   *
   */
  DoublyLinkedList();

  /**
   * Destructor  of Doubly Linked List
   *
   * During Doubly Linked List destruction, all elements of Doubly Linked List
   * are deleted.
   *
   */
  ~DoublyLinkedList();

  /**
   * Copy Constructor of Doubly Linked List
   *
   * Clones head node of origin
   */
  DoublyLinkedList(const DoublyLinkedList &rhs) : head(nullptr) {
    head = new Node();
    *head = *rhs.head;
  }

  /**
   * Copy Assignment of Doubly Linked List
   *
   * Uses copy and swap idiom
   */
  DoublyLinkedList &operator=(const DoublyLinkedList &rhs) {
    if (this == &rhs)
      return *this;
    delete head;
    head = new Node();
    *head = *rhs.head;
    return *this;
  }

  /**
   * Move Constructor of Doubly Linked List
   *
   * Swaps head node of origin
   */
  DoublyLinkedList(DoublyLinkedList &&rhs) noexcept : head{rhs.head} {
    rhs.head = nullptr;
  }

  /**
   * Move Assignment of Doubly Linked List
   *
   * Swaps head node of origin
   */
  DoublyLinkedList &operator=(DoublyLinkedList &&rhs) noexcept {
    if (this == &rhs)
      return *this;
    delete head;
    head = rhs.head;
    rhs.head = nullptr;
    return *this;
  }

  /**
   * Head Node's value is the smallest value of key of all Nodee in Doubly
   * Linked List.
   */
  Node *head = nullptr;

  /**
   * Insert Node to Doubly Linked List
   *
   * Nodes are inserted in order, from the lowest to the highest key value. All
   * links for Node that's to be inserted are fetched. Pointer of predecessor
   * and new Node, and new Node and next Node is connected. If the list is
   * empty, Node is inserted as head Node. If the value of new Node is smaller
   * then the value of head Node, new Node is set as head Node.
   *
   * @tparam V newValue key value of Node
   *
   */
  void insertNode(V &&newValue);

  /**
   * Removes Node to Doubly Linked List
   *
   * Pointers of Node's predecessor is fetched. Pointers of
   * predecessor and successor of removed Node are connected.
   *
   * @tparam V value key value of Node
   *
   * @return true if Node with the same key value as value is
   * deleted in Skip List, else returns false
   */
  bool eraseNode(const V &value);

  /**
   * Search Node in Doubly Linked List for given key value
   *
   * @tparam V value key value of Node
   *
   * @return true if Node with the same key value as value is
   * inserted in Doubly Linked List, else returns false
   */
  const bool searchNode(const V &value) const;

  /**
   * Implementation of the Iterator structure.
   *
   * Using implemented methods, it will be possible to iterate through Doubly
   * Linked List.
   *
   * @param node Node in Doubly Linked List
   */
  struct Iterator {
    /**
     * Bidirectional iterator, since it is possible to go to next and previous
     * node.
     */
    using iterator_category = std::bidirectional_iterator_tag;

    /**
     * Constructor of Iterator
     *
     * @param node Node in Doubly Linked List
     *
     */
    Iterator(Node *node) : node(node) {}

    /**
     * Copy Constructor of Iterator that copies node of rhs object to this node
     * object
     *
     * @param rhs Iterator object
     *
     */
    Iterator(const Iterator &rhs) : node(rhs.node) {}

    /**
     * == operator implementation
     *
     * Implementation of == operator for Iterator class object, that
     * checks if node of current Iterator object is equal to
     * rhs node object.
     *
     * @return true if nodes are equal equal between this and rhs object
     */
    bool operator==(const Iterator &it) const { return node == it.node; }

    /**
     * != operator implementation
     *
     * Implementation of != operator for Iterator class object, that
     * checks if node of current Iterator object is not equal to
     * rhs node object.
     *
     * @return true if nodes are not equal equal between this and rhs object
     */
    bool operator!=(const Iterator &it) const { return node != it.node; }

    /**
     * preincrement operator implementation
     *
     * Implementation of preincrement operator for Iterator class object (++it),
     * that returns next node for current Iterator object node. If there is no
     * next, it returns current node.
     *
     * @return next node of current node, if there is no next, it returns
     * current node
     */
    Iterator &operator++() {
      if (node && node->next) {
        node = node->next;
      }
      return *this;
    }

    /**
     * postincrement operator implementation
     *
     * Implementation of postincrement operator for Iterator class object
     * (it++), that returns next node for current Iterator object node. If there
     * is no next, it returns current node. int is dummy, since it is used only
     * to destinguish form pre- and post- increment object.
     *
     * @return next node of current node, if there is no next, it returns
     * current node
     */
    Iterator operator++(int) {
      Iterator temp(*this);
      operator++();
      return temp;
    }

    /**
     * predecrement operator implementation
     *
     * Implementation of predecrement operator for Iterator class object (--it),
     * that returns previous node for current Iterator object node. If there is
     * no previous, it returns current node.
     *
     * @return previous node of current node, if there is no previous, it
     * returns current node
     */
    Iterator &operator--() {
      if (node && node->previous) {
        node = node->previous;
      }
      return *this;
    }

    /**
     * postdecrement operator implementation
     *
     * Implementation of postdecrement operator for Iterator class object
     * (it--), that returns previous node for current Iterator object node. If
     * there is no previous, it returns current node. int is dummy, since it is
     * only use to destinguish pre- and post-decrement operator.
     *
     * @return previous node of current node, if there is no previous, it
     * returns current node
     */
    Iterator operator--(int) {
      Iterator temp(*this);
      operator--();
      return temp;
    }

    /**
     * dereference operator implementation
     *
     * Implementation of dereference operator for Iterator class object
     * that returns value of current Iterator object node.
     *
     * @return node's value of current node
     */
    V &operator*() const { return node->value; }

  private:
    Node *node;
  };

  /**
   * begin() implementation
   *
   * Implementation of begin() for Doubly Linked List class object
   * that returns head node.
   *
   * @return head node
   */
  Iterator begin() const { return Iterator(head); }
};

template <typename V> DoublyLinkedList<V>::DoublyLinkedList() {}

template <typename V> DoublyLinkedList<V>::~DoublyLinkedList() {
  DoublyLinkedList<V>::Node *current = head;
  while (current) {
    head = current->next;
    delete current;
    current = head;
  }
}

template <typename V> void DoublyLinkedList<V>::insertNode(V &&newValue) {
  DoublyLinkedList<V>::Node *newNode = addNode(std::forward<V>(newValue));
  if (!head) {
    head = newNode;
    return;
  }
  DoublyLinkedList<V>::Node *tempNode;
  tempNode = head;
  if (newNode->value < head->value) {
    head->previous = newNode;
    newNode->next = head;
    head = newNode;
    return;
  }
  if (tempNode->next != nullptr && tempNode->next->value < newValue) {
    tempNode = tempNode->next;
  }
  newNode->previous = tempNode;
  newNode->next = tempNode->next;
  if (tempNode->next != nullptr)
    tempNode->next->previous = newNode;
  tempNode->next = newNode;
}

template <typename V> bool DoublyLinkedList<V>::eraseNode(const V &newValue) {
  DoublyLinkedList<V>::Node *tempNode, *prevNode;
  tempNode = head;
  if (tempNode != nullptr && tempNode->value == newValue) {
    head = tempNode->next;
    head->next = tempNode->next->next;
    head->previous = nullptr;
    delete tempNode;
    return true;
  }

  while (tempNode != nullptr && tempNode->value != newValue) {
    prevNode = tempNode;
    tempNode = tempNode->next;
  }
  if (prevNode->next == nullptr) {
    return false;
  } else {
    prevNode->previous = tempNode->previous;
    prevNode->next = tempNode->next;
    delete tempNode;
    return true;
  }
  return false;
}

template <typename V>
const bool DoublyLinkedList<V>::searchNode(const V &value) const {
  DoublyLinkedList<V>::Node *tempNode = head;
  while (tempNode != nullptr) {
    if (tempNode->value == value) {
      return true;
    }
    tempNode = tempNode->next;
  }
  return false;
}

} // namespace list
