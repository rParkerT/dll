#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "doublyLinkedList.h"
#include <catch.hpp>

TEST_CASE("Doubly Linked List Check if all inserted") {
  list::DoublyLinkedList<int> dll;
  for (int i = 0; i < 1000; ++i) {
    dll.insertNode(std::forward<int>(i));
  }

  for (int i = 0; i < 1000; ++i) {
    REQUIRE(dll.searchNode(i) == true);
  }
  dll.insertNode(1000);
  REQUIRE(dll.searchNode(1000) == true);
  dll.insertNode(2000);
  REQUIRE(dll.searchNode(2000) == true);
  REQUIRE(dll.searchNode(1) == true);
  REQUIRE(dll.eraseNode(1) == true);
  REQUIRE(dll.eraseNode(2) == true);
  REQUIRE(dll.eraseNode(2222) == false);
  REQUIRE(dll.eraseNode(-20) == false);
  REQUIRE(dll.eraseNode(333) == true);
}

TEST_CASE("Doubly Linked List Check Iterators") {
  list::DoublyLinkedList<int> dll;
  dll.insertNode(10);
  dll.insertNode(1);
  dll.insertNode(150);
  dll.insertNode(55);

  REQUIRE(dll.head->value == 1);
  REQUIRE(dll.head->next->value == 10);
  REQUIRE(dll.head->next->previous->value == 1);
  REQUIRE(dll.head->next->next->value == 55);
  REQUIRE(dll.head->next->next->previous->value == 10);
  REQUIRE(dll.head->next->next->next->value == 150);
  REQUIRE(dll.head->next->next->next->previous->value == 55);

  auto it = dll.begin();
  ++it;
  REQUIRE(*it == 10);
  it++;
  REQUIRE(*it == 55);
  it++;
  REQUIRE(*it == 150);
  it++;
  REQUIRE(*it == 150);
  it--;
  REQUIRE(*it == 55);
  --it;
  REQUIRE(*it == 10);
  --it;
  REQUIRE(*it == 1);
  --it;
  REQUIRE(*it == 1);

  REQUIRE(dll.eraseNode(1) == true);
  REQUIRE(dll.head->value == 10);

  it = dll.begin();
  ++it;
  REQUIRE(*it == 55);
  ++it;
  REQUIRE(*it == 150);
  it++;
  REQUIRE(*it == 150);
  it--;
  REQUIRE(*it == 55);
  --it;
  REQUIRE(*it == 10);

  REQUIRE(dll.eraseNode(10) == true);
  REQUIRE(dll.head->value == 55);

  it = dll.begin();
  ++it;
  REQUIRE(*it == 150);
  ++it;
  REQUIRE(*it == 150);
  --it;
  REQUIRE(*it == 55);

  REQUIRE(dll.eraseNode(55) == true);
  it = dll.begin();
  REQUIRE(dll.head->value == 150);

  ++it;
  REQUIRE(*it == 150);
  it--;
  REQUIRE(*it == 150);

  dll.insertNode(250);
  it = dll.begin();
  auto it1 = it;
  REQUIRE((it == it1) == true);

  auto it2 = ++it;
  REQUIRE((it1 != it2) == true);
}

TEST_CASE("Doubly Linked List Check Copy and Move Constructors/Assignment "
          "operators") {
  list::DoublyLinkedList<int> dll;
  dll.insertNode(1);
  REQUIRE(dll.searchNode(1) == true);

  list::DoublyLinkedList<int> dll1{dll};
  REQUIRE(dll1.head->value == 1);

  list::DoublyLinkedList<int> dll2;
  dll2 = dll1;
  REQUIRE(dll2.head->value == 1);

  list::DoublyLinkedList<int> dll3{std::move(dll2)};
  REQUIRE(dll3.head->value == 1);

  list::DoublyLinkedList<int> dll4;
  dll4 = std::move(dll3);
  REQUIRE(dll4.head->value == 1);
}

TEST_CASE("Doubly Linked List insert and search - Benchmark") {
  list::DoublyLinkedList<int> dll;
  BENCHMARK("Add 100.000 nodes in Doubly Linked List") {
    for (int j = 0; j < 100000; j++) {
      dll.insertNode(std::forward<int>(j));
    }
  };

  BENCHMARK("Search 100 nodes in Doubly Linked List of 100.000 nodes") {
    for (int j = 0; j < 10; j++) {
      dll.searchNode(j + 11);
      dll.searchNode(j + 23);
      dll.searchNode(j + 97);
      dll.searchNode(j + 123);
      dll.searchNode(j + 217);
      dll.searchNode(j + 313);
      dll.searchNode(j + 457);
      dll.searchNode(j + 1117);
      dll.searchNode(j + 38928);
      dll.searchNode(j + 78922);
    }
  };
}
